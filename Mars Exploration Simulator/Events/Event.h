#pragma once
#include<iostream>
class MarsStation;
class Event
{
private:
	//these are the common data members between all events
	const int eventDay;
public:
	int getEventDay()const;
	virtual void execute(MarsStation*) = 0; //pure virtual as each event has its logic and to make the event abstract class
	Event(int);
	virtual ~Event();
};




