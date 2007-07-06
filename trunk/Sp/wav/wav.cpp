// This is the main DLL file.

#include "wav.h"
#ifdef _MANAGED
#pragma managed(push, off)
#endif
#define COLUMNS 16384
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
void appropriate1(unsigned int toArray[][COLUMNS], const byte* fromArray, int columns,int channell)
{
	int i1;
	i1 = 0;
	if (channell == 2)
	{
		
		for (int j=0; j<columns; j++)
		{
			toArray[0][i1] = fromArray[j];
			j = j + 1;
			toArray[1][i1] = fromArray[j];
			i1 = i1 + 1;
		}
	}
	else 
	{
		for (int j=0; j<columns; j++)
		{
			toArray[0][j] = fromArray[j];
			toArray[1][j] = NULL;
		}
	}
}//разделяет одномерный массив на две строчки двумерного массива (8 bits)
void appropriate2(unsigned int toArray[][COLUMNS], unsigned short int* fromArray, int columns,int channell)
{
	int i1;
	i1 = 0;
	if (channell == 2)
	{
		
		for (int j=0; j<columns; j++)
		{
			toArray[0][i1] = fromArray[j];
			j = j + 1;
			toArray[1][i1] = fromArray[j];
			i1 = i1 + 1;
		}
	}
	else 
	{
		for (int j=0; j<columns; j++)
		{
			toArray[0][j] = fromArray[j];
			toArray[1][j] = NULL;
		}
	}
}//разделяет одномерный массив на две строчки двумерного массива (16 bits)
extern "C" __declspec(dllexport) void read2(char* name)
{
	int i = 0;
	FILE * f;
	TitleWave tw;
	
	f=fopen(name,"r");
	if ( f==0 ) { printf("Cannot open file - %s\n",name); return; }
	fread(&tw,sizeof(TitleWave),1,f);
	fclose(f);
	printf("LEN RIFF\t - %ld\n", tw.len_riff );
	if ( strncmp(tw.id_riff,"RIFF",4)!=0 )
		printf("problem - identificator RIFF\n");
		printf("LEN Chuck\t - %ld\n", tw.len_chuck );
	
	if ( strncmp(tw.id_chuck,"WAVE",4)!=0 )
		printf("problem - identificator CHUCK\n");
	if ( strncmp(tw.fmt,"fmt ",4)!=0 )
		printf("problem - identificatorН FMT\n");
	printf("Type\t\t - %d\n", tw.type );
	printf("Channels\t - %d\n", tw.channels );
	printf("Sample Per Sec\t - %d\n", tw.freq );
	printf("Bytes Per Sec\t - %d\n", tw.bytes );
	printf("Bits\t\t - %d\n", tw.bits );
	printf("Aligned\t\t - %d\n", tw.align );
	printf("LEN Data\t - %ld\n", tw.len_data );
	if ( strncmp(tw.id_data,"data",4)!=0 )
		printf("problem - identificator DATA\n");

	byte *samp8 = tw.sample;
	unsigned short int *samp16 = (unsigned short int *)tw.sample;
	unsigned int buff[2][COLUMNS];

	if (tw.bits == 8)
	{
		appropriate1(buff, samp8, tw.len_data,tw.channels);
		while (i<tw.len_data)
		{
			printf("sample\t - %d\n",buff[0][i]);
			if (tw.channels == 2)
			{
				printf("s\t - %d\n",buff[1][i]);
			}
			i=i+1;
		}
	}
	else
	{
		appropriate2(buff, samp16, 16384,tw.channels);
		while (i<16384)
		{
			printf("sample\t - %d\n",buff[0][i]);
			if (tw.channels == 2)
			{
				printf("s\t - %d\n",buff[1][i]);
			}
			i=i+1;
		}
	}
}

//TODO:
extern "C" __declspec(dllexport) void write(write_parameters* parameters)
{}

#ifdef _MANAGED
#pragma managed(pop)
#endif


