#pragma once
#include"Mission.h"
class PolarMission :public Mission
{
	//there is no data members needed
public:
	PolarMission(int, int, int, int, double);
};



PolarMission::PolarMission(int fD, int tL, int mD, int iD, double sig):Mission(fD,tL,mD,iD,sig)
{}
