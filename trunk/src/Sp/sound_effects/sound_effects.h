// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>

//TODO:
typedef  void eff_parameters;

extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters);


