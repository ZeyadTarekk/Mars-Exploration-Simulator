#include "Rover.h"

Rover::Rover(double roverspeed, int checkupCount, int Days)
{
	ID = idCounter;
	speed = (roverspeed > 0 ? roverspeed : 0);
	checkupDays = (Days > 0 ? Days : 0);
	checkupMissions = (checkupCount > 0 ? checkupCount : 0);

	missionId = -1;
	missionDuration = -1;
	missionOrCheckupEndDay = -1;
	missionLocation = -1;

	missionsNumber = 0;
	inMaintainance = false;
	inCheckup = false;
	needCheckup = false;
	needMaintainance = false;
	idCounter++;

	overallDistance = 0;
}

Rover::~Rover()
{
}

void Rover::reset()
{
	missionId = -1;
	missionDuration = -1;
	missionOrCheckupEndDay = -1;
	missionLocation = -1;

}

void Rover::assignMission(int idMission, int duration, int location, unsigned long long curDay)
{
	missionId = (idMission > 0 ? idMission : 0);
	missionDuration = (duration > 0 ? duration : 0);
	missionLocation = (location > 0 ? location : 0);
	missionOrCheckupEndDay = curDay + missionDuration + ceil((2 * (float)missionLocation / speed) / 25.0);

	missionsNumber++;
	if (missionsNumber % checkupMissions == 0 && missionsNumber>= checkupMissions)
		needCheckup = true;
	overallDistance += missionLocation;
	if (overallDistance >= 1000 && missionsNumber >= 5) 
		needMaintainance = true;
}

void Rover::assignCheckup(unsigned long long curDay)
{
	inCheckup = true;
	reset();
	missionOrCheckupEndDay = curDay + checkupDays;
	//missionsNumber = 0;
	needCheckup = false;
}


void Rover::decreaseSpeedToHalf()
{
	inMaintainance = true;
	speed /= 2;
}

void Rover::increaseSpeedToDouble()
{
	inMaintainance = false;
	speed *= 2;
}

void Rover::assignMaintainance(int curDay)
{
	decreaseSpeedToHalf();
	missionsNumber = 0;
	missionOrCheckupEndDay = curDay + maintainanceDuration;
	//missionsNumber = 0;
	needCheckup = false;
	reset();
	overallDistance = 0;
	needMaintainance = false;
}

void Rover::setOutOfCheckup()
{
	inCheckup = false;
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

bool Rover::getRoverInCheckup() const
{
	return inCheckup;
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

bool Rover::getMaintainance() const
{
	return inMaintainance;
}

int Rover::getOverallDistance() const
{
	return overallDistance;
}

bool Rover::getneedMaintainance() const
{
	return needMaintainance;
}


unsigned int Rover::idCounter = 1;