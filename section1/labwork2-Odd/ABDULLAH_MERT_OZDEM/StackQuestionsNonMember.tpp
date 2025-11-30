// StackQuestionsNonMember.tpp
// Contains Q3 solution

namespace StackUtils {

template <typename T>
bool isSubsequence(const Stack<T>& mainStack, const Stack<T>& potential) {
    if (potential.size() == 0)
        return true;

    Stack<T> m = mainStack;
    Stack<T> p = potential;

    std::vector<T> mv;
    std::vector<T> pv;

    while (!m.isEmpty()) {
        mv.push_back(m.top());
        m.pop();
    }

    while (!p.isEmpty()) {
        pv.push_back(p.top());
        p.pop();
    }

    int i = 0, j = 0;

    while (i < (int)mv.size() && j < (int)pv.size()) {
        if (mv[i] == pv[j])
            j++;
        i++;
    }

    return j == (int)pv.size();
}

} // namespace StackUtils
