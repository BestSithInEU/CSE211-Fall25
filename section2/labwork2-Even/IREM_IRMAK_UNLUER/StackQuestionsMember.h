#ifndef STACK_QUESTIONS_MEMBER_H
#define STACK_QUESTIONS_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T> class Stack; // Forward declaration

// Extend Stack with additional member functions
template <typename T> class StackQuestions : public Stack<T> {
public:
  using Stack<T>::Stack; // Inherit constructors

  // ============================================================================
  // Question 1: Longest Consecutive Subsequence
  // ============================================================================
  /**
   * @brief Find the length of the longest consecutive increasing sequence
   * @return Length of longest consecutive sequence
   *
   * Time: O(n), Space: O(n)
   * Approach: Traverse stack tracking consecutive increases
   */
  size_t longestConsecutiveSequence() const{
  if (this->empty()) return 0;

    Stack<T> temp(*this);
    size_t longest = 1;
    size_t current = 1;
	T prev = temp.top();
    temp.pop();

    while (!temp.empty()) {
        T cur = temp.top();
        temp.pop();

        if (cur == prev + 1){
            current++;
		}
        else{
            current = 1;
        }

        if (current > longest){
        	longest = current;
		}

        prev = cur;
    }

    return longest;
  }

  // ============================================================================
  // Question 2: Rotate Stack
  // ============================================================================
  /**
   * @brief Rotate the stack k positions
   * @param k Number of positions to rotate (positive = right, negative = left)
   *
   * Time: O(n), Space: O(n)
   * Approach: Split and recombine using temporary stacks
   *
   * Example: [1,2,3,4,5] (top=1) rotateStack(2) -> [4,5,1,2,3] (top=4)
   */
  void rotateStack(int k){
  	
  }
};

// Include template implementation
#include "StackQuestionsMember.tpp"

#endif // STACK_QUESTIONS_MEMBER_H
