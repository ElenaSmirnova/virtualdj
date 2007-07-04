// This is the main DLL file.

#include "wav.h"
#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
extern "C" __declspec(dllexport) void read(char* name)
{
	int i = 0;
	printf("enter name of .wav file\n");
	printf("Hello world!\n");
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
		printf("problem - identificatorÍ FMT\n");
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

	if (tw.bits == 8)
	{
    	while (samp8[i]!=0)
		{
			printf("sample\t - %d\n",samp8[i]);
			i=i+1;
		}
	}
	else
	{
    	while (samp16[i]!=0)
		{
			printf("sample\t - %d\n",samp16[i]);
			i=i+1;
		}
	}
 /*i=0;
	while (tw.sample1[i]!=0)
	{
		printf("sample\t - %d\n",tw.sample1[i]);
		i=i+1;
	}*/
	//printf("sample\t - %d\n",tw.fg);
}

//TODO:
extern "C" __declspec(dllexport) void write(write_parameters* parameters)
{}

#ifdef _MANAGED
#pragma managed(pop)
#endif


