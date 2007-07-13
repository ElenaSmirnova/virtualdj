
#include "main.h"
#include <conio.h>

void main()
{
    printf("Start\n");
    //TODO:
    //вызов функции из динамической библиотеки wav
	SoundBuffer *nullBuffer = new SoundBuffer(NULL, 0, 0);
    read2(nullBuffer, "I:\\virtualdj\\Sp\\sound\\TC Delete Complete.wav");
	write2(nullBuffer, NULL);
	write2(nullBuffer, "I:\\virtualdj\\Sp\\sound\\TC Delete Complete.wav");

    printf("Stop\n");
	getch();
}
