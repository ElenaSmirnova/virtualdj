
#pragma once
#include <windows.h>
#include <stdio.h>

typedef  void read_parameters;
//���������� ������� �� ������������ ���������� wav. ���� ���������� ����� ��������� ��� ������ ����������.
extern "C" __declspec(dllimport) void read(read_parameters* parameters);
