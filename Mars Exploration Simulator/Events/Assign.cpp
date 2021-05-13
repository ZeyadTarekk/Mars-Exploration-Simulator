#include"Assign.h"


//constructor
Assign::Assign(int eV) :Event(eV)
{}  

//destructor
Assign::~Assign() {}


//execute
void Assign::execute(MarsStation* ms)
{
	while (ms->assignEmergencyMission(getEventDay()));
	while (ms->assignMountainousMission(getEventDay()));
	while (ms->assignPolarMission(getEventDay()));
}