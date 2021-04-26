#pragma once
//Class PriorityNode for Priority Queue 
// inherites from Node class
#include"Node.h"
template<class type>
class PriorityNode:public Node<type>
{
	long long priority;
public:

	//Construtors
	PriorityNode(const long long&);									//Recives priority only
	PriorityNode(const type&, const long long&);						//Recives item and priority 
	PriorityNode(const type&, PriorityNode<type>*,const long long&);	//Recives item ,next and priority
	
	//Additional Setters and getters
	void setPriority(const long long&);
	long long getPriority() const;
};

template<class type>
inline PriorityNode<type>::PriorityNode(const long long& recivedPriority):priority(recivedPriority)
{
}

template<class type>
inline PriorityNode<type>::PriorityNode(const type& recivedItem,const long long& recivedPriority):Node<type>(recivedItem),priority(recivedPriority)
{
}

template<class type>
inline PriorityNode<type>::PriorityNode(const type&recivedItem, PriorityNode<type>*recivedNext,const long long& recivedPriority):Node<type>(recivedItem, recivedNext),priority(recivedPriority)
{
}

template<class type>
inline void PriorityNode<type>::setPriority(const long long& recivedPriority)
{
	priority = recivedPriority;
}

template<class type>
inline long long PriorityNode<type>::getPriority() const
{
	return priority;
}
