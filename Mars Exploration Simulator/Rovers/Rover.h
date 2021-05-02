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
	virtual void assignMission(int idMission,int duration, int location);
	virtual void assignCheckup();

	//getters
	virtual unsigned int getID();
	virtual int getSpeed();
	virtual int getCheckupReqDays();
	virtual int getCheckupReqMissions();

	virtual int getMissionID();
	virtual int getMissionDuration();
	virtual int getMissionLocation();
	virtual int getMissionOrCheckupEndDay();

	virtual int getMissionNumber();
	virtual bool getneedCheckup();
};

