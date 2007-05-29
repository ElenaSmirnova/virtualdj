// EffectsDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "EffectsDLL.h"
#include <iostream>
using namespace std;


#define DELAY 2

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
(������, ��� � ������, � ������� ������ ������ ���� 16384 (�� ���� ������), � 16 ��� ������ ��� ������������)

�������� ���������:
buffer - ������ � ��� ����������� �����������
***************************************/

bool distortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]){
		for (int i = 0; i < CANALS; i++){
			for (int j = 1; j < LENGTH; j++){
				if (buffer[i][j] != NULL) {
					if (buffer[i][j] > highLimit) { buffer[i][j] = highLimit; }
					else{
						if (buffer[i][j] < lowLimit) { buffer[i][j] = lowLimit; }
					}
				}else{
					cout << "one element of buffer is empty\n";
					return false;
				}
			}
		}
		return true;
}

int setHighLimit(){
	int highLimit;
	cout << "\nEnter the high limit of the amplitude\n";
	cin >> highLimit;
	return highLimit;
}

int setLowLimit(){
	int lowLimit;
	cout << "\nEnter the low limit of the amplitude\n";
	cin >> lowLimit;
	return lowLimit;
}

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH])
{
	bool distResult = false;

	while (highLimit <= lowLimit) {
		cout << "\nSorry, but you have entered wrong limits. Try again, please\n";
		highLimit = setHighLimit();
		lowLimit = setLowLimit();
	}

	if (buffer != NULL) {
		distResult = distortion(highLimit, lowLimit, buffer);
	}else{
		cout << "buffer is empty\n";
		return 1;
	}

	if (!distResult) {
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

void appropriate(int* toArray, const int* fromArray, int columns){
	for (int j=0; j<columns; j++){
		toArray[j] = fromArray[j];
	}
}//������������ ���������� �������

void echo(int* toBuffer,const int* fromBuffer, int length){
	for (int j=0; j<length; j++){
		toBuffer[j] = (int) (coeff*fromBuffer[j]);
	}
}//�������� ���������� ������ �� �����������

int sumBuffers(int* buffer,const int* memoryBuffer){
	int firstEcho[LENGTH];//������ ��� ������� ���
	int secondEcho[LENGTH];//������ ��� ������� ���
	int firstMemoryBuffer[DELAY];//������ ��� ������� �� ������� ���
	int secondMemoryBuffer[2*DELAY];//������ ��� ������� �� ������� ���

	if (memoryBuffer != NULL) {//���� ��� �� ������ ������ �� ������
		for (int i=0; i<2*DELAY; i++){
			secondMemoryBuffer[i] = memoryBuffer[LENGTH - 2*DELAY + i];
		}
		for (int i=0; i<DELAY; i++){
			firstMemoryBuffer[i] = memoryBuffer[LENGTH - DELAY +i];
		}
	}else{//���� ������ �����, �� ���� ������������ ������ ������ �� ������
		for (int i=0; i<2*DELAY; i++){
			secondMemoryBuffer[i] = 0;
		}
		for (int i=0; i<DELAY; i++){
			firstMemoryBuffer[i] = 0;
		}
	}
	
	if (NULL != buffer){
		echo((int*)firstEcho, (const int*)buffer, LENGTH);//�������� ������ ���
		echo((int*)secondEcho,(const int*)firstEcho, LENGTH);//�������� ������ ���
		
		echo((int*)firstMemoryBuffer, (const int*)firstMemoryBuffer,DELAY);//�������� ������ ��� �������
		echo((int*)secondMemoryBuffer, (const int*)secondMemoryBuffer, 2*DELAY);
		echo((int*)secondMemoryBuffer, (const int*)secondMemoryBuffer, 2*DELAY);//�������� ������ ��� �������
				
		for (int j=0; j<LENGTH; j++){
			if (j<DELAY) {buffer[j] = buffer[j] + firstMemoryBuffer[j];}
			if (j<2*DELAY) {buffer[j] = buffer[j] + secondMemoryBuffer[j];}
			if (j>=DELAY) {buffer[j] = buffer[j] + firstEcho[j-DELAY];}
			if (j>=2*DELAY) {buffer[j] = buffer[j] + secondEcho[j-2*DELAY];}
		}//������� �������� ������
		
	}else{
		cout << "buffer is empty\n";
		return 1;
	}
	return 0;
}

void setMemory(int buffer[CANALS][LENGTH], bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]){
	if (flagOfFirstUse){
		for (int i=0; i<CANALS; i++){
			for (int j=0; j<LENGTH; j++){
				memoryBuffer[i][j] = NULL;
			}
		}
	}
	int tempMemoryBuffer[CANALS][LENGTH];
	for (int i=0; i<CANALS; i++){
		appropriate((int*)tempMemoryBuffer[i],(const int*)buffer[i],LENGTH);
		if (!flagOfFirstUse) {
			sumBuffers((int*)buffer[i],memoryBuffer[i]);
		}else{
			sumBuffers((int*)buffer[i], (int*)NULL);
		}
	}
	for (int i=0; i<CANALS; i++){
		appropriate((int*)memoryBuffer[i],(const int*)tempMemoryBuffer[i],LENGTH);
	}
}

extern "C" __declspec(dllexport) int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]){
	while ((coefficient < 0) || (coefficient >1)){
		cout << "\nSorry, but coefficient must be in [0,1]. Try again please\n";
		cin >> coefficient;
	}

	coeff = coefficient;
	if (buffer != NULL){
		setMemory(buffer, flagOfFirstUse, memoryBuffer);
	}else{ return 1; }
	return 0;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif