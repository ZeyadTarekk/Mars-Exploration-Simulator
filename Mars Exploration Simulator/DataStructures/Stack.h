#pragma once
#include"Node.h"
#include<iostream>
template<class itemType>
class Stack
{
private:
	Node<itemType>* top; //pointer that refers to the last node in the stack
public:
	Stack(); //default constructor
	Stack(const Stack<itemType>&);//copy construtor 
	bool isEmpty()const;//check if stack is empty or not
	void push(const itemType&);//push values in the top of the stack
	bool pop(itemType&);    //delete the last Node in the stack   
	bool peek(itemType& ) const;//can get top value
	bool clearAll(); //clear the whole stack
	void printStack() const; //print all values in the stack
	~Stack();
};
template<class itemType>
Stack<itemType>::Stack()
{
	top = nullptr;
}

template<class itemType>
Stack<itemType>::Stack(const Stack<itemType>& stackTemp)
{
	Node<itemType>* originalTop = stackTemp.top;
	if (stackTemp.isEmpty())
	{
		top = nullptr;
	}
	else
	{
		Stack<itemType>* tempPtr = new Stack<itemType>(); //temp Stack

		while (originalTop)
		{
			itemType item = originalTop->getItem();
			tempPtr->push(item);
			originalTop = originalTop->getNext();
		}
		Node<itemType>* copyPtr = tempPtr->top; //copy temp stack into invoked stack
		while (copyPtr)
		{
			itemType itemCopy = copyPtr->getItem();
			this->push(itemCopy);
			copyPtr = copyPtr->getNext();
		}
		delete tempPtr; // delete temp stack
		tempPtr = nullptr;
	}
}

template<class itemType>
void Stack<itemType>::push(const itemType& value)
{
	Node<itemType>* newNode = new Node<itemType>(value);      //create a new Node  
	if (!isEmpty())
	{
		newNode->setNext(top);      //link new Node with the previous node 
		top = newNode;              //top points to the newNode
	}
	else
	{
		top = newNode;
		newNode->setNext(nullptr);
	}
}

template<class itemType>
bool Stack<itemType>::isEmpty()const
{
	if (top == nullptr)
	{
		return true;
	}
	return false;
}
template<class itemType>
bool Stack<itemType>::pop(itemType& item)     //delete the last Node in the stack
{
	if (!isEmpty())
	{
		Node<itemType>* temp = top;  //create temp pointer
		item = temp->getItem();
		top = top->getNext();           //increament top
		delete temp;                //delete topEntry value
		temp = nullptr;
		return true;
	}
	return false;
}
template<class itemType>
bool Stack<itemType>::peek(itemType& topItem) const //can get top value
{
	if (!isEmpty())
	{
		topItem = top->getItem();
		return true;
	}
	return false;
}
template<class itemType>
bool Stack<itemType>::clearAll() //clear the whole stack
{
	if (isEmpty())
		return false;
	else
	{
		itemType item;

		while (!isEmpty())
		{
			this->pop(item);
		}
	}
}
template<class itemType>
void Stack<itemType>::printStack() const 
{
	Node<itemType>* temp = top;
	if (!isEmpty())
	{
		while (temp)
		{
			std::cout << "(" << temp->getItem() << ")" << "--->";
			temp = temp->getNext();
		}
		std::cout << "NULL" << std::endl;;
	}
	else
		std::cout << "List is Empty" << std::endl;
}
template<class itemType>
Stack<itemType>::~Stack()
{
	clearAll();
}

