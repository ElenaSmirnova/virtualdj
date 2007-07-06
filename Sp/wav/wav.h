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
	char id[4]; //- идентификатор файла = "RIFF" = 0x46464952
	long len[4];   //- длина файла без этого заголовка
	} IDRiff;
typedef struct {
	char id[4];  //- идентификатор = "WAVE" = 0x45564157
	char fmt[4]; //- идентификатор = "fmt " = 0x20746D66
	long len;    //- длина этого куска WAV - файла,
	} IDChuckWave;
typedef struct {
        int type;   //- тип звуковых данных, бывает - !!!
					//1 - просто выборка;
					//0x101 - IBM mu-law;
                    //0x102 - IBM a-law;
                    //0x103 - ADPCM.
        int channels; //- число каналов 1/2 - !!!
        long SamplesPerSec; //- частота выборки - !!!
        long AvgBytesPerSec; //- частота выдачи байтов
        int align; //- выравнивание
        int bits; //- число бит на выборку  - !!!
	} IDWave;
typedef struct {
	char id[4]; //- идентификатор ="data" =0x61746164
        long len; //  - длина выборки ( кратно 2 )
	} IDSampleWave;
typedef struct {
	char id_riff[4];//- идентификатор файла = "RIFF" = 0x46464952
    long len_riff;//- длина файла без этого заголовка

	char id_chuck[4];//- идентификатор = "WAVE" = 0x45564157
	char fmt[4];//- идентификатор = "fmt " = 0x20746D66
	long len_chuck; //- длина этого куска WAV - файла,

	short int  type; //- тип звуковых данных
	short int  channels;//- число каналов
	long freq;//- частота выборки 
	long bytes;//- частота выдачи байтов
	short int  align;//- выравнивание
	short int  bits;//- число бит на выборку

	char id_data[4];//- идентификатор ="data" =0x61746164
	long len_data;//  - длина выборки
	//byte fg;
	//byte sample[250];
	byte sample[400];
//	unsigned short int sample[300];
	} TitleWave;
#pragma pack(pop)

extern "C" __declspec(dllexport) void read2(char* name);

extern "C" __declspec(dllexport) void write(write_parameters* parameters);

