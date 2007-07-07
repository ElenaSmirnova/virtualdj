
#include "main.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;


void printArray(int arr[][LENGTH]){
	for (int i=0; i<CANALS; i++){
		for(int j=0; j<LENGTH; j++){
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
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
	}else{
		cout << "mainDistortion exit with error\n";
	}

	float coefficient = 10;
	int memoryBuffer[CANALS][LENGTH];
	if (0 == mainEcho(bufferFromUser, coefficient, true, memoryBuffer)){
		cout << "\nfirst echoed buffer\n";
		printArray(bufferFromUser);
	}else{
		cout << "first mainEcho exit with error\n";
	}
	if (0 == mainEcho(bufferFromUser, coefficient, false, memoryBuffer)){
		cout << "\nsecond echoed buffer\n";
		printArray(bufferFromUser);
	}else{
		cout << "second mainEcho exit with error\n";
	}
	
	getch();
	return 0;
}