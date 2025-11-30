"""Handler for generating human-readable plagiarism reports."""

import csv
from collections import defaultdict
from pathlib import Path
from typing import Optional

from rich.console import Console
from rich.panel import Panel
from rich.table import Table
from rich.text import Text

try:
    import plotly.graph_objects as go
    import plotly.express as px
    import networkx as nx
    import numpy as np
    PLOTLY_AVAILABLE = True
except ImportError:
    PLOTLY_AVAILABLE = False
    np = None  # Fallback

from ..ui.formatters import print_error, print_info, print_success


class ReportHandler:
    """Handler for generating plagiarism detection reports.

    Generates student-centric, human-readable reports from aggregated results.
    """

    # Detector metadata for multi-detector analysis
    DETECTOR_INFO = {
        'jplag': {
            'technique': 'TOKEN',
            'name': 'JPlag',
            'description': 'Token-based comparison',
            'catches': 'Variable renaming, statement reordering',
            'misses': 'Structural refactoring, AST changes'
        },
        'dolos': {
            'technique': 'AST',
            'name': 'Dolos',
            'description': 'Abstract Syntax Tree comparison',
            'catches': 'Structural similarity, logic copying',
            'misses': 'Surface-level changes only'
        },
        'moss': {
            'technique': 'NGRAM',
            'name': 'MOSS',
            'description': 'Fingerprint/k-gram matching',
            'catches': 'Near-exact copies, common substrings',
            'misses': 'Significant code restructuring'
        },
        'copydetect': {
            'technique': 'NGRAM',
            'name': 'CopyDetect',
            'description': 'N-gram based detection',
            'catches': 'Character sequences, local similarity',
            'misses': 'AST-level transformations'
        }
    }

    # Severity thresholds
    CRITICAL_THRESHOLD = 80.0  # Red - Very likely plagiarism
    HIGH_THRESHOLD = 60.0      # Orange - Suspicious
    MEDIUM_THRESHOLD = 40.0    # Yellow - Review recommended

    def __init__(self, verbose: bool = False):
        self.verbose = verbose
        self.console = Console()

    def generate(
        self,
        results_path: str | Path,
        output_path: Optional[str | Path] = None,
        threshold: float = 50.0,
        format: str = "console"
    ) -> None:
        """Generate plagiarism report from aggregated results.

        Args:
            results_path: Path to aggregated.csv or results directory
            output_path: Optional output file path for HTML
            threshold: Minimum similarity to include in report
            format: Output format ('console' or 'html')
        """
        results_path = Path(results_path)

        # Find aggregated.csv
        if results_path.is_dir():
            csv_path = results_path / "aggregated.csv"
            if not csv_path.exists():
                csv_path = results_path / "results" / "aggregated.csv"
        else:
            csv_path = results_path

        if not csv_path.exists():
            raise FileNotFoundError(f"Aggregated results not found: {csv_path}")

        # Load data
        pairs, detectors = self._load_results(csv_path)

        # Generate student summary
        student_stats = self._compute_student_stats(pairs)

        # Filter flagged pairs
        flagged = [p for p in pairs if p['average'] >= threshold]
        flagged.sort(key=lambda x: x['average'], reverse=True)

        if format == "html":
            self._generate_html(pairs, student_stats, flagged, detectors, output_path or "report.html", threshold)
        else:
            self._print_console_report(student_stats, flagged, detectors, threshold)

    def _load_results(self, csv_path: Path) -> tuple[list, list]:
        """Load results from aggregated CSV."""
        pairs = []
        detectors = []

        with open(csv_path, 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)

            # Get detector columns (exclude metadata columns)
            skip_cols = {'First Submission', 'Second Submission', 'Average', 'Count'}
            detectors = [col for col in reader.fieldnames if col not in skip_cols]

            for row in reader:
                pair = {
                    'student1': row['First Submission'],
                    'student2': row['Second Submission'],
                    'average': float(row['Average']),
                    'count': int(row['Count']),
                    'scores': {}
                }
                for det in detectors:
                    val = row.get(det, '-')
                    pair['scores'][det] = float(val) if val != '-' else None
                pairs.append(pair)

        return pairs, detectors

    def _compute_student_stats(self, pairs: list) -> dict:
        """Compute per-student statistics."""
        stats = defaultdict(lambda: {
            'max_score': 0.0,
            'max_partner': '',
            'avg_score': 0.0,
            'total_pairs': 0,
            'critical_count': 0,  # >= 80%
            'high_count': 0,      # >= 60%
            'scores': []
        })

        for pair in pairs:
            for student, partner in [
                (pair['student1'], pair['student2']),
                (pair['student2'], pair['student1'])
            ]:
                s = stats[student]
                s['scores'].append(pair['average'])
                s['total_pairs'] += 1

                if pair['average'] > s['max_score']:
                    s['max_score'] = pair['average']
                    s['max_partner'] = partner

                if pair['average'] >= self.CRITICAL_THRESHOLD:
                    s['critical_count'] += 1
                elif pair['average'] >= self.HIGH_THRESHOLD:
                    s['high_count'] += 1

        # Compute averages
        for student, s in stats.items():
            if s['scores']:
                s['avg_score'] = sum(s['scores']) / len(s['scores'])
            # Count is halved since each pair counted twice
            s['critical_count'] //= 2
            s['high_count'] //= 2
            s['total_pairs'] //= 2

        return dict(stats)

    def _get_severity_style(self, score: float) -> str:
        """Get Rich style based on score severity."""
        if score >= self.CRITICAL_THRESHOLD:
            return "bold red"
        elif score >= self.HIGH_THRESHOLD:
            return "bold yellow"
        elif score >= self.MEDIUM_THRESHOLD:
            return "yellow"
        return "green"

    # ========================
    # THRESHOLD SUGGESTION
    # ========================

    def _suggest_thresholds(self, pairs: list, student_stats: dict) -> dict:
        """Suggest thresholds based on statistical analysis.

        Uses a hybrid approach:
        1. Modified Z-Score (MAD) for outlier detection (Critical)
        2. Percentile-based for relative ranking (High/Medium)
        3. Detector agreement for confidence weighting
        """
        if np is None:
            # Fallback if numpy not available
            return {
                'critical': 80.0, 'high': 60.0, 'medium': 40.0,
                'confidence': 'low', 'stats': {}, 'counts': {}
            }

        scores = [s['max_score'] for s in student_stats.values()]
        n = len(scores)

        if n < 5:
            # Too few students, use defaults
            return {
                'critical': 80.0, 'high': 60.0, 'medium': 40.0,
                'confidence': 'low',
                'stats': {'n': n, 'reason': 'Too few students for statistical analysis'},
                'counts': {'critical': 0, 'high': 0, 'medium': 0}
            }

        # Robust statistics
        scores_arr = np.array(scores)
        median = float(np.median(scores_arr))
        mad = float(np.median(np.abs(scores_arr - median)))  # Median Absolute Deviation
        p75, p90, p95 = [float(x) for x in np.percentile(scores_arr, [75, 90, 95])]

        # Modified Z-score threshold for outliers (Critical)
        # k = 1.4826 is the consistency constant for normal distribution
        k = 1.4826
        if mad > 0:
            # Outliers where Modified Z-score > 2.5
            critical = median + 2.5 * k * mad
        else:
            # If MAD is 0 (all scores identical), use P95
            critical = p95

        # Percentile-based for High/Medium
        high = p90
        medium = p75

        # Ensure separation and apply minimum floors
        MIN_CRITICAL, MIN_HIGH, MIN_MEDIUM = 70.0, 50.0, 30.0
        MAX_CRITICAL = 95.0

        critical = max(MIN_CRITICAL, min(MAX_CRITICAL, critical))
        high = max(MIN_HIGH, min(critical - 10, high))
        medium = max(MIN_MEDIUM, min(high - 10, medium))

        # Ensure minimum 10% gap between thresholds
        if critical - high < 10:
            high = critical - 10
        if high - medium < 10:
            medium = high - 10

        # Round to nice values
        critical = round(critical, 0)
        high = round(high, 0)
        medium = round(medium, 0)

        # Count students in each category
        counts = {
            'critical': sum(1 for s in scores if s >= critical),
            'high': sum(1 for s in scores if high <= s < critical),
            'medium': sum(1 for s in scores if medium <= s < high),
            'low': sum(1 for s in scores if s < medium)
        }

        # Compute confidence based on detector agreement
        if pairs:
            multi_detector_pairs = sum(1 for p in pairs if p.get('count', 1) >= 2)
            agreement_ratio = multi_detector_pairs / len(pairs)
            if agreement_ratio > 0.7:
                confidence = 'high'
            elif agreement_ratio > 0.4:
                confidence = 'medium'
            else:
                confidence = 'low'
        else:
            confidence = 'low'

        return {
            'critical': critical,
            'high': high,
            'medium': medium,
            'confidence': confidence,
            'stats': {
                'n': n,
                'median': round(median, 1),
                'mad': round(mad, 1),
                'p75': round(p75, 1),
                'p90': round(p90, 1),
                'p95': round(p95, 1)
            },
            'counts': counts
        }

    def _create_suggestion_html(self, suggestions: dict) -> str:
        """Generate HTML for the threshold suggestion card."""
        stats = suggestions.get('stats', {})
        counts = suggestions.get('counts', {})
        confidence = suggestions.get('confidence', 'low')

        confidence_colors = {'high': '#2ed573', 'medium': '#ffa502', 'low': '#ff4757'}
        confidence_color = confidence_colors.get(confidence, '#888')

        html = f"""
    <div class="suggestion-card">
        <h3>📊 Suggested Thresholds</h3>
        <p class="suggestion-subtitle">Based on statistical analysis of this dataset</p>
        <div class="suggestions-grid">
            <div class="suggestion-item critical">
                <div class="suggestion-label">Critical</div>
                <div class="suggestion-value">≥ {suggestions['critical']:.0f}%</div>
                <div class="suggestion-count">{counts.get('critical', 0)} students</div>
            </div>
            <div class="suggestion-item high">
                <div class="suggestion-label">High</div>
                <div class="suggestion-value">≥ {suggestions['high']:.0f}%</div>
                <div class="suggestion-count">{counts.get('high', 0)} students</div>
            </div>
            <div class="suggestion-item medium">
                <div class="suggestion-label">Medium</div>
                <div class="suggestion-value">≥ {suggestions['medium']:.0f}%</div>
                <div class="suggestion-count">{counts.get('medium', 0)} students</div>
            </div>
        </div>
        <div class="suggestion-stats">
            <span>📈 {stats.get('n', 0)} students | Median: {stats.get('median', 0):.1f}% | MAD: {stats.get('mad', 0):.1f}</span>
            <span class="confidence-badge" style="background: {confidence_color};">
                Confidence: {confidence.upper()}
            </span>
        </div>
    </div>
"""
        return html

    # ========================
    # MULTI-DETECTOR ANALYSIS
    # ========================

    def _compute_detector_confidence(self, pair: dict, detectors: list, min_score: float = 50.0) -> dict:
        """Compute confidence based on detector agreement and technique diversity.

        Args:
            pair: The pair data with scores
            detectors: List of detector names
            min_score: Minimum score to consider a detector as "finding" plagiarism.
                       A score of 22% should NOT count as agreement - that's saying "not similar".
        """
        # Get which detectors found this pair with meaningful similarity
        # A detector only "agrees" if its score is above the minimum threshold
        found_by = []
        for d in detectors:
            d_lower = d.lower()
            score = pair['scores'].get(d)
            # Only count if score exists AND is above the meaningful threshold
            if score is not None and score >= min_score:
                found_by.append(d_lower)

        if not found_by:
            return {
                'level': 'none',
                'score': 0.0,
                'detectors_found': [],
                'techniques': [],
                'explanation': 'No detectors found significant similarity'
            }

        # Get unique techniques
        techniques = set()
        for d in found_by:
            if d in self.DETECTOR_INFO:
                techniques.add(self.DETECTOR_INFO[d]['technique'])

        # Compute confidence based on count and diversity
        detector_count = len(found_by)
        technique_count = len(techniques)

        if detector_count >= 3:
            confidence = 'very_high'
            conf_score = 0.95
        elif technique_count >= 2:
            confidence = 'high'
            conf_score = 0.85
        elif detector_count >= 2:
            confidence = 'medium'
            conf_score = 0.70
        else:
            confidence = 'low'
            conf_score = 0.50

        return {
            'level': confidence,
            'score': conf_score,
            'detectors_found': found_by,
            'techniques': list(techniques),
            'explanation': self._generate_explanation(found_by, techniques)
        }

    def _generate_explanation(self, found_by: list, techniques: set) -> str:
        """Generate human-readable explanation of detector agreement/disagreement."""
        if not found_by:
            return "No significant similarity detected"

        technique_list = list(techniques)

        # All detectors agree (4 detectors)
        if len(found_by) >= 4:
            return "All detectors agree - very strong evidence"

        # Multiple techniques agree
        if 'AST' in techniques and 'TOKEN' in techniques:
            return "Structure + tokens match - strong evidence of copying"

        if 'AST' in techniques and 'NGRAM' in techniques:
            return "Structure + characters match - likely renamed variables"

        if 'TOKEN' in techniques and 'NGRAM' in techniques:
            return "Tokens + characters match - similar surface code"

        # Single technique type
        if techniques == {'AST'}:
            return "Structural match only - code logic similar but surface differs"

        if techniques == {'TOKEN'}:
            return "Token match only - similar code surface, verify structure"

        if techniques == {'NGRAM'}:
            if len(found_by) >= 2:
                return "Multiple n-gram detectors agree - character patterns match"
            return "N-gram match only - character patterns similar, verify manually"

        # Fallback
        detector_names = [self.DETECTOR_INFO.get(d, {}).get('name', d) for d in found_by]
        return f"Detected by {', '.join(detector_names)}"

    def _get_recommended_action(self, pair: dict, confidence: dict, suggestions: dict) -> dict:
        """Determine recommended action based on score and confidence."""
        score = pair['average']
        conf_level = confidence['level']
        critical = suggestions.get('critical', 80)
        high = suggestions.get('high', 60)
        medium = suggestions.get('medium', 40)

        # Very high or high confidence + critical score → INVESTIGATE
        if conf_level in ['very_high', 'high'] and score >= critical:
            return {
                'action': 'INVESTIGATE',
                'color': '#ff4757',
                'icon': '🔴',
                'description': 'Strong evidence - requires investigation'
            }

        # Very high or high confidence + high score → REVIEW
        # (Fixed: was missing 'very_high' check)
        if conf_level in ['very_high', 'high'] and score >= high:
            return {
                'action': 'REVIEW',
                'color': '#ffa502',
                'icon': '🟠',
                'description': 'Likely plagiarism - detailed review needed'
            }

        # Very high or high confidence + medium score → CHECK
        if conf_level in ['very_high', 'high'] and score >= medium:
            return {
                'action': 'CHECK',
                'color': '#ffd43b',
                'icon': '🟡',
                'description': 'Multiple detectors agree - manual check recommended'
            }

        # Medium confidence + critical score → REVIEW
        if conf_level == 'medium' and score >= critical:
            return {
                'action': 'REVIEW',
                'color': '#ffa502',
                'icon': '🟠',
                'description': 'High score but same technique - review needed'
            }

        # Medium confidence + high score → CHECK
        if conf_level == 'medium' and score >= high:
            return {
                'action': 'CHECK',
                'color': '#ffd43b',
                'icon': '🟡',
                'description': 'Manual verification recommended'
            }

        # Low confidence (single detector) → VERIFY
        if conf_level == 'low':
            return {
                'action': 'VERIFY',
                'color': '#888888',
                'icon': '⚪',
                'description': 'Single detector - could be false positive'
            }

        # No significant confidence → MONITOR
        return {
            'action': 'MONITOR',
            'color': '#2ed573',
            'icon': '🟢',
            'description': 'Low risk - no immediate action needed'
        }

    def _create_detector_info_html(self, detectors: list) -> str:
        """Generate HTML for detector info panel."""
        cards_html = ""
        for d in detectors:
            d_lower = d.lower()
            info = self.DETECTOR_INFO.get(d_lower, {})
            if info:
                technique = info.get('technique', 'Unknown')
                technique_colors = {'TOKEN': '#00d4ff', 'AST': '#ff6b6b', 'NGRAM': '#ffd43b'}
                color = technique_colors.get(technique, '#888')
                cards_html += f"""
            <div class="detector-card">
                <div class="detector-header">
                    <strong>{info.get('name', d)}</strong>
                    <span class="technique-badge" style="background: {color};">{technique}</span>
                </div>
                <p class="detector-desc">{info.get('description', '')}</p>
                <div class="detector-details">
                    <span class="catches">✓ {info.get('catches', '')}</span>
                    <span class="misses">✗ {info.get('misses', '')}</span>
                </div>
            </div>"""

        return f"""
    <div class="detector-info-panel">
        <h3>🔍 Detection Techniques Used</h3>
        <div class="detector-grid">{cards_html}
        </div>
    </div>
"""

    def _create_action_definitions_html(self) -> str:
        """Generate HTML for action definitions panel."""
        actions = [
            {
                'icon': '🔴',
                'name': 'INVESTIGATE',
                'color': '#ff4757',
                'when': 'High confidence + Critical score (≥89%)',
                'meaning': 'Strong evidence of plagiarism. Multiple detectors using different techniques report very high similarity. Requires immediate investigation - compare the code directly.'
            },
            {
                'icon': '🟠',
                'name': 'REVIEW',
                'color': '#ffa502',
                'when': 'High confidence + High score (≥77%)',
                'meaning': 'Likely plagiarism. Multiple techniques agree on high similarity. Detailed manual review needed - examine actual code structure and logic.'
            },
            {
                'icon': '🟡',
                'name': 'CHECK',
                'color': '#ffd43b',
                'when': 'High confidence + Medium score, or Medium confidence + High score',
                'meaning': 'Possible plagiarism. Detectors agree but scores aren\'t extreme. Quick manual verification recommended.'
            },
            {
                'icon': '⚪',
                'name': 'VERIFY',
                'color': '#888888',
                'when': 'Low confidence (single detector)',
                'meaning': 'Uncertain - could be false positive. Only one detector flagged this pair. Similarity might be coincidental (common algorithms, starter code). Verify before acting.'
            },
            {
                'icon': '🟢',
                'name': 'MONITOR',
                'color': '#2ed573',
                'when': 'Score below all thresholds',
                'meaning': 'Low risk. Even if detectors agree, similarity is below concerning levels. No immediate action needed.'
            }
        ]

        cards_html = ""
        for action in actions:
            cards_html += f"""
            <div class="action-def-card">
                <div class="action-def-header">
                    <span class="action-def-badge" style="background: {action['color']};">{action['icon']} {action['name']}</span>
                </div>
                <p class="action-def-when"><strong>When:</strong> {action['when']}</p>
                <p class="action-def-meaning">{action['meaning']}</p>
            </div>"""

        return f"""
    <div class="action-definitions-panel">
        <h3>📋 Action Definitions</h3>
        <div class="action-def-grid">{cards_html}
        </div>
    </div>
"""

    # ========================
    # PLOTLY VISUALIZATIONS
    # ========================

    def _create_heatmap(self, pairs: list, student_stats: dict, suggestions: dict = None) -> str:
        """Create similarity heatmap matrix as HTML div."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Use suggested thresholds or defaults (normalized to 0-1 for colorscale)
        critical = (suggestions.get('critical', 80) / 100) if suggestions else 0.8
        high = (suggestions.get('high', 60) / 100) if suggestions else 0.6
        medium = (suggestions.get('medium', 40) / 100) if suggestions else 0.4

        # Ensure colorscale values are monotonically increasing with proper spacing
        # Apply minimum gaps to prevent overlapping color stops
        if medium >= high - 0.05:
            medium = high - 0.05
        if high >= critical - 0.05:
            high = critical - 0.05
        medium = max(0.1, medium)
        high = max(medium + 0.05, high)
        critical = max(high + 0.05, min(0.95, critical))

        # Get all students sorted by max score (high risk first)
        students = sorted(
            student_stats.keys(),
            key=lambda x: student_stats[x]['max_score'],
            reverse=True
        )

        # Build similarity matrix
        n = len(students)
        matrix = [[0.0] * n for _ in range(n)]
        student_idx = {s: i for i, s in enumerate(students)}

        for pair in pairs:
            i = student_idx.get(pair['student1'])
            j = student_idx.get(pair['student2'])
            if i is not None and j is not None:
                matrix[i][j] = pair['average']
                matrix[j][i] = pair['average']

        # Create heatmap with dynamic colorscale based on suggested thresholds
        # Ensure strictly increasing values for colorscale
        colorscale_stops = [
            [0.0, '#1a1a2e'],           # Dark blue for 0%
            [medium * 0.5, '#16213e'],  # Darker blue for low values
            [medium, '#ffd43b'],        # Yellow at medium threshold
            [high, '#ffa502'],          # Orange at high threshold
            [critical, '#ff4757'],      # Red at critical threshold
            [1.0, '#ff0000'],           # Bright red for 100%
        ]

        fig = go.Figure(data=go.Heatmap(
            z=matrix,
            x=students,
            y=students,
            colorscale=colorscale_stops,
            zmin=0, zmax=100,
            hoverongaps=False,
            hovertemplate='%{y} ↔ %{x}<br>Similarity: %{z:.1f}%<extra></extra>',
            colorbar=dict(
                title=dict(text="Similarity %", font=dict(color='#eee')),
                ticksuffix="%",
                tickfont=dict(color='#eee')
            )
        ))

        fig.update_layout(
            title=dict(text='Student Similarity Heatmap', font=dict(color='#00d4ff')),
            paper_bgcolor='#1a1a2e',
            plot_bgcolor='#1a1a2e',
            font=dict(color='#eee'),
            xaxis=dict(
                tickangle=45,
                side='bottom',
                gridcolor='#0f3460'
            ),
            yaxis=dict(
                autorange='reversed',
                gridcolor='#0f3460'
            ),
            height=max(400, n * 25),
            margin=dict(l=150, r=50, t=50, b=150)
        )

        return fig.to_html(full_html=False, include_plotlyjs=False)

    def _create_network_graph(self, pairs: list, threshold: float = 50.0, suggestions: dict = None) -> str:
        """Create network graph showing student similarity connections."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Use suggested thresholds or defaults
        critical = suggestions.get('critical', 80) if suggestions else 80
        high = suggestions.get('high', 60) if suggestions else 60

        # Filter pairs above threshold
        high_sim_pairs = [p for p in pairs if p['average'] >= threshold]

        if not high_sim_pairs:
            return "<p style='color: #888; text-align: center;'>No connections above threshold</p>"

        # Build graph
        G = nx.Graph()
        for pair in high_sim_pairs:
            G.add_edge(
                pair['student1'], pair['student2'],
                weight=pair['average']
            )

        # Layout
        pos = nx.spring_layout(G, k=2, iterations=50, seed=42)

        # Edge traces (colored by similarity using suggested thresholds)
        edge_traces = []
        for edge in G.edges(data=True):
            x0, y0 = pos[edge[0]]
            x1, y1 = pos[edge[1]]
            weight = edge[2]['weight']

            # Color based on suggested thresholds
            if weight >= critical:
                color = '#ff4757'
                width = 3
            elif weight >= high:
                color = '#ffa502'
                width = 2
            else:
                color = '#ffd43b'
                width = 1

            edge_traces.append(go.Scatter(
                x=[x0, x1, None], y=[y0, y1, None],
                mode='lines',
                line=dict(width=width, color=color),
                hoverinfo='none',
                showlegend=False
            ))

        # Node trace
        node_x = [pos[node][0] for node in G.nodes()]
        node_y = [pos[node][1] for node in G.nodes()]

        # Calculate node sizes based on number of connections
        node_sizes = [max(20, G.degree(node) * 8) for node in G.nodes()]

        # Calculate max similarity for each node
        node_colors = []
        for node in G.nodes():
            max_sim = max(
                (G[node][neighbor]['weight'] for neighbor in G.neighbors(node)),
                default=0
            )
            node_colors.append(max_sim)

        node_trace = go.Scatter(
            x=node_x, y=node_y,
            mode='markers+text',
            text=list(G.nodes()),
            textposition="top center",
            textfont=dict(size=10, color='#eee'),
            hovertemplate='%{text}<br>Max similarity: %{marker.color:.1f}%<extra></extra>',
            marker=dict(
                size=node_sizes,
                color=node_colors,
                colorscale=[
                    [0.0, '#2ed573'],
                    [0.5, '#ffd43b'],
                    [0.6, '#ffa502'],
                    [0.8, '#ff4757'],
                    [1.0, '#ff0000'],
                ],
                cmin=threshold,
                cmax=100,
                line=dict(width=2, color='#0f3460'),
                colorbar=dict(
                    title=dict(text="Max Sim %", font=dict(color='#eee')),
                    ticksuffix="%",
                    tickfont=dict(color='#eee')
                )
            )
        )

        fig = go.Figure(data=edge_traces + [node_trace])
        fig.update_layout(
            title=dict(text=f'Similarity Network (≥{threshold:.0f}%)', font=dict(color='#00d4ff')),
            showlegend=False,
            paper_bgcolor='#1a1a2e',
            plot_bgcolor='#1a1a2e',
            font=dict(color='#eee'),
            xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            height=600,
            margin=dict(l=20, r=20, t=50, b=20)
        )

        return fig.to_html(full_html=False, include_plotlyjs=False)

    def _create_bar_chart(self, student_stats: dict, suggestions: dict = None) -> str:
        """Create bar chart showing per-student risk scores."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Use suggested thresholds or defaults
        critical = suggestions.get('critical', 80) if suggestions else 80
        high = suggestions.get('high', 60) if suggestions else 60
        medium = suggestions.get('medium', 40) if suggestions else 40

        # Sort by max score
        sorted_students = sorted(
            student_stats.items(),
            key=lambda x: x[1]['max_score'],
            reverse=True
        )

        students = [s[0] for s in sorted_students]
        max_scores = [s[1]['max_score'] for s in sorted_students]
        avg_scores = [s[1]['avg_score'] for s in sorted_students]

        # Color based on suggested thresholds
        colors = []
        for score in max_scores:
            if score >= critical:
                colors.append('#ff4757')
            elif score >= high:
                colors.append('#ffa502')
            elif score >= medium:
                colors.append('#ffd43b')
            else:
                colors.append('#2ed573')

        fig = go.Figure()

        # Max score bars
        fig.add_trace(go.Bar(
            x=students,
            y=max_scores,
            name='Max Similarity',
            marker_color=colors,
            hovertemplate='%{x}<br>Max: %{y:.1f}%<extra></extra>'
        ))

        # Avg score line
        fig.add_trace(go.Scatter(
            x=students,
            y=avg_scores,
            name='Avg Similarity',
            mode='lines+markers',
            line=dict(color='#00d4ff', width=2),
            marker=dict(size=6),
            hovertemplate='%{x}<br>Avg: %{y:.1f}%<extra></extra>'
        ))

        # Threshold lines using suggested values
        fig.add_hline(y=critical, line_dash="dash", line_color="#ff4757",
                      annotation_text=f"Critical ({critical:.0f}%)", annotation_position="right")
        fig.add_hline(y=high, line_dash="dash", line_color="#ffa502",
                      annotation_text=f"High ({high:.0f}%)", annotation_position="right")

        fig.update_layout(
            title=dict(text='Student Risk Scores', font=dict(color='#00d4ff')),
            paper_bgcolor='#1a1a2e',
            plot_bgcolor='#16213e',
            font=dict(color='#eee'),
            xaxis=dict(
                tickangle=45,
                gridcolor='#0f3460',
                title='Student'
            ),
            yaxis=dict(
                gridcolor='#0f3460',
                title='Similarity %',
                range=[0, 105]
            ),
            legend=dict(
                bgcolor='#16213e',
                bordercolor='#0f3460'
            ),
            height=400,
            margin=dict(l=50, r=100, t=50, b=150)
        )

        return fig.to_html(full_html=False, include_plotlyjs=False)

    def _create_histogram(self, student_stats: dict, suggestions: dict = None) -> str:
        """Create histogram of student risk score distribution."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Use max_score per student (not pair averages)
        scores = [s['max_score'] for s in student_stats.values()]

        # Use suggested thresholds or defaults
        critical = suggestions.get('critical', 80) if suggestions else 80
        high = suggestions.get('high', 60) if suggestions else 60
        medium = suggestions.get('medium', 40) if suggestions else 40

        fig = go.Figure()

        fig.add_trace(go.Histogram(
            x=scores,
            nbinsx=10,  # Fewer bins for student count
            marker=dict(
                color='#00d4ff',
                line=dict(color='#0f3460', width=1)
            ),
            hovertemplate='Range: %{x:.0f}%<br>Students: %{y}<extra></extra>'
        ))

        # Add threshold regions using suggested values
        fig.add_vrect(x0=critical, x1=100, fillcolor="#ff4757", opacity=0.2,
                      annotation_text=f"Critical (≥{critical:.0f}%)", annotation_position="top")
        fig.add_vrect(x0=high, x1=critical, fillcolor="#ffa502", opacity=0.2,
                      annotation_text=f"High (≥{high:.0f}%)", annotation_position="top")
        fig.add_vrect(x0=medium, x1=high, fillcolor="#ffd43b", opacity=0.2,
                      annotation_text=f"Medium (≥{medium:.0f}%)", annotation_position="top")

        fig.update_layout(
            title=dict(text='Student Risk Score Distribution', font=dict(color='#00d4ff')),
            paper_bgcolor='#1a1a2e',
            plot_bgcolor='#16213e',
            font=dict(color='#eee'),
            xaxis=dict(
                title='Max Similarity %',
                gridcolor='#0f3460',
                range=[0, 100]
            ),
            yaxis=dict(
                title='Number of Students',
                gridcolor='#0f3460'
            ),
            height=350,
            margin=dict(l=50, r=50, t=50, b=50),
            bargap=0.1
        )

        return fig.to_html(full_html=False, include_plotlyjs=False)

    def _print_console_report(
        self,
        student_stats: dict,
        flagged: list,
        detectors: list,
        threshold: float
    ) -> None:
        """Print report to console using Rich."""

        # Header
        self.console.print()
        self.console.print(Panel.fit(
            "[bold blue]PLAGIARISM DETECTION REPORT[/bold blue]",
            border_style="blue"
        ))

        # Summary stats
        total_students = len(student_stats)
        critical_students = sum(1 for s in student_stats.values() if s['max_score'] >= self.CRITICAL_THRESHOLD)
        high_students = sum(1 for s in student_stats.values() if s['max_score'] >= self.HIGH_THRESHOLD)

        summary = Table(show_header=False, box=None, padding=(0, 2))
        summary.add_column()
        summary.add_column()
        summary.add_row("Total Students:", f"[bold]{total_students}[/bold]")
        summary.add_row("Flagged Pairs (≥{:.0f}%):".format(threshold), f"[bold]{len(flagged)}[/bold]")
        summary.add_row("Critical Risk (≥80%):", f"[bold red]{critical_students}[/bold red] students")
        summary.add_row("High Risk (≥60%):", f"[bold yellow]{high_students}[/bold yellow] students")
        summary.add_row("Detectors Used:", ", ".join(detectors))

        self.console.print(Panel(summary, title="Summary", border_style="cyan"))

        # Student Risk Table
        self.console.print()
        self.console.print("[bold]STUDENT RISK SUMMARY[/bold] (sorted by max similarity)")
        self.console.print()

        student_table = Table(show_header=True, header_style="bold")
        student_table.add_column("Student", style="cyan")
        student_table.add_column("Max Score", justify="right")
        student_table.add_column("Highest Match With")
        student_table.add_column("Avg Score", justify="right")
        student_table.add_column("Critical", justify="center")
        student_table.add_column("High", justify="center")

        # Sort by max score
        sorted_students = sorted(
            student_stats.items(),
            key=lambda x: x[1]['max_score'],
            reverse=True
        )

        for student, s in sorted_students:
            style = self._get_severity_style(s['max_score'])
            student_table.add_row(
                student,
                Text(f"{s['max_score']:.1f}%", style=style),
                s['max_partner'],
                f"{s['avg_score']:.1f}%",
                str(s['critical_count']) if s['critical_count'] > 0 else "-",
                str(s['high_count']) if s['high_count'] > 0 else "-"
            )

        self.console.print(student_table)

        # Flagged Pairs
        if flagged:
            self.console.print()
            self.console.print(f"[bold]FLAGGED PAIRS[/bold] (≥{threshold:.0f}% similarity)")
            self.console.print()

            pairs_table = Table(show_header=True, header_style="bold")
            pairs_table.add_column("#", justify="right", style="dim")
            pairs_table.add_column("Student 1", style="cyan")
            pairs_table.add_column("Student 2", style="cyan")
            for det in detectors:
                pairs_table.add_column(det, justify="right")
            pairs_table.add_column("Average", justify="right")
            pairs_table.add_column("Risk", justify="center")

            for i, pair in enumerate(flagged[:30], 1):  # Top 30
                style = self._get_severity_style(pair['average'])

                # Risk level
                if pair['average'] >= self.CRITICAL_THRESHOLD:
                    risk = Text("CRITICAL", style="bold red")
                elif pair['average'] >= self.HIGH_THRESHOLD:
                    risk = Text("HIGH", style="bold yellow")
                else:
                    risk = Text("MEDIUM", style="yellow")

                row = [
                    str(i),
                    pair['student1'],
                    pair['student2'],
                ]

                # Add detector scores
                for det in detectors:
                    score = pair['scores'].get(det)
                    if score is not None:
                        row.append(f"{score:.1f}%")
                    else:
                        row.append("-")

                row.append(Text(f"{pair['average']:.1f}%", style=style))
                row.append(risk)

                pairs_table.add_row(*row)

            self.console.print(pairs_table)

            if len(flagged) > 30:
                self.console.print(f"\n[dim]... and {len(flagged) - 30} more pairs[/dim]")

        # Legend
        self.console.print()
        self.console.print(Panel(
            "[red]●[/red] CRITICAL (≥80%) - Very likely plagiarism\n"
            "[yellow]●[/yellow] HIGH (≥60%) - Suspicious, review needed\n"
            "[green]●[/green] MEDIUM (<60%) - May be coincidental",
            title="Risk Levels",
            border_style="dim"
        ))

    def _generate_html(
        self,
        pairs: list,
        student_stats: dict,
        flagged: list,
        detectors: list,
        output_path: str | Path,
        threshold: float
    ) -> None:
        """Generate HTML report with interactive Plotly visualizations."""

        total_students = len(student_stats)
        critical_students = sum(1 for s in student_stats.values() if s['max_score'] >= self.CRITICAL_THRESHOLD)
        high_students = sum(1 for s in student_stats.values() if s['max_score'] >= self.HIGH_THRESHOLD)

        # Sort students by max score
        sorted_students = sorted(
            student_stats.items(),
            key=lambda x: x[1]['max_score'],
            reverse=True
        )

        # Generate threshold suggestions first (needed for charts)
        suggestions = self._suggest_thresholds(pairs, student_stats)
        suggestion_html = self._create_suggestion_html(suggestions)

        # Generate charts (all use suggested thresholds)
        heatmap_html = self._create_heatmap(pairs, student_stats, suggestions)
        network_html = self._create_network_graph(pairs, threshold, suggestions)
        bar_chart_html = self._create_bar_chart(student_stats, suggestions)
        histogram_html = self._create_histogram(student_stats, suggestions)

        # Generate detector info panel and action definitions
        detector_info_html = self._create_detector_info_html(detectors)
        action_definitions_html = self._create_action_definitions_html()

        # Plotly JS CDN
        plotly_cdn = '<script src="https://cdn.plot.ly/plotly-2.27.0.min.js"></script>' if PLOTLY_AVAILABLE else ''

        html = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Plagiarism Detection Report</title>
    {plotly_cdn}
    <style>
        * {{ box-sizing: border-box; }}
        body {{
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            margin: 0; padding: 20px; background: #1a1a2e; color: #eee;
        }}
        h1 {{ color: #00d4ff; border-bottom: 2px solid #00d4ff; padding-bottom: 10px; }}
        h2 {{ color: #ff6b6b; margin-top: 30px; }}
        .summary {{
            display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px; margin: 20px 0;
        }}
        .stat-card {{
            background: #16213e; padding: 20px; border-radius: 10px;
            border-left: 4px solid #00d4ff;
        }}
        .stat-card.critical {{ border-left-color: #ff4757; }}
        .stat-card.high {{ border-left-color: #ffa502; }}
        .stat-value {{ font-size: 2em; font-weight: bold; }}
        .stat-label {{ color: #888; font-size: 0.9em; }}
        table {{
            width: 100%; border-collapse: collapse; margin: 20px 0;
            background: #16213e; border-radius: 10px; overflow: hidden;
        }}
        th {{ background: #0f3460; color: #00d4ff; padding: 12px; text-align: left; }}
        td {{ padding: 10px 12px; border-bottom: 1px solid #0f3460; }}
        tr:hover {{ background: #1f4068; }}
        .critical {{ color: #ff4757; font-weight: bold; }}
        .high {{ color: #ffa502; font-weight: bold; }}
        .medium {{ color: #ffd43b; }}
        .low {{ color: #2ed573; }}
        .badge {{
            display: inline-block; padding: 3px 8px; border-radius: 4px;
            font-size: 0.8em; font-weight: bold;
        }}
        .badge.critical {{ background: #ff4757; color: white; }}
        .badge.high {{ background: #ffa502; color: black; }}
        .badge.medium {{ background: #ffd43b; color: black; }}
        .legend {{
            margin: 20px 0; padding: 15px; background: #16213e;
            border-radius: 10px; display: flex; gap: 20px; flex-wrap: wrap;
        }}
        .legend-item {{ display: flex; align-items: center; gap: 8px; }}
        .legend-dot {{ width: 12px; height: 12px; border-radius: 50%; }}
        .legend-dot.critical {{ background: #ff4757; }}
        .legend-dot.high {{ background: #ffa502; }}
        .legend-dot.medium {{ background: #ffd43b; }}
        .chart-container {{
            background: #16213e; border-radius: 10px; padding: 15px; margin: 20px 0;
        }}
        .chart-row {{
            display: grid; grid-template-columns: 1fr 1fr; gap: 20px; margin: 20px 0;
        }}
        @media (max-width: 1200px) {{
            .chart-row {{ grid-template-columns: 1fr; }}
        }}
        .tab-container {{
            margin: 20px 0;
        }}
        .tab-buttons {{
            display: flex; gap: 10px; margin-bottom: 15px;
        }}
        .tab-button {{
            padding: 10px 20px; background: #16213e; border: none;
            color: #888; cursor: pointer; border-radius: 5px;
            transition: all 0.3s;
        }}
        .tab-button:hover {{ background: #1f4068; color: #eee; }}
        .tab-button.active {{ background: #0f3460; color: #00d4ff; }}
        .tab-content {{ display: none; }}
        .tab-content.active {{ display: block; }}
        .suggestion-card {{
            background: linear-gradient(135deg, #16213e 0%, #1a1a2e 100%);
            border: 1px solid #0f3460; border-radius: 12px;
            padding: 20px; margin: 25px 0;
        }}
        .suggestion-card h3 {{
            color: #00d4ff; margin: 0 0 5px 0; font-size: 1.2em;
        }}
        .suggestion-subtitle {{
            color: #888; font-size: 0.85em; margin: 0 0 15px 0;
        }}
        .suggestions-grid {{
            display: grid; grid-template-columns: repeat(3, 1fr); gap: 15px;
        }}
        .suggestion-item {{
            background: #0f3460; border-radius: 8px; padding: 15px; text-align: center;
        }}
        .suggestion-item.critical {{ border-top: 3px solid #ff4757; }}
        .suggestion-item.high {{ border-top: 3px solid #ffa502; }}
        .suggestion-item.medium {{ border-top: 3px solid #ffd43b; }}
        .suggestion-label {{
            font-size: 0.8em; color: #888; text-transform: uppercase; letter-spacing: 1px;
        }}
        .suggestion-value {{
            font-size: 1.8em; font-weight: bold; margin: 5px 0;
        }}
        .suggestion-item.critical .suggestion-value {{ color: #ff4757; }}
        .suggestion-item.high .suggestion-value {{ color: #ffa502; }}
        .suggestion-item.medium .suggestion-value {{ color: #ffd43b; }}
        .suggestion-count {{
            font-size: 0.85em; color: #aaa;
        }}
        .suggestion-stats {{
            display: flex; justify-content: space-between; align-items: center;
            margin-top: 15px; padding-top: 15px; border-top: 1px solid #0f3460;
            font-size: 0.85em; color: #888;
        }}
        .confidence-badge {{
            padding: 4px 10px; border-radius: 12px; font-size: 0.75em;
            font-weight: bold; color: #1a1a2e;
        }}
        @media (max-width: 600px) {{
            .suggestions-grid {{ grid-template-columns: 1fr; }}
        }}
        /* Detector Info Panel */
        .detector-info-panel {{
            background: #16213e; border-radius: 10px; padding: 20px; margin: 20px 0;
        }}
        .detector-info-panel h3 {{
            color: #00d4ff; margin: 0 0 15px 0;
        }}
        .detector-grid {{
            display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 15px;
        }}
        .detector-card {{
            background: #0f3460; border-radius: 8px; padding: 15px;
        }}
        .detector-header {{
            display: flex; justify-content: space-between; align-items: center; margin-bottom: 8px;
        }}
        .technique-badge {{
            padding: 2px 8px; border-radius: 10px; font-size: 0.7em;
            font-weight: bold; color: #1a1a2e;
        }}
        .detector-desc {{
            color: #aaa; font-size: 0.85em; margin: 0 0 10px 0;
        }}
        .detector-details {{
            font-size: 0.8em;
        }}
        .detector-details .catches {{
            color: #2ed573; display: block; margin-bottom: 4px;
        }}
        .detector-details .misses {{
            color: #ff6b6b; display: block;
        }}
        /* Action Definitions Panel */
        .action-definitions-panel {{
            background: #16213e; border-radius: 10px; padding: 20px; margin: 20px 0;
        }}
        .action-definitions-panel h3 {{
            color: #00d4ff; margin: 0 0 15px 0;
        }}
        .action-def-grid {{
            display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 15px;
        }}
        .action-def-card {{
            background: #0f3460; border-radius: 8px; padding: 15px;
        }}
        .action-def-header {{
            margin-bottom: 10px;
        }}
        .action-def-badge {{
            padding: 5px 12px; border-radius: 6px; font-size: 0.9em;
            font-weight: bold; color: #1a1a2e; display: inline-block;
        }}
        .action-def-when {{
            color: #aaa; font-size: 0.85em; margin: 8px 0;
        }}
        .action-def-when strong {{
            color: #00d4ff;
        }}
        .action-def-meaning {{
            color: #ddd; font-size: 0.85em; margin: 0; line-height: 1.4;
        }}
        /* Table Confidence & Action Badges */
        .conf-badge {{
            padding: 3px 8px; border-radius: 4px; font-size: 0.75em;
            font-weight: bold; display: inline-block;
        }}
        .conf-badge.very_high {{ background: #2ed573; color: #1a1a2e; }}
        .conf-badge.high {{ background: #00d4ff; color: #1a1a2e; }}
        .conf-badge.medium {{ background: #ffa502; color: #1a1a2e; }}
        .conf-badge.low {{ background: #888; color: #eee; }}
        .action-badge {{
            padding: 4px 10px; border-radius: 4px; font-size: 0.8em;
            font-weight: bold; display: inline-block; color: #1a1a2e;
        }}
        .explanation-text {{
            font-size: 0.75em; color: #888; display: block; margin-top: 4px;
        }}
    </style>
</head>
<body>
    <h1>Plagiarism Detection Report</h1>

    <div class="summary">
        <div class="stat-card">
            <div class="stat-value">{total_students}</div>
            <div class="stat-label">Total Students</div>
        </div>
        <div class="stat-card">
            <div class="stat-value">{len(flagged)}</div>
            <div class="stat-label">Flagged Pairs (≥{threshold:.0f}%)</div>
        </div>
        <div class="stat-card critical">
            <div class="stat-value">{critical_students}</div>
            <div class="stat-label">Critical Risk Students</div>
        </div>
        <div class="stat-card high">
            <div class="stat-value">{high_students}</div>
            <div class="stat-label">High Risk Students</div>
        </div>
    </div>

    <div class="legend">
        <div class="legend-item"><div class="legend-dot critical"></div> Critical (≥{suggestions['critical']:.0f}%) - Very likely plagiarism</div>
        <div class="legend-item"><div class="legend-dot high"></div> High (≥{suggestions['high']:.0f}%) - Suspicious</div>
        <div class="legend-item"><div class="legend-dot medium"></div> Medium (≥{suggestions['medium']:.0f}%) - Review recommended</div>
    </div>

    {suggestion_html}

    {detector_info_html}

    {action_definitions_html}

    <!-- Visualizations Section -->
    <h2>Visual Analysis</h2>
    <div class="tab-container">
        <div class="tab-buttons">
            <button class="tab-button active" onclick="showTab('heatmap')">Heatmap</button>
            <button class="tab-button" onclick="showTab('network')">Network</button>
            <button class="tab-button" onclick="showTab('barchart')">Risk Scores</button>
            <button class="tab-button" onclick="showTab('histogram')">Distribution</button>
        </div>
        <div id="heatmap" class="tab-content active chart-container">
            {heatmap_html}
        </div>
        <div id="network" class="tab-content chart-container">
            {network_html}
        </div>
        <div id="barchart" class="tab-content chart-container">
            {bar_chart_html}
        </div>
        <div id="histogram" class="tab-content chart-container">
            {histogram_html}
        </div>
    </div>

    <script>
    function showTab(tabId) {{
        // Hide all tabs
        document.querySelectorAll('.tab-content').forEach(tab => tab.classList.remove('active'));
        document.querySelectorAll('.tab-button').forEach(btn => btn.classList.remove('active'));
        // Show selected tab
        document.getElementById(tabId).classList.add('active');
        event.target.classList.add('active');
        // Trigger Plotly resize for proper rendering
        if (window.Plotly) {{
            Plotly.Plots.resize(document.getElementById(tabId).querySelector('.plotly-graph-div'));
        }}
    }}
    </script>

    <h2>Student Risk Summary</h2>
    <table>
        <thead>
            <tr>
                <th>Student</th>
                <th>Max Score</th>
                <th>Highest Match With</th>
                <th>Avg Score</th>
                <th>Critical Flags</th>
                <th>High Flags</th>
            </tr>
        </thead>
        <tbody>
"""

        for student, s in sorted_students:
            score_class = 'critical' if s['max_score'] >= 80 else 'high' if s['max_score'] >= 60 else 'medium' if s['max_score'] >= 40 else 'low'
            html += f"""            <tr>
                <td>{student}</td>
                <td class="{score_class}">{s['max_score']:.1f}%</td>
                <td>{s['max_partner']}</td>
                <td>{s['avg_score']:.1f}%</td>
                <td>{s['critical_count'] if s['critical_count'] > 0 else '-'}</td>
                <td>{s['high_count'] if s['high_count'] > 0 else '-'}</td>
            </tr>
"""

        html += """        </tbody>
    </table>

    <h2>Flagged Pairs</h2>
    <table>
        <thead>
            <tr>
                <th>#</th>
                <th>Student 1</th>
                <th>Student 2</th>
"""

        for det in detectors:
            html += f"                <th>{det}</th>\n"

        html += """                <th>Average</th>
                <th>Confidence</th>
                <th>Action</th>
            </tr>
        </thead>
        <tbody>
"""

        for i, pair in enumerate(flagged, 1):
            # Compute confidence and action
            # Use 50% as minimum for detector agreement - anything below is "not similar"
            min_agreement_score = max(50.0, suggestions.get('medium', 50))
            confidence = self._compute_detector_confidence(pair, detectors, min_agreement_score)
            action = self._get_recommended_action(pair, confidence, suggestions)

            # Score class based on suggested thresholds
            critical = suggestions.get('critical', 80)
            high = suggestions.get('high', 60)
            medium = suggestions.get('medium', 40)
            score_class = 'critical' if pair['average'] >= critical else 'high' if pair['average'] >= high else 'medium' if pair['average'] >= medium else 'low'

            html += f"""            <tr>
                <td>{i}</td>
                <td>{pair['student1']}</td>
                <td>{pair['student2']}</td>
"""
            for det in detectors:
                score = pair['scores'].get(det)
                if score is not None:
                    html += f"                <td>{score:.1f}%</td>\n"
                else:
                    html += "                <td>-</td>\n"

            html += f"""                <td class="{score_class}">{pair['average']:.1f}%</td>
                <td>
                    <span class="conf-badge {confidence['level']}">{confidence['level'].upper().replace('_', ' ')}</span>
                    <span class="explanation-text">{confidence['explanation']}</span>
                </td>
                <td>
                    <span class="action-badge" style="background: {action['color']};">{action['icon']} {action['action']}</span>
                </td>
            </tr>
"""

        html += """        </tbody>
    </table>
</body>
</html>
"""

        output_path = Path(output_path)
        output_path.write_text(html, encoding='utf-8')
        print_success(f"HTML report saved to: {output_path}")
