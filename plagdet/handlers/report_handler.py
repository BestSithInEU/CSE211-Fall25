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
    PLOTLY_AVAILABLE = True
except ImportError:
    PLOTLY_AVAILABLE = False

from ..ui.formatters import print_error, print_info, print_success


class ReportHandler:
    """Handler for generating plagiarism detection reports.

    Generates student-centric, human-readable reports from aggregated results.
    """

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
    # PLOTLY VISUALIZATIONS
    # ========================

    def _create_heatmap(self, pairs: list, student_stats: dict) -> str:
        """Create similarity heatmap matrix as HTML div."""
        if not PLOTLY_AVAILABLE:
            return ""

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

        # Create heatmap
        fig = go.Figure(data=go.Heatmap(
            z=matrix,
            x=students,
            y=students,
            colorscale=[
                [0.0, '#1a1a2e'],      # Dark blue for 0%
                [0.4, '#16213e'],      # Darker blue for <40%
                [0.5, '#ffd43b'],      # Yellow for 50%
                [0.6, '#ffa502'],      # Orange for 60%
                [0.8, '#ff4757'],      # Red for 80%
                [1.0, '#ff0000'],      # Bright red for 100%
            ],
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

    def _create_network_graph(self, pairs: list, threshold: float = 50.0) -> str:
        """Create network graph showing student similarity connections."""
        if not PLOTLY_AVAILABLE:
            return ""

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

        # Edge traces (colored by similarity)
        edge_traces = []
        for edge in G.edges(data=True):
            x0, y0 = pos[edge[0]]
            x1, y1 = pos[edge[1]]
            weight = edge[2]['weight']

            # Color based on severity
            if weight >= self.CRITICAL_THRESHOLD:
                color = '#ff4757'
                width = 3
            elif weight >= self.HIGH_THRESHOLD:
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

    def _create_bar_chart(self, student_stats: dict) -> str:
        """Create bar chart showing per-student risk scores."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Sort by max score
        sorted_students = sorted(
            student_stats.items(),
            key=lambda x: x[1]['max_score'],
            reverse=True
        )

        students = [s[0] for s in sorted_students]
        max_scores = [s[1]['max_score'] for s in sorted_students]
        avg_scores = [s[1]['avg_score'] for s in sorted_students]

        # Color based on risk level
        colors = []
        for score in max_scores:
            if score >= self.CRITICAL_THRESHOLD:
                colors.append('#ff4757')
            elif score >= self.HIGH_THRESHOLD:
                colors.append('#ffa502')
            elif score >= self.MEDIUM_THRESHOLD:
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

        # Threshold lines
        fig.add_hline(y=80, line_dash="dash", line_color="#ff4757",
                      annotation_text="Critical (80%)", annotation_position="right")
        fig.add_hline(y=60, line_dash="dash", line_color="#ffa502",
                      annotation_text="High (60%)", annotation_position="right")

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

    def _create_histogram(self, student_stats: dict) -> str:
        """Create histogram of student risk score distribution."""
        if not PLOTLY_AVAILABLE:
            return ""

        # Use max_score per student (not pair averages)
        scores = [s['max_score'] for s in student_stats.values()]

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

        # Add threshold regions
        fig.add_vrect(x0=80, x1=100, fillcolor="#ff4757", opacity=0.2,
                      annotation_text="Critical", annotation_position="top")
        fig.add_vrect(x0=60, x1=80, fillcolor="#ffa502", opacity=0.2,
                      annotation_text="High", annotation_position="top")
        fig.add_vrect(x0=40, x1=60, fillcolor="#ffd43b", opacity=0.2,
                      annotation_text="Medium", annotation_position="top")

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

        # Generate charts
        heatmap_html = self._create_heatmap(pairs, student_stats)
        network_html = self._create_network_graph(pairs, threshold)
        bar_chart_html = self._create_bar_chart(student_stats)
        histogram_html = self._create_histogram(student_stats)

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
        <div class="legend-item"><div class="legend-dot critical"></div> Critical (≥80%) - Very likely plagiarism</div>
        <div class="legend-item"><div class="legend-dot high"></div> High (≥60%) - Suspicious</div>
        <div class="legend-item"><div class="legend-dot medium"></div> Medium (≥40%) - Review recommended</div>
    </div>

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
                <th>Risk</th>
            </tr>
        </thead>
        <tbody>
"""

        for i, pair in enumerate(flagged, 1):
            score_class = 'critical' if pair['average'] >= 80 else 'high' if pair['average'] >= 60 else 'medium'
            badge_class = score_class
            badge_text = 'CRITICAL' if pair['average'] >= 80 else 'HIGH' if pair['average'] >= 60 else 'MEDIUM'

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
                <td><span class="badge {badge_class}">{badge_text}</span></td>
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
