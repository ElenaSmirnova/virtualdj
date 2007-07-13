// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "..\wav\structure.h"

#define CANALS 2

//TODO:
typedef  void eff_parameters;

extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters);
extern "C" __declspec(dllexport) int mainEcho(SoundBuffer *buffer, float coefficient, bool flagOfFirstUse, SoundBuffer *memoryBuffer);
extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, SoundBuffer *buffer);
