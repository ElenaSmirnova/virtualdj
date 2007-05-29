// CallLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define LENGTH 6 //16384
#define CANALS 2

int (*mainDistortion)(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]);
int (*mainEcho)(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]);

void printArray(int arr[][LENGTH]){
	for (int i=0; i<CANALS; i++){
		for(int j=0; j<LENGTH; j++){
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hEffectsDLL;
	hEffectsDLL=LoadLibrary(L"EffectsDLL");
	if (hEffectsDLL==NULL) throw "EffectsDLL.dll loading error";

	mainDistortion =(int (*) (int highLimit, int lowLimit, int buffer[CANALS][LENGTH]))GetProcAddress(hEffectsDLL,"mainDistortion");
	mainEcho = (int (*) (int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]))GetProcAddress(hEffectsDLL,"mainEcho");
	if (mainDistortion==NULL) throw "mainDistortion loading error";
	if (mainEcho==NULL) throw "mainEcho loading error";
	
	int bufferFromUser[CANALS][LENGTH];

	for (int i = 0; i < CANALS; i++){
		for (int j = 0; j < LENGTH; j++){
			bufferFromUser[i][j] = - RAND_MAX/2 + rand();
		}
	}

	printArray(bufferFromUser);

	if (0 == mainDistortion(0,0,bufferFromUser)){
		cout << "\n after distortion \n\n";
		printArray(bufferFromUser);
	}

	float coefficient = 10;
	int memoryBuffer[CANALS][LENGTH];
	mainEcho(bufferFromUser, coefficient, true, memoryBuffer);
	cout << "\nfirst echoed buffer\n";
	printArray(bufferFromUser);
	mainEcho(bufferFromUser, coefficient, false, memoryBuffer);
	cout << "\nsecond echoed buffer\n";
	printArray(bufferFromUser);

	if (hEffectsDLL) FreeLibrary(hEffectsDLL);
	
	getch();
	return 0;
}