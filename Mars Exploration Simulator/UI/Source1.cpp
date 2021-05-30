//#include<iostream>
//#include<fstream>
//#include"UI.h"
//#include"../MarsStation/MarsStation.h"
//#include"../Events/Assign.h"
//using namespace std;
//int main()
//{
//
//	MarsStation *MS = new MarsStation();
//	UI u(MS);
//	
//	//Mission* emMission=new EmergencyMission()
//
//	Rover* emRover = new PolarRover(0, 0, 0);
////	emRover->assignCheckup(0);
//
//	Rover* emRover1 = new PolarRover(0, 0, 0);
//	//emRover1->assignCheckup(0);
//
//	Rover* emRover2 = new MountainousRover(0, 0, 0);
////	emRover2->assignCheckup(0);
//
//	Rover* emRover3 = new MountainousRover(0, 0, 0);
//	//emRover3->assignCheckup(0);
//
//	Rover* emRover4 = new EmergencyRover(0, 0, 0);
//	//emRover4->assignCheckup(0);
//	//MS->ExecuteEm(emRover4);
//
//
//	/*MS->addUnavailableRover(emRover);
//	MS->addUnavailableRover(emRover1);
//	MS->addUnavailableRover(emRover2);
//	MS->addUnavailableRover(emRover3);
//	MS->addUnavailableRover(emRover4);*/
//	Assign* as = new Assign(1);
//	cout << MS->getAvgSpeed() << endl;
//	cout << "Emergency rovers \n\n";
////	MS->printEmRovers();
//	cout << "\n\nmountainous rovers \n\n";
////	MS->printMountRovers();
//	cout << "\n\Polar rovers \n\n";
//	//MS->printPolarRovers();
//	cout << "\nun av Polar rovers \n\n";
////	MS->printUnavRovers();
//	
//	MS->executeEvents();
//	MS->ExecuteEm(emRover4);
//	MS->CompleteMission();
//	MS->CompleteMission();
//	cout << "\n\nEmergency Missions \n\n";
////	MS->PrintEmergencyList();
//	cout << "\n\nmount Missions \n\n";
////	MS->PrintMountList();
//	cout << "\n\nPolar Missions \n\n";
////	MS->printPolarList();
//	cout << "No of Em Rovers : " << MS->getEmRoverCount() << endl;
//	cout << "No of mount Rovers  : " << MS->getMountRoverCount() << endl;
//	cout << "No of Pol Rovers  : " << MS->getPolRoverCount() << endl;
//	cout << "No of event : " << MS->getEventCount() << endl;
//	cout << "No of Total Rovers  : " << MS->getTotalNoRovers() << endl;
//	cout << "Mode of operation :" << ((MS->getModeOperation() == Interactive) ? "Interactve" :
//		(MS->getModeOperation() == step_by_step) ? "step_by_step":
//		(MS->getModeOperation() == silent) ? "silent" : "Error");
//	//as->execute(MS);
//	u.printDay();
////	u.outputStart();
//	
//	u.outputFile();
//	return 0;
//}
////ofstream out;
////out.open("OutputFiles/Output.txt");
////if (out.is_open())
////	out << "Hello" << endl;
////else
////	cout << "Error";
////ifstream in("InputFiles/Input.txt");
////int x;
////in >> x;
////cout << "X = " << x<<" ";
////in >> x;
////cout << "X = " << x << " ";