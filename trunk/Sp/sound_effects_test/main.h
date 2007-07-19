#pragma once
#include <windows.h>
#include <stdio.h>
#include "..\wav\structure.h"

#define CANALS 2

typedef  void eff_parameters;
//Объявление функции из динамической библиотеки wav. Сама библиотека будет загружена при старте приложения.
extern "C" __declspec(dllimport) int mainEcho(SoundBuffer *buffer, float coefficient, long delay);
extern "C" __declspec(dllimport) int mainDistortion(int highLimit, int lowLimit, SoundBuffer *buffer);