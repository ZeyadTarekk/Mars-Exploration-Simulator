#pragma once
#include"Event.h"
#include<stdlib.h>
#include<time.h>
class MissionFailure:public Event
{
public:
	MissionFailure(int);
	~MissionFailure();
	int IDprobability();
	virtual void execute(MarsStation*);
};

