#pragma once
#include"Mission.h"
class EmergencyMission :public Mission
{
private:
	 double priority;
	double calculatePriority(double); //utility function will be called in only constructor
public:
	EmergencyMission(int, int, int, int, double,double);
	double getPriority();
	~EmergencyMission() ;
};



