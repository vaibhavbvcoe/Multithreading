// synchoronization.cpp : Defines the entry point for the console application.
//

/*
this is the sample code to demonstrate the synchorinization using the events.
This program would print the hello word for 100 times.
Thread 1 would print Hello
Thread 2 would print the word
*/
#include "stdafx.h"
#include<Windows.h>
#include<iostream>
using namespace std;

HANDLE hellowrd[2];
DWORD WINAPI ThreadFun1( LPVOID n )
{
	int i=0;
	while(i++<100)
	{
		if(WaitForSingleObject(hellowrd[0],INFINITE)==WAIT_OBJECT_0)
		{
			ResetEvent(hellowrd[0]);
			std::cout<<"Hello ";
			SetEvent(hellowrd[1]);
			//Sleep(1000);
		}
	}
	return 0;
}

DWORD WINAPI ThreadFun2( LPVOID n )
{
	int i=0;
	while(i++<100)
	{
		if(WaitForSingleObject(hellowrd[1],INFINITE)==WAIT_OBJECT_0)
		{
			ResetEvent(hellowrd[1]);
			std::cout << " word"<<std::endl;
			SetEvent(hellowrd[0]);
			//Sleep(1000);
		}
	}
	return 0;
}

HANDLE Th[2];
int _tmain(int argc, _TCHAR* argv[])
{

	
	hellowrd[0] = CreateEvent(NULL,FALSE,FALSE,(LPCWSTR)"Hello ");
	hellowrd[1] = CreateEvent(NULL,FALSE,FALSE,(LPCWSTR)"word");
	
	SetEvent(hellowrd[0]);
	
	DWORD Id[2];
	
	Th[0] = CreateThread ( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun1,0,0,&Id[0] );

	
	Th[1] = CreateThread ( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun2,0,0,&Id[1] );

	WaitForMultipleObjects(2,Th,TRUE,INFINITE);
	
	return 0;
}

