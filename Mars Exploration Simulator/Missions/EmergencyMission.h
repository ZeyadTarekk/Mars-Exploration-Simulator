#pragma once
#include"Mission.h"
class EmergencyMission :public Mission
{
private:
	const double priority;
	double calculatePriority(); //utility function will be called in only constructor
public:
	EmergencyMission(int, int, int, int, double);
	double getPriority();
};



EmergencyMission::EmergencyMission(int fD, int tL, int mD, int i, double s) :
	Mission(fD, tL, mD, i, s),
	priority(calculatePriority())
{}



double EmergencyMission::calculatePriority()
{
	return getSignificance() / (getFormulationDay() * getMissionDuration() * getTargetLocation());
	//this equation is primary one 
}


double EmergencyMission::getPriority() 
{
	return priority;
}