#include "MissionFailure.h"
#include"FormulationEvent.h"
MissionFailure::MissionFailure(int day):Event(day)
{
}

MissionFailure::~MissionFailure()
{
}

int MissionFailure::IDprobability()
{
	srand(time(0));
	return rand()%100 +1; // generate rondom number form 1 to 100
}

void MissionFailure::execute(MarsStation* MStation)
{
	Mission* foundMission = MStation->inserviceRemove(IDprobability());
	//Mission* foundMission = MStation->inserviceRemove(3);
	if (foundMission)
	{
		MStation->addMission(foundMission); //reformulate mission
		Rover* foundRover = MStation->UnavailableRemove(foundMission->getAssignedRover()->getID());//remover rover
		foundMission->getAssignedRover()->reset(); //Reset info
		if (foundRover)
		{
			foundRover->assignCheckup(MStation->getCurDay());
			MStation->addUnavailableRover(foundRover);
		}
		//else {
		//	cout << "Rover not found in unavailable rovers --> Mission failure event" << endl;
		//	exit(12);
		//}
	}
	else {
		cout << "Mission not found" << endl;
	}
}
