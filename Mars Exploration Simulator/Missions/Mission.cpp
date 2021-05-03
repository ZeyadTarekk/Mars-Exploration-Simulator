#include"Mission.h"

Mission::Mission(int fD, int tL, int mD, int i, double s):formulationDay(fD),targetLocation(tL),missionDuration(mD),id(i),significance(s)
{
	assignedRover = nullptr;
}



void Mission::assignRover(Rover* rV)
{
	assignedRover = rV;
	endDay = rV->getMissionOrCheckupEndDay();
}


int Mission::getFormulationDay()const
{
	return formulationDay;
}

int Mission::getTargetLocation()const
{
	return targetLocation;
}

int Mission::getMissionDuration()const 
{ 
	return missionDuration;
}

double Mission::getSignificance() const 
{ 
	return significance;
}

Rover* Mission::getAssignedRover() const 
{ 
	return assignedRover; 
}