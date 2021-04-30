//#include<iostream>
////=====================================================
////             testing DataStructures                 = 
////=====================================================
//#include"PriorityQueue.h"
//#include"Queue.h"
//#include"Stack.h"
//using namespace std;
//int main()
//{
//	//=====================================================
//	//             testing PriorityQueue                  = 
//	//=====================================================
//	PriorityQueue<int> pQ1;
//	cout << pQ1.isEmpty() << endl;
//	pQ1.enqueue(5, 1);
//	pQ1.enqueue(12, 5);
//	pQ1.enqueue(6, 2);
//	pQ1.enqueue(9, 3); // 12-> 9 -> 6 -> 5
//	PriorityQueue<int> pQ2(pQ1);
//
//	int x;
//	pQ2.peek(x);
//	cout << x << endl;
//	pQ1.peek(x);
//	cout << x << endl; //12 
//	pQ1.dequeue(x);
//	cout << x << endl; //12
//	pQ1.dequeue(x);
//	cout << x << endl; //9
//	pQ1.dequeue(x);
//	cout << x << endl; // 6
//	pQ1.dequeue(x);
//	cout << x << endl;  //5
//	int y;
//	pQ1.dequeue(y);  // pQueue is Empty  so it returns false only and y is garbage
//	cout << y << endl;
//
//
//	//=====================================================
//	//             testing Queue                          = 
//	//=====================================================
//	Queue <int> q1;
//	cout << q1.isEmpty() << endl;
//	q1.enqueue(11);
//	q1.enqueue(2);
//	q1.enqueue(5);
//	q1.enqueue(12); // 11 -> 2 -> 5 -> 12 
//	Queue<int>q2(q1);
//    int z;
//	//q2 = q1;
//	q2.peek(z);
//	cout << z << endl;
//	q1.dequeue(z);
//	cout << z << endl; // 11
//	q1.dequeue(z);
//	cout << z << endl; // 2 
//	q1.dequeue(z);
//	cout << z << endl; // 5 
//	q1.dequeue(z);
//	cout << z << endl; // 12
//
//
//	return 0;
//}