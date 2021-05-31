////#include<iostream>
////#include<fstream>
////#include"..//MarsStation/MarsStation.h"
////#include"CompletionEvent.h"
////#include"../UI/UI.h"
////#include"Assign.h"
////using namespace std;
////int main()
////{
////	//mission
////	EmergencyMission *me = new EmergencyMission(1,1,1,662,1,1);
////	MountainousMission* M = new MountainousMission(1,2,2,2,2,2);
////	PolarMission* p = new PolarMission(1,3,3,3,3);
////
////	//rovers
////	//EmergencyRover* eR = new EmergencyRover(4,4,4);
////	MountainousRover* Mr = new MountainousRover(5, 5, 5);
////	PolarRover* pR = new PolarRover(6, 6, 6);
////
////	//mars-station
////	MarsStation* m = new MarsStation();
////
////	////assign rover to mission
////	//eR->assignMission(1, 1, 1, 1); 
////	//eR->assignCheckup(2); //checkup day 
////
////	
////	//m->addRover(eR);
////	m->addRover(Mr);
////	m->addRover(pR);
////
////	//add emergency in waiting list
////	m->addMission(me);
////	m->addMission(M);
////	m->addMission(p);
////
////	/*execution function
////	m->ExecuteEm(eR);
////	m->Executemount(Mr);
////	m->ExecutePolar(pR);*/
////	//test Assign 
////	Assign* A = new Assign(1);
////	A->execute(m);
////	//complete event has been created
////	int i1 = me->getEndDay();
////	//int i2 = M->getEndDay(); special case
////	int i3 = p->getEndDay();
////	CompletionEvent* C = new CompletionEvent(i1);
////	CompletionEvent* C2 = new CompletionEvent(4);
////	CompletionEvent* C3 = new CompletionEvent(i3);
////
////	//execute complete
////	C->execute(m);
////	C2->execute(m);
////	C3->execute(m);
////	//print unavailable rovers
////	cout << "Unavailable Rovers :" << endl;
////	m->printUnavRovers();
////
////	//print completed mission
////	cout << "====================" << endl;
////	cout << "Completed Mission :" << endl;
////	m->printCompleteMission();
////}
//#include<iostream>
//#include<fstream>
//#include"..//MarsStation/MarsStation.h"
//#include"CompletionEvent.h"
//#include"../UI/UI.h"
//#include"Assign.h"
//using namespace std;
//int main()
//{
//	MarsStation* m = new MarsStation();
//
//	//mission
//	EmergencyMission *Em1 = new EmergencyMission(1,500,1,1,1,20); //3 days
//	EmergencyMission* Em2 = new EmergencyMission(2, 400, 2, 4, 1, 20);// 4 days
//	EmergencyMission* Em3 = new EmergencyMission(1, 450, 3, 7, 1, 20); // 5 days 
//	EmergencyMission* Em4 = new EmergencyMission(1, 540, 4, 10, 1, 20); // 7 days
//	//EmergencyMission* Em5 = new EmergencyMission(1, 620, 1, 13, 1, 20); // 4 days
//	//***********************************************************
//	//MountainousMission* M1 = new MountainousMission(3,750,2, 2, 2, 6);
//	//MountainousMission* M2 = new MountainousMission(2, 450, 2, 5,2 ,8);
//	///***********************************************************
//	PolarMission* P1 = new PolarMission(1, 600, 3, 3, 3);
//	PolarMission* P2 = new PolarMission(1, 550, 3, 3, 3);
//	//************************************
//	//rovers
//	EmergencyRover* eR = new EmergencyRover(20, 4, 4);
//	m->addRover(eR);
//	//*********************
//	m->addMission(Em1);
//	m->addMission(Em2);
//	m->addMission(Em3);
//	m->addMission(Em4);
//	//m->addMission(Em5);
//	//m->addMission(M1);
//	//m->addMission(M2);
//	m->addMission(P1);
//	m->addMission(P2);
//	//**************************
//	// day 3
//	CompletionEvent* completionarray[100];
//	Assign* assignarray[100];
//
//	for (int i = 0; i < 100; i++)
//	{
//		assignarray[i] = new  Assign(i+1);
//		assignarray[i]->execute(m);
//		completionarray[i] = new CompletionEvent(i + 1);
//		completionarray[i]->execute(m);
//	}
//
//
//
//	/*MountainousMission* M = new MountainousMission(1, 2, 2, 2, 2, 2);
//	PolarMission* p = new PolarMission(1, 3, 3, 3, 3);
//	EmergencyMission* me = new EmergencyMission(1, 1, 1, 662, 1, 1);
//	MountainousMission* M = new MountainousMission(1, 2, 2, 2, 2, 2);
//	PolarMission* p = new PolarMission(1, 3, 3, 3, 3);
//	EmergencyMission* me = new EmergencyMission(1, 1, 1, 662, 1, 1);
//	MountainousMission* M = new MountainousMission(1, 2, 2, 2, 2, 2);
//	PolarMission* p = new PolarMission(1, 3, 3, 3, 3);
//	EmergencyMission* me = new EmergencyMission(1, 1, 1, 662, 1, 1);
//	MountainousMission* M = new MountainousMission(1, 2, 2, 2, 2, 2);
//	PolarMission* p = new PolarMission(1, 3, 3, 3, 3);*/
//
//	
//	/*MountainousRover* Mr = new MountainousRover(5, 5, 5);
//	PolarRover* pR = new PolarRover(6, 6, 6);*/
//
//	//mars-station
//	
//
//	////assign rover to mission
//	//eR->assignMission(1, 1, 1, 1); 
//	//eR->assignCheckup(2); //checkup day 
//
//	
//	
//	/*m->addRover(Mr);
//	m->addRover(pR);*/
//
//	//add emergency in waiting list
//	
//	/*execution function
//	m->ExecuteEm(eR);
//	//m->Executemount(Mr);
//	m->ExecutePolar(pR);*/
//	//test Assign 
//	
//	//complete event has been created
//	/*int i1 = me->getEndDay();*/
//	//int i2 = M->getEndDay(); special case
//	/*int i3 = p->getEndDay();*/
//	/*CompletionEvent* C2 = new CompletionEvent(4);
//	CompletionEvent* C3 = new CompletionEvent(i3);*/
//
//	
//	//print unavailable rovers
//	cout << "Unavailable Rovers :" << endl;
//	m->printUnavRovers();
//	//print completed mission
//	cout << "====================" << endl;
//	cout << "Completed Mission :" << endl;
//	m->printCompleteMission();
//	cout << eR->getMaintainance() << endl;
//}
