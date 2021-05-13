#include<iostream>
#include"../MarsStation/MarsStation.h"
#include"../Events/PromotionEvent.h"
#include"../Events/FormulationEvent.h"
#include"../Events/MissionFailure.h"
#include"../Missions/EmergencyMission.h"
#include"../Missions/MountainousMission.h"
#include"../Missions/PolarMission.h"
#include"../Rovers/EmergencyRover.h"
#include"../Rovers/MountainousRover.h"
#include"../Rovers/PolarRover.h"
#include"../Events/CancelationEvent.h"
using namespace std;
int main()
{
	MarsStation* MStation = new MarsStation();
	FormulationEvent F[6] = {
			FormulationEvent(1, 1, "M", 1, 1, 1),
			FormulationEvent(2, 2, "M", 2, 2, 2),
			FormulationEvent(3, 3, "EM", 3, 3, 3),
			FormulationEvent(4, 4, "EM", 4, 4, 4),
			FormulationEvent(5, 5, "P", 5, 5, 5),
			FormulationEvent(6, 6, "P", 6, 6, 6)
	};
	for (int i = 0;i < 6;i++)
		F[i].execute(MStation);
	PolarRover p1(11, 11, 11);
	MountainousRover m1(22, 22, 22);
	EmergencyRover em1(33, 33, 33);
	MStation->addRover(&p1);
	MStation->addRover(&m1);
	MStation->addRover(&em1);

	MStation->ExecutePolar(&p1);
	MStation->Executemount(&m1);
	MStation->ExecuteEm(&em1);
	
	MissionFailure MFail1(2);
	MFail1.execute(MStation);
	
	cout << "*****Emergency List********" << endl;
	MStation->PrintEmergencyList();
	cout << "*****Mountainous List********" << endl;
	MStation->PrintMountList();
	cout << "*****polar List********" << endl;
	MStation->printPolarList();
	cout << "*****Inservice List********" << endl;
	MStation->printInserviceMissions();
	
	cout << "*****mount Rover List********" << endl;
	MStation->printMountRovers();
	cout << "*****EM Rover List********" << endl;
	MStation->printEmRovers();
	cout << "*****polar Rover List********" << endl;
	MStation->printPolarRovers();
	cout << "*****Unavailable Rover List********" << endl;
	MStation->printUnavRovers();

	
	MarsStation* m = new MarsStation;
	FormulationEvent f1(1, 1, "M", 1, 1, 1);
	FormulationEvent f2(2, 2, "M", 2, 2, 2);
	f1.execute(m);f2.execute(m);
	PromotionEvent Pevent(1,2);

	cout << "\nMountainous before promotion" << endl;
	m->PrintMountList();
	Pevent.execute(m);
	cout << "\nMountainous After promotion" << endl;
	m->PrintMountList();
	cout << "\nEmergency After promotion" << endl;
	m->PrintEmergencyList();

	cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Testing Cancelation\n";

	FormulationEvent f3(6, 3, "M", 1, 1, 1);
	FormulationEvent f4(7, 4, "M", 2, 2, 2);
	f3.execute(m);
	f4.execute(m);
	CancelationEvent cEvent(3, 3);
	CancelationEvent cEvent2(3, 3);
	cout << "\nMountainous before promotion" << endl;
	m->PrintMountList();
	cEvent.execute(m);
	cEvent2.execute(m);
	cout << "\nMountainous After cancelation" << endl;
	m->PrintMountList();
	CancelationEvent cEvent3(3, 4);
	cEvent3.execute(m);
	m->PrintMountList();
	return 0;
}
//Test Promotion
	//MarsStation* m = new MarsStation;
	//FormulationEvent f1(1, 1, 'M', 1, 1, 1);
	//FormulationEvent f2(2, 2, 'M', 2, 2, 2);
	//f1.execute(m);f2.execute(m);
	//PromotionEvent Pevent(1,-1);
	//cout << "\nMountainous before promotion" << endl;
	//m->PrintMountList();
	//Pevent.execute(m);
	//cout << "\nMountainous After promotion" << endl;
	//m->PrintMountList();
	//cout << "\nEmergency After promotion" << endl;
	//m->PrintEmergencyList();