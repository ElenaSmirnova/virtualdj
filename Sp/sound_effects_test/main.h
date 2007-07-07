#pragma once
#include <windows.h>
#include <stdio.h>

#define LENGTH 6 //16384
#define CANALS 2

typedef  void eff_parameters;
//Объявление функции из динамической библиотеки wav. Сама библиотека будет загружена при старте приложения.
extern "C" __declspec(dllimport) void sound_effect(eff_parameters* parameters);
extern "C" __declspec(dllimport) int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]);
extern "C" __declspec(dllimport) int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]);