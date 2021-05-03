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



