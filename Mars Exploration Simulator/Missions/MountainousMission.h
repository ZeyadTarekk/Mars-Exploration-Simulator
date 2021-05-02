#pragma once
#include"Mission.h"
class MountainousMission:public Mission
{
	//there is no data members needed
public:
	MountainousMission(int, int, int, int, double);
};

MountainousMission::MountainousMission(int fD, int tL, int mD, int iD, double sig) :Mission(fD, tL, mD, iD, sig)
{}

