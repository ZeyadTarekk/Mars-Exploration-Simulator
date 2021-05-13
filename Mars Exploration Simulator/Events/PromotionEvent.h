#pragma once
#include"Event.h"
#include"../Missions/EmergencyMission.h"
class PromotionEvent:public Event
{
	const int id;
public:
	PromotionEvent(int,int);
	int getId() const;
	~PromotionEvent();
	virtual void execute(MarsStation*);
};

