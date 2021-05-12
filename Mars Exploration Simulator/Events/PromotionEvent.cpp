#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int i, int day):Event(i,day)
{}

PromotionEvent::~PromotionEvent()
{
}

void PromotionEvent::execute(MarsStation* MStation)
{
	MountainousMission mountMission(0, 0, 0,Event::getId(),0);
	int indexOfMission = MStation->IndexOfMountainousMission(mountMission);
	//cout << "Index = " << indexOfMission << endl;
	if (indexOfMission != -1)
	{
		MountainousMission mountMission2 = MStation->getMountainousMission(indexOfMission);
		EmergencyMission* emMission = new EmergencyMission(
			mountMission2.getFormulationDay(),
			mountMission2.getTargetLocation(),
			mountMission2.getMissionDuration(),
			mountMission2.getID(),
			mountMission2.getSignificance());
		MStation->removeMountainousMission(indexOfMission);
		MStation->addMission(emMission);
	}
}
