#include"FormulationEvent.h"



//constructor
FormulationEvent::FormulationEvent(int i, int e, char t, int tL, int nD, int s) :  
	Event(i, e),
	missionType(t),
	targetLocation(tL),
	numDaysNeeded(nD),
	missionSignificance(s) {}



//destructor
FormulationEvent::~FormulationEvent(){}

//getTargetLocation
int FormulationEvent::getTargetLocation()const { return targetLocation; }

//getnumDaysNeeded
int FormulationEvent::getNumDaysNeeded()const { return numDaysNeeded; }

//getmissionSignificance
int FormulationEvent::getMissionSignificance()const { return missionSignificance; }

//execute
void FormulationEvent::execute()
{
	switch (missionType)
	{
	case 'M':
		//create new mission
		Mission * newMission = new MountainousMission(getEventDay(),getTargetLocation(),getNumDaysNeeded(),getId(),getMissionSignificance());
		//put it in appropriate list

		break;
	case 'E':
		break;
	case 'P':
		break;
	default:
		break;
	}
}