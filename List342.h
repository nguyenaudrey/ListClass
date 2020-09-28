/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #3: List342
* Description: This is the h file for the List342 class
*/

#ifndef LIST342_H
#define LIST342_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class ItemType>
class List342
{
public:
	// Default constructor
	List342();

	// Copy constructor
	List342(const List342 &list);

	// Deconstructor
	~List342();

	// Builds a list using the contents of a file
	bool BuildList(string fileName);

	// Inserts a user specified object
	bool Insert(ItemType* obj);

	// Removes a user specified object
	bool Remove(ItemType target, ItemType& result);
	
	// Checks if a specific item is there
	bool Peek(ItemType target, ItemType& result) const;

	// Checks if the list is empty
	bool isEmpty() const;
	
	// Removes all content from the list
	void DeleteList();

	// Merges two lists together
	bool Merge(List342<ItemType>& list1);

	// Adds lists together to make a new list
	List342 operator+(const List342& list) const;

	// Adds list to this list
	List342& operator+=(const List342& list);

	// My Weird Function
	bool MyFunc(List342<ItemType>& list1);

	// Prints out the list
	friend ostream& operator<<(ostream& outStream, const List342& list)
	{
		List342::Node* current = list.head;
		while (current != NULL)
		{
			outStream << *(current->data);
			current = current->next;
		}
		return outStream;
	}

	// Checks for equality
	bool operator==(const List342& list) const;

	// Checks for inequality
	bool operator!=(const List342& list) const;

	// Assignment overload operator
	List342& operator = (const List342&);

private: 
	struct Node
	{
		ItemType* data = nullptr;
		Node* next = nullptr;
	};

	Node* head; 
};

/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #3: List342
* Description: This is the cpp file for the List342 class
*/

// Default constructor
template <class ItemType>
List342<ItemType>::List342()
{
	head = NULL;
}
//Copy constructor
template <class ItemType>
List342<ItemType>::List342(const List342 &list)
{
	// If right hand side is null return
	if (list.head == NULL)
	{
		head = NULL;
		return;
	}
	else
	{
		// Setting the head
		Node* position = new Node;
		ItemType* newHead = new ItemType(*(list.head->data));
		position->data = newHead;
		position->next = NULL;
		head = position;
		Node* current = list.head->next;

		// Adding deep copy of the rest of the items
		while (current != NULL)
		{
			Node* newNode = new Node;
			ItemType* newItem = new ItemType(*(current->data));
			newNode->data = newItem;
			newNode->next = current->next;
			position->next = newNode;
			position = position->next;
			current = current->next;
		}
	}
}
// Default deconstructor
template <class ItemType>
List342<ItemType>::~List342()
{
	DeleteList();
}

// Builds a list using the contents of a file
template <class ItemType>
bool List342<ItemType>::BuildList(string fileName)
{
	ifstream file;
	file.open(fileName);
	ItemType nextItem;

	// Checks if file has been opened. If so, reads items and adds to list
	if (file.is_open())
	{
		// Reads in contents of file
		while (!file.fail() && !file.eof())
		{
			ItemType item;
			file >> item;
			Insert(&item);
		}
		file.close();
		return true;
	}

	// Terminates program and throws an error if file not found
	else
	{
		cerr << "Could not find file: " << fileName << endl;
		return false;
	}

}

// Inserts a user specified object
template <class ItemType>
bool List342<ItemType>::Insert(ItemType* obj)
{
	// Checks if it is an empty list
	// If so, assigns the head the user specified object
	if (head == NULL)
	{
		Node* newHead = new Node;
		ItemType* newItem = new ItemType(*obj);
		newHead->data = newItem;
		newHead->next = NULL;
		head = newHead;
		return true;
	}
	// Else, check if the new object's data is identical to head's data
	// If so return false
	else if (*obj == *(head->data))
	{
		return false;
	}

	// Else, check if the new object's data is less than head's data
	// Assign it as the new head and make it point to head
	else if (*obj < *(head->data))
	{
		Node* newNode = new Node;
		ItemType* newItem = new ItemType(*obj);
		newNode->data = newItem;
		newNode->next = head;
		head = newNode;
		return true;
	}

	// Else, it is adding to a populated list 
	Node* current = head;
	while ((current->next != NULL) && (*(current->next->data) <= *obj))
	{
		// Checks if there is a duplicate in the next object. If so, return false.
		if (*(current->next->data) == *obj)
		{
			return false;
		}
		current = current->next;
	}
	// Adds the node to the list
	Node* newNode = new Node;
	ItemType* newItem = new ItemType(*obj);
	newNode->data = newItem;
	newNode->next = current->next;
	current->next = newNode;
	return true;
}

// Removes a user specified object
template <class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType& result)
{

	// Checks if head is null. If so, returnns false.
	if (head == NULL)
	{
		return false;
	}

	// Checks if head's data is the same as the target
	// Removes the target and returns it in result
	if (*(head->data) == target)
	{
		Node* temp;
		temp = head;
		result = *(head->data);
		head = head->next;
		delete temp->data;
		delete temp;
		return true;
	}

	// Otherwise search the list for the value
	// If it is found, remove it and returns true
	// If found, also returns the item in the ItemType result
	Node* current;
	Node* temp;
	current = head;
	while (current->next != NULL)
	{
		if (*(current->next->data) == target)
		{
			temp = current->next;
			result = *(current->next->data);
			current->next = current->next->next;
			delete temp->data;
			delete temp;
			return true;
		}
		current = current->next;
	}
	return false;

}

// Checks if a specific item is there
// Returns true if found
// If found, also returns the item in the ItemType result
template <class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType& result) const
{
	// Checks if head is null. If so, returnns false.
	if (head == NULL)
	{
		return false;
	}

	// Checks if head's data is the same as the target
	// Removes the target and returns it in result
	if (*(head->data) == target)
	{
		result = *(head->data);
		return true;
	}

	// Otherwise search the list for the value
	// If it is found, remove it and return it in a result
	Node* current;
	current = head;
	while (current->next != NULL)
	{
		if (*(current->next->data) == target)
		{
			result = *(current->next->data);
			return true;
		}
		current = current->next;
	}
	return false;
}

// Checks if the list is empty
template <class ItemType>
bool List342<ItemType>::isEmpty() const
{
	// If the head is null, return true because it must be empty
	if (head == NULL)
	{
		return true;
	}

	// Otherwise return false
	return false;
}

// Removes all content from the list
template <class ItemType>
void List342<ItemType>::DeleteList()
{
	if (head == NULL)
	{
		return;
	}
	Node* current = head;
	while (current != NULL)
	{
		Node* temp = current;
		current = current->next;
		delete temp->data;
		delete temp;
	}
	head = NULL;
}

// Merges two lists together
template <class ItemType>
bool List342<ItemType>::Merge(List342& list1)
{
	// If the lists are equal, there is nothing to merge
	if (*this==list1)
	{
		return true;
	}
	Node* leftCurrent = head;
	Node* rightCurrent = list1.head;
	Node dummy;
	Node* tail = &dummy;

	// If the other list is empty there is nothing to merge
	if (rightCurrent == NULL)
	{
		return true;
	}

	// If our list is empty, we assign it all of the other list's nodes
	if (leftCurrent == NULL)
	{
		head = rightCurrent;
		list1.head = NULL;
		return true;
	}

	while ((leftCurrent != NULL) || (rightCurrent != NULL))
	{
		// Checks if left is null
		if (leftCurrent == NULL)
		{
			tail->next = rightCurrent;
			break;
		}

		// Checks if right is null
		if (rightCurrent == NULL)
		{
			tail->next = leftCurrent;
			break;
		}

		// Checks if left data is greater than right data
		if (*(leftCurrent->data) > *(rightCurrent)->data)
		{
			tail->next = rightCurrent;
			rightCurrent = rightCurrent->next;
		}

		// Otherwise right data is greater or equal to left data
		else
		{
			// Removes right data if it is equal to left
			if (*(leftCurrent->data) == *(rightCurrent)->data)
			{
				Node* temp = rightCurrent;
				rightCurrent = rightCurrent->next;
				delete temp->data;
				delete temp;
			}
			tail->next = leftCurrent;
			leftCurrent = leftCurrent->next;
		}
		tail = tail->next;
	}
	head = dummy.next;
	list1.head = NULL;
	return true;
}

// Overloads the + operator
template <class ItemType>
List342<ItemType> List342<ItemType>::operator+(const List342& list) const
{
	List342<ItemType> copy = *this;
	List342<ItemType> result = list;
	result.Merge(copy);
	return List342<ItemType>(result);
}

// Overloads the += operator
template <class ItemType>
List342<ItemType>& List342<ItemType>::operator+=(const List342& list)
{
	// If both left and right sides are equal there is nothing to add
	if (*this == list)
	{
		return *this;
	}

	// If the right hand list is empty there is nothing to add
	if (list.head == NULL)
	{
		return *this;
	}

	// Creates a copy of list and merges it
	List342 newList = list;
	Merge(newList);

	// Attempted implementation 
	/*
	Node* leftCurrent = head;
	Node* rightCurrent = list.head;
	while (rightCurrent != NULL)
	{
		
		// Checks if right data is equal to left data
		if (*(leftCurrent->data) == *(rightCurrent->data))
		{
			rightCurrent = rightCurrent->next;
		}
		// Checks if right data is less than left data
		if (*(leftCurrent->data) > *(rightCurrent->data))
		{
			Node* newNode = new Node;
			ItemType* newItem = new ItemType(*(rightCurrent->data));
			newNode->data = newItem;

			// Checks if adding to head
			if (*(leftCurrent->data) == *(head->data))
			{
				newNode->next = head;
				head = newNode;
			}
			// Otherwise it is adding to other places in the list
			else
			{
				newNode->next = leftCurrent;
				leftCurrent->next = newNode;
				leftCurrent = leftCurrent->next;
			}
		}

		if (*(leftCurrent->data) < *(rightCurrent->data))
		{
			Node* newNode = new Node;
			Node* temp = leftCurrent->next;
			ItemType* newItem = new ItemType(*(rightCurrent->data));
			newNode->data = newItem;
			newNode->next = temp;
			leftCurrent->next = newNode;
			leftCurrent = leftCurrent->next;
		}

		rightCurrent = rightCurrent->next;
	}
	*/

	return *this;
}
// Prints out the list. Commented out because the code is already implemented in the h file
/*
template <class ItemType>
ostream& operator<<(ostream& outStream, const List342<ItemType>& list)
{
	List342::Node* current = list.head;
	while (current != NULL)
	{
		outStream << current->data;
		current = current->next;
	}
	return outStream;
}
*/

// Overloads the == operator
template <class ItemType>
bool List342<ItemType>::operator==(const List342& list) const
{
	Node* leftCurrent = head;
	Node* rightCurrent = list.head;
	// Iterates through list until both the left hand and right hand sides are null
	while ((leftCurrent != NULL) && (rightCurrent != NULL))
	{
		// Checks if the data is equal. If not, return false
		if (*(leftCurrent->data) != *(rightCurrent->data))
		{
			return false;
		}
		leftCurrent = leftCurrent->next;
		rightCurrent = rightCurrent->next;
	}

	// Lists should both be null if they are equal
	return (leftCurrent == NULL) && (rightCurrent == NULL);
}

// Overloads the != operator
template <class ItemType>
bool List342<ItemType>::operator!=(const List342& list) const
{
	if (*this == list)
	{
		return false;
	}
	return true;
}

// Overloads assignment operator
template <class ItemType>
List342<ItemType>& List342<ItemType>::operator = (const List342& other)
{
	// If both sides are equal, return. 
	if (this == &other)
	{
		return *this;
	}

	// If right hand side is null return
	if (other.head == NULL)
	{
		return *this;
	}

	// Empty left hand side
	DeleteList();

	// Setting the head
	Node* position = new Node;
	ItemType* newHead = new ItemType(*(other.head->data));
	position->data = newHead;
	position->next = NULL;
	head = position;
	Node* current = other.head->next;

	// Adding deep copy of the rest of the items
	while (current != NULL)
	{
		Node* newNode = new Node;
		ItemType* newItem = new ItemType(*(current->data));
		newNode->data = newItem;
		newNode->next = current->next;
		position->next = newNode;
		position = position->next;
		current = current->next;
	}

	// Returns the list
	return *this;
}

template <class ItemType>
bool List342<ItemType>::MyFunc(List342<ItemType>& list1)
{
	Node* temp = list1.head;
	Insert(temp->data);
	return true;
}

#endif 

