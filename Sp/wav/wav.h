// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "structure.h"

//TODO:

#pragma pack(push,1)

#pragma pack(pop)

extern "C" __declspec(dllexport) void read2(SoundBuffer *buffer, char* name);
extern "C" __declspec(dllexport) void write2(SoundBuffer *buffer, char* name);