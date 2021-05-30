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
	int executionDay;
	Rover * assignedRover;   //the attribute isn't const because it's assigned after formulation
public:
	Mission(int, int, int, int, double);
	void assignRover(Rover*,long long);
	long long getExecutionDay();
	int getFormulationDay() const;
	int getTargetLocation() const;
	int getMissionDuration() const;
	int getEndDay()const;
	double getSignificance() const;
	int getID();
	//void print()const;//for testing only 
	Rover * getAssignedRover() const;
	virtual ~Mission()=0 ;  //make destructor pure virtual to make the class abstract
	bool operator==(const Mission&);
};


