// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "structure.h"

//TODO:
typedef  void write_parameters;
#pragma pack(push,1)

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

	byte sample[1000768];//- массив из амплитуд;
} TitleWave;


#pragma pack(pop)

extern "C" __declspec(dllexport) void read2(SoundBuffer *buffer, char* name);

extern "C" __declspec(dllexport) void write(write_parameters* parameters);

