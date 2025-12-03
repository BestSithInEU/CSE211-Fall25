// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"
using namespace std;

// Q1: Display list in reverse (recursive helper)
template <typename T>
class node{
public:
	T data;
	node* next;
};



void displayReverseHelper(node<T>* node, bool& isFirst) {
	if (node == nullptr)
	{
		return;
	}
	displayReverseHelper(node->next);
	cout<<node->data<<" ";
	
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
	 if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        displayReverseHelper(head);
        cout << endl;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  // TODO
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
int main()
{
	LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.displayReverse();
	return 0;
}
