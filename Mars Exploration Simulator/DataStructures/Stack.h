#pragma once
#include<iostream>
using namespace std;
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
	bool pop(T& item)     //delete the last Node in the stack
	{
		if (!isEmpty())
		{
			Node<T>* temp = top;  //create temp pointer
			item = temp->getItem();
			top = top->getNext();           //increament top
			delete temp;                //delete topEntry value
			temp = nullptr;
			return true;
		}
		return false;

	}
	bool peek( T& topItem) const //can get top value
	{
		if (!isEmpty())
		{
			topItem = top->getItem();
			return true;
		}
		return false;
	}
	bool clear() //clear the whole stack
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			while (top)
			{
				Node<T>* newPtr = top;
				top = top->getNext();
				delete newPtr;
				newPtr = nullptr;
				

			}
			
		}

		
		return true;
	}
	void DisplayStack() const //print all values in the stack
	{
		Node<T>* temp = top;
		if (!isEmpty())
		{
			while (temp)
			{
				cout << "(" << temp->getItem() << ")" << "--->";
				temp = temp->getNext();

			}
			cout << "NULL" << endl;;
		}
		else
			cout << "List is Empty" << endl;
	}


};