
#pragma once
#include <windows.h>
#include <stdio.h>
#include "..\wav\wav.h"

//Объявление функции из динамической библиотеки wav. Сама библиотека будет загружена при старте приложения.
extern "C" __declspec(dllimport) void _cdecl read2(SoundBuffer *buffer, char* name);
extern "C" __declspec(dllimport) void _cdecl write2(SoundBuffer *buffer, char* name);