
#pragma once
#include <windows.h>
#include <stdio.h>
#include "..\wav\wav.h"

//���������� ������� �� ������������ ���������� wav. ���� ���������� ����� ��������� ��� ������ ����������.
extern "C" __declspec(dllimport) void _cdecl read2(SoundBuffer *buffer, char* name);
extern "C" __declspec(dllimport) void _cdecl write2(SoundBuffer *buffer, char* name);