#include "UI.h"
#include<Windows.h>
void UI::calcAvgSpeed()
{
	for (int i = 0; i < mountRoverCount; i++)
		avgSpeed += mountSpeed[i];
	for (int i = 0; i < polRoverCount; i++)
		avgSpeed += polSpeed[i];
	for (int i = 0; i < emRoverCount; i++)
		avgSpeed += emSpeed[i];
	avgSpeed /= (mountRoverCount + emRoverCount + polRoverCount);
}

void UI::read()
{
	string Filename;
	cout << "Please enter the name of the input file without the extention: ";
	cin >> Filename;

	ifstream in;
	in.open("InputFiles/"+Filename+".txt");
	if (!in.is_open())
	{
		cout << Filename+".txt not found" << endl;
		exit(1);
	}
	int ModeOfOperation;
	cout << "Please choose mode of operation : -" << endl;
	cout << "For interactive mode press 1 :" << endl;
	cout << "For step-by-step mode press 2 :" << endl;
	cout << "For silent mode press any other key :" << endl;
	cin >> ModeOfOperation;
	MStation->setModeOperation(ModeOfOperation);

	in >> mountRoverCount >> polRoverCount >> emRoverCount;
	MStation->setEmRoverCount(emRoverCount);
	MStation->setMountRoverCount(mountRoverCount);
	MStation->setPolRoverCount(polRoverCount);
	mountSpeed = new int[mountRoverCount];
	polSpeed = new int[polRoverCount];
	emSpeed = new int[emRoverCount];
	for (int i = 0; i < mountRoverCount; i++)
		in >> mountSpeed[i];
	for (int i = 0; i < polRoverCount; i++)
		in >> polSpeed[i];
	for (int i = 0; i < emRoverCount; i++)
		in >> emSpeed[i];
	in >> checkCount >> mountCheck >> polCheck >> emCheck;

	createRovers();
	calcAvgSpeed();
	MStation->setAvgSpeed(avgSpeed);
	in >> autoPromLimit;
	MStation->setAutoPromot(autoPromLimit);

	in >> NoEvents;
	MStation->setEventCount(NoEvents);
	for (int i = 0; i < NoEvents; i++)
	{
		in >> eventType;
		//cout << eventType << endl;
		switch (eventType)
		{
		case 'F':
		{
			in >> missionType >> eventDay >> ID >> location >> duration >> signifiance;
			//cout << missionType << " " << eventDay << " " << ID << " " << location << " " << duration << " " << signifiance << endl;
			MStation->createFormEvent(missionType, eventDay, ID, location, duration, signifiance);
			break;
		}
		case 'X':
		{
			in >> eventDay >> ID;
			MStation->createCancelEvent(eventDay, ID);
			break;
		}
		case 'P':
		{
			in >> eventDay >> ID;
			MStation->createPromotEvent(eventDay, ID);
			break;
		}
		}
	}
	in.close();
}



void UI::createRovers()
{
	for (int i = 0; i < mountRoverCount; i++)
		MStation->createRover('M', mountSpeed[i], checkCount, mountCheck);
	for (int i = 0; i < polRoverCount; i++)
		MStation->createRover('P', polSpeed[i], checkCount, polCheck);
	for (int i = 0; i < emRoverCount; i++)
		MStation->createRover('E', emSpeed[i], checkCount, emCheck);
}


void UI::TestPrint()
{
	cout << mountRoverCount << " " << polRoverCount << " " << emRoverCount << endl;
	for (int i = 0; i < mountRoverCount; i++)
		cout << mountSpeed[i] << " ";
	cout << endl;
	for (int i = 0; i < polRoverCount; i++)
		cout << polSpeed[i] << " ";
	cout << endl;
	for (int i = 0; i < emRoverCount; i++)
		cout << emSpeed[i] << " ";
	cout << endl;
	cout << checkCount << " " << mountCheck << " " << polCheck << " " << emCheck << endl;
	cout << autoPromLimit << endl;
	cout << NoEvents << endl;
}

void UI::printDay()
{
//	int n;
	//cout << "Please select the mode\n1 for Interactive Mode\n2 for Step-By-Step Mode\n3 for Silent Mode\n";
	//cin >> n;
	//int no = currentDay;
	EmergencyMission* emMission;
	//MountainousMission mountMission(0, 0, 0, 0, 0, 0);
	PolarMission* polarMission;
	Mission* tempMission;
	Rover* tempRover;
	EmergencyRover* emRover;
	PolarRover* polarRover;
	MountainousRover* mountRover;
	
		//while (true)
		//{
			//waiting
			PriorityQueue<EmergencyMission*>tempEmergencyWaitingMission =MStation-> emergencyWaitingMission;
			List<MountainousMission>tempMountainousWaitingMission = MStation->mountainousWaitingMission;
			Queue<PolarMission*>tempPolarWaitingMission = MStation->polarWaitingMission;
			// 3) Execution (In-service) missions
			PriorityQueue<Mission*>tempInServiceMissions = MStation->inServiceMissions;
			//available rovers
			PriorityQueue<EmergencyRover*>tempEmergencyAvailableRover = MStation->emergencyAvailableRover;
			PriorityQueue<PolarRover*>tempPolarAvailableRover = MStation->polarAvailableRover;
			PriorityQueue<MountainousRover*>tempMountainousAvailableRover = MStation->mountainousAvailableRover;
			//2) Unavailable rovers
			PriorityQueue<Rover*>tempUnavailableRovers = MStation->unavailableRovers;
			//completed
			Queue<Mission*> tempCompletedMissions = MStation->completedMissions;
			int no = 0, i = 0, j = 0, k = 0, iEx = 0, jEx = 0, kEx = 0, noEx = 0, noAvRo = 0;
			int arri[100], arrj[100], arrk[100], arriEx[100], arrjEx[100], arrkEx[100], arriExRO[100], arrjExRO[100], arrkExRO[100];
			int iRo = 0, jRo = 0, kRo = 0, noComp = 0, iComp = 0, jComp = 0, kComp = 0;
			int arriRo[100], arrjRo[100], arrkRo[100], arriComp[100], arrjComp[100], arrkComp[100];
			int noCheckup = 0, iCheck = 0, jCheck = 0, kCheck = 0;
			int* arriCheck = new int[MStation->getTotalNoRovers()];
			int* arrjCheck = new int[MStation->getTotalNoRovers()];
			int* arrkCheck = new int[MStation->getTotalNoRovers()];
			cout << "\nCurrent day:" << MStation->currentDay << endl;
			while (tempEmergencyWaitingMission.dequeue(emMission))
			{
				no++;
				arri[i++] = emMission->getID();
			}
			while (!tempMountainousWaitingMission.isEmpty())
			{
				no++;
				arrk[k++] = tempMountainousWaitingMission.getEntry(1).getID();
				tempMountainousWaitingMission.remove(1);
			}
			while (tempPolarWaitingMission.dequeue(polarMission))
			{
				no++;
				arrj[j++] = polarMission->getID();
			}
			cout << no << " Waiting missions:";
			if (i != 0)
			{
				cout << " [" << arri[0];
				for (int im = 1; im < i; im++)
					cout << ',' << arri[im];
				cout << "] ";
			}

			if (j != 0)
			{
				cout << '(' << arrj[0];
				for (int ip = 1; ip < j; ip++)
					cout << ',' << arrj[ip];
				cout << ')';
			}
			if (k != 0)
			{
				cout << " {" << arrk[0];
				for (int imm = 1; imm < k; imm++)
					cout << ',' << arrk[imm];
				cout << '}';
			}
			cout << "\n-------------------------------------------------------\n";
			while (tempInServiceMissions.dequeue(tempMission))
			{
				noEx++;
				if (dynamic_cast<EmergencyMission*>(tempMission) != nullptr)
				{

					arriEx[iEx] = tempMission->getID();
					arriExRO[iEx++] = tempMission->getAssignedRover()->getID();
				}
				else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
				{

					arrjEx[jEx] = tempMission->getID();
					arrjExRO[jEx++] = tempMission->getAssignedRover()->getID();
				}
				else if (dynamic_cast<MountainousMission*>(tempMission) != nullptr)
				{

					arrkEx[kEx] = tempMission->getID();
					arrkExRO[kEx++] = tempMission->getAssignedRover()->getID();
				}
			}
			cout << noEx << " In-Execution Missions/Rovers:";
			if (iEx != 0)
			{
				cout << " [" << arriEx[0] << '/' << arriExRO[0];
				for (int iemex = 1; iemex < iEx; iemex++)
					cout << ',' << arriEx[iemex] << '/' << arriExRO[iemex];
				cout << ']';
			}

			if (jEx != 0)
			{
				cout << " (" << arrjEx[0] << '/' << arrjExRO[0];
				for (int jemex = 1; jemex < jEx; jemex++)
					cout << ',' << arrjEx[jemex] << '/' << arrjExRO[jemex];
				cout << ')';
			}

			if (kEx != 0)
			{
				cout << " {" << arrkEx[0] << '/' << arrkExRO[0];
				for (int kemex = 1; kemex < kEx; kemex++)
					cout << ',' << arrkEx[kemex] << '/' << arrkExRO[kemex];
				cout << "} ";
			}
			cout << "\n-------------------------------------------------------\n";
			while (tempEmergencyAvailableRover.dequeue(emRover))
			{
				noAvRo++;
				arriRo[iRo++] = emRover->getID();
			}
			while (tempPolarAvailableRover.dequeue(polarRover))
			{
				noAvRo++;
				arrjRo[jRo++] = polarRover->getID();
			}
			while (tempMountainousAvailableRover.dequeue(mountRover))
			{
				noAvRo++;
				arrkRo[kRo++] = mountRover->getID();
			}
			cout << noAvRo << " Available Rovers : ";
			if (iRo != 0)
			{
				cout << "[" << arriRo[0];
				for (int avEm = 1; avEm < iRo; avEm++)
					cout << ',' << arriRo[avEm];
				cout << "] ";
			}

			if (jRo != 0)
			{
				cout << "(" << arrjRo[0];
				for (int avEm = 1; avEm < jRo; avEm++)
					cout << ',' << arrjRo[avEm];
				cout << ") ";
			}

			if (kRo != 0)
			{
				cout << "{" << arrkRo[0];
				for (int avEm = 1; avEm < kRo; avEm++)
					cout << ',' << arrkRo[avEm];
				cout << "} ";
			}
			cout << "\n-------------------------------------------------------\n";
			while (tempUnavailableRovers.dequeue(tempRover))
			{
				if (tempRover->getRoverInCheckup() == true)
				{
					noCheckup++;
					if (dynamic_cast<EmergencyRover*>(tempRover) != nullptr)
						arriCheck[iCheck++] = tempRover->getID();
					if (dynamic_cast<PolarRover*>(tempRover) != nullptr)
						arrjCheck[jCheck++] = tempRover->getID();
					if (dynamic_cast<MountainousRover*>(tempRover) != nullptr)
						arrkCheck[kCheck++] = tempRover->getID();
				}

			}
			cout << noCheckup << " In-Checkup Rovers: ";
			if (iCheck != 0)
			{

				cout << '[' << arriCheck[0];
				for (int i = 1; i < iCheck; i++)
				{
					cout << ',' << arriCheck[i];
				}
				cout << "] ";
			}

			if (jCheck != 0)
			{
				cout << '(' << arrjCheck[0];
				for (int i = 1; i < jCheck; i++)
				{
					cout << ',' << arrjCheck[i];
				}
				cout << ") ";
			}
			
			if (kCheck != 0)
			{
				cout << '{' << arrkCheck[0];
				for (int i = 1; i < kCheck; i++)
				{
					cout << ',' << arrkCheck[i];
				}
				cout << "} ";
			}




			cout << "\n-------------------------------------------------------\n";
			while (tempCompletedMissions.dequeue(tempMission))
			{
				noComp++;
				if (dynamic_cast<EmergencyMission*>(tempMission) != nullptr)
					arriComp[iComp++] = tempMission->getID();
				else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
					arrjComp[jComp++] = tempMission->getID();
				else if (dynamic_cast<MountainousMission*>(tempMission) != nullptr)
					arrkComp[kComp++] = tempMission->getID();
			}
			cout << noComp << " Completed Missions:";
			if (kComp != 0)
			{
				cout << " {" << arrkComp[0];
				for (int compIter = 1; compIter < kComp; compIter++)
					cout << ',' << arrkComp[compIter];
				cout << '}';
			}
			if (iComp != 0)
			{
				cout << " [" << arriComp[0];
				for (int compIter = 1; compIter < iComp; compIter++)
					cout << ',' << arriComp[compIter];
				cout << ']';
			}
			if (jComp != 0)
			{
				cout << " (" << arrjComp[0];
				for (int compIter = 1; compIter < jComp; compIter++)
					cout << ',' << arrjComp[compIter];
				cout << ')';
			}


			//o << "zeyadwwww";




			//currentDay++;
		//	Sleep(3000);
		


	//}
}

void UI::outputFile()
{
	ofstream out;
	Mission* tempMission;
	out.open("OutputFiles/Output.txt");
	out << "CD\tID\tFD\tWD\tED\n";
	while (MStation->completedMissions.dequeue(tempMission))
	{
		totalMissions++;
		if (dynamic_cast<EmergencyMission*>(tempMission) != nullptr)
			totalEmMissions++;
		else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
			totalPolarMissions++;
		else if (dynamic_cast<PolarMission*>(tempMission) != nullptr)
			totalMountMissions++;

		out << tempMission->getEndDay() << '\t' << tempMission->getID() << '\t' << tempMission->getFormulationDay();
		out << '\t' << tempMission->getExecutionDay() - tempMission->getFormulationDay() << '\t';
		out << tempMission->getEndDay() - tempMission->getExecutionDay() << endl;
		totalWaitingDays += tempMission->getExecutionDay() - tempMission->getFormulationDay();
		totalExecutionDays += tempMission->getEndDay() - tempMission->getExecutionDay();
	}
	out << "Missions: " << totalMissions << "[M:" << totalMountMissions << ", P:" << totalPolarMissions << ", E:" << totalEmMissions << "]\n";
	out << "Rovers: " << MStation->getTotalNoRovers() << "[M:" << MStation->getMountRoverCount() << ", P:" << MStation->getPolRoverCount() << ", E:" << MStation->getEmRoverCount() << "]\n";
	out << "Avg Wait = " << float(totalWaitingDays) / totalMissions;
	out << ", Avg Exec = " << float(totalExecutionDays) / totalMissions << endl;

	out.close();
}

UI::UI(MarsStation* MS) :MStation(MS)
{
	read();
	totalMissions = 0;
	totalWaitingDays = 0;
	totalExecutionDays = 0;
	totalEmMissions = 0;
	totalPolarMissions = 0;
	totalMountMissions = 0;
}



UI::~UI() {}
