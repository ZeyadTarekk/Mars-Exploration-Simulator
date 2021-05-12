#pragma once
#include"Node.h"
template<class itemType>
class List
{
	Node<itemType>* head; //pointer points to the first node in the list
	Node<itemType>* tail; //pointer points to the last node in the list
	int count; //current count of list item
	Node<itemType>* getNodeAt(int position) const //get pointer which refers to this position
	{
		Node<itemType>* temp = head;
		if (count < position || position <= 0)
		{
			return nullptr;
		}
		else
		{
			temp = head;
			for (int i = 1; i < position; i++)
			{
				temp = temp->getNext();
			}
			return temp;
		}
	}

	//getEntry
	//remove(pos)
public:
	List() //default constructor
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	List(const List<itemType> &L2) //copy constructor
	{
		head = tail = nullptr; // warnings
		Node<itemType>* original = L2.head;
		if (original == nullptr)
		{
			return;
		}
		int i = 1;
		while (original)
		{
			//itemType item = original->getItem();
			this->insert(i, original->getItem());
			original = original->getNext();
			i++;
		}
		count = L2.count;
	}
	bool isEmpty()const
	{
		if (head==nullptr)
		{
			return false;
		}
		return true;
	}
	int getLength()const
	{
		return count;
	}
	itemType getEntry(int pos)const
	{
		Node<itemType>* target = getNodeAt(pos);
		if (target)
			return target->getItem();
		else {
			std::cout << "Out of range in get entry method --> list ADT" << std::endl;
			exit(12);
		}
	}
	bool insert(const int index, const itemType& item)
	{
		if (count+1 < index || index <= 0)
			return false;
		Node<itemType>* newNode = new Node<itemType>(item);
		if (index == 1)
		{
			newNode->setNext(head);
			tail = newNode;
			head = newNode;
		}
		else if (index==count+1)
		{
			tail->setNext(newNode);
			tail = newNode;
		}
		else
		{
			Node<itemType>* temp = head;
			for (int i = 1; i < index - 1 && temp->getNext(); i++)
			{
				temp = temp->getNext();
			}
			if (temp->getNext() == tail)
			{
				temp->setNext(newNode);
				newNode->setNext(tail);
				return true;
			}
			newNode->setNext(temp->getNext());
			temp->setNext(newNode);
		}
		count++;
		return true;
	}
	bool remove(int pos)
	{
		Node<itemType>* temp = getNodeAt(pos);
		if (temp)
		{
			Node<itemType>* target = head;
			if (temp==head)
			{
				head = head->getNext();
				delete temp;      
			}
			else if (temp==tail)
			{
				while (target->getNext()!=tail)
				{
					target = target->getNext();
				}
				tail = target;
				tail->setNext(nullptr);
				delete temp;
			}
			else
			{
				while (target->getNext()!=temp)
				{
					target = target->getNext();
				}
				target->setNext(temp->getNext());
				delete temp;
			}
			count--;
			return true;
		}
		return false;
	}
	void clear() 
	{
		if (isEmpty())
		{
			while (head)
			{
				Node<itemType>* temp = head;
				head=head->getNext();
				delete temp;
			}
			count = 0;
		}
		
	}
	int getIndexOf(const itemType& target)const
	{
		bool found = false;
		Node<itemType>* targetPtr = head;
		int position = -1;
		int count = 1;
		while (!found && targetPtr)
		{
			if (targetPtr->getItem() == target)
			{
				found = true;
				position = count;
			}
			else
				targetPtr = targetPtr->getNext();
			count++;
		}
		return position;
	}
	void print()const //for testing
	{
		Node<itemType>* temp = head;
		while (temp)
		{
			std::cout << temp->getItem() << "-->";
			temp = temp->getNext();
		}
		std::cout << "NULL" << std::endl;
	}
	virtual ~List()
	{
		clear();
	}

};

