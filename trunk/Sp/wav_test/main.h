
#pragma once
#include <windows.h>
#include <stdio.h>
#include "..\wav\wav.h"

//���������� ������� �� ������������ ���������� wav. ���� ���������� ����� ��������� ��� ������ ����������.
extern "C" __declspec(dllimport) void _cdecl read2(Buffer *buffer, char* name);
