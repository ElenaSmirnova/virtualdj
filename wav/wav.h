// wav.h
#pragma once

#include <windows.h>
#include <stdio.h>

//TODO:
typedef  void read_parameters;
typedef  void write_parameters;

extern "C" __declspec(dllexport) void read(read_parameters* parameters);

extern "C" __declspec(dllexport) void write(write_parameters* parameters);

