// This is the main DLL file.


#include "sound_effects.h"
#include <iostream>
using namespace std;


#define DELAY 2

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

/***************************************
Эффект Дисторшн
дистошн (distortion - искажение) - намеpенное искажение фоpмы звука, что пpидает ему pезкий, скpежещущий оттенок. 
Hаибольшее пpименение получил в качестве гитаpного эффекта (классическая гитаpа heavy metal). 
Получается пеpеусилением исходного сигнала до появления огpаничений в усилителе (сpеза веpхушек импульсов) 
и даже его самовозбуждения. Благодаpя этому исходный сигнал становится похож на пpямоугольный, отчего в нем 
появляется большое количество новых частотных составляющих, pезко pасшиpяющих спектp.

Входные параметры:
highLimit - верхний предел амплитуд
lowLimit - нижний предел амплитуд
buffer - массив с данными

Выходные параметры:
buffer - массив с уже обрезанными амплитудами
***************************************/

bool distortion(int highLimit, int lowLimit, Buffer *buffer){
		for (int i = 0; i < CANALS; i++){
			for (int j = 0; j < buffer->len_buff; j++){
				if (buffer->buff[j][i] != NULL) {
					if (buffer->buff[j][i] > highLimit) { buffer->buff[j][i] = highLimit; }
					else{
						if (buffer->buff[j][i] < lowLimit) { buffer->buff[j][i] = lowLimit; }
					}
				}
			}
		}
		return true;
}

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, Buffer *buffer)
{
	bool distResult = false;

	if (highLimit <= lowLimit) {
		cout << "\nSorry, but you have entered wrong limits\n";
		return 1;
	}

	if (buffer != NULL) {
		distResult = distortion(highLimit, lowLimit, buffer);
	}else{
		cout << "The buffer is empty\n";
		return 1;
	}

	return 0;
}

/***************************************
Эхо
На использовании метода задержки построено создание эффекта "эхо" (echo). 
Фактически для получения эха необходимо на оригинальный входной сигнал наложить его 
задержанную во времени копию. Для того, чтобы человеческое ухо воспринимало вторую 
копию сигнала как повторение, а не как отзвук основного сигнала, необходимо время задержки
установить равным примерно 50 мс. Кроме того, на основной сигнал можно наложить не одну 
его копию, а несколько, что позволит на выходе получить эффект многократного повторения звука 
(многоголосного эха). Чтобы эхо казалось затухающим, необходимо на исходный сигнал накладывать 
не просто задержанные копии сигнала, а и приглушенные по амплитуде.

Входные параметры:
buffer - массив с данными
coefficient - коэффициент эха, т. е. коэффициент, на который будет домножаться входной буффер
flagOfFirstUse - флажок того, первый ли это буффер или нет (потому, что если не первый, то надо прибывлять эхо от предыдущего буффера)
memoryBuffer - предшествующий буффер. используется, если это не первый вызов функции mainEcho для данного файла

Выходные параметры:
buffer - уже обработанный массив
memoryBuffer - буффер, который был послан на обработку. может использоваться для дальнейшей обработки звукового файла эффектом эхо
***************************************/

float coeff = 1;

void appropriate(Buffer *toMatrix, Buffer *fromMatrix, int columns){
	for (int i = 0; i < CANALS; i++){
		for (int j=0; j<columns; j++){
			toMatrix->buff[j][i] = fromMatrix->buff[j][i];
		}
	}
}

void echo(int** toBuffer,int** fromBuffer, int length){
	for (int j=0; j<length; j++){
		for (int i=0; i<CANALS; i++){
			toBuffer[j][i] = (int) (coeff*fromBuffer[j][i]);
		}
	}
}//умножаем одномерный массив на коэффициент

int sumBuffers(Buffer *buffer,Buffer *memoryBuffer){
	//int* firstEcho= new int[buffer->len_buff];//массив для первого эха
	int** firstEcho = (int  **)calloc(buffer->len_buff,sizeof(int  *));
	for (int i = 0; i < buffer->len_buff; i ++)
	{
              buffer->buff[i]=(int *)calloc(2, sizeof(int));
	}

	//int* secondEcho = new int[buffer->len_buff];//массив для второго эха
	int** secondEcho = (int  **)calloc(buffer->len_buff,sizeof(int  *));
	for (int i = 0; i < buffer->len_buff; i ++)
	{
              buffer->buff[i]=(int *)calloc(2, sizeof(int));
	}

	int firstMemoryBuffer[CANALS][DELAY];//массив для остатка от первого эха
	int secondMemoryBuffer[CANALS][2*DELAY];//массив для остатка от второго эха

	for (int j=0; j<CANALS; j++){
		if (memoryBuffer->buff != NULL) {//если уже не первый буффер со звуком
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[j][i] = memoryBuffer->buff[buffer->len_buff - 2*DELAY + i][j];
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[j][i] = (int)memoryBuffer->buff[buffer->len_buff - DELAY +i][j];
			}
		}else{//если начало песни, то есть обрабатываем первый буффер со свуком
			for (int i=0; i<2*DELAY; i++){
				secondMemoryBuffer[j][i] = 0;
			}
			for (int i=0; i<DELAY; i++){
				firstMemoryBuffer[j][i] = 0;
			}
		}
	}

	if (NULL != buffer->buff){
		echo(firstEcho, buffer->buff, buffer->len_buff);//получили первое эхо
		echo(secondEcho,firstEcho, buffer->len_buff);//получили второе эхо
		
		echo((int**)firstMemoryBuffer, (int**)firstMemoryBuffer,DELAY);//получили первое эхо остатка
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);
		echo((int**)secondMemoryBuffer, (int**)secondMemoryBuffer, 2*DELAY);//получили второе эхо остатка
				
		for (int j=0; j<buffer->len_buff; j++){
			for (int i=0; i<CANALS; i++){
				if (j<DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstMemoryBuffer[i][j];}
				if (j<2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondMemoryBuffer[i][j];}
				if (j>=DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + firstEcho[j-DELAY][i];}
				if (j>=2*DELAY) {buffer->buff[j][i] = buffer->buff[j][i] + secondEcho[j-2*DELAY][i];}
			}
		}//создаем выходной буффер
		
	}
	return 0;
}

void setMemory(Buffer *buffer, bool flagOfFirstUse, Buffer *memoryBuffer){
	if (flagOfFirstUse){
		for (int i=0; i<CANALS; i++){
			for (int j=0; j<buffer->len_buff; j++){
				memoryBuffer->buff[i][j] = NULL;
			}
		}
	}
	
	Buffer *tempMemoryBuffer = new Buffer();

	appropriate(tempMemoryBuffer,buffer,buffer->len_buff);
	if (!flagOfFirstUse) {
		sumBuffers(buffer,memoryBuffer);
	}else{
		sumBuffers(buffer, new Buffer());
	}
	
	for (int i=0; i<CANALS; i++){
		appropriate(memoryBuffer,tempMemoryBuffer,buffer->len_buff);
	}
}

extern "C" __declspec(dllexport) int mainEcho(Buffer *buffer, float coefficient, bool flagOfFirstUse, Buffer *memoryBuffer){
	while ((coefficient < 0) || (coefficient >1)){
		cout << "\nSorry, but coefficient must be in [0,1]\n";
		return 1;
	}

	coeff = coefficient;
	if (buffer != NULL){
		setMemory(buffer, flagOfFirstUse, memoryBuffer);
	}else{ 
		cout << "The buffer is empty\n";
		return 1; 
	}

	return 0;
}
extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters)
{}

#ifdef _MANAGED
#pragma managed(pop)
#endif