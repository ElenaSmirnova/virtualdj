#pragma once
#include <windows.h>
#include <stdio.h>

typedef  void view_parameters;
//���������� ������� �� ������������ ���������� wav. ���� ���������� ����� ��������� ��� ������ ����������.
extern "C" __declspec(dllimport) void view(SoundBuffer *buffer);
