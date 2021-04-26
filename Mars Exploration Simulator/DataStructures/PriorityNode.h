#pragma once
//Class PriorityNode for Priority Queue 
// inherites from Node class
template<class type>
class PriorityNode
{
	long long priority;
	PriorityNode<type>* next;
	type item;
public:

	//Construtors
	PriorityNode(const long long);									//Recives priority only
	PriorityNode(const type&, const long long);						//Recives item and priority 
	PriorityNode(const type&, PriorityNode<type>*, const long long);	//Recives item ,next and priority

	//Additional Setters and getters
	void setPriority(const long long);
	long long getPriority() const;

	void setNext(PriorityNode<type>*);
	PriorityNode<type>* getNext() const;

	void setItem(const type&);
	type getItem() const;
};

template<class type>
inline PriorityNode<type>::PriorityNode(const long long recivedPriority) :priority(recivedPriority), next(nullptr)
{
}

template<class type>
inline PriorityNode<type>::PriorityNode(const type& recivedItem, const long long recivedPriority) : item(recivedItem), priority(recivedPriority), next(nullptr)
{
}

template<class type>
inline PriorityNode<type>::PriorityNode(const type& recivedItem, PriorityNode<type>* recivedNext, const long long recivedPriority) : item(recivedItem), next(recivedNext), priority(recivedPriority)
{
}

template<class type>
inline void PriorityNode<type>::setPriority(const long long recivedPriority)
{
	priority = recivedPriority;
}

template<class type>
inline long long PriorityNode<type>::getPriority() const
{
	return priority;
}

template<class type>
inline void PriorityNode<type>::setNext(PriorityNode<type>* recivedNext)
{
	next = recivedNext;
}

template<class type>
inline PriorityNode<type>* PriorityNode<type>::getNext() const
{
	return next;
}

template<class type>
inline void PriorityNode<type>::setItem(const type& recivedItem)
{
	item = recivedItem;
}

template<class type>
inline type PriorityNode<type>::getItem() const
{
	return item;
}
