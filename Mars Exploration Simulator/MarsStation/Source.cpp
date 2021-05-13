#include<iostream>
#include"../MarsStation/MarsStation.h"
#include"../Events/PromotionEvent.h"
#include"../Events/FormulationEvent.h"
#include"../Events/CancelationEvent.h"
using namespace std;
int main()
{
	MarsStation* m = new MarsStation;
	FormulationEvent f1(1, 1, 'M', 1, 1, 1);
	FormulationEvent f2(2, 2, 'M', 2, 2, 2);
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

	FormulationEvent f3(6, 3, 'M', 1, 1, 1);
	FormulationEvent f4(7, 4, 'M', 2, 2, 2);
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