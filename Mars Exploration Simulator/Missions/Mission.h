#pragma once
#include"../Rovers/Rover.h"
class Mission
{
private:
	const int formulationDay,
		targetLocation,
		missionDuration,
		id;
	const double significance;
	Rover * assignedRover;   //the attribute isn't const because it's assigned after formulation
public:
	Mission(int, int, int, int, double);
	virtual ~Mission() = 0;  //make destructor pure virtual to make the class abstract
	void assignRover(Rover*);
	int getFormulationDay() const;
	int getTargetLocation() const;
	int getMissionDuration() const;
	double getSignificance() const;
	Rover * getAssignedRover() const;
};


Mission::Mission(int fD, int tL, int mD, int i, double s) :
	formulationDay(fD),
	targetLocation(tL),
	missionDuration(mD),
	id(i),
	significance(s)
{}



void Mission::assignRover(Rover* rV)
{
	assignedRover = rV;
}


int Mission::getFormulationDay()const { return formulationDay; }

int Mission::getTargetLocation()const { return targetLocation; }

int Mission::getMissionDuration()const { return missionDuration; }

double Mission::getSignificance() const { return significance; }

Rover* Mission::getAssignedRover() const { return assignedRover; }