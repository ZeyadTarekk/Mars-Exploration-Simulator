#pragma once
#include"Event.h"
class CancelationEvent : public Event
{
private:
	int id;
public:
	CancelationEvent(int day,int id);
	void execute(MarsStation* mStation);



	~CancelationEvent();

};

