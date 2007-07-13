
#include "main.h"
#include <conio.h>

void main()
{
    printf("Start\n");
    //TODO:
    //вызов функции из динамической библиотеки wav
	SoundBuffer *nullBuffer = new SoundBuffer(NULL, 0, 0);
    read2(nullBuffer, "C:\\temp\\newVirtualDj\\sound\\asteroidexplode.wav");

    printf("Stop\n");
	getch();
}
