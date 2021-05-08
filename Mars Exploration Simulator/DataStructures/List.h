#pragma once
#include"Node.h"
template<class itemType>
class List
{
	Node<itemType>* head; //pointer points to the first node in the list
	Node<itemType>* tail; //pointer points to the last node in the list
	Node<itemType>* getNodeAt(int position) const //get pointer which refers to this position
	{
		int count = 0;
		Node<itemType>* temp = head;
		while (temp)
		{
			count++;
			temp = temp->getNext();
		}
		if (count < position || position < 0)
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
public:
	List() //default constructor
	{
		head = nullptr;
		tail = nullptr;
	}
	List(const List<itemType> &L2) //copy constructor
	{
		head = tail = nullptr; // warnings
		Node<itemType>* original = L2.head;
		if (original == nullptr)
		{
			return;
		}
		while (original)
		{
			itemType item = original->getItem();
			this->insertEnd(item);
			original = original->getNext();
		}
	}
	bool contains()const
	{
		if (head==nullptr)
		{
			return false;
		}
		return true;
	}
	bool search(const itemType&item)const
	{
		Node<itemType>* targetPtr = head;
		while (targetPtr)
		{
			if (targetPtr->getItem() == item)
			{
				return true;
			}
			targetPtr = targetPtr->getNext();
		}
		return false;
	}

	void insertEnd(itemType& item)
	{
		Node<itemType>* newNode = new Node<itemType>(item);
		Node<itemType>* temp = head;
		if (temp == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->setNext(newNode);
			tail = newNode;
		}
	
	}
	
	bool deleteNode(const itemType&item)
	{
		if (!contains())
			return false;
		Node<itemType>* temp = head;
		Node<itemType>* prev = head;
		if (temp->getItem() == item)
		{
			head = head->getNext();
			delete temp;
			temp = nullptr;
			return true;
		}
		else
		{
			while (temp->getNext() != nullptr && temp->getItem()!= item)
			{
				prev = temp;
				temp = temp->getNext();

			}
			if (!temp)
			{
				return false;
			}
			else
			{
				prev->setNext(temp->getNext());
				delete temp;
				temp = nullptr;
				return true;
			}

		}
	}
	void deleteFirst()
	{
		Node<itemType>* temp = head;
		if (contains())
		{
			head = head->getNext();
			delete temp;
		}
		/*deleteNode(getNodeAt(1)->getItem());*/
	}
	void deleteAll() 
	{
		if (contains())
		{
			while (head)
			{
				Node<itemType>* temp = head;
				head=head->getNext();
				delete temp;
			}
		}
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
	~List()
	{
		deleteAll();
	}

};

