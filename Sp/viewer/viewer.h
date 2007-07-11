// viewer.h
#pragma once

#include <windows.h>
#include <stdio.h>
#include "..\wav\structure.h"

//TODO:
typedef  void view_parameters;

extern "C" __declspec(dllexport) void view(Buffer* buf);


