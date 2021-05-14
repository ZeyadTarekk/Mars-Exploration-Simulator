#pragma once
#include"Mission.h"
class MountainousMission:public Mission
{
	//there is no data members needed
	int autoPromot;
public:
	MountainousMission(int, int, int, int, double,int);
	~MountainousMission();
	int getAutoProm();
	bool needAutoProm(int curDay);
};



