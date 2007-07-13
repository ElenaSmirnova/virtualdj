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
void appropriate1(int **toArray, const byte *fromArray,long int columns,int channell)
{
	int i1;
	i1 = 0;
	if (channell == 2)
	{
		
		for (long int j = 0; j < columns; j ++)
		{
			toArray[i1][0] = fromArray[j];
			j = j + 1;
			toArray[i1][1] = fromArray[j];
			i1 = i1 + 1;
		}
	}
	else 
	{
		for (long int j = 0; j < columns; j ++)
		{
			toArray[j][0] = (int)fromArray[j];
			toArray[j][1] = NULL;
		}
	}
}//��������� ���������� ������ �� ��� ������� ���������� ������� (8 bits)
void appropriate2(int **toArray, short int *fromArray, long int columns,int channell)
{
	int i1;
	i1 = 0;
	if (channell == 2)
	{
		
		for (long int j = 0; j < columns; j ++)
		{
			toArray[i1][0] = fromArray[j];
			j = j + 1;
			toArray[i1][1] = fromArray[j];
			i1 = i1 + 1;
		}
	}
	else 
	{
		for (long int j = 0; j < columns; j ++)
		{
			toArray[j][0] = fromArray[j];
			toArray[j][1] = NULL;
		}
	} 
}//��������� ���������� ������ �� ��� ������� ���������� ������� (16 bits)
extern "C" __declspec(dllexport) void read2(SoundBuffer *buffer, char* name)
{
	int i = 0;
	FILE * f;
	TitleWave tw;
	
	f=fopen(name,"r");
	if ( f == 0 ) 
	{ 
		printf("Cannot open file - %s\n", name); 
		return; 
	}
	fread(&tw,sizeof(TitleWave),1,f);
	fclose(f);
	printf("LEN RIFF\t - %ld\n", tw.len_riff );
	if ( strncmp(tw.id_riff,"RIFF",4)!=0 )
		printf("problem - identificator RIFF\n");
		printf("LEN Chuck\t - %ld\n", tw.len_chuck );
	
	if ( strncmp(tw.id_chuck,"WAVE",4)!=0 )
		printf("problem - identificator CHUCK\n");
	if ( strncmp(tw.fmt,"fmt ",4)!=0 )
		printf("problem - identificator� FMT\n");
	printf("Type\t\t - %d\n", tw.type );
	printf("Channels\t - %d\n", tw.channels );
	printf("Sample Per Sec\t - %d\n", tw.freq );
	printf("Bytes Per Sec\t - %d\n", tw.bytes );
	printf("Bits\t\t - %d\n", tw.bits );
	printf("Aligned\t\t - %d\n", tw.align );
	printf("LEN Data\t - %ld\n", tw.len_data );
	if ( strncmp(tw.id_data,"data",4)!=0 )
		printf("problem - identificator DATA\n");

	if ((tw.bits == 16) && ( tw.channels == 2)){
		buffer->setLength(tw.len_data/4);
	}else{
		buffer->setLength(tw.len_data);
	}

	buffer->frequency = tw.freq;
	byte *samp8 = tw.sample;
	short int *samp16 = (short int *)tw.sample;

	i = 0;
	if (tw.bits == 8)
	{
		appropriate1(buffer->buff, samp8, tw.len_data, tw.channels);
		while (i < tw.len_data)
		{
			printf("sampleChannel1\t - %d\n", buffer->buff[i][0]);
			if (tw.channels == 2)
			{
				printf("sampleChannel2\t - %d\n", buffer->buff[i][1]);
			}
			i = i+1;
		}
	}
	else
	{
		appropriate2(buffer->buff, samp16, tw.len_data/2, tw.channels);
		while (i < tw.len_data/4)
		{
			printf("sampleChannel1\t - %d\n", buffer->buff[i][0]);
			if (tw.channels == 2)
			{
				printf("sampleChannel2\t - %d\n", buffer->buff[i][1]);
			}
			i = i+1;
		}
	}
	printf("len\t - %d\n", buffer->getLength());
	printf("fr\t - %d\n", buffer->frequency);
}

//TODO:
extern "C" __declspec(dllexport) void write2(SoundBuffer *buffer, char* name)
{
	char* name1 = "I:\\virtualdj\\Sp\\sound\\TC Delete Complete.wav";
	char* name2 = "I:\\virtualdj\\Sp\\sound\\newfile.wav";
	long int i;
	i = 0;
	FILE * f, *f1;
	TitleWave tw;
	//Buf bb;
	
	f = fopen(name1,"r");
	if ( f == 0 ) { 
		printf("Cannot open file - %s\n", name1);
		return; 
	}
	fread(&tw,sizeof(TitleWave), 1, f);
	fclose(f);

	f1 = fopen(name2,"w+"); //create new file if it doesn't exist, else overwrite the file
	fwrite(&tw,46, 1, f1); 
	fwrite(buffer->buff, buffer->getLength(), 1, f1);
	fclose(f1);
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


