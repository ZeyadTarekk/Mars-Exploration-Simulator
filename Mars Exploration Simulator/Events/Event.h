#pragma once
#include<iostream>
#include"../MarsStation/MarsStation.h"
class Event
{
private:
	//these are the common data members between all events
	const int id;
	const int eventDay;
public:
	int getId() const;
	int getEventDay()const;
	virtual void execute(MarsStation*) = 0; //pure virtual as each event has its logic and to make the event abstract class
	Event(int, int);
	~Event();
};




