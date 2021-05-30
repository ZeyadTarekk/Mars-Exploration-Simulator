#include<iostream>
#include<fstream>
#include"..//MarsStation/MarsStation.h"
#include"CompletionEvent.h"
#include"../UI/UI.h"
#include"Assign.h"
using namespace std;
int main()
{
	//mission
	EmergencyMission *me = new EmergencyMission(1,1,1,662,1,1);
	MountainousMission* M = new MountainousMission(1,2,2,2,2,2);
	PolarMission* p = new PolarMission(1,3,3,3,3);

	//rovers
	//EmergencyRover* eR = new EmergencyRover(4,4,4);
	MountainousRover* Mr = new MountainousRover(5, 5, 5);
	PolarRover* pR = new PolarRover(6, 6, 6);

	//mars-station
	MarsStation* m = new MarsStation();

	////assign rover to mission
	//eR->assignMission(1, 1, 1, 1); 
	//eR->assignCheckup(2); //checkup day 

	
	//m->addRover(eR);
	m->addRover(Mr);
	m->addRover(pR);

	//add emergency in waiting list
	m->addMission(me);
	m->addMission(M);
	m->addMission(p);

	/*execution function
	m->ExecuteEm(eR);
	m->Executemount(Mr);
	m->ExecutePolar(pR);*/
	//test Assign 
	Assign* A = new Assign(1);
	A->execute(m);
	//complete event has been created
	int i1 = me->getEndDay();
	//int i2 = M->getEndDay(); special case
	int i3 = p->getEndDay();
	CompletionEvent* C = new CompletionEvent(i1);
	CompletionEvent* C2 = new CompletionEvent(4);
	CompletionEvent* C3 = new CompletionEvent(i3);

	//execute complete
	C->execute(m);
	C2->execute(m);
	C3->execute(m);
	//print unavailable rovers
	cout << "Unavailable Rovers :" << endl;
	m->printUnavRovers();

	//print completed mission
	cout << "====================" << endl;
	cout << "Completed Mission :" << endl;
	m->printCompleteMission();
}
