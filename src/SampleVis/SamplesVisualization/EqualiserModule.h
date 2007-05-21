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
	void SetBrushes();				// ф-ия для предварительной подготовки к отрисовке
	void LoadDlls();
	
	HINSTANCE hFFT;
	HINSTANCE hEffects;
	fft_func FFT;
	test_func FreqFilter;

public:

// св-ва класса


	int m_iVolume;					// громкость звука (1-100), пока не используется
	
	int* m_ptiSampleL;				// указатель на массив отчетов левого канала

//	int* m_ptiFreqRealFactorL;		// указатель на массив Re() от коэффициентов после преобразования Фурье для левого канала
//	int* m_ptiFreqImagFactorL;		// указатель на массив Im() от коэффициентов после преобразования Фурье для левого канала

	int* m_ptiSampleR;				// указатель на массив отчетов левого канала

//	int* m_ptiFreqRealFactorR;		// указатель на массив Re() от коэффициентов после преобразования Фурье для правого канала
//	int* m_ptiFreqImagFactorR;		// указатель на массив Im() от коэффициентов после преобразования Фурье для правого канала

	int m_iSampleLength;			// кол-во отчетов, с которыми мы работаем(обязательно должно быть степенью 2)

// конструкторы
	CEqualiserModule();				// конструктор, задающий массив отчетов =border, определенному в EqualiserModule.cpp
	CEqualiserModule(int, int);		// конструктор, задающий массив отчетов в виде синусоиды с заданным периодом(1ый параметр) и фазой(2ой параметр)

	void PaintSample(CDC* );		// отрисовка массива отчетов(здесь и далее подразумевается отрисовка левого канал)
//	void PaintFreq(CDC* );			// отрисовка массива частот
	void Filter(filter_func,int);
// деструктор
	~CEqualiserModule();
};