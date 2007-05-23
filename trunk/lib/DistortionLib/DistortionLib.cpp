// DistortionLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define column 16 //16384
#define canal 2

int (*mainDistortion)(int highLimit, int lowLimit, volatile int **buffer, int length, int canals);

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE h;
	h=LoadLibrary(L"EffectsDLL");
	if (!h)
    {
      printf("������ - �� ���� ����� EffectsDLL.dll\n");
      return 1;
    }

	mainDistortion =(int (*) (int highLimit, int lowLimit, volatile int **buffer, int length, int canals))GetProcAddress(h,"mainDistortion");
	if (!mainDistortion)
    {
      printf("������! � EffectsDLL ����������� �-��� mainDistortion\n");
      return 1;
    }



	int bufferFromUser[canal][column];

	for (int i = 0; i < canal; i++)
		for (int j = 0; j < column; j++){
			bufferFromUser[i][j] = - RAND_MAX/2 + rand();
		}

	for (int i=0; i<canal; i++){
		for (int j = 0; j < column; j++){
			cout << bufferFromUser[i][j] << " ";
		}
		cout << "\n";
	}

	if (0 == mainDistortion(0,0,(volatile int **)bufferFromUser,column,canal)){
		cout << "\n after distortion \n\n";
		for (int i=0; i<canal; i++){
			for (int j = 0; j < column; j++){
				cout << bufferFromUser[i][j] << " ";
			}
			cout << "\n";
		}
	}


	if (h) FreeLibrary(h);
	
	getch();
	return 0;
}