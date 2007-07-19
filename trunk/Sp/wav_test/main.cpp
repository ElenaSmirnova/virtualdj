
#include "main.h"
#include <conio.h>

void main()
{
    printf("Start\n");
    //TODO:
    //вызов функции из динамической библиотеки wav
	SoundBuffer *nullBuffer = new SoundBuffer(NULL, 0);
    read2(nullBuffer, "C:\\Documents and Settings\\Belka\\Рабочий стол\\virtualDj\\Sp\\sound\\ARROW.wav");
	write2(nullBuffer, "C:\\Documents and Settings\\Belka\\Рабочий стол\\virtualDj\\Sp\\sound\\try.wav");

	printf("Stop\n");
}