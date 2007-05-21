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
 


// �� ���� �������� ������� � �������������� � ����������� ������ ������������� ��������������
extern "C" __declspec(dllexport) void FFT(int* index_signal1, int* index_signal2, int Npoint, bool direction);


// �������� ������� �� Npoint sin � cos
void gen_twiddle32x32(int *w, int n);
// �-��, ��� ������������ ���������� ��� �������� ����-���
void MainFFTCalculation(const int * w,int n,int * x,int * y);		
// �-�� ��� ��������������� ���������� ����� �������� fft_cn1 ��� ������ ���
void PreconditioningDirectFFT(int*  real, int*  image, int* w1,int point);
// �-�� ��� ��������������� ���������� ����� �������� fft_cn1 ��� �������� ���
void PreconditioningInverseFFT(int* real, int* image, int* w1,int point);
// �-�� ��� �������������� double � short
int d2s(double d);

void HammingWindowApply(int* real, int point);


