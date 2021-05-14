#pragma once
#include"Event.h"
#include"../MarsStation/MarsStation.h"

class Assign :public Event
{
public:
	Assign(int);
	~Assign();
	virtual void execute(MarsStation*);

};