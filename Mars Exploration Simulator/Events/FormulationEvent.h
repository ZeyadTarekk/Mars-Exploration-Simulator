#pragma once
#include"Event.h"

//class FormulatoinEvent
class FormulationEvent : public Event
{
private:
	const int id;
	const char missionType;
	const int targetLocation;
	const int numDaysNeeded;
	const int missionSignificance;
public:
	FormulationEvent(int, int, char, int, int, int);
	~FormulationEvent();
	virtual void execute(MarsStation*);
	int getTargetLocation()const;
	int getNumDaysNeeded()const;
	int getMissionSignificance()const;
	int getId() const;
};
