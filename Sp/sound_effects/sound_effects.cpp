// This is the main DLL file.


#include "sound_effects.h"
#include <iostream>
#include <math.h>
using namespace std;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

/***************************************
������ ��������
������� (distortion - ���������) - ����p����� ��������� ��p�� �����, ��� �p����� ��� p�����, ��p�������� �������. 
H��������� �p�������� ������� � �������� ����p���� ������� (������������ ����p� heavy metal). 
���������� ��p���������� ��������� ������� �� ��������� ��p�������� � ��������� (�p��� ��p����� ���������) 
� ���� ��� ���������������. �������p� ����� �������� ������ ���������� ����� �� �p�����������, ������ � ��� 
���������� ������� ���������� ����� ��������� ������������, p���� p����p����� �����p.

������� ���������:
highLimit - ������� ������ ��������
lowLimit - ������ ������ ��������
buffer - ������ � �������

�������� ���������:
buffer - ������ � ��� ����������� �����������
***************************************/

bool distortion(int highLimit, int lowLimit, SoundBuffer *buffer){
		for (int i = 0; i < CANALS; i++){
			for (int j = 0; j < buffer->getLength(); j++){
				if (buffer->buff[j][i] != NULL) {
					if (buffer->buff[j][i] > highLimit) { buffer->buff[j][i] = highLimit; }
					else{
						if (buffer->buff[j][i] < lowLimit) { buffer->buff[j][i] = lowLimit; }
					}
				}
			}
		}
		return true;
}

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, SoundBuffer *buffer)
{
	bool distResult = false;

	if (highLimit <= lowLimit) {
		cout << "\nSorry, but you have entered wrong limits\n";
		return 1;
	}

	if (buffer != NULL) {
		distResult = distortion(highLimit, lowLimit, buffer);
	}else{
		cout << "The buffer is empty\n";
		return 1;
	}

	return 0;
}

/***************************************
���
�� ������������� ������ �������� ��������� �������� ������� "���" (echo). 
���������� ��� ��������� ��� ���������� �� ������������ ������� ������ �������� ��� 
����������� �� ������� �����. ��� ����, ����� ������������ ��� ������������ ������ 
����� ������� ��� ����������, � �� ��� ������ ��������� �������, ���������� ����� ��������
���������� ������ �������� 50 ��. ����� ����, �� �������� ������ ����� �������� �� ���� 
��� �����, � ���������, ��� �������� �� ������ �������� ������ ������������� ���������� ����� 
(�������������� ���). ����� ��� �������� ����������, ���������� �� �������� ������ ����������� 
�� ������ ����������� ����� �������, � � ������������ �� ���������.

������� ���������:
buffer - ������ � �������
coefficient - ����������� ���, �. �. �����������, �� ������� ����� ����������� ������� ������
flagOfFirstUse - ������ ����, ������ �� ��� ������ ��� ��� (������, ��� ���� �� ������, �� ���� ���������� ��� �� ����������� �������)
memoryBuffer - �������������� ������. ������������, ���� ��� �� ������ ����� ������� mainEcho ��� ������� �����

�������� ���������:
buffer - ��� ������������ ������
memoryBuffer - ������, ������� ��� ������ �� ���������. ����� �������������� ��� ���������� ��������� ��������� ����� �������� ���
***************************************/

float coeff = 1;
int DELAY;

void appropriate(SoundBuffer *toMatrix, SoundBuffer *fromMatrix, int columns){
	for (int i = 0; i < CANALS; i++){
		for (int j=0; j<columns; j++){
			toMatrix->buff[j][i] = fromMatrix->buff[j][i];
		}
	}
}

void echo(int** toBuffer,int** fromBuffer, int length){
	for (int j=0; j<length; j++){
		for (int i=0; i<CANALS; i++){
			float result = coeff*fromBuffer[j][i];
			toBuffer[j][i] = floor(0.5 + result);
		}
	}
}

int sumBuffers(SoundBuffer *buffer,SoundBuffer *memoryBuffer){
	//int* firstEcho= new int[buffer->len_buff];//������ ��� ������� ���
	int** firstEcho = (int  **)calloc(buffer->getLength(),sizeof(int  *));
	for (int i = 0; i < buffer->getLength(); i ++)
	{
              firstEcho[i]=(int *)calloc(2, sizeof(int));
	}

	//int* secondEcho = new int[buffer->len_buff];//������ ��� ������� ���
	int** secondEcho = (int  **)calloc(buffer->getLength(),sizeof(int  *));
	for (int i = 0; i < buffer->getLength(); i ++)
	{
              secondEcho[i]=(int *)calloc(2, sizeof(int));
	}

	//������ ��� ������� �� ������� ���
	int** firstMemoryBuffer = (int  **)calloc(DELAY,sizeof(int *));
	for (int i = 0; i < DELAY; i++){
              firstMemoryBuffer[i]=(int *)calloc(2, sizeof(int));
	}
	//������ ��� ������� �� ������� ���
	int** secondMemoryBuffer = (int  **)calloc(2*DELAY,sizeof(int  *));
	for (int i = 0; i < 2*DELAY; i ++){
              secondMemoryBuffer[i]=(int *)calloc(2, sizeof(int));
	}

	for (int j=0; j<CANALS; j++){
		if (memoryBuffer->buff != NULL) {//���� ��� �� ������ ������ �� ������
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[i][j] = memoryBuffer->buff[buffer->getLength() - 2*DELAY + i][j];
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[i][j] = (int)memoryBuffer->buff[buffer->getLength() - DELAY +i][j];
			}
		}else{//���� ������ �����, �� ���� ������������ ������ ������ �� ������
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[i][j] = 0;
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[i][j] = 0;
			}
		}
	}

	if (NULL != buffer->buff){
		echo(firstEcho, buffer->buff, buffer->getLength());//�������� ������ ���
		echo(secondEcho,firstEcho, buffer->getLength());//�������� ������ ���
		
		echo((int**)firstMemoryBuffer, (int**)firstMemoryBuffer,DELAY);//�������� ������ ��� �������
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);//�������� ������ ��� �������
		
		for (int j=0; j<buffer->getLength(); j++){
			for (int i=0; i<CANALS; i++){
				if (j<DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstMemoryBuffer[j][i];}
				if (j<2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondMemoryBuffer[j][i];}
				if (j>=DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstEcho[j-DELAY][i];}
				if (j>=2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondEcho[j-2*DELAY][i];}
			}
		}//������� �������� ������
		
	}
	return 0;
}

void setMemory(SoundBuffer *buffer, bool flagOfFirstUse, SoundBuffer *memoryBuffer){
	if (flagOfFirstUse){
		for (int i=0; i<CANALS; i++){
			for (int j=0; j<memoryBuffer->getLength(); j++){
				memoryBuffer->buff[i][j] = NULL;
			}
		}
	}
	
	SoundBuffer *tempMemoryBuffer = new SoundBuffer(NULL, buffer->getLength(), buffer->frequency);
	
	appropriate(tempMemoryBuffer,buffer,buffer->getLength());
	if (!flagOfFirstUse) {
		sumBuffers(buffer,memoryBuffer);
	}else{
		sumBuffers(buffer, new SoundBuffer(NULL, buffer->getLength(), buffer->frequency));
	}
	
	for (int i=0; i<CANALS; i++){
		appropriate(memoryBuffer,tempMemoryBuffer,buffer->getLength());
	}
}

extern "C" __declspec(dllexport) int mainEcho(SoundBuffer *buffer, float coefficient, bool flagOfFirstUse, SoundBuffer *memoryBuffer){
	if ((coefficient <= 0) || (coefficient >1)){
		cout << "\nSorry, but coefficient must be in [0,1]\n";
		return 1;
	}
	if (buffer->frequency <= 0) {
		cout << "Sorry, error with the digitization\n";
		return 1;
	}

	coeff = coefficient;
	if (buffer != NULL){
		DELAY = floor((buffer->frequency/20)+0.5);
		setMemory(buffer, flagOfFirstUse, memoryBuffer);
	}else{ 
		cout << "The buffer is empty\n";
		return 1; 
	}

	return 0;
}
extern "C" __declspec(dllexport) void sound_effect(SoundBuffer *buffer)
{
	if (buffer->buff != NULL) {
	}else{
		return 1;
	}
}

#ifdef _MANAGED
#pragma managed(pop)
#endif