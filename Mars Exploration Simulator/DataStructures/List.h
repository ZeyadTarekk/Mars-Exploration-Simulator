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
	Node<itemType>* search(const itemType& target)const
	{
		bool found = false;
		Node<itemType>* targetPtr = head;
		while (!found && targetPtr)
		{
			if (targetPtr->getItem() == target)
				found = true;
			else
				targetPtr = targetPtr->getNext();

		}
		return targetPtr;
	}
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
		while (original)
		{
			itemType item = original->getItem();
			this->insertEnd(item);
			original = original->getNext();
		}
		count = L2.count;
	}
	bool contains()const
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
	

	void insertEnd(const itemType& item)
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
		count++;
	
	}
	bool insert(const int index, const itemType item)
	{
		if (count+1 < index || index <= 0)
			return false;
		Node<itemType>* newNode = new Node<itemType>(item);
		if (index == 1)
		{
			newNode->setNext(head);
			head = newNode;
		}
		else if (index==count)
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
			newNode->setNext(temp->getNext());
			temp->setNext(newNode);
		}
		count++;
		return true;
		
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
		count--;
	}
	void deleteFirst()
	{
		if (contains())
		{
			Node<itemType>* temp = head;
			head = head->getNext();
			delete temp;
			count--;
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
			count = 0;
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
	virtual ~List()
	{
		deleteAll();
	}

};

