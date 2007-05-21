
#define LENGTH 16384

typedef void (*fft_func)(int*,int*,int,bool);
typedef void (*effect_func)(int*,int*,int,int);
typedef void (*filter_func)(int*, int*, int);

extern "C" __declspec(dllexport) void Filter(int* SampleL, int* SampleR, filter_func pfnFilter, fft_func FFT, int SampleLength, int pos);