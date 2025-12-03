// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"
#include <string>

// Q1: Display list in reverse (recursive helper)
template <typename T>
std::string displayReverseHelper(Node<T>* node) 
{
    if (node == nullptr)
        return "";

    std::string remaining = displayReverseHelper(node->next);

    if (remaining.empty())
    {
	    std::string return_string = std::to_string(node->data);
        return return_string;
    }
    else
    {
    	std::string return_string = std::to_string(node->data);
        return remaining + " <== " + return_string;
	}
}

template <typename T>
void displayReverse(const LinkedList<T>& list)
{
	if (list.size() == 0)
	{
		cout << "There aren't any elements in this list." << endl;
		return;
	}
	
	Node<T> *firstPtr = list.head;
	cout << displayReverseHelper(firstPtr) << endl;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list)
{
	if (list.size() == 0 || list.size() == 1)
		return;
	
	Node<T> *pairFirstPtr = list.head;
	Node<T> *pairSecondPtr = pairFirstPtr->next;
	T temporaryFirstPtr;
	T temporarySecondPtr;
	
	while(pairFirstPtr != nullptr && pairSecondPtr != nullptr)
	{
        temporaryFirstPtr = pairFirstPtr->data;
        temporarySecondPtr = pairSecondPtr->data;

        pairFirstPtr->data = temporarySecondPtr;
        pairSecondPtr->data = temporaryFirstPtr;
		
        pairFirstPtr = pairSecondPtr->next;
        if (pairFirstPtr != nullptr)
            pairSecondPtr = pairFirstPtr->next;
        else
            break;
	}
	return;	
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k)
{
	if (list.size() == 0 || list.size() == 1 || k == 0)
		return;	

    size_t size = 1;
    Node<T>* tailPointer = list.head;
    
    while (tailPointer->next != nullptr)
	{
        tailPointer = tailPointer->next;
        size++;
    }

	if (k >= size)
	{
		k = k % size;
		if (k == 0)
			return;
	}

    Node<T>* fastPointer = list.head;
    Node<T>* slowPointer = list.head;
    
    for (size_t i = 0; i < k; ++i)
    {
    	fastPointer = fastPointer->next;
	}

    while (fastPointer->next != nullptr)
	{
		fastPointer = fastPointer->next;
        slowPointer = slowPointer->next;
    }

    Node<T>* newHead = slowPointer->next;
    slowPointer->next = nullptr;
    fastPointer->next = list.head;
    list.head = newHead; 	
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1, const LinkedList<T>& list2)
{
	if (list1.size() == 0 && list2.size() == 0)
	{
		LinkedList<T> emptyOutputList;
		return emptyOutputList;
	}
	
	Node<T> *firstPointer = list1.head;
	Node<T> *secondPointer = list2.head;
	
	LinkedList<T> mergedOutputList;
	
	while (firstPointer != nullptr && secondPointer != nullptr)
	{
    	mergedOutputList.push_back(firstPointer->data);
    	mergedOutputList.push_back(secondPointer->data);
    	
    	firstPointer = firstPointer->next;
    	secondPointer = secondPointer->next;
	}
	
	while (secondPointer != nullptr)
	{
    	mergedOutputList.push_back(secondPointer->data);
    	secondPointer = secondPointer->next;
	}

	while (firstPointer != nullptr)
	{
    	mergedOutputList.push_back(firstPointer->data);
    	firstPointer = firstPointer->next;
	}
	
	return mergedOutputList;
}
// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
