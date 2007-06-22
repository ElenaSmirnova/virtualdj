
#pragma once
#include <windows.h>
#include <stdio.h>

typedef  void read_parameters;
//Объявление функции из динамической библиотеки wav. Сама библиотека будет загружена при старте приложения.
extern "C" __declspec(dllimport) void read(read_parameters* parameters);
