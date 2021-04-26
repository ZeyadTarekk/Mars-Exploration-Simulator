#pragma once
#include"PriorityNode.h"
template<class itemType>
class PriorityQueue
{
	//No need for backPtr? insertion not and the end
	PriorityNode<itemType>* frontPtr; 
	//Gets the node before the passed priority
	PriorityNode<itemType>* getNodeBefore(const long long&);
public:
	// Constructors and destructors
	PriorityQueue();
	PriorityQueue(const PriorityQueue<itemType>&);
	~PriorityQueue();

	bool enqueue(const itemType&, const long long&);
	bool dequeue(itemType&);
	bool peek(itemType&);
	bool isEmpty();
};

template<class itemType>
PriorityNode<itemType>* PriorityQueue<itemType>::getNodeBefore(const long long& recivedPriority)
{
	PriorityNode<itemType>* curPtr = frontPtr;
	PriorityNode<itemType>* prevPtr = nullptr;
	while ((curPtr != nullptr) && (recivedPriority <= curPtr->getPriority()))
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
	}
	return prevPtr;
}

template<class itemType>
PriorityQueue<itemType>::PriorityQueue() :frontPtr(nullptr)
{
}

template<class itemType>
PriorityQueue<itemType>::PriorityQueue(const PriorityQueue<itemType>& recivedQueue)
{
	PriorityNode<itemType>* tempRecived = recivedQueue.frontPtr;
	if (tempRecived == nullptr)
		frontPtr = nullptr;
	else {
		frontPtr = new PriorityNode<itemType>(tempRecived->getItem(), tempRecived->getPriority());
		PriorityNode<itemType>* curPtr = frontPtr;
		tempRecived = tempRecived->getNext();
		//Same logic as that of enqueue
		while (tempRecived)
		{
			PriorityNode<itemType>* newNodePtr = new PriorityNode<itemType>(tempRecived->getItem(), tempRecived->getPriority());
			PriorityNode<itemType>* prevNode = getNodeBefore(tempRecived->getPriority());
			if (isEmpty() || (prevNode == nullptr))
			{
				newNodePtr->setNext(frontPtr);
				frontPtr = newNodePtr;
			}
			else {
				newNodePtr->setNext(prevNode->getNext());
				prevNode->setNext(newNodePtr);
			}
			tempRecived = tempRecived->getNext();
		}
	}
}

template<class itemType>
PriorityQueue<itemType>::~PriorityQueue()
{
	itemType temp;
	while (!isEmpty())
		dequeue(temp);
}

template<class itemType>
bool PriorityQueue<itemType>::enqueue(const itemType& item, const long long& recivedPriority)
{
	PriorityNode<itemType>* newNodePtr = new PriorityNode<itemType>(item, recivedPriority);
	PriorityNode<itemType>* prevNode = getNodeBefore(recivedPriority);
	if (isEmpty() || (prevNode == nullptr)) //if empty or insert at the begining
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else {
		newNodePtr->setNext(prevNode->getNext());
		prevNode->setNext(newNodePtr);
	}
	return true;
}

template<class itemType>
bool PriorityQueue<itemType>::dequeue(itemType& recivedItem)
{
	if (!isEmpty())
	{
		PriorityNode<itemType>* nodeToDeletePtr = frontPtr;
		recivedItem = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		nodeToDeletePtr->setNext(nullptr); //Not necessary
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;		   //Not necessary
		return true;
	}
	return false;
}

template<class itemType>
bool PriorityQueue<itemType>::peek(itemType& recivedItem)
{
	if (!isEmpty())
	{
		recivedItem = frontPtr->getItem();
		return true;
	}
	return false;
}

template<class itemType>
bool PriorityQueue<itemType>::isEmpty()
{
	return frontPtr == nullptr;
}
