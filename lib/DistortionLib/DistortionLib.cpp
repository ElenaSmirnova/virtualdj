// DistortionLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define columns 16 //16384

// мне не нравится, что columns описывается два раза. это может привести к ошибке...

int (*mainDistortion)(int highLimit, int lowLimit, volatile int buffer[][columns]);

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE h;
	h=LoadLibrary(L"DistortionDLL");
	if (!h)
    {
      printf("Ошибка - не могу найти DistortionDLL.dll\n");
      return 1;
    }

	mainDistortion =(int (*) (int highLimit, int lowLimit, volatile int buffer[][columns]))GetProcAddress(h,"mainDistortion");
	if (!mainDistortion)
    {
      printf("Ошибка! В DistortionDLL отсутствует ф-ция mainDistortion\n");
      return 1;
    }



	int bufferFromUser[2][columns];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < columns; j++){
			bufferFromUser[i][j] = - RAND_MAX/2 + rand();
		}

	for (int i=0; i<2; i++){
		for (int j = 0; j < columns; j++){
			cout << bufferFromUser[i][j] << " ";
		}
		cout << "\n";
	}

	if (0 == mainDistortion(0,0,bufferFromUser)){
		cout << "\n after distortion \n\n";
		for (int i=0; i<2; i++){
			for (int j = 0; j < columns; j++){
				cout << bufferFromUser[i][j] << " ";
			}
			cout << "\n";
		}
	}


	if (h) FreeLibrary(h);
	
	getch();
	return 0;
}