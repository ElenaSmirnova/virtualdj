
#include "main.h"
#include <conio.h>

void main()
{
    printf("Start\n");
    //TODO:
    //вызов функции из динамической библиотеки wav
	Buffer *nullBuffer = new Buffer();
    read2(nullBuffer, "I:\\virtualdj\\Sp\\sound\\TC Delete Complete.wav");

    printf("Stop\n");
	getch();
}
