#include "MarsStation.h"

template<class T>
Rover* MarsStation::getFastestRover(List<T>*maintainanceList)
{
	Rover* fastest = maintainanceList->getEntry(1);
	Rover* temp ;
	for (int i = 2; i <= maintainanceList->getLength(); i++)
	{
		temp = maintainanceList->getEntry(i);
		if (temp->getSpeed() > fastest->getSpeed())
			fastest = temp;
	}
	return fastest;
}

void MarsStation::simulate()
{
	UI* uiPtr = new UI(this);
	AutoPromotionEvent* autoPromotion;
	Assign* assignEvent;
	MissionFailure* missionFailure;
	CompletionEvent* completionEvent;
	bool status;
	Event* tempEvent;
	if (eventList.isEmpty())
	{
		switch (Mode)
		{
		case Interactive:
			uiPtr->printDay();
			cin.get();
			break;
		case step_by_step:
			uiPtr->printDay();
			Sleep(1500);
			break;
		case silent:
			uiPtr->printSilent();
			break;
		}
		uiPtr->outputFile();
		return;
	}
		
	eventList.peek(tempEvent);
	currentDay = tempEvent->getEventDay();
	bool increment = false;
	cin.get();
	do
	{
		if (eventList.peek(tempEvent))
		{
			if (tempEvent->getEventDay() <= currentDay)
			{
				tempEvent->execute(this);
				eventList.dequeue(tempEvent);
				increment = false;
			}
			else
				increment = true;
		}
		else
			increment = true;

		autoPromotion = new AutoPromotionEvent(currentDay);
		assignEvent = new Assign(currentDay);
		missionFailure = new MissionFailure(currentDay);
		completionEvent = new CompletionEvent(currentDay);
		autoPromotion->execute(this);
		missionFailure->execute(this);
		completionEvent->execute(this);
		assignEvent->execute(this);
		
		switch (Mode)
		{
		case Interactive:
			if (increment)
			{
				uiPtr->printDay();
				cin.get();
			}
			break;
		case step_by_step:
			if (increment)
			{
				uiPtr->printDay();
				Sleep(1500);
			}
			break;
		case silent :
			break;
		}
		if(increment)
			currentDay++;
		if (currentDay == 25)
			cout << "" << endl;
		//eventList.dequeue(tempEvent);
		status = !emergencyWaitingMission.isEmpty() || !eventList.isEmpty() || !polarWaitingMission.isEmpty() || !mountainousWaitingMission.isEmpty() || !inServiceMissions.isEmpty() || !unavailableRovers.isEmpty();
		delete autoPromotion;delete assignEvent;delete missionFailure; delete completionEvent;
	} while (status);
	if(Mode == silent)
		uiPtr->printSilent();
	uiPtr->outputFile();
}

MarsStation::MarsStation() :currentDay(0)
{
	avgSpeed = 0;
	mountRoverNo = 0;
	emRoverNo = 0;
	polRoverNo = 0;
	eventCount = 0;
	autoPromot = 0;
	numberOfPromotedMissions = 0;
	mountMissionCount = 0;
}

MarsStation::~MarsStation()
{
	// delete objects in the heap;
	while (!emergencyWaitingMission.isEmpty())
	{
		EmergencyMission* temp;
		emergencyWaitingMission.dequeue(temp);
		delete temp;
	}
	while (!polarWaitingMission.isEmpty())
	{
		PolarMission* temp;
		polarWaitingMission.dequeue(temp);
		delete temp;
	}
	while (!completedMissions.isEmpty())
	{
		Mission* temp;
		completedMissions.dequeue(temp);
		delete temp;
	}
	while (!emergencyAvailableRover.isEmpty())
	{
		EmergencyRover* temp;
		emergencyAvailableRover.dequeue(temp);
		delete temp;
	}
	while (!mountainousAvailableRover.isEmpty())
	{
		MountainousRover* temp;
		mountainousAvailableRover.dequeue(temp);
		delete temp;
	}
	while (!polarAvailableRover.isEmpty())
	{
		PolarRover* temp;
		polarAvailableRover.dequeue(temp);
		delete temp;
	}
}
int MarsStation::getMountMissionCount()
{
	return mountMissionCount;
}
int MarsStation::getEventCount() const
{
	return eventCount;
}
int MarsStation::getEmRoverCount() const
{
	return emRoverNo;
}
int MarsStation::getMountRoverCount() const
{
	return mountRoverNo;
}
int MarsStation::getPolRoverCount() const
{
	return polRoverNo;
}
int MarsStation::getTotalNoRovers() const
{
	return polRoverNo+mountRoverNo+emRoverNo;
}
void MarsStation::setEventCount(int count)
{
	eventCount = (count >= 0 ? count : 0);
}
void MarsStation::setEmRoverCount(int count)
{
	emRoverNo = (count >= 0 ? count : 0);
}
void MarsStation::setMountRoverCount(int count)
{
	mountRoverNo = (count >= 0 ? count : 0);
}
void MarsStation::setPolRoverCount(int count)
{
	polRoverNo = (count >= 0 ? count : 0);
}
void MarsStation::setAutoPromot(int autoProm)
{
	autoPromot = autoProm;
}
int MarsStation::getAutoPromot()
{
	return autoPromot;
}
int MarsStation::getNumberOfPromotedMissions()
{
	return numberOfPromotedMissions;
}
unsigned long long MarsStation::getCurDay()
{
	return currentDay;
}
void MarsStation::setModeOperation(int m)
{
	switch (m)
	{
	case 1:
		Mode = Interactive;
		break;
	case 2:
		Mode = step_by_step;
		break;
	default:
		Mode = silent;
	}
}
ModeOpeartion MarsStation::getModeOperation()
{
	return Mode;
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
		mountMissionCount++;
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

void MarsStation::promoteMountainousToEmergencyMission(int cD)
{	
	if (mountainousWaitingMission.isEmpty()) 
		return;
	MountainousMission* mtemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
	while(mtemp->needAutoProm(cD))
	{
		EmergencyMission* PromotedMission = new EmergencyMission(mtemp->getFormulationDay(),
			mtemp->getTargetLocation(),
			mtemp->getMissionDuration(), mtemp->getID(),
			mtemp->getSignificance(),getAvgSpeed());
		numberOfPromotedMissions++; //increament No. of Promoted Mission
		emergencyWaitingMission.enqueue(PromotedMission,PromotedMission->getPriority());
		mountainousWaitingMission.remove(1);
		if (mountainousWaitingMission.isEmpty())
			return;
		mtemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
	/*	numberOfPromotedMissions++;*/
	}
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

void MarsStation::addToUnavaiRover(Rover*r)
{
	unavailableRovers.enqueue(r,9);
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
		EmMission->assignRover(r, currentDay);
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
		EmMission->assignRover(r,currentDay);
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
		EmMission->assignRover(r,currentDay);
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

void MarsStation::CompleteMission()
{
	EmergencyMission* emMission;
	if (emergencyWaitingMission.dequeue(emMission))
		completedMissions.enqueue(emMission);

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
		cout << "End day in mission : " << EMission->getEndDay() << endl;
		cout << "End day in rover : " << EMission->getAssignedRover()->getMissionOrCheckupEndDay() << endl;

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
		emRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(emRoverTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());  // -1*evDay to make the search in complete more easy
		unavailableRovers.enqueue(emRoverTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}
	MountainousRover* mRoverTemp;
	if (mountainousAvailableRover.dequeue(mRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		mRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(mRoverTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());// -1*evDay to make the search in complete more easy
		unavailableRovers.enqueue(mRoverTemp, -1 * emMissionTemp->getEndDay());
		return true;
	}
	PolarRover* pRoverTemp;
	if (polarAvailableRover.dequeue(pRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		pRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(pRoverTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());// -1*evDay to make the search in complete more easy

		unavailableRovers.enqueue(pRoverTemp, -1 * emMissionTemp->getEndDay());
		return true;
	}
	// now we will check the lists of maintainance Rovers
	Rover* generalTemp;
	if (!unAvailableMaintainanceEmergency.isEmpty())
	{
		generalTemp= getFastestRover(&unAvailableMaintainanceEmergency);
		emergencyWaitingMission.dequeue(emMissionTemp);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());

		unavailableRovers.enqueue(generalTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainanceMountainous.isEmpty())
	{
		generalTemp = getFastestRover(&unAvailableMaintainanceMountainous);
		emergencyWaitingMission.dequeue(emMissionTemp);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());

		unavailableRovers.enqueue(generalTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainancePolar.isEmpty())
	{
		generalTemp = getFastestRover(&unAvailableMaintainancePolar);
		emergencyWaitingMission.dequeue(emMissionTemp);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(emMissionTemp, -1 * emMissionTemp->getEndDay());

		unavailableRovers.enqueue(generalTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
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
	{																			 //->>> .getEntry(1))
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(1)); //getEntry of first mission in list due to its day (waitlinglist priority ->>>autoPromotoion)
		mountainousWaitingMission.remove(1); //->>remove(1)
		
		mRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(mRoverTemp, currentDay);
		inServiceMissions.enqueue(mMissionTemp, -1 * mMissionTemp->getEndDay());
		unavailableRovers.enqueue(mRoverTemp, -1 * mMissionTemp->getEndDay());
		return true;
	}
	EmergencyRover* emRoverTemp;
	if (emergencyAvailableRover.dequeue(emRoverTemp))
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
		mountainousWaitingMission.remove(1);
		
		emRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(emRoverTemp, currentDay);
		inServiceMissions.enqueue(mMissionTemp, -1 * mMissionTemp->getEndDay());
		unavailableRovers.enqueue(emRoverTemp, -1 * mMissionTemp->getEndDay());
		return true;
	}

	// check the maintainance Rovers
	Rover* generalTemp;
	if (!unAvailableMaintainanceMountainous.isEmpty())
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
		mountainousWaitingMission.remove(1);
		
		generalTemp = getFastestRover(&unAvailableMaintainanceMountainous);
		generalTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(mMissionTemp, -1 * mMissionTemp->getEndDay());
		unavailableRovers.enqueue(generalTemp, -1 * mMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainanceEmergency.isEmpty())
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
		mountainousWaitingMission.remove(1);
		generalTemp = getFastestRover(&unAvailableMaintainanceEmergency);
		generalTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(mMissionTemp, -1 * mMissionTemp->getEndDay());

		unavailableRovers.enqueue(generalTemp, -1 * mMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
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
		pRoverTemp->assignMission(pMissionTemp->getID(), pMissionTemp->getMissionDuration(), pMissionTemp->getTargetLocation(), evDay);
		pMissionTemp->assignRover(pRoverTemp, currentDay);
		inServiceMissions.enqueue(pMissionTemp, -1 * pMissionTemp->getEndDay());

		unavailableRovers.enqueue(pRoverTemp, -1 * pMissionTemp->getEndDay());
		return true;
	}

	//check the maintainance Rovers
	Rover* generalTemp;
	if (!unAvailableMaintainancePolar.isEmpty())
	{
		generalTemp = getFastestRover(&unAvailableMaintainancePolar);
		polarWaitingMission.dequeue(pMissionTemp);
		generalTemp->assignMission(pMissionTemp->getID(), pMissionTemp->getMissionDuration(), pMissionTemp->getTargetLocation(), evDay);
		pMissionTemp->assignRover(generalTemp, currentDay);
		inServiceMissions.enqueue(pMissionTemp, -1 * pMissionTemp->getEndDay());
		unavailableRovers.enqueue(generalTemp, -1 * pMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	return false;  //if polar rovers are un available
}

void MarsStation::addToCompletedMission()
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
		if (rV->getneedCheckup())
		{
			rV->assignCheckup(eD);
			unavailableRovers.enqueue(rV, -1*rV->getMissionOrCheckupEndDay());
		}
		else 
		{
			rV->setOutOfCheckup();  //rover is available to be assigned	 
			EmergencyRover* eR = dynamic_cast<EmergencyRover*>(rV);
			MountainousRover* mR = dynamic_cast<MountainousRover*>(rV);
			PolarRover* pR = dynamic_cast<PolarRover*>(rV);
			if (rV->getneedMaintainance())
			{
				rV->assignMaintainance(eD);
				if (eR)
					unAvailableMaintainanceEmergency.insert(unAvailableMaintainanceEmergency.getLength() + 1, eR);
				else if (mR)
					unAvailableMaintainanceMountainous.insert(unAvailableMaintainanceMountainous.getLength() + 1, mR);
				else
					unAvailableMaintainancePolar.insert(unAvailableMaintainancePolar.getLength() + 1, pR);

			}
			else
			{
				if (eR)
					emergencyAvailableRover.enqueue(eR, eR->getSpeed());
				else if (mR)
					mountainousAvailableRover.enqueue(mR, mR->getSpeed());
				else if(pR)
					polarAvailableRover.enqueue(pR, pR->getSpeed());

				//rV->setOutOfCheckup();  //rover is available to be assigned	    
			}
			
		}
		Found = unavailableRovers.peek(rV);
	}
}

bool MarsStation::isCompleted(int eD)
{
	Mission* mTemp = nullptr;
	bool Found = inServiceMissions.peek(mTemp);
	if (Found && mTemp->getEndDay() <= eD) // check if there is a mission in IN-Ex. 
		return true;
	return false;
}
