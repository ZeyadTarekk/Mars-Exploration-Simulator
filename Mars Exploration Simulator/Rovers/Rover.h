#pragma once
#include<iostream>

class Rover
{
	static unsigned int idCounter;
	
	//essential info ---> given
	unsigned int ID;
	double speed;
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
	Rover(double roverspeed, int checkupCount, int Days); //essential data only

	void reset();

	//setters
	virtual void assignMission(int idMission,int duration, int location);
	virtual void assignCheckup();
	virtual void decreaseSpeedToHalf();

	//getters
	virtual unsigned int getID() const;
	virtual double getSpeed() const ;
	virtual int getCheckupReqDays() const;
	virtual int getCheckupReqMissions() const;

	virtual int getMissionID()const;
	virtual int getMissionDuration()const;
	virtual int getMissionLocation()const;
	virtual int getMissionOrCheckupEndDay()const;

	virtual int getMissionNumber()const;
	virtual bool getneedCheckup()const;
};

