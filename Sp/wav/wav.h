// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>

//TODO:
typedef  void read_parameters;
typedef  void write_parameters;
#pragma pack(push,1)
typedef struct {
	byte t1;
	short int t2;
	} IDType;
typedef struct {
	char id[4]; //- ������������� ����� = "RIFF" = 0x46464952
	long len[4];   //- ����� ����� ��� ����� ���������
	} IDRiff;
typedef struct {
	char id[4];  //- ������������� = "WAVE" = 0x45564157
	char fmt[4]; //- ������������� = "fmt " = 0x20746D66
	long len;    //- ����� ����� ����� WAV - �����,
	} IDChuckWave;
typedef struct {
        int type;   //- ��� �������� ������, ������ - !!!
					//1 - ������ �������;
					//0x101 - IBM mu-law;
                    //0x102 - IBM a-law;
                    //0x103 - ADPCM.
        int channels; //- ����� ������� 1/2 - !!!
        long SamplesPerSec; //- ������� ������� - !!!
        long AvgBytesPerSec; //- ������� ������ ������
        int align; //- ������������
        int bits; //- ����� ��� �� �������  - !!!
	} IDWave;
typedef struct {
	char id[4]; //- ������������� ="data" =0x61746164
        long len; //  - ����� ������� ( ������ 2 )
	} IDSampleWave;
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
	//byte fg;
	//byte sample[250];
	byte sample[400];
//	unsigned short int sample[300];
	} TitleWave;
#pragma pack(pop)

extern "C" __declspec(dllexport) void read2(char* name);

extern "C" __declspec(dllexport) void write(write_parameters* parameters);

