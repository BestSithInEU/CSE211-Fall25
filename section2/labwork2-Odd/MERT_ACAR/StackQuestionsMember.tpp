#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"
#include / StackQuestionMember.tpp
src/ StackQuestionNonMember.cpp


// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const
{
    if (items.empty())
        return true;

    int left = 0;
    int right = item.size() -1;

    while (left < right)
    {
        if(items[left] != items[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates()
{
  int left = 0;
  int control = item.size() + 1 - item.size();

  while(left!=control){            // 5, 1, 4, 2, 3, 2, 1
      control++;
      if(control==item.size)
      {
          control = 0;
          left++;
      }


      if(left!=control)
      {
          remove(control);
          left++;
      }

  }



}

#endif // STACK_QUESTIONS_MEMBER_TPP
