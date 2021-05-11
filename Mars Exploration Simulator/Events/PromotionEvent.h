#pragma once
#include"Event.h"
#include"../Missions/EmergencyMission.h"
class PromotionEvent:public Event
{
public:
	PromotionEvent(int, int);
	~PromotionEvent();
	virtual void execute(MarsStation*);
};

