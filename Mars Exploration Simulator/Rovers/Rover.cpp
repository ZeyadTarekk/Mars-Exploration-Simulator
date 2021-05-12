#include "Rover.h"

Rover::Rover(double roverspeed, int checkupCount, int Days)
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

void Rover::assignMission(int idMission, int duration,int location, int curDay)
{
	missionId = (idMission>0?idMission:0);
	missionDuration = (duration>0?duration:0);
	missionLocation = (location > 0? location : 0);
	missionOrCheckupEndDay = curDay + missionDuration + ceil( (2*(float)missionLocation / speed ) /25.0);
	
	missionsNumber++;
	if (missionsNumber%checkupMissions==0)
		needCheckup = true;
}

void Rover::assignCheckup(int curDay)
{
	missionOrCheckupEndDay = curDay+checkupDays;
	//missionsNumber = 0;
	needCheckup = false;
	reset();
}

void Rover::decreaseSpeedToHalf()
{
	speed /= 2;
}

unsigned int Rover::getID() const
{
	return ID;
}

double Rover::getSpeed() const
{
	return speed;
}

int Rover::getCheckupReqDays() const
{
	return checkupDays;
}

int Rover::getCheckupReqMissions() const
{
	return checkupMissions;
}

int Rover::getMissionID() const
{
	return missionId;
}

int Rover::getMissionDuration() const
{
	return missionDuration;
}

int Rover::getMissionLocation() const
{
	return missionLocation;
}

int Rover::getMissionOrCheckupEndDay() const
{
	return missionOrCheckupEndDay;
}

int Rover::getMissionNumber() const
{
	return missionsNumber;
}

bool Rover::getneedCheckup() const
{
	return needCheckup;
}


unsigned int Rover::idCounter = 1;