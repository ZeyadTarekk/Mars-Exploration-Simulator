#include"EmergencyMission.h"

EmergencyMission::EmergencyMission(int fD, int tL, int mD, int i, double s,double avgSpeed):Mission(fD, tL, mD, i, s),priority(calculatePriority(avgSpeed))
{
}



double EmergencyMission::calculatePriority(double avgSpeed)
{
	
	priority = getSignificance() / (getMissionDuration() + ceil((2 * getTargetLocation() * 0.75) / (25.0*avgSpeed)));
	return priority;
	//this equation is primary one 
}


double EmergencyMission::getPriority()
{
	return priority;
}

EmergencyMission::~EmergencyMission()
{
}
