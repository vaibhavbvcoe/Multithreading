// synchoronization.cpp : Defines the entry point for the console application.
//

/*
this is the sample code to demonstrate the synchorinization using the CRITICAL SECTION.

Thread 1 would PRINT ODD NO
Thread 2 would PRINT EVEN NO
*/
#include "stdafx.h"
#include<Windows.h>
#include<iostream>
using namespace std;

HANDLE hellowrd[2];
HANDLE Th[2];
HANDLE mutex;

CRITICAL_SECTION cs;
int i=0;

DWORD WINAPI ThreadFun1( LPVOID n )
{
	while(i< 100)
	{
		EnterCriticalSection(&cs);
		if(i%2 !=0 )
		{
			std::cout<<" thread id is " <<GetCurrentThreadId() <<" Odd no " << i++<<std::endl;		
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI ThreadFun2( LPVOID n )
{
	while(i< 100)
	{
		EnterCriticalSection(&cs);
		if(i%2==0)
		{	std::cout<<" thread id is " <<GetCurrentThreadId() <<" Even no " << i++<<std::endl;
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{

	//InitializeCriticalSection(&cs);
	InitializeCriticalSectionAndSpinCount(&cs,0x000004000);


	DWORD Id[2];

	Th[0] = CreateThread ( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun1,0,0,&Id[0] );


	Th[1] = CreateThread ( NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun2,0,0,&Id[1] );

	WaitForMultipleObjects(2,Th,TRUE,INFINITE);
	DeleteCriticalSection(&cs);	

	return 0;
}

