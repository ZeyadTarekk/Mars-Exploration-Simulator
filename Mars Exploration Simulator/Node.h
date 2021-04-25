#pragma once
template<typename T>
class Node
{
protected:
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;
	// pointer to next node
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(const T &newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;
	}
	Node(const T &newItem, Node<T>*nextNode ) //non-default constructor
	{
		item = newItem;
		next = nextNode;
	}

	void setItem(const T &newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}

}; 