// DistortionDLL.cpp : Defines the entry point for the DLL application.
//


#include "stdafx.h"
#include <stdio.h>
#include <iostream> 
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
(������, ��� � ������, � ������� ������ ������ ���� 16384 (�� ���� ������), � 16 ��� ������ ��� ������������)

�������� ���������:
buffer - ������ � ��� ����������� �����������
***************************************/

#define columns 16 //16384

bool distortion(int highLimit, int lowLimit, volatile int buffer[][columns]){
		for (int i = 0; i < columns; i++){
			if ((buffer[0][i] != NULL)&&(buffer[1][i] != NULL)){

				if (buffer[0][i] > highLimit) { buffer[0][i] = highLimit; }
				else{
					if (buffer[0][i] < lowLimit) { buffer[0][i] = lowLimit; }
				}

				if (buffer[1][i] > highLimit) { buffer[1][i] = highLimit; }
				else{
					if (buffer[1][i] < lowLimit) { buffer[1][i] = lowLimit; }
				}

			}else{
			cout << "one element of buffer is empty!\n";
			return false;
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

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, volatile int buffer[][columns])
{
	bool distResult = false;

	while (highLimit <= lowLimit) {
		cout << "Sorry, but you have entered wrong limits. Try again, please\n";
		highLimit = setHighLimit();
		lowLimit = setLowLimit();
	}

	if (buffer != NULL) {
		distResult = distortion(highLimit, lowLimit, buffer);
	}else{
		cout << "buffer is empty!\n";
		return 1;
	}

	if (!distResult) {
		return 1;
	}

	return 0;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif