
#include "main.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;


void printArray(SoundBuffer *buffer){
	for (int i=0; i<CANALS; i++){
		for(int j=0; j<buffer->getLength(); j++){
			cout << buffer->buff[j][i] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	SoundBuffer *bufferFromUser = new SoundBuffer(NULL,6);
	
	bufferFromUser->buff = (int  **)calloc(bufferFromUser->getLength(),sizeof(int  *));
	for (int i = 0; i < bufferFromUser->getLength(); i ++)
	{
              bufferFromUser->buff[i]=(int *)calloc(2, sizeof(int));
	}

	/*for (int j = 0; j < bufferFromUser->getLength(); j++){
		for (int i = 0; i < CANALS; i++){
			bufferFromUser->buff[j][i] = - RAND_MAX/2 + rand();
		}
	}*/

	bufferFromUser->buff[0][0] = 10;
	bufferFromUser->buff[0][1] = 70;
	bufferFromUser->buff[1][0] = 20;
	bufferFromUser->buff[1][1] = 80;
	bufferFromUser->buff[2][0] = 30;
	bufferFromUser->buff[2][1] = 90;
	bufferFromUser->buff[3][0] = 40;
	bufferFromUser->buff[3][1] = 100;
	bufferFromUser->buff[4][0] = 50;
	bufferFromUser->buff[4][1] = 110;
	bufferFromUser->buff[5][0] = 60;
	bufferFromUser->buff[5][1] = 120;

	printArray(bufferFromUser);

	if (0 == mainDistortion(10000,-15000,bufferFromUser)){
		cout << "\n after distortion \n\n";
		printArray(bufferFromUser);
	}else{
		cout << "mainDistortion exit with error\n";
	}

	float coefficient = 0.9;
	if (0 == mainEcho(bufferFromUser, coefficient, 2)){
		cout << "\nfirst echoed buffer\n";
		printArray(bufferFromUser);
	}else{
		cout << "first mainEcho exit with error\n";
	}
	if (0 == mainEcho(bufferFromUser, 0, 2)){
		cout << "\nsecond echoed buffer\n";
		printArray(bufferFromUser);
	}else{
		cout << "second mainEcho exit with error\n";
	}
	
	getch();
	return 0;
}