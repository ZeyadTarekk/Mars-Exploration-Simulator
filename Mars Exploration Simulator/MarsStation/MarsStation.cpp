#include "MarsStation.h"

MarsStation::MarsStation() :currentDay(0)
{
}

MarsStation::~MarsStation()
{
}
unsigned long long MarsStation::getCurDay()
{
	return currentDay;
}
void MarsStation::addMission(Mission* nM) //add new mission im the appropriate function
{
	EmergencyMission* newMission1 = dynamic_cast<EmergencyMission*>(nM);
	if (newMission1)
	{
		emergencyWaitingMission.enqueue(newMission1, newMission1->getPriority());
		return;
	}
	MountainousMission* newMission2 = dynamic_cast<MountainousMission*>(nM);
	if (newMission2)
	{
		mountainousWaitingMission.insert(mountainousWaitingMission.getLength() + 1, *newMission2);
		return;
	}
	PolarMission* newMission3 = dynamic_cast<PolarMission*>(nM);
	if (newMission3)
	{
		polarWaitingMission.enqueue(newMission3);
		return;
	}
}

void MarsStation::addRover(Rover* genRover)
{
	if (dynamic_cast<EmergencyRover*>(genRover))
		emergencyAvailableRover.enqueue((EmergencyRover*)genRover, genRover->getSpeed());
	else if (dynamic_cast<MountainousRover*>(genRover))
		mountainousAvailableRover.enqueue((MountainousRover*)genRover, genRover->getSpeed());
	else if (dynamic_cast<PolarRover*>(genRover))
		polarAvailableRover.enqueue((PolarRover*)genRover, genRover->getSpeed());
}

void MarsStation::addUnavailableRover(Rover* rov)
{
	unavailableRovers.enqueue(rov, -1 * rov->getMissionOrCheckupEndDay());
}

int MarsStation::IndexOfMountainousMission(const MountainousMission& mMission)
{
	return mountainousWaitingMission.getIndexOf(mMission);
}

MountainousMission MarsStation::getMountainousMission(int index)
{
	return mountainousWaitingMission.getEntry(index);
}

void MarsStation::removeMountainousMission(int index)
{
	mountainousWaitingMission.remove(index);
}

Mission* MarsStation::inserviceRemove(int id)
{
	Mission* genMission = nullptr;
	Mission* foundMission = nullptr;
	PriorityQueue<Mission*> tempQ;
	bool found = false;
	while (inServiceMissions.dequeue(genMission))
	{
		if (!found && genMission->getID() == id)
		{
			foundMission = genMission;
			found = true;
		}
		else
			tempQ.enqueue(genMission, -1 * genMission->getEndDay());
	}
	while (tempQ.dequeue(genMission))
		inServiceMissions.enqueue(genMission, -1 * genMission->getEndDay());
	return foundMission;
}

Rover* MarsStation::UnavailableRemove(int id)
{
	Rover* genRover = nullptr;
	Rover* foundRover = nullptr;
	PriorityQueue<Rover*> tempQ;
	bool found = false;
	while (unavailableRovers.dequeue(genRover))
	{
		if (!found && genRover->getID() == id)
		{
			found = true;
			foundRover = genRover;
		}
		else
			tempQ.enqueue(genRover, -1 * genRover->getMissionOrCheckupEndDay());
	}
	while (tempQ.dequeue(genRover))
		unavailableRovers.enqueue(genRover, -1 * genRover->getMissionOrCheckupEndDay());

	return foundRover;
}

void MarsStation::PrintMountList()
{
	cout << "Size of mountianous list is : " << mountainousWaitingMission.getLength() << endl;
	for (int i = 0; i < mountainousWaitingMission.getLength(); i++)
	{
		std::cout << "\nItem number : " << i + 1 << std::endl;
		std::cout << "FormulationDay : " << mountainousWaitingMission.getEntry(i + 1).getFormulationDay() << std::endl;
		std::cout << "TargetLocation : " << mountainousWaitingMission.getEntry(i + 1).getTargetLocation() << std::endl;
		std::cout << "MissionDuration : " << mountainousWaitingMission.getEntry(i + 1).getMissionDuration() << std::endl;
		std::cout << "Significance : " << mountainousWaitingMission.getEntry(i + 1).getSignificance() << std::endl;
	}
}

void MarsStation::PrintEmergencyList()
{
	EmergencyMission* EMission;
	while (emergencyWaitingMission.dequeue(EMission))
	{
		std::cout << "FormulationDay : " << EMission->getFormulationDay() << std::endl;
		std::cout << "TargetLocation : " << EMission->getTargetLocation() << std::endl;
		std::cout << "MissionDuration : " << EMission->getMissionDuration() << std::endl;
		std::cout << "Significance : " << EMission->getSignificance() << std::endl;
		std::cout << "Priority : " << EMission->getPriority() << std::endl;
	}
}

void MarsStation::printPolarList()
{
	PolarMission* EMission;
	while (polarWaitingMission.dequeue(EMission))
	{
		std::cout << "FormulationDay : " << EMission->getFormulationDay() << std::endl;
		std::cout << "TargetLocation : " << EMission->getTargetLocation() << std::endl;
		std::cout << "MissionDuration : " << EMission->getMissionDuration() << std::endl;
		std::cout << "Significance : " << EMission->getSignificance() << std::endl;
	}
}

void MarsStation::printUnavRovers()
{
	Rover* genRover = nullptr;
	while (unavailableRovers.dequeue(genRover))
	{
		cout << "ID = " << genRover->getID() << endl;
		cout << "Speed = " << genRover->getSpeed() << endl;
		cout << "CheckupReqDays = " << genRover->getCheckupReqDays() << endl;
		cout << "CheckupReqMissions = " << genRover->getCheckupReqMissions() << endl;
		cout << "MissionID = " << genRover->getMissionID() << endl;
		cout << "MissionDuration = " << genRover->getMissionDuration() << endl;
		cout << "MissionLocation = " << genRover->getMissionLocation() << endl;
		cout << "MissionOrCheckupEndDay = " << genRover->getMissionOrCheckupEndDay() << endl;
	}
}

void MarsStation::printMountRovers()
{
	MountainousRover* genRover = nullptr;
	while (mountainousAvailableRover.dequeue(genRover))
	{
		cout << "ID = " << genRover->getID() << endl;
		cout << "Speed = " << genRover->getSpeed() << endl;
		cout << "CheckupReqDays = " << genRover->getCheckupReqDays() << endl;
		cout << "CheckupReqMissions = " << genRover->getCheckupReqMissions() << endl;
		cout << "MissionID = " << genRover->getMissionID() << endl;
		cout << "MissionDuration = " << genRover->getMissionDuration() << endl;
		cout << "MissionLocation = " << genRover->getMissionLocation() << endl;
		cout << "MissionOrCheckupEndDay = " << genRover->getMissionOrCheckupEndDay() << endl;
	}
}

void MarsStation::printEmRovers()
{
	EmergencyRover* genRover = nullptr;
	while (emergencyAvailableRover.dequeue(genRover))
	{
		cout << "ID = " << genRover->getID() << endl;
		cout << "Speed = " << genRover->getSpeed() << endl;
		cout << "CheckupReqDays = " << genRover->getCheckupReqDays() << endl;
		cout << "CheckupReqMissions = " << genRover->getCheckupReqMissions() << endl;
		cout << "MissionID = " << genRover->getMissionID() << endl;
		cout << "MissionDuration = " << genRover->getMissionDuration() << endl;
		cout << "MissionLocation = " << genRover->getMissionLocation() << endl;
		cout << "MissionOrCheckupEndDay = " << genRover->getMissionOrCheckupEndDay() << endl;
	}
}

void MarsStation::printPolarRovers()
{
	PolarRover* genRover = nullptr;
	while (polarAvailableRover.dequeue(genRover))
	{
		cout << "ID = " << genRover->getID() << endl;
		cout << "Speed = " << genRover->getSpeed() << endl;
		cout << "CheckupReqDays = " << genRover->getCheckupReqDays() << endl;
		cout << "CheckupReqMissions = " << genRover->getCheckupReqMissions() << endl;
		cout << "MissionID = " << genRover->getMissionID() << endl;
		cout << "MissionDuration = " << genRover->getMissionDuration() << endl;
		cout << "MissionLocation = " << genRover->getMissionLocation() << endl;
		cout << "MissionOrCheckupEndDay = " << genRover->getMissionOrCheckupEndDay() << endl;
	}
}

void MarsStation::ExecuteEm(Rover* r)
{
	EmergencyMission* EmMission = nullptr;
	if (emergencyWaitingMission.dequeue(EmMission))
	{
		EmMission->assignRover(r);
		inServiceMissions.enqueue(EmMission, 0);
		unavailableRovers.enqueue(r, 0);
	}
	else
		cout << "Empty list" << endl;

}

void MarsStation::Executemount(Rover* r)
{
	if (!mountainousWaitingMission.isEmpty())
	{
		MountainousMission* EmMission = new MountainousMission(mountainousWaitingMission.getEntry(1));
		mountainousWaitingMission.remove(1);
		EmMission->assignRover(r);
		inServiceMissions.enqueue(EmMission, 0);
		unavailableRovers.enqueue(r, 0);
	}
	else
		cout << "Empty list" << endl;
}

void MarsStation::ExecutePolar(Rover* r)
{
	PolarMission* EmMission = nullptr;
	if (polarWaitingMission.dequeue(EmMission))
	{
		EmMission->assignRover(r);
		inServiceMissions.enqueue(EmMission, 0);
		unavailableRovers.enqueue(r, 0);
	}
	else
		cout << "Empty list" << endl;
}

void MarsStation::printInserviceMissions()
{
	Mission* EMission;
	while (inServiceMissions.dequeue(EMission))
	{
		std::cout << "FormulationDay : " << EMission->getFormulationDay() << std::endl;
		std::cout << "TargetLocation : " << EMission->getTargetLocation() << std::endl;
		std::cout << "MissionDuration : " << EMission->getMissionDuration() << std::endl;
		std::cout << "Significance : " << EMission->getSignificance() << std::endl;
		//std::cout << "Priority : " << EMission->getPriority() << std::endl;
	}
}



bool MarsStation::assignEmergencyMission(int evDay)
{
	EmergencyMission* emMissionTemp;
	if (!emergencyWaitingMission.peek(emMissionTemp))
		return false;   //if emergency waiting list is empty
	EmergencyRover* emRoverTemp;
	if (emergencyAvailableRover.dequeue(emRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		emMissionTemp->assignRover(emRoverTemp);
		emRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	MountainousRover* mRoverTemp;
	if (mountainousAvailableRover.dequeue(mRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		emMissionTemp->assignRover(mRoverTemp);
		mRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	PolarRover* pRoverTemp;
	if (polarAvailableRover.dequeue(pRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		emMissionTemp->assignRover(mRoverTemp);
		pRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	return false;//if all rovers are unavailable
}


bool MarsStation::assignMountainousMission(int evDay)
{
	MountainousMission* mMissionTemp;
	if (mountainousWaitingMission.getLength() == 0)
		return false; //if the list of waiting mountainous mission is empty
	MountainousRover* mRoverTemp;
	if (mountainousAvailableRover.dequeue(mRoverTemp))
	{
		mMissionTemp =new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		mMissionTemp->assignRover(mRoverTemp);
		mRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	EmergencyRover* emRoverTemp;
	if (emergencyAvailableRover.dequeue(emRoverTemp))
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		mMissionTemp->assignRover(emRoverTemp);
		emRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	return false;  //if all mountainous and emergency rovers are unavailable
}

bool MarsStation::assignPolarMission(int evDay)
{
	PolarMission* pMissionTemp;
	if (!polarWaitingMission.peek(pMissionTemp))
		return false;   //if the list of waiting polar mission is empty 
	PolarRover* pRoverTemp;
	if (polarAvailableRover.dequeue(pRoverTemp))
	{
		polarWaitingMission.dequeue(pMissionTemp);
		pMissionTemp->assignRover(pRoverTemp);
		pRoverTemp->assignMission(pMissionTemp->getID(), pMissionTemp->getMissionDuration(), pMissionTemp->getTargetLocation(), evDay);
		return true;
	}
	return false;  //if polar rovers are un available
}