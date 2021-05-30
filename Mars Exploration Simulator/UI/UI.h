#pragma once
#include"../MarsStation/MarsStation.h"
//#include""
#include<fstream>
class UI
{
	MarsStation* MStation;
	//Line 1
	int emRoverCount, mountRoverCount, polRoverCount;
	//line 2,3,4
 	int* emSpeed, *mountSpeed, *polSpeed;
	//Line 5
	int checkCount, emCheck,mountCheck, polCheck;
	//line 6
	int autoPromLimit;
	//line 7
	int NoEvents;
	//line 8
	char eventType, missionType; int eventDay, ID, location, duration, signifiance;
	// for output file
	long long totalMissions, totalWaitingDays, totalExecutionDays;
	long long totalEmMissions, totalPolarMissions, totalMountMissions;
	double avgSpeed;
	void calcAvgSpeed();
	void read();
	void createRovers();
public:
	UI(MarsStation*);
	~UI();
	void TestPrint();
	void printDay();
	void outputFile();

};

