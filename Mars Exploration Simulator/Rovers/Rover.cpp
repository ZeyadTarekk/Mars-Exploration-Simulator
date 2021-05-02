#include "Rover.h"

Rover::Rover(int roverspeed, int checkupCount, int Days)
{
	ID = idCounter;
	speed = (roverspeed > 0 ? roverspeed : 0);
	checkupDays = (Days>0?Days:0);
	checkupMissions = (checkupCount > 0 ? checkupCount : 0);

	missionId = -1;
	missionDuration = -1;
	missionOrCheckupEndDay = -1;
	missionLocation = -1;

	missionsNumber = 0;
	
	
	needCheckup = false;

	idCounter++;

}

void Rover::reset()
{
	missionId = -1;
	missionDuration = -1;
	missionOrCheckupEndDay = -1;
	missionLocation = -1;
}

void Rover::assignMission(int idMission, int duration,int location)
{
	missionId = (idMission>0?idMission:0);
	missionDuration = (duration>0?duration:0);
	missionLocation = (location > 0? location : 0);
	missionOrCheckupEndDay = missionDuration + ceil( (2*(float)missionLocation / speed ) /25.0);
	
	missionsNumber++;
	if (missionsNumber%checkupMissions==0)
		needCheckup = true;
}

void Rover::assignCheckup()
{
	missionOrCheckupEndDay = checkupDays;
	//missionsNumber = 0;
	needCheckup = false;
	reset();
}

unsigned int Rover::getID()
{
	return ID;
}

int Rover::getSpeed()
{
	return speed;
}

int Rover::getCheckupReqDays()
{
	return checkupDays;
}

int Rover::getCheckupReqMissions()
{
	return checkupMissions;
}

int Rover::getMissionID()
{
	return missionId;
}

int Rover::getMissionDuration()
{
	return missionDuration;
}

int Rover::getMissionLocation()
{
	return missionLocation;
}

int Rover::getMissionOrCheckupEndDay()
{
	return missionOrCheckupEndDay;
}

int Rover::getMissionNumber()
{
	return missionsNumber;
}

bool Rover::getneedCheckup()
{
	return needCheckup;
}


unsigned int Rover::idCounter = 1;