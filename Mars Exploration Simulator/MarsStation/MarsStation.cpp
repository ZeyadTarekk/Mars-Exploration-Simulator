#include "MarsStation.h"

MarsStation::MarsStation():currentDay(0)
{
}

MarsStation::~MarsStation()
{
}
void MarsStation::addMission(Mission*nM) //add new mission im the appropriate function
{
	EmergencyMission* newMission1 = dynamic_cast<EmergencyMission*>(nM);
	if (newMission1)
	{
		emergencyWaitingMission.enqueue(newMission1,newMission1->getPriority());
		return;
	}
	MountainousMission* newMission2 = dynamic_cast<MountainousMission*>(nM);
	if (newMission2)
	{
		mountainousWaitingMission.insert(mountainousWaitingMission.getLength()+1,*newMission2);
		return;
	}
	PolarMission* newMission3 = dynamic_cast<PolarMission*>(nM);
	if (newMission3)
	{
		polarWaitingMission.enqueue(newMission3);
		return;
	}
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

void MarsStation::PrintMountList()
{
	cout << "Size of mountianous list is : " << mountainousWaitingMission.getLength() << endl;
	for (int i = 0;i < mountainousWaitingMission.getLength();i++)
	{
		std::cout << "\nItem number : " << i + 1 << std::endl;
		std::cout<<"FormulationDay : " << mountainousWaitingMission.getEntry(i + 1).getFormulationDay() << std::endl;
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
