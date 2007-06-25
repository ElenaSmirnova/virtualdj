// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>

//TODO:
typedef  void eff_parameters;

#define LENGTH 6 //16384
#define CANALS 2

extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters);
extern "C" __declspec(dllexport) int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]);
extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]);
