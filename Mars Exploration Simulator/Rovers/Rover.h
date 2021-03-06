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
	int overallDistance;        //all distance had been taken by the rover to enter in maintainance
	int maintainanceDuration;   //the period the rover will take 

	//missions info
	int missionId;				//given
	int missionDuration;		//given
	int missionLocation;		//given
	int missionOrCheckupEndDay;	//calculated
	
	//checkupInfo
	int missionsNumber;			//calculated
	bool needCheckup;			//calculated
	bool inMaintainance;		//calculated
	bool inCheckup;				//Checkup Status's rover
	bool needMaintainance;      //calculated

public:
	Rover(double roverspeed, int checkupCount, int Days); //essential data only
	virtual ~Rover();
	void reset();

	//setters
	virtual void assignMission(int idMission,int duration, int location, unsigned long long curDay);
	virtual void assignCheckup(unsigned long long curDay);
	virtual void decreaseSpeedToHalf();
	virtual void increaseSpeedToDouble();
	virtual void assignMaintainance(int);
	virtual void setOutOfCheckup();
	//getters
	virtual unsigned int getID() const;
	virtual double getSpeed() const ;
	virtual int getCheckupReqDays() const;
	virtual int getCheckupReqMissions() const;
	virtual bool getRoverInCheckup()const;

	virtual int getMissionID()const;
	virtual int getMissionDuration()const;
	virtual int getMissionLocation()const;
	virtual int getMissionOrCheckupEndDay()const;

	virtual int getMissionNumber()const;
	virtual bool getneedCheckup()const;
	virtual bool getMaintainance()const;
	virtual int getOverallDistance()const;
	virtual bool getneedMaintainance()const;

};

