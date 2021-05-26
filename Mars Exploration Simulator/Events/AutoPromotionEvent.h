#pragma once
#include"Event.h"
#include"../MarsStation/MarsStation.h"
class AutoPromotionEvent:public Event
{
public:
	AutoPromotionEvent(int);
	void execute(MarsStation* mStation);

	
};

