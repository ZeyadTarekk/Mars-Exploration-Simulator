#include"EmergencyMission.h"

EmergencyMission::EmergencyMission(int fD, int tL, int mD, int i, double s):Mission(fD, tL, mD, i, s),priority(calculatePriority())
{
}



double EmergencyMission::calculatePriority()
{
	
	priority = getSignificance() / (getMissionDuration() + ceil((2 * getTargetLocation() * 0.75) / (25*12.5)));
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
