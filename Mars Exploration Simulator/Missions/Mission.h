#pragma once
#include"../Rovers/Rover.h"
class Mission
{
private:
	//-->>>Check if we should use enumerator soon or not in mission's status(completed||waiting||in-excuetion)
	const int formulationDay,
		targetLocation,
		missionDuration,
		id;
	const double significance;
	int endDay;
	Rover * assignedRover;   //the attribute isn't const because it's assigned after formulation
public:
	Mission(int, int, int, int, double);
	void assignRover(Rover*);
	int getFormulationDay() const;
	int getTargetLocation() const;
	int getMissionDuration() const;
	double getSignificance() const;
	Rover * getAssignedRover() const;
	virtual ~Mission()=0 ;  //make destructor pure virtual to make the class abstract
};


