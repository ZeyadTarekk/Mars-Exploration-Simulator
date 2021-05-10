#include"FormulationEvent.h"



//constructor
FormulationEvent::FormulationEvent(int i, int e, char t, int tL, int nD, int s) :
	Event(i, e),
	missionType(t),
	targetLocation(tL),
	numDaysNeeded(nD),
	missionSignificance(s) {}



//destructor
FormulationEvent::~FormulationEvent() {}

//getTargetLocation
int FormulationEvent::getTargetLocation()const { return targetLocation; }

//getnumDaysNeeded
int FormulationEvent::getNumDaysNeeded()const { return numDaysNeeded; }

//getmissionSignificance
int FormulationEvent::getMissionSignificance()const { return missionSignificance; }

//execute
void FormulationEvent::execute(MarsStation* station)
{


	if (missionType == 'M')
	{
		//create new Mountainous mission
		Mission* newMountainousMission = new MountainousMission(getEventDay(), getTargetLocation(), getNumDaysNeeded(), getId(), getMissionSignificance());
		//put it in appropriate list
		station->addMission(newMountainousMission);
		return;
	}
	if (missionType == 'EM')
	{	//create new Emergency mission
		Mission* newEmergencyMission = new EmergencyMission(getEventDay(), getTargetLocation(), getNumDaysNeeded(), getId(), getMissionSignificance());
		//put it in appropriate list
		station->addMission(newEmergencyMission);
		return;
	}
	if (missionType == 'P')
	{//create new Polar mission
		Mission* newPolarMission = new PolarMission(getEventDay(), getTargetLocation(), getNumDaysNeeded(), getId(), getMissionSignificance());
		//put it in appropriate list
		station->addMission(newPolarMission);
		return;
	}
	return;
}
