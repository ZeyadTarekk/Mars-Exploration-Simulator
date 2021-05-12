#include"Mission.h"
using namespace std;
Mission::Mission(int fD, int tL, int mD, int i, double s):formulationDay(fD),targetLocation(tL),missionDuration(mD),id(i),significance(s)
{
	assignedRover = nullptr;
	endDay = -1;
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

int Mission::getEndDay() const
{
	return endDay;
}

double Mission::getSignificance() const 
{	
	return significance;
}

int Mission::getID()
{
	return id;
}

Rover* Mission::getAssignedRover() const 
{ 
	return assignedRover; 
}

Mission::~Mission()
{
}

bool Mission::operator==(const Mission&recivedMission)
{
	if(recivedMission.id == id)
		return true;
	return false;
}
