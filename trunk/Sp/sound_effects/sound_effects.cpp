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

int sumBuffers(SoundBuffer *buffer){
	//������ ��� ������� ���
	int** firstEcho = (int  **)calloc(buffer->getLength(),sizeof(int  *));
	for (int i = 0; i < buffer->getLength(); i ++)
	{
              firstEcho[i]=(int *)calloc(2, sizeof(int));
	}

	//������ ��� ������� ���
	int** secondEcho = (int  **)calloc(buffer->getLength(),sizeof(int  *));
	for (int i = 0; i < buffer->getLength(); i ++)
	{
              secondEcho[i]=(int *)calloc(2, sizeof(int));
	}

	if (NULL != buffer->buff){
		echo(firstEcho, buffer->buff, buffer->getLength());//�������� ������ ���
		echo(secondEcho,firstEcho, buffer->getLength());//�������� ������ ���
		
		for (int j=0; j<buffer->getLength(); j++){
			for (int i=0; i<CANALS; i++){
				if (j>=DELAY) {
					buffer->buff[j][i] = buffer->buff[j][i] + firstEcho[j-DELAY][i];
				}
				if (j>=2*DELAY) {
					buffer->buff[j][i] = buffer->buff[j][i] + secondEcho[j-2*DELAY][i];
				}
			}
		}//������� �������� ������
		
	}
	return 0;
}

extern "C" __declspec(dllexport) int mainEcho(SoundBuffer *buffer, float coefficient, long delay){
	if ((coefficient <= 0) || (coefficient >1)){
		cout << "\nSorry, but coefficient must be in [0,1]\n";
		return 1;
	}
	if (buffer->titleWave.freq <= 0) {
		cout << "Sorry, error with the digitization\n";
		return 1;
	}
	if ((delay <= 0)||(delay >= buffer->getLength())){
		cout << "Sorry, delay must be positive and not to be bigger then the real buffer\n";
		return 1;
	}

	coeff = coefficient;
	if (buffer != NULL){
		DELAY = delay;
		sumBuffers(buffer);
	}else{ 
		cout << "The buffer is empty\n";
		return 1; 
	}

	return 0;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif