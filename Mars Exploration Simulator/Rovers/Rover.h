#pragma once
#include<iostream>

class Rover
{
	static unsigned int idCounter;
	
	//essential info ---> given
	unsigned int ID;
	int speed;
	int checkupDays;
	int checkupMissions;	

	//missions info
	int missionId;				//given
	int missionDuration;		//given
	int missionLocation;		//given
	int missionOrCheckupEndDay;	//calculated
	
	//checkupInfo
	int missionsNumber;			//calculated
	bool needCheckup;			//calculated

public:
	Rover(int roverspeed, int checkupCount, int Days); //essential data only

	void reset();

	//setters
	void assignMission(int idMission,int duration, int location);
	void assignCheckup();

	//getters
	unsigned int getID();
	int getSpeed();
	int getCheckupReqDays();
	int getCheckupReqMissions();

	int getMissionID();
	int getMissionDuration();
	int getMissionLocation();
	int getMissionOrCheckupEndDay();

	int getMissionNumber();
	bool getneedCheckup();
};

