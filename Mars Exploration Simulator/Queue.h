#pragma once
#include"DataStructures/Node.h"


template<class dataType>
class Queue
{

private:
	Node<dataType>* top;
	Node<dataType>* rear;

public:

	Queue();

	Queue(const Queue<dataType>&);

	bool enqueue(const dataType&);

	bool dequeue(dataType&);

	bool peek(dataType&);

	bool isEmpty();

	~Queue();
};
//default constructor
template<class datatype>
Queue<datatype>::Queue() :top(nullptr), rear(nullptr) {}



//copy constructor
template<class dataType>
Queue<dataType>::Queue(const Queue& q2)
{
	while (!this->isEmpty())  // make sure the destination is empty
	{
		this->dequeue();
	}
	Node<dataType>* front = q2.top;
	while (front)
	{
		this->enqueue(front->getItem());
		front = front->getNext();
	}
}



// function enqueue
template<class dataType>
bool Queue<dataType>::enqueue(const dataType& item)
{
	Node<dataType>* temp = new Node<dataType>(item, nullptr);
	if (temp) {
		if (!top)   //if en queue first time
			top = temp;
		else
			rear->setNext(temp);
		rear = temp;
		return true;
	}
	return false; //if not available memory
}




//function dequeue
template<class dataType>
bool Queue<dataType>::dequeue(dataType& item)
{
	if (isEmpty())return false;
	Node<dataType>* temp = top;
	top = top->getNext();
	item = temp->getItem();
	delete temp;
	if (rear == temp)rear = nullptr; //if dequeue the last item
	return true;
}



//function peek
template<class dataType>
bool Queue<dataType>::peek(dataType& item)
{
	if (isEmpty)return false;
	item = top->getItem();
	return  true;
}



//function isEmpty
template<class dataType>
bool Queue<dataType>::isEmpty()
{
	return (top == nullptr);
}


//destructor
template<class dataType>
Queue<dataType>::~Queue()
{
	dataType dummy;
	while (this->dequeue(dummy));
}