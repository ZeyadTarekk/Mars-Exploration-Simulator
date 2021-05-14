#include<iostream>
#include<fstream>
#include"UI.h"
#include"../MarsStation/MarsStation.h"
using namespace std;
int main()
{
	MarsStation *MS = new MarsStation();
	UI u(MS);
	cout << "Emergency rovers \n\n";
	MS->printEmRovers();
	cout << "\n\nmountainous rovers \n\n";
	MS->printMountRovers();
	cout << "\n\Polar rovers \n\n";
	MS->printPolarRovers();
	
	MS->executeEvents();
	cout << "\n\nEmergency Missions \n\n";
	MS->PrintEmergencyList();
	cout << "\n\nmount Missions \n\n";
	MS->PrintMountList();
	cout << "\n\nPolar Missions \n\n";
	MS->printPolarList();
	return 0;
}
//ofstream out;
//out.open("OutputFiles/Output.txt");
//if (out.is_open())
//	out << "Hello" << endl;
//else
//	cout << "Error";
//ifstream in("InputFiles/Input.txt");
//int x;
//in >> x;
//cout << "X = " << x<<" ";
//in >> x;
//cout << "X = " << x << " ";