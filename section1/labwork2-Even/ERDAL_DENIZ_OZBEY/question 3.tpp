#define STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP
#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  while (!source.isEmpty()) {
        stack1.push(source.pop());
        if (!source.isEmpty()) {
            stack2.push(source.pop());
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
