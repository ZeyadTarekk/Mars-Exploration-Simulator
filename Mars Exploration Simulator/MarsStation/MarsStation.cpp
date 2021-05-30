#include "MarsStation.h"
#include<fstream>
#include<Windows.h>
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

MarsStation::MarsStation() :currentDay(0)
{
	avgSpeed = 0;
	mountRoverNo = 0;
	emRoverNo = 0;
	polRoverNo = 0;
	eventCount = 0;
	autoPromot = 0;
}

MarsStation::~MarsStation()
{
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

		emergencyWaitingMission.enqueue(PromotedMission,PromotedMission->getPriority());
		mountainousWaitingMission.remove(1);
		if (mountainousWaitingMission.isEmpty())
			return;
		mtemp = new MountainousMission(mountainousWaitingMission.getEntry(1));
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

//void MarsStation::printOutput(ofstream& o)
//{
//	int n;
//	cout << "Please select the mode\n1 for Interactive Mode\n2 for Step-By-Step Mode\n3 for Silent Mode\n";
//	cin >> n;
//	//int no = currentDay;
//	EmergencyMission* emMission;
//	//MountainousMission mountMission(0, 0, 0, 0, 0, 0);
//	PolarMission* polarMission;
//	Mission* tempMission;
//	EmergencyRover* emRover;
//	PolarRover* polarRover;
//	MountainousRover* mountRover;
//	if (n == 2)
//	{
//		while (true)
//		{
//			//waiting
//			PriorityQueue<EmergencyMission*>tempEmergencyWaitingMission = emergencyWaitingMission;
//			List<MountainousMission>tempMountainousWaitingMission = mountainousWaitingMission;
//			Queue<PolarMission*>tempPolarWaitingMission = polarWaitingMission;
//			// 3) Execution (In-service) missions
//			PriorityQueue<Mission*>tempInServiceMissions = inServiceMissions;
//			//available rovers
//			PriorityQueue<EmergencyRover*>tempEmergencyAvailableRover = emergencyAvailableRover;
//			PriorityQueue<PolarRover*>tempPolarAvailableRover = polarAvailableRover;
//			PriorityQueue<MountainousRover*>tempMountainousAvailableRover = mountainousAvailableRover;
//			//2) Unavailable rovers
//			PriorityQueue<Rover*>tempUnavailableRovers = unavailableRovers;
//
//			int no = 0, i = 0, j = 0, k = 0, iEx = 0, jEx = 0, kEx = 0, noEx = 0, noAvRo = 0;
//			int arri[100], arrj[100], arrk[100], arriEx[100], arrjEx[100], arrkEx[100], arriExRO[100], arrjExRO[100], arrkExRO[100];
//			int iRo = 0, jRo = 0, kRo = 0, noComp = 0, iComp = 0, jComp = 0, kComp = 0;
//			int arriRo[100], arrjRo[100], arrkRo[100], arriComp[100], arrjComp[100], arrkComp[100];
//
//			cout << "Current day:" << currentDay << endl;
//			while (tempEmergencyWaitingMission.dequeue(emMission))
//			{
//				no++;
//				arri[i++] = emMission->getID();
//			}
//			while (!tempMountainousWaitingMission.isEmpty())
//			{
//				no++;
//				arrk[k++] = tempMountainousWaitingMission.getEntry(1).getID();
//				tempMountainousWaitingMission.remove(1);
//			}
//			while (tempPolarWaitingMission.dequeue(polarMission))
//			{
//				no++;
//				arrj[j++] = polarMission->getID();
//			}
//			cout << no << " Waiting missions:";
//			if (i != 0)
//			{
//				cout << " [" << arri[0];
//				for (int im = 1; im < i; im++)
//					cout << ',' << arri[im];
//				cout << "] ";
//			}
//
//			if (j != 0)
//			{
//				cout << '(' << arrj[0];
//				for (int ip = 1; ip < j; ip++)
//					cout << ',' << arrj[ip];
//				cout << ')';
//			}
//			if (k != 0)
//			{
//				cout << " {" << arrk[0];
//				for (int imm = 1; imm < k; imm++)
//					cout << ',' << arrk[imm];
//				cout << '}';
//			}
//			cout << "\n-------------------------------------------------------\n";
//			while (tempInServiceMissions.dequeue(tempMission))
//			{
//				noEx++;
//				if (dynamic_cast<EmergencyMission*>(tempMission) != nullptr)
//				{
//
//					arriEx[iEx] = tempMission->getID();
//					arriExRO[iEx++] = tempMission->getAssignedRover()->getID();
//				}
//				else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
//				{
//
//					arrjEx[jEx] = tempMission->getID();
//					arrjExRO[jEx++] = tempMission->getAssignedRover()->getID();
//				}
//				else if (dynamic_cast<MountainousMission*>(tempMission) != nullptr)
//				{
//
//					arrkEx[kEx] = tempMission->getID();
//					arrkExRO[kEx++] = tempMission->getAssignedRover()->getID();
//				}
//			}
//			cout << noEx << " In-Execution Missions/Rovers:";
//			if (iEx != 0)
//			{
//				cout << " [" << arriEx[0] << '/' << arriExRO[0];
//				for (int iemex = 1; iemex < iEx; iemex++)
//					cout << ',' << arriEx[iemex] << '/' << arriExRO[iemex];
//				cout << ']';
//			}
//
//			if (jEx != 0)
//			{
//				cout << " (" << arrjEx[0] << '/' << arrjExRO[0];
//				for (int jemex = 1; jemex < jEx; jemex++)
//					cout << ',' << arrjEx[jemex] << '/' << arrjExRO[jemex];
//				cout << ')';
//			}
//
//			if (kEx != 0)
//			{
//				cout << " {" << arrkEx[0] << '/' << arrkExRO[0];
//				for (int kemex = 1; kemex < kEx; kemex++)
//					cout << ',' << arrkEx[kemex] << '/' << arrkExRO[kemex];
//				cout << "} ";
//			}
//			cout << "\n-------------------------------------------------------\n";
//			while (tempEmergencyAvailableRover.dequeue(emRover))
//			{
//				noAvRo++;
//				arriRo[iRo++] = emRover->getID();
//			}
//			while (tempPolarAvailableRover.dequeue(polarRover))
//			{
//				noAvRo++;
//				arrjRo[jRo++] = polarRover->getID();
//			}
//			while (tempMountainousAvailableRover.dequeue(mountRover))
//			{
//				noAvRo++;
//				arrkRo[kRo++] = mountRover->getID();
//			}
//			cout << noAvRo << " Available Rovers : ";
//			if (iRo != 0)
//			{
//				cout << "[" << arriRo[0];
//				for (int avEm = 1; avEm < iRo; avEm++)
//					cout << ',' << arriRo[avEm];
//				cout << "] ";
//			}
//
//			if (jRo != 0)
//			{
//				cout << "(" << arrjRo[0];
//				for (int avEm = 1; avEm < jRo; avEm++)
//					cout << ',' << arrjRo[avEm];
//				cout << ") ";
//			}
//
//			if (kRo != 0)
//			{
//				cout << "{" << arrkRo[0];
//				for (int avEm = 1; avEm < kRo; avEm++)
//					cout << ',' << arrkRo[avEm];
//				cout << "} ";
//			}
//			cout << "\n-------------------------------------------------------\n";
//
//			cout << "In-Checkup Rovers:";
//
//			cout << "\n-------------------------------------------------------\n";
//			while (completedMissions.dequeue(tempMission))
//			{
//				noComp++;
//				if (dynamic_cast<EmergencyMission*>(tempMission) != nullptr)
//					arriComp[iComp++] = tempMission->getID();
//				else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
//					arrjComp[jComp++] = tempMission->getID();
//				else if (dynamic_cast<MountainousMission*>(tempMission) != nullptr)
//					arrkComp[kComp++] = tempMission->getID();
//			}
//			cout << noComp << " Completed Missions:";
//			if (kComp != 0)
//			{
//				cout << " {" << arrkComp[0];
//				for (int compIter = 1; compIter < kComp; compIter++)
//					cout << ',' << arrkComp[compIter];
//				cout << '}';
//			}
//			if (iComp != 0)
//			{
//				cout << " [" << arriComp[0];
//				for (int compIter = 1; compIter < iComp; compIter++)
//					cout << ',' << arriComp[compIter];
//				cout << ']';
//			}
//			if (jComp != 0)
//			{
//				cout << " (" << arrjComp[0];
//				for (int compIter = 1; compIter < jComp; compIter++)
//					cout << ',' << arrjComp[compIter];
//				cout << ')';
//			}
//			
//
//			while (true)
//			{
//
//			}
//
//
//
//
//
//
//			o << "zeyadwwww";
//
//
//
//
//			currentDay++;
//			Sleep(3000);
//		}
//
//
//	}
//
//
//
//
//
//}



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
		inServiceMissions.enqueue(emMissionTemp,-1*evDay);  // -1*evDay to make the search in complete more easy
		emRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(emRoverTemp, currentDay);
		unavailableRovers.enqueue(emRoverTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}
	MountainousRover* mRoverTemp;
	if (mountainousAvailableRover.dequeue(mRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		inServiceMissions.enqueue(emMissionTemp, -1 * evDay);// -1*evDay to make the search in complete more easy
		mRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(mRoverTemp, currentDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * emMissionTemp->getEndDay());
		return true;
	}
	PolarRover* pRoverTemp;
	if (polarAvailableRover.dequeue(pRoverTemp))
	{
		emergencyWaitingMission.dequeue(emMissionTemp);
		inServiceMissions.enqueue(emMissionTemp, -1 * evDay);// -1*evDay to make the search in complete more easy
		pRoverTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(mRoverTemp, currentDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * emMissionTemp->getEndDay());
		return true;
	}
	// now we will check the lists of maintainance Rovers
	Rover* generalTemp;
	if (!unAvailableMaintainanceEmergency.isEmpty())
	{
		generalTemp= getFastestRover(&unAvailableMaintainanceEmergency);
		emergencyWaitingMission.dequeue(emMissionTemp);
		inServiceMissions.enqueue(emMissionTemp, -1 * evDay);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
		unavailableRovers.enqueue(generalTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainanceMountainous.isEmpty())
	{
		generalTemp = getFastestRover(&unAvailableMaintainanceMountainous);
		emergencyWaitingMission.dequeue(emMissionTemp);
		inServiceMissions.enqueue(emMissionTemp, -1 * evDay);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
		unavailableRovers.enqueue(generalTemp, -1 * emMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainancePolar.isEmpty())
	{
		generalTemp = getFastestRover(&unAvailableMaintainancePolar);
		emergencyWaitingMission.dequeue(emMissionTemp);
		inServiceMissions.enqueue(emMissionTemp, -1 * evDay);
		generalTemp->assignMission(emMissionTemp->getID(), emMissionTemp->getMissionDuration(), emMissionTemp->getTargetLocation(), evDay);
		emMissionTemp->assignRover(generalTemp, currentDay);
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
		inServiceMissions.enqueue(mMissionTemp, -1 * evDay);
		mRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(mRoverTemp, currentDay);
		unavailableRovers.enqueue(mRoverTemp, -1 * mMissionTemp->getEndDay());
		return true;
	}
	EmergencyRover* emRoverTemp;
	if (emergencyAvailableRover.dequeue(emRoverTemp))
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		inServiceMissions.enqueue(mMissionTemp, -1 * evDay);
		emRoverTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(emRoverTemp, currentDay);
		unavailableRovers.enqueue(emRoverTemp, -1 * mMissionTemp->getEndDay());
		return true;
	}

	// check the maintainance Rovers
	Rover* generalTemp;
	if (!unAvailableMaintainanceMountainous.isEmpty())
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		inServiceMissions.enqueue(mMissionTemp, -1 * evDay);
		generalTemp = getFastestRover(&unAvailableMaintainanceMountainous);
		generalTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(generalTemp, currentDay);
		unavailableRovers.enqueue(generalTemp, -1 * mMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
		return true;
	}

	if (!unAvailableMaintainanceEmergency.isEmpty())
	{
		mMissionTemp = new MountainousMission(mountainousWaitingMission.getEntry(mountainousWaitingMission.getLength()));
		mountainousWaitingMission.remove(mountainousWaitingMission.getLength());
		inServiceMissions.enqueue(mMissionTemp, -1 * evDay);
		generalTemp = getFastestRover(&unAvailableMaintainanceEmergency);
		generalTemp->assignMission(mMissionTemp->getID(), mMissionTemp->getMissionDuration(), mMissionTemp->getTargetLocation(), evDay);
		mMissionTemp->assignRover(generalTemp, currentDay);
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
		inServiceMissions.enqueue(pMissionTemp, -1 * evDay);
		pRoverTemp->assignMission(pMissionTemp->getID(), pMissionTemp->getMissionDuration(), pMissionTemp->getTargetLocation(), evDay);
		pMissionTemp->assignRover(pRoverTemp, currentDay);
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
		inServiceMissions.enqueue(pMissionTemp, -1 * evDay);
		unavailableRovers.enqueue(generalTemp, -1 * pMissionTemp->getEndDay()); //due to enqueue rover in order of it's day
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
		if (rV->getneedCheckup())
		{
			rV->assignCheckup(eD);
			unavailableRovers.enqueue(rV, -1*rV->getMissionOrCheckupEndDay());
		}
		else 
		{
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

				rV->setOutOfCheckup();  //rover is available to be assigned	    
			}
			
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
