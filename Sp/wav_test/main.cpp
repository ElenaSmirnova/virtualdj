
#include "main.h"
#include <conio.h>

void main()
{
    printf("Start\n");
    //TODO:
    //����� ������� �� ������������ ���������� wav
	SoundBuffer *nullBuffer = new SoundBuffer(NULL, 0);
    read2(nullBuffer, "C:\\Documents and Settings\\Belka\\������� ����\\virtualDj\\Sp\\sound\\ARROW.wav");
	write2(nullBuffer, "C:\\Documents and Settings\\Belka\\������� ����\\virtualDj\\Sp\\sound\\try.wav");

	printf("Stop\n");
}