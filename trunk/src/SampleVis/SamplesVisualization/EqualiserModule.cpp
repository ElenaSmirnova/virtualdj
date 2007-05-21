#include "stdafx.h"
#include "EqualiserModule.h"


void CEqualiserModule::SetBrushes()
{
	pSamplesBrush=new CBrush;
	pFreqBrush=new CBrush;

	COLORREF crSamplesClr=RGB(128,0,0);
	COLORREF crFreqClr=RGB(128,128,128);

	pSamplesBrush->CreateSolidBrush(crSamplesClr);
	pFreqBrush->CreateSolidBrush(crFreqClr);
}

void CEqualiserModule::LoadDlls()
{
	hFFT=LoadLibrary("debug\\FFT");
	if (hFFT==NULL) throw "FFT.dll loading error";
	FFT=(fft_func)GetProcAddress(hFFT,"FFT");
	if (FFT==NULL) throw "FFT func error";

	hEffects=LoadLibrary("debug\\Effects");
	if (hEffects==NULL) throw "Effects.dll loading error";
	FreqFilter=(test_func)GetProcAddress(hEffects,"Filter");
	if (FreqFilter==NULL) throw "FreqFilter func error";
}

CEqualiserModule::CEqualiserModule(): m_iVolume(50), m_iSampleLength(1024), FFT(NULL), FreqFilter(NULL)
{
	SetBrushes();
	LoadDlls();
	
	m_ptiSampleL=new int[m_iSampleLength];
	m_ptiSampleR=new int[m_iSampleLength];
	for (int i=0; i<m_iSampleLength; i++)
	{
		m_ptiSampleL[i]=BORDER;
		m_ptiSampleR[i]=BORDER;
	}
}

CEqualiserModule::CEqualiserModule(int iPeriod, int iPhase): m_iVolume(50), m_iSampleLength(35000), FFT(NULL), FreqFilter(NULL)
{
	SetBrushes();
	LoadDlls();

	m_ptiSampleL=new int[m_iSampleLength];
	m_ptiSampleR=new int[m_iSampleLength];
	float t=2*PI/iPeriod;
	for (int i=0; i<m_iSampleLength; i++)
	{
		m_ptiSampleL[i]=BORDER*(sin(iPhase+t*i) + 1);
		m_ptiSampleR[i]=m_ptiSampleL[i];
	}
}

void CEqualiserModule::PaintSample(CDC* pDC)
{
	CRect rect;
	int max=0;
	for (int i=1; i<m_iSampleLength; i++)
		if (m_ptiSampleL[i]>m_ptiSampleL[max]) max=i;
	float scale_coef=300.0/m_ptiSampleL[max];
	rect.bottom=304;
	int dist=ceil(m_iSampleLength/80.0); // после стоит изменить для переменного размера окна
	float curr_sample=0;
	for (int i=0; i<80; i++)
	{
		for (int j=dist*i; j<dist*(i+1)&&j<m_iSampleLength; j++)
			curr_sample+=m_ptiSampleL[j];
		curr_sample/=dist;
		rect.top=rect.bottom-curr_sample*scale_coef;
		rect.left=i*8+1 +5;
		rect.right=(i+1)*8-1 +5;
		pDC->FillRect(rect,pSamplesBrush);
		curr_sample=0;
	}
}

/*
void CEqualiserModule::PaintFreq(CDC* pDC)
{
	int* ptiAmplitude=new int[m_iSampleLength/2];
	for (int i=0; i<m_iSampleLength/2; i++)
		ptiAmplitude[i]=sqrt((double)m_ptiFreqRealFactorL[i]*(double)m_ptiFreqRealFactorL[i] + (double)m_ptiFreqImagFactorL[i]*(double)m_ptiFreqImagFactorL[i]);
	CRect rect;
	rect.bottom=619;
	int max=0;
	for (int i=1; i<m_iSampleLength/2; i++)
		if (ptiAmplitude[i]>ptiAmplitude[max]) max=i;
	double scale_coef;
	scale_coef=300.0/ptiAmplitude[max];
	int dist=ceil(m_iSampleLength/2/40.0); 
	double curr_freq=0;
	for (int i=0; i<40; i++)
	{
		for (int j=dist*i; j<dist*(i+1)&&j<m_iSampleLength/2; j++)
			curr_freq+=ptiAmplitude[j];
		curr_freq/=dist;
		rect.top=rect.bottom-curr_freq*scale_coef;
		rect.left=i*16+1 +5;
		rect.right=(i+1)*16-1 +5;
		pDC->FillRect(rect,pFreqBrush);
		curr_freq=0;
	}
}
*/

void CEqualiserModule::Filter(filter_func pfnFilter, int pos)
{
	//предподготовка

	if (m_iSampleLength-pos<LENGTH)
		return;

	if(!FFT) throw "FFT func error";
	if(!FreqFilter) throw "FreqFilter func error";
	
	FreqFilter(m_ptiSampleL, m_ptiSampleL, pfnFilter, FFT, m_iSampleLength, pos);
}

CEqualiserModule::~CEqualiserModule()
{
//	if (m_ptiFreqRealFactorL) delete [] m_ptiFreqRealFactorL;
//	if (m_ptiFreqImagFactorL) delete [] m_ptiFreqImagFactorL;
	if (m_ptiSampleL) delete [] m_ptiSampleL;
//	if (m_ptiFreqRealFactorR) delete [] m_ptiFreqRealFactorR;
//	if (m_ptiFreqImagFactorR) delete [] m_ptiFreqImagFactorR;
	if (m_ptiSampleR) delete [] m_ptiSampleR;
	if (pFreqBrush) delete pFreqBrush;
	if (pSamplesBrush) delete pSamplesBrush;
	if (hFFT) FreeLibrary(hFFT);
	if (hFFT) FreeLibrary(hEffects);
}
