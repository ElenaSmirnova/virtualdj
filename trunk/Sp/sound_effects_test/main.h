#pragma once
#include <windows.h>
#include <stdio.h>

typedef  void eff_parameters;
//���������� ������� �� ������������ ���������� wav. ���� ���������� ����� ��������� ��� ������ ����������.
extern "C" __declspec(dllimport) void sound_effect(eff_parameters* parameters);