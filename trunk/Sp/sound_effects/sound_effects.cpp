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

bool distortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]){
		for (int i = 0; i < CANALS; i++){
			for (int j = 0; j < LENGTH; j++){
				if (buffer[i][j] != NULL) {
					if (buffer[i][j] > highLimit) { buffer[i][j] = highLimit; }
					else{
						if (buffer[i][j] < lowLimit) { buffer[i][j] = lowLimit; }
					}
				}
			}
		}
		return true;
}

extern "C" __declspec(dllexport) int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH])
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

void appropriate(int* toArray, const int* fromArray, int columns){
	for (int j=0; j<columns; j++){
		toArray[j] = fromArray[j];
	}
}//приравнивает одномерные массивы

void echo(int* toBuffer,const int* fromBuffer, int length){
	for (int j=0; j<length; j++){
		toBuffer[j] = (int) (coeff*fromBuffer[j]);
	}
}//умножаем одномерный массив на коэффициент

int sumBuffers(int* buffer,const int* memoryBuffer){
	int firstEcho[LENGTH];//массив для первого эха
	int secondEcho[LENGTH];//массив для второго эха
	int firstMemoryBuffer[DELAY];//массив для остатка от первого эха
	int secondMemoryBuffer[2*DELAY];//массив для остатка от второго эха

	if (memoryBuffer != NULL) {//если уже не первый буффер со звуком
		for (int i=0; i<2*DELAY; i++){
			secondMemoryBuffer[i] = memoryBuffer[LENGTH - 2*DELAY + i];
		}
		for (int i=0; i<DELAY; i++){
			firstMemoryBuffer[i] = memoryBuffer[LENGTH - DELAY +i];
		}
	}else{//если начало песни, то есть обрабатываем первый буффер со свуком
		for (int i=0; i<2*DELAY; i++){
			secondMemoryBuffer[i] = 0;
		}
		for (int i=0; i<DELAY; i++){
			firstMemoryBuffer[i] = 0;
		}
	}
	
	if (NULL != buffer){
		echo((int*)firstEcho, (const int*)buffer, LENGTH);//получили первое эхо
		echo((int*)secondEcho,(const int*)firstEcho, LENGTH);//получили второе эхо
		
		echo((int*)firstMemoryBuffer, (const int*)firstMemoryBuffer,DELAY);//получили первое эхо остатка
		echo((int*)secondMemoryBuffer, (const int*)secondMemoryBuffer, 2*DELAY);
		echo((int*)secondMemoryBuffer, (const int*)secondMemoryBuffer, 2*DELAY);//получили второе эхо остатка
				
		for (int j=0; j<LENGTH; j++){
			if (j<DELAY) {buffer[j] = buffer[j] + firstMemoryBuffer[j];}
			if (j<2*DELAY) {buffer[j] = buffer[j] + secondMemoryBuffer[j];}
			if (j>=DELAY) {buffer[j] = buffer[j] + firstEcho[j-DELAY];}
			if (j>=2*DELAY) {buffer[j] = buffer[j] + secondEcho[j-2*DELAY];}
		}//создаем выходной буффер
		
	}
	return 0;
}

void setMemory(int buffer[CANALS][LENGTH], bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]){
	if (flagOfFirstUse){
		for (int i=0; i<CANALS; i++){
			for (int j=0; j<LENGTH; j++){
				memoryBuffer[i][j] = NULL;
			}
		}
	}
	int tempMemoryBuffer[CANALS][LENGTH];
	for (int i=0; i<CANALS; i++){
		appropriate((int*)tempMemoryBuffer[i],(const int*)buffer[i],LENGTH);
		if (!flagOfFirstUse) {
			sumBuffers((int*)buffer[i],memoryBuffer[i]);
		}else{
			sumBuffers((int*)buffer[i], (int*)NULL);
		}
	}
	for (int i=0; i<CANALS; i++){
		appropriate((int*)memoryBuffer[i],(const int*)tempMemoryBuffer[i],LENGTH);
	}
}

extern "C" __declspec(dllexport) int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]){
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