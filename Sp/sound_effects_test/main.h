#pragma once
#include <windows.h>
#include <stdio.h>
#include "..\wav\structure.h"

#define CANALS 2

typedef  void eff_parameters;
//Объявление функции из динамической библиотеки wav. Сама библиотека будет загружена при старте приложения.
extern "C" __declspec(dllimport) void sound_effect(eff_parameters* parameters);
extern "C" __declspec(dllimport) int mainEcho(SoundBuffer *buffer, float coefficient, bool flagOfFirstUse, SoundBuffer *memoryBuffer);
extern "C" __declspec(dllimport) int mainDistortion(int highLimit, int lowLimit, SoundBuffer *buffer);