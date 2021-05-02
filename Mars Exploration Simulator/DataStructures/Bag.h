#pragma once
#include "Node.h"
template <class itemType>
class Bag
{

private:
	Node<itemType>* headPtr;
	int itemCount;
	Node<itemType>* getPointerTo(const itemType& target) const;
public:
	Bag();
	Bag(const Bag<itemType>& aBag);
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const itemType& newEntry);
	bool remove(const itemType& anEntry);
	void clear();
	bool contains(const itemType& anEntry) const;
	int getFrequencyOf(const itemType& anEntry) const;
	~Bag();

};


template < class itemType>
Bag<itemType>::Bag() : headPtr(nullptr), itemCount(0)
{
}

template < class itemType>
Bag<itemType>::Bag(const Bag<itemType>& aBag)
{
	Node<itemType>* ptrBagToCopy = aBag.headPtr;
	if (ptrBagToCopy == nullptr)
		headPtr = nullptr;
	else
	{
		Node<itemType>* newNode = new Node<itemType>(ptrBagToCopy->getItem());
		headPtr = newNode;
		itemCount++;
		ptrBagToCopy = ptrBagToCopy->getNext();
		while (ptrBagToCopy)
		{
			//newNode = new Node<itemType>(ptrBagToCopy->getItem());
			add(ptrBagToCopy->getItem());
			ptrBagToCopy = ptrBagToCopy->getNext();
		}
	}
}

template<class itemType>
Node<itemType>* Bag<itemType>::getPointerTo(const itemType& target) const
{
	Node<itemType>* tempPtr = headPtr;
	while (tempPtr)
	{
		if (tempPtr->getItem() == target)
			return tempPtr;
		tempPtr = tempPtr->getNext();
	}
	return nullptr;
}


template<class itemType>
int Bag<itemType>::getCurrentSize() const
{
	return itemCount;
}

template<class itemType>
bool Bag<itemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class itemType>
bool Bag<itemType>::add(const itemType& newEntry)
{
	Node<itemType>* newNode = new Node<itemType>(newEntry);
	newNode->setNext(headPtr);
	headPtr = newNode;
	itemCount++;
	return true;
}

template<class itemType>
bool Bag<itemType>::remove(const itemType& anEntry)
{
	Node<itemType>* tempPtr = getPointerTo(anEntry);
	if (tempPtr != nullptr)
	{
		tempPtr->setItem(headPtr->getItem());
		Node<itemType>* delPtr = headPtr;
		headPtr = headPtr->getNext();
		delete delPtr;
		itemCount--;
		return true;
	}
	return false;

}

template<class itemType>
void Bag<itemType>::clear()
{
	Node<itemType>* delPtr;
	while (headPtr)
	{
		delPtr = headPtr;
		headPtr = headPtr->getNext();
		delete delPtr;
		itemCount--;
	}
}

template<class itemType>
bool Bag<itemType>::contains(const itemType& anEntry) const
{
	if (getFrequencyOf(anEntry) == 0)
		return false;
	return true;
}

template<class itemType>
int Bag<itemType>::getFrequencyOf(const itemType& anEntry) const
{
	int freq = 0;
	Node<itemType>* tempPtr = headPtr;
	while (tempPtr)
	{
		if (tempPtr->getItem() == anEntry)
			freq++;
		tempPtr = tempPtr->getNext();
	}
	return freq;
}

template<class itemType>
Bag<itemType>::~Bag()
{
	clear();
}
