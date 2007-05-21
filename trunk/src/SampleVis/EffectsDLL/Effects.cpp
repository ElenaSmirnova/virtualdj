// EffectsDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "effects.h"
#include <math.h>
#ifdef _MANAGED
#pragma managed(push, off)
#endif


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void HammingWindowApply(int* real, int point)
{
	int k=point/2;
	for (int i=0; i<k; i++)
	{
		real[i]*=(double)i/k;
		real[i+k]*=(1 - (double)i/k);
	}
}

extern "C" __declspec(dllexport) void Filter(int* SampleL, int* SampleR, filter_func pfnFilter, fft_func FFT, int SampleLength, int pos)
{
	//предподготовка

	int tempLI[LENGTH];
	int tempLR[LENGTH];
	int tempRI[LENGTH];
	int tempRR[LENGTH];

	int* oldSampleL=new int[SampleLength-pos];
	int* oldSampleR=new int[SampleLength-pos];

	for (int j=0; j < LENGTH/2; j++)
	{
		oldSampleL[j]=SampleL[j+pos];
		SampleL[j+pos]*=1 - 2 * (double)j/LENGTH;
		oldSampleR[j]=SampleR[j+pos];
		SampleR[j+pos]*=1 - 2 * (double)j/LENGTH;
	}

	for(int j=LENGTH/2; j < SampleLength - pos; j++)
	{
		oldSampleL[j]=SampleL[j+pos];
		SampleL[j+pos]=0;
		oldSampleR[j]=SampleR[j+pos];
		SampleR[j+pos]=0;
	}
	
	//основные вычисления
	int i;
	for (i=pos; i < SampleLength - LENGTH; i+=LENGTH/2)
	{
		for (int j=0; j < LENGTH; j++)
		{
			tempLR[j]=oldSampleL[j + i-pos];
			tempLI[j]=0;
			tempRR[j]=oldSampleR[j + i-pos];
			tempRI[j]=0;
		}
		HammingWindowApply(tempLR, LENGTH);
		HammingWindowApply(tempRR, LENGTH);
/*		FFT(tempLR, tempLI, LENGTH, true);
		FFT(tempRR, tempRI, LENGTH, true);

		if(pfnFilter)
		{
			pfnFilter(tempLR, tempLI, LENGTH);
			pfnFilter(tempLR, tempLI, LENGTH);
		}

		FFT(tempLR, tempLI, LENGTH, false);
		FFT(tempRR, tempRI, LENGTH, false);
*/
		for (int j=0; j < LENGTH; j++)
		{
			SampleL[i+j]+=tempLR[j];
			SampleR[i+j]+=tempRR[j];
		}

	}

	// обработка хвоста

	int k = SampleLength-pos - LENGTH;

	if (k==0)
	{
		delete [] oldSampleL;
		delete [] oldSampleR;
		return;
	}

	for (int j=0; j < LENGTH; j++)
	{
		tempLR[j]=oldSampleL[k+j];
		tempLI[j]=0;
		tempRR[j]=oldSampleR[k+j];
		tempRI[j]=0;
	}
	HammingWindowApply(tempLR, LENGTH);
	HammingWindowApply(tempRR, LENGTH);
/*	FFT(tempLR, tempLI, LENGTH, true);
	FFT(tempRR, tempRI, LENGTH, true);

	if(pfnFilter)
	{
		pfnFilter(tempLR, tempLI, LENGTH);
		pfnFilter(tempLR, tempLI, LENGTH);
	}
	FFT(tempLR, tempLI, LENGTH, false);
	FFT(tempRR, tempRI, LENGTH, false);
*/
	// нормализация хвоста
	// работает неправильно, но по этому можно осознать благородство помыслов))
	int maxSL=0;
	int	maxTL=0;
	int maxSumL=0;
	int maxSR=0;
	int	maxTR=0;
	int maxSumR=0;

	for (int j=i + LENGTH/2; j < SampleLength; j++)
	{// считаем, что в сумме будут отчеты >0
		if(abs(SampleL[j])>maxSL)	maxSL=abs(SampleL[j]);
		if(abs(SampleR[j])>maxSR)	maxSR=abs(SampleR[j]);

		if(abs(tempLR[LENGTH - (SampleLength-j)])>maxTL)	maxTL=abs(tempLR[LENGTH - (SampleLength-j)]);
		if(abs(tempRR[LENGTH - (SampleLength-j)])>maxTR)	maxTR=abs(tempRR[LENGTH - (SampleLength-j)]);

		SampleL[j]+=tempLR[LENGTH - (SampleLength-j)];
		SampleR[j]+=tempRR[LENGTH - (SampleLength-j)];

		if(abs(SampleL[j])>maxSumL)	maxSumL=abs(SampleL[j]);
		if(abs(SampleR[j])>maxSumR)	maxSumR=abs(SampleR[j]);
	}
	// здесь название теряет свою мнемоничность(если она вообще была)
	maxSL=maxSL < maxTL ? maxTL : maxSL;
	maxSR=maxSR < maxTR ? maxTR : maxSR;
	if (maxSL!=maxSumL)
	{
		for (int j=i + LENGTH/2; j < SampleLength; j++)
			SampleL[j]*=maxSL/maxSumL;
	}
	if (maxSR!=maxSumR)
	{
		for (int j=i + LENGTH/2; j < SampleLength; j++)
			SampleR[j]*=maxSR/maxSumR;
	}


	delete [] oldSampleL;
	delete [] oldSampleR;
}



#ifdef _MANAGED
#pragma managed(pop)
#endif

