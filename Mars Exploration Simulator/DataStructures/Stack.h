#pragma once
#include"Node.h"
template<class T>
class Stack
{
private:
	Node<T>* top; //pointer that refers to the last node in the stack
public:
	Stack() //default constructor
	{
		top = nullptr;

	}
	bool isEmpty()const //check if stack is empty or not
	{
		if (top == nullptr)
		{
			return true;
		}
		return false;

	}
	void push(const T& value) //push values in the top of the stack
	{
		Node<T>* newNode = new Node<T>(value);      //create a new Node  
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
	void pop()     //delete the last Node in the stack
	{
		if (!isEmpty())
		{
			Node<T>* temp = top;             //create temp pointer 
			top = top->getNext();           //increament top
			delete temp;                //delete topEntry value
			temp = nullptr;

		}

	}


};