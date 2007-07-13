// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "structure.h"

//TODO:
typedef  void write_parameters;
#pragma pack(push,1)

typedef struct {
	char id_riff[4];//- ������������� ����� = "RIFF" = 0x46464952
    long len_riff;//- ����� ����� ��� ����� ���������

	char id_chuck[4];//- ������������� = "WAVE" = 0x45564157
	char fmt[4];//- ������������� = "fmt " = 0x20746D66
	long len_chuck; //- ����� ����� ����� WAV - �����,

	short int  type; //- ��� �������� ������
	short int  channels;//- ����� �������
	long freq;//- ������� ������� 
	long bytes;//- ������� ������ ������
	short int  align;//- ������������
	short int  bits;//- ����� ��� �� �������

	char id_data[4];//- ������������� ="data" =0x61746164
	long len_data;//  - ����� �������

	byte sample[1000768];//- ������ �� ��������;
} TitleWave;


#pragma pack(pop)

extern "C" __declspec(dllexport) void read2(SoundBuffer *buffer, char* name);

extern "C" __declspec(dllexport) void write(write_parameters* parameters);

