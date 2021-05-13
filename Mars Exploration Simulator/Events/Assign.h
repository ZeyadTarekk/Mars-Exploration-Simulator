#pragma once
#include"Event.h"

class Assign :public Event
{
public:
	Assign(int);
	~Assign();
	virtual void execute(MarsStation*);

};