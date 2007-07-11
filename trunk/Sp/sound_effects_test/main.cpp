
#include "main.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;


void printArray(Buffer *buffer){
	for (int i=0; i<CANALS; i++){
		for(int j=0; j<buffer->len_buff; j++){
			cout << buffer->buff[j][i] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	Buffer *bufferFromUser = new Buffer();
	bufferFromUser->len_buff = 6;
	
	bufferFromUser->buff = (int  **)calloc(bufferFromUser->len_buff,sizeof(int  *));
	for (int i = 0; i < bufferFromUser->len_buff; i ++)
	{
              bufferFromUser->buff[i]=(int *)calloc(2, sizeof(int));
	}

	for (int j = 0; j < bufferFromUser->len_buff; j++){
		for (int i = 0; i < CANALS; i++){
			bufferFromUser->buff[j][i] = - RAND_MAX/2 + rand();
		}
	}

	printArray(bufferFromUser);

	if (0 == mainDistortion(10000,-15000,bufferFromUser)){
		cout << "\n after distortion \n\n";
		printArray(bufferFromUser);
	}else{
		cout << "mainDistortion exit with error\n";
	}

	float coefficient = 0.9;
	Buffer *memoryBuffer = new Buffer();

	memoryBuffer->buff = (int  **)calloc(bufferFromUser->len_buff,sizeof(int  *));
	for (int i = 0; i < bufferFromUser->len_buff; i ++)
	{
              bufferFromUser->buff[i]=(int *)calloc(2, sizeof(int));
	}

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