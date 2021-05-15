#include "MarsStation.h"

MarsStation::MarsStation() :currentDay(0)
{
}

MarsStation::~MarsStation()
{
}
void MarsStation::setAutoPromot(int autoProm)
{
	autoPromot = autoProm;
}
int MarsStation::getAutoPromot()
{
	return autoPromot;
}
unsigned long long MarsStation::getCurDay()
{
	return currentDay;
}
void MarsStation::setAvgSpeed(double speed)
{
	avgSpeed = speed;
}
double MarsStation::getAvgSpeed()
{
	return avgSpeed;
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

void MarsStation::createRover(char type, int speed, int checkCount, int checkDays)
{
	switch (type)
	{
	case 'M':
	{
		MountainousRover* mountRover = new MountainousRover(speed, checkCount, checkDays);
		mountainousAvailableRover.enqueue(mountRover, speed);
		break;
	}
	case 'P':
	{
		PolarRover* polRover = new PolarRover(speed, checkCount, checkDays);
		polarAvailableRover.enqueue(polRover, speed);
		break;
	}
	case'E':
	{
		EmergencyRover* emRover = new EmergencyRover(speed, checkCount, checkDays);
		emergencyAvailableRover.enqueue(emRover, speed);
		break;
	}
	}

}

void MarsStation::createFormEvent(char type, int eventDay, int id, int targetLoc, int MDuration, int sig)
{
	FormulationEvent* fEvent = new FormulationEvent(eventDay, id, type, targetLoc, MDuration, sig);
	eventList.enqueue(fEvent);
}

void MarsStation::createCancelEvent(int eventDay, int id)
{
	CancelationEvent* cEvent = new CancelationEvent(eventDay, id);
	eventList.enqueue(cEvent);
}

void MarsStation::createPromotEvent(int eventDay, int id)
{
	PromotionEvent* pEvent = new PromotionEvent(eventDay, id);
	eventList.enqueue(pEvent);
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
			tempQ.enqueue(genMission, -1 * genMission->getAssignedRover()->getCheckupReqDays());
	}
	while (tempQ.dequeue(genMission))
		inServiceMissions.enqueue(genMission, -1 * genMission->getAssignedRover()->getCheckupReqDays());
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

void MarsStation::executeEvents()
{
	Event* e;
	while (eventList.dequeue(e))
		e->execute(this);
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

void MarsStation::printCompleteMission()
{
	Mission* EMission;
	while (completedMissions.dequeue(EMission))
	{
		std::cout << "ID :" << EMission->getID() << endl;
		std::cout << "FormulationDay : " << EMission->getFormulationDay() << std::endl;
		std::cout << "TargetLocation : " << EMission->getTargetLocation() << std::endl;
		std::cout << "MissionDuration : " << EMission->getMissionDuration() << std::endl;
		std::cout << "Significance : " << EMission->getSignificance() << std::endl;


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
		unavailableRovers.enqueue(emRoverTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}
	MountainousRover* mRoverTemp;
	if (mountainousAvailableRover.dequeue(mRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		emMissionTemp->assignRover(mRoverTemp);
		mRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * emMissionTemp->getEndDay());
		return true;
	}
	PolarRover* pRoverTemp;
	if (polarAvailableRover.dequeue(pRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		emMissionTemp->assignRover(mRoverTemp);
		pRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * emMissionTemp->getEndDay());
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
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		mMissionTemp->assignRover(mRoverTemp);
		mRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * mMissionTemp->getEndDay());
		return true;
	}
	EmergencyRover* emRoverTemp;
	if (emergencyAvailableRover.dequeue(emRoverTemp))
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		mMissionTemp->assignRover(emRoverTemp);
		emRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		unavailableRovers.enqueue(emRoverTemp, -1 * mMissionTemp->getEndDay());
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
		unavailableRovers.enqueue(pRoverTemp, -1 * pMissionTemp->getEndDay());
		return true;
	}
	return false;  //if polar rovers are un available
}

void MarsStation::addToCompletedMission(int eD)
{
	Mission* m;
	inServiceMissions.dequeue(m);
	completedMissions.enqueue(m);

}

void MarsStation::moveRoverFromExcuetionToCheckUp(int eD)
{
	Rover* rV;
	bool Found = unavailableRovers.peek(rV);
	while (Found && rV->getMissionOrCheckupEndDay() == eD)
	{
		unavailableRovers.dequeue(rV);
		rV->reset();
		if (rV->getneedCheckup())
		{
			rV->assignCheckup(eD);
			unavailableRovers.enqueue(rV, rV->getMissionOrCheckupEndDay());
		}

		else
		{
			if (rV->getMaintainance())
				rV->assignMaintainance(eD);

			EmergencyRover* eR = dynamic_cast<EmergencyRover*>(rV);
			MountainousRover* mR = dynamic_cast<MountainousRover*>(rV);
			PolarRover* pR = dynamic_cast<PolarRover*>(rV);
			if (eR)
				emergencyAvailableRover.enqueue(eR, eR->getSpeed());
			else if (mR)
				mountainousAvailableRover.enqueue(mR, mR->getSpeed());
			else if (pR)
				polarAvailableRover.enqueue(pR, pR->getSpeed());
		}
		Found = unavailableRovers.peek(rV);
	}
}

bool MarsStation::isCompleted(int eD)
{
	Mission* mTemp = nullptr;
	bool Found = inServiceMissions.peek(mTemp);
	if (Found && mTemp->getEndDay() == eD) // check if there is a mission in IN-Ex. 
		return true;
	return false;
}
