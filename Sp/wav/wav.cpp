// This is the main DLL file.

#include "wav.h"
#include <iostream>
using namespace std;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
void appropriate(int **toArray, const int *fromArray,long int columns,int channell)
{
	int i1 = 0;
	if (channell == 2){
		for (long int j=0; j < 2*columns; j++){
			toArray[i1][0] = fromArray[j];
			j = j + 1;
			toArray[i1][1] = fromArray[j];
			i1 = i1 + 1;
		}
	}else{
		for (long int j = 0; j < columns; j ++){
			toArray[j][0] = (int)fromArray[j];
			toArray[j][1] = NULL;
		}
	}
}//разделяет одномерный массив на две строчки двумерного массива

extern "C" __declspec(dllexport) void read2(SoundBuffer *buffer, char* name)
{
	FILE * f;
	TitleWave tw;
	
	f=fopen(name,"rb");
	if ( f == 0 ){ 
		printf("Cannot open file - %s\n", name); 
		return; 
	}
	fread(&tw,sizeof(TitleWave),1,f);

	long i=0;
	int *sample = new int[10000000];
	memset(sample, 0, 10000000*sizeof(int));
	while (!feof(f)){
		if (tw.bits == 8){
			fread(&sample[i], 1, 1, f);
		}else{
			if(tw.bits == 16){
				fread(&sample[i], 2, 1, f);
			}else{
				return;
			}
		}
		i++;
	}
	
	if (tw.channels == 1){
		buffer->setLength(i-1);
		appropriate(buffer->buff, sample, buffer->getLength(), tw.channels);
	}else{
		if (tw.channels == 2){
			buffer->lastSimbol = i-1;
			buffer->setLength((i-1)/2+1);
			appropriate(buffer->buff, sample, buffer->getLength(), tw.channels);
		}else{
			return;
		}
	}

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

	buffer->titleWave = tw;

	printf("len\t - %d\n", buffer->getLength());
	printf("fr\t - %d\n", buffer->titleWave.freq);

	fclose(f);
}

//TODO:
extern "C" __declspec(dllexport) void write2(SoundBuffer *buffer, char* name)
{
	FILE *f;
	
	fopen_s(&f,name,"wb+"); //create new file if it doesn't exist, else overwrite the file
	fwrite(&(buffer->titleWave), sizeof(TitleWave), 1, f);

	if (buffer->titleWave.bits == 8){
		if (buffer->titleWave.channels == 2){
			for (long int j = 0; j < buffer->getLength()-1; j++){
				fwrite(&buffer->buff[j][0], 1, 1, f);
				fwrite(&buffer->buff[j][1], 1, 1, f);
				if (2*j+3 == buffer->lastSimbol){
						fwrite(&buffer->buff[j+1][0], 1, 1, f);
				}
			}
		}else{
			for (long int j = 0; j < buffer->getLength(); j ++){
				fwrite(&buffer->buff[j][0], 1, 1, f);
			}
		}
	}else{
		if (buffer->titleWave.bits == 16){
			if (buffer->titleWave.channels == 2){
				for (long int j = 0; j < buffer->getLength()-1; j ++){
					fwrite(&buffer->buff[j][0], 2, 1, f);
					fwrite(&buffer->buff[j][1], 2, 1, f);
					if (2*j+3 == buffer->lastSimbol){
						fwrite(&buffer->buff[j+1][0], 2, 1, f);
					}
				}
			}else{
				for (long int j = 0; j < buffer->getLength(); j ++){
					fwrite(&buffer->buff[j][0], 2, 1, f);
				}
			} 
		}
	}

	fclose(f);
}

#ifdef _MANAGED
#pragma managed(pop)
#endif