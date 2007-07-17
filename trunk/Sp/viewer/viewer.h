// viewer.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "..\wav\wav.h"

//TODO:
//typedef  void view_parameters;

extern "C" __declspec(dllexport) void view(SoundBuffer* buf);



