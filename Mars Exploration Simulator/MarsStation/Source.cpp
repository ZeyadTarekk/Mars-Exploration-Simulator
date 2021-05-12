#include<iostream>
#include"../MarsStation/MarsStation.h"
#include"../Events/PromotionEvent.h"
#include"../Events/FormulationEvent.h"
using namespace std;
int main()
{
	MarsStation* m = new MarsStation;
	FormulationEvent f1(1, 1, 'M', 1, 1, 1);
	FormulationEvent f2(2, 2, 'M', 2, 2, 2);
	f1.execute(m);f2.execute(m);
	PromotionEvent Pevent(1,-1);
	cout << "\nMountainous before promotion" << endl;
	m->PrintMountList();
	Pevent.execute(m);
	cout << "\nMountainous After promotion" << endl;
	m->PrintMountList();
	cout << "\nEmergency After promotion" << endl;
	m->PrintEmergencyList();
	return 0;
}