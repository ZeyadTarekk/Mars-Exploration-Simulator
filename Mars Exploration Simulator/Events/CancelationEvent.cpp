#include "CancelationEvent.h"

CancelationEvent::CancelationEvent(int day, int i): Event(day)
{
	id = i;
}

void CancelationEvent::execute(MarsStation* mStation)
{
	MountainousMission mountMission(0, 0, 0, id, 0, 0);
	int indexOfMission = mStation->IndexOfMountainousMission(mountMission);
	if (indexOfMission != -1)
		mStation->removeMountainousMission(indexOfMission);
}

CancelationEvent::~CancelationEvent()
{
}
