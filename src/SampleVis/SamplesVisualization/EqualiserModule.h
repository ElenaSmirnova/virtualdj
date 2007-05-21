//#include "FFT.h"
#define BORDER 50
#define LENGTH 16384
#include <math.h>
#ifndef PI
#define PI (3.14159265358979323846)
#endif

typedef void (*fft_func)(int*,int*,int,bool);
typedef void (*effect_func)(int*,int*,int,int);
typedef void (*filter_func)(int*, int*, int);
typedef void (*test_func)(int*, int*, filter_func, fft_func, int, int);
//typedef void (*effect_func)();

class CEqualiserModule
{
	CBrush* pSamplesBrush;
	CBrush* pFreqBrush;
	void SetBrushes();				// �-�� ��� ��������������� ���������� � ���������
	void LoadDlls();
	
	HINSTANCE hFFT;
	HINSTANCE hEffects;
	fft_func FFT;
	test_func FreqFilter;

public:

// ��-�� ������


	int m_iVolume;					// ��������� ����� (1-100), ���� �� ������������
	
	int* m_ptiSampleL;				// ��������� �� ������ ������� ������ ������

//	int* m_ptiFreqRealFactorL;		// ��������� �� ������ Re() �� ������������� ����� �������������� ����� ��� ������ ������
//	int* m_ptiFreqImagFactorL;		// ��������� �� ������ Im() �� ������������� ����� �������������� ����� ��� ������ ������

	int* m_ptiSampleR;				// ��������� �� ������ ������� ������ ������

//	int* m_ptiFreqRealFactorR;		// ��������� �� ������ Re() �� ������������� ����� �������������� ����� ��� ������� ������
//	int* m_ptiFreqImagFactorR;		// ��������� �� ������ Im() �� ������������� ����� �������������� ����� ��� ������� ������

	int m_iSampleLength;			// ���-�� �������, � �������� �� ��������(����������� ������ ���� �������� 2)

// ������������
	CEqualiserModule();				// �����������, �������� ������ ������� =border, ������������� � EqualiserModule.cpp
	CEqualiserModule(int, int);		// �����������, �������� ������ ������� � ���� ��������� � �������� ��������(1�� ��������) � �����(2�� ��������)

	void PaintSample(CDC* );		// ��������� ������� �������(����� � ����� ��������������� ��������� ������ �����)
//	void PaintFreq(CDC* );			// ��������� ������� ������
	void Filter(filter_func,int);
// ����������
	~CEqualiserModule();
};