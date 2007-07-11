// This is the main DLL file.


#include "sound_effects.h"
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

�������� ���������:
buffer - ������ � ��� ����������� �����������
***************************************/

bool distortion(int highLimit, int lowLimit, Buffer *buffer){
		for (int i = 0; i < CANALS; i++){
			for (int j = 0; j < buffer->len_buff; j++){
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

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, Buffer *buffer)
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

void appropriate(Buffer *toMatrix, Buffer *fromMatrix, int columns){
	for (int i = 0; i < CANALS; i++){
		for (int j=0; j<columns; j++){
			toMatrix->buff[j][i] = fromMatrix->buff[j][i];
		}
	}
}

void echo(int** toBuffer,int** fromBuffer, int length){
	for (int j=0; j<length; j++){
		for (int i=0; i<CANALS; i++){
			toBuffer[j][i] = (int) (coeff*fromBuffer[j][i]);
		}
	}
}//�������� ���������� ������ �� �����������

int sumBuffers(Buffer *buffer,Buffer *memoryBuffer){
	//int* firstEcho= new int[buffer->len_buff];//������ ��� ������� ���
	int** firstEcho = (int  **)calloc(buffer->len_buff,sizeof(int  *));
	for (int i = 0; i < buffer->len_buff; i ++)
	{
              buffer->buff[i]=(int *)calloc(2, sizeof(int));
	}

	//int* secondEcho = new int[buffer->len_buff];//������ ��� ������� ���
	int** secondEcho = (int  **)calloc(buffer->len_buff,sizeof(int  *));
	for (int i = 0; i < buffer->len_buff; i ++)
	{
              buffer->buff[i]=(int *)calloc(2, sizeof(int));
	}

	int firstMemoryBuffer[CANALS][DELAY];//������ ��� ������� �� ������� ���
	int secondMemoryBuffer[CANALS][2*DELAY];//������ ��� ������� �� ������� ���

	for (int j=0; j<CANALS; j++){
		if (memoryBuffer->buff != NULL) {//���� ��� �� ������ ������ �� ������
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[j][i] = memoryBuffer->buff[buffer->len_buff - 2*DELAY + i][j];
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[j][i] = (int)memoryBuffer->buff[buffer->len_buff - DELAY +i][j];
			}
		}else{//���� ������ �����, �� ���� ������������ ������ ������ �� ������
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[j][i] = 0;
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[j][i] = 0;
			}
		}
	}

	if (NULL != buffer->buff){
		echo(firstEcho, buffer->buff, buffer->len_buff);//�������� ������ ���
		echo(secondEcho,firstEcho, buffer->len_buff);//�������� ������ ���
		
		echo((int**)firstMemoryBuffer, (int**)firstMemoryBuffer,DELAY);//�������� ������ ��� �������
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);//�������� ������ ��� �������
				
		for (int j=0; j<buffer->len_buff; j++){
			for (int i=0; i<CANALS; i++){
				if (j<DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstMemoryBuffer[i][j];}
				if (j<2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondMemoryBuffer[i][j];}
				if (j>=DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstEcho[j-DELAY][i];}
				if (j>=2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondEcho[j-2*DELAY][i];}
			}
		}//������� �������� ������
		
	}
	return 0;
}

void setMemory(Buffer *buffer, bool flagOfFirstUse, Buffer *memoryBuffer){
	if (flagOfFirstUse){
		for (int i=0; i<CANALS; i++){
			for (int j=0; j<buffer->len_buff; j++){
				memoryBuffer->buff[i][j] = NULL;
			}
		}
	}
	
	Buffer *tempMemoryBuffer = new Buffer();

	appropriate(tempMemoryBuffer,buffer,buffer->len_buff);
	if (!flagOfFirstUse) {
		sumBuffers(buffer,memoryBuffer);
	}else{
		sumBuffers(buffer, new Buffer());
	}
	
	for (int i=0; i<CANALS; i++){
		appropriate(memoryBuffer,tempMemoryBuffer,buffer->len_buff);
	}
}

extern "C" __declspec(dllexport) int mainEcho(Buffer *buffer, float coefficient, bool flagOfFirstUse, Buffer *memoryBuffer){
	while ((coefficient < 0) || (coefficient >1)){
		cout << "\nSorry, but coefficient must be in [0,1]\n";
		return 1;
	}

	coeff = coefficient;
	if (buffer != NULL){
		setMemory(buffer, flagOfFirstUse, memoryBuffer);
	}else{ 
		cout << "The buffer is empty\n";
		return 1; 
	}

	return 0;
}
extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters)
{}

#ifdef _MANAGED
#pragma managed(pop)
#endif