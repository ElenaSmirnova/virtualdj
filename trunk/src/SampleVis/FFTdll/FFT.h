#include <math.h>

#ifndef PI
#define PI (3.14159265358979323846)
#endif

# define DIG_REV(i, m, j) \
	do { \
	unsigned _ = (i); \
	_ = ((_ & 0x33333333) << 2) | ((_ & ~0x33333333) >> 2); \
	_ = ((_ & 0x0F0F0F0F) << 4) | ((_ & ~0x0F0F0F0F) >> 4); \
	_ = ((_ & 0x00FF00FF) << 8) | ((_ & ~0x00FF00FF) >> 8); \
	_ = ((_ & 0x0000FFFF) << 16) | ((_ & ~0x0000FFFF) >> 16); \
	(j) = _ >> (m); \
	} while (0)
 


// на вход подаются массивы с действительной и комплексной частью коэффициентов соответственно
extern "C" __declspec(dllexport) void FFT(int* index_signal1, int* index_signal2, int Npoint, bool direction);


// создание таблицы из Npoint sin и cos
void gen_twiddle32x32(int *w, int n);
// ф-ия, где производятся фактически все подсчеты коэф-тов
void MainFFTCalculation(const int * w,int n,int * x,int * y);		
// ф-ия для предварительной подготовки перед запуском fft_cn1 при прямом БПФ
void PreconditioningDirectFFT(int*  real, int*  image, int* w1,int point);
// ф-ия для предварительной подготовки перед запуском fft_cn1 при обратном БПФ
void PreconditioningInverseFFT(int* real, int* image, int* w1,int point);
// ф-ия для преобразования double к short
int d2s(double d);

void HammingWindowApply(int* real, int point);


