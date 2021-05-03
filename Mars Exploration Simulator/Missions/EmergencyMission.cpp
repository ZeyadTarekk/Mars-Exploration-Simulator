#include"EmergencyMission.h"

EmergencyMission::EmergencyMission(int fD, int tL, int mD, int i, double s):Mission(fD, tL, mD, i, s),priority(calculatePriority())
{
}



double EmergencyMission::calculatePriority()
{
	return getSignificance() / (getFormulationDay() * getMissionDuration() * getTargetLocation());
	//this equation is primary one 
}


double EmergencyMission::getPriority()
{
	return priority;
}

EmergencyMission::~EmergencyMission()
{
}
