// FFTdll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "FFT.h"
#include <stdio.h>

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
		real[i]=d2s(real[i] * (double)i/k);
		real[i+k]=d2s(real[i+k]*(1 - (double)i/k));
	}
}

void _nassert(bool bAssertion)
{
	if (!bAssertion)
		printf("FFT exception");
}


extern "C" __declspec(dllexport) void FFT(int* index_signal1, int* index_signal2, int Npoint, bool direction)
{
	_nassert(index_signal1);
	_nassert(index_signal2||direction);
	if (!index_signal2)
		index_signal2=new int[Npoint];
	//TODO: define&init index_signal1,index_signal2,Filter
	int* w1= new int[2*Npoint];

	/*заполнение таблицы синусов и косинусов дл€ fft*/
	gen_twiddle32x32(w1, Npoint); 
	if (direction)
		PreconditioningDirectFFT(index_signal1,index_signal2,w1,Npoint);
	else PreconditioningInverseFFT(index_signal1,index_signal2,w1,Npoint);

}

int d2s(double d)
{
	d = floor(0.5 + d); /* Explicit rounding to integer */
	if (d >= 32767.0) return 32767;
	if (d <= -32678.0) return -32768;
	return (short)d;
}

void gen_twiddle32x32(int *w, int n)
{
	double M = 32767.5;
	for (int i=0; i<n; i++)
	{
		w[2*i]=d2s(M * sin(2 * PI * i / n));
		w[2*i+1]=d2s(M * cos(2 * PI * i / n));
	}
}

void PreconditioningDirectFFT(int*  real, int*  image,int* w1 ,int point){
	int index;
	/*заполнение x[],y[]*/
	int* x=new int[2*point];
	int* y=new int[2*point];

	for(index=0;index<point;index++)
	{    
		x[index*2]=(real[index]);
		x[index*2+1]=0;			// здесь вводилась комплексна€ часть, но в нашем случае она всегда равна 0
		y[index*2]=0;
		y[index*2+1]=0;    	
	}	
	/*fft*/   
	MainFFTCalculation(w1,point,x,y);
	/*спектр*/
	for(index=0;index<point;index++)
	{
		real[index]=(y[2*index]);
		image[index]=(y[2*index+1]);
	}
}

void PreconditioningInverseFFT(int* real, int* image , int* w1, int point){
	int index;
	/*заполнение x[],y[],трансформаци€ y[] дл€ ifft*/
	int* x=new int[2*point];
	int* y=new int[2*point];

	for(index=0;index<point;index++)
	{
		y[index*2]=((real[index])/point);
		y[index*2+1]=-((image[index])/point);
		x[index*2]=0;
		x[index*2+1]=0;    	
	}              	 	 	
	/*ifft*/     
	MainFFTCalculation(w1,point,y,x);
	for(index=0;index<point;index++)
	{
		real[index]=(x[2*index]);
//		image[index]=0; // здесь выводилась комплексна€ часть, но будем считать, что она равна 0
	} 	
/*	//јнтиќконна€ функци€
	if (number > 5)  {*/
	HammingWindowApply(real,point);
	//	AntiHammingWindowApply1(real);
//	}*/
}


void MainFFTCalculation(const int * w,int n,int * x,int * y) 
{
	int stride, i, j, k_1, t, s, m;
	int xh0, xh1, xh20, xh21;
	int xl0, xl1, xl20, xl21;
	int xt0, yt0, xt1, yt1;
	int xt2, yt2, xt3, yt3;
#ifndef NOASSUME
	_nassert((int)x % 8 == 0);
	_nassert((int)y % 8 == 0);
	_nassert((int)w % 8 == 0);
	_nassert(n >= 16);
	_nassert(n < 32768);
#endif
	for (stride = n, t = 0; stride > 4; stride >>= 2)
	{
		s = stride >> 2;
#ifndef NOASSUME
		_nassert(stride >= 16);
		_nassert(s >= 4);
#endif
		for (i = 0; i < n; i += stride)
		{
#ifndef NOASSUME
			_nassert(i % 4 == 0);
			_nassert(s >= 4);
#endif
			for (j = 0; j < s; j += 2)
			{
				for (k_1 = 0; k_1 < 2; k_1++)
				{
					int w1c, w1s, w2c, w2s, w3c, w3s;
					int x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
					int y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;

					x0r = x[2*(i+j+k_1 ) + 0]; x0i = x[2*(i+j+k_1 ) + 1];
					x1r = x[2*(i+j+k_1 + s) + 0]; x1i = x[2*(i+j+k_1 + s) + 1];
					x2r = x[2*(i+j+k_1 + 2*s) + 0]; x2i = x[2*(i+j+k_1 + 2*s) + 1];
					x3r = x[2*(i+j+k_1 + 3*s) + 0]; x3i = x[2*(i+j+k_1 + 3*s) + 1];

					w1s = w[t + 2*k_1 + 6*j + 0]; w1c = w[t + 2*k_1 + 6*j + 1];
					w2s = w[t + 2*k_1 + 6*j + 4]; w2c = w[t + 2*k_1 + 6*j + 5];
					w3s = w[t + 2*k_1 + 6*j + 8]; w3c = w[t + 2*k_1 + 6*j + 9];

					xh0 = x0r + x2r;
					xh1 = x0i + x2i;
					xh20 = x1r + x3r;
					xh21 = x1i + x3i;
					xl0 = x0r - x2r;
					xl1 = x0i - x2i;
					xl20 = x1r - x3r;
					xl21 = x1i - x3i;
					xt0 = xh0 + xh20;
					yt0 = xh1 + xh21;
					xt1 = xl0 + xl21;
					yt1 = xl1 - xl20;
					xt2 = xh0 - xh20;
					yt2 = xh1 - xh21;
					xt3 = xl0 - xl21;
					yt3 = xl1 + xl20;

					y0r = xt0;
					y0i = yt0;

					y1r= (((xt1>>14) *    w1c       + (yt1>>14) *     w1s)>>1)
						+(((xt1&0x3fff) * w1c       + (yt1&0x3fff) *  w1s)>>15);
					y1i= (((yt1>>14) *    w1c       - (xt1>>14) *     w1s)>>1) 
						+(((yt1&0x3fff) * w1c       - (xt1&0x3fff) *  w1s)>>15);
					y2r= (((xt2>>14) *    w2c       + (yt2>>14) *     w2s)>>1) 
						+(((xt2&0x3fff) * w2c       + (yt2&0x3fff) *  w2s)>>15);
					y2i= (((yt2>>14) *    w2c       - (xt2>>14) *     w2s)>>1) 
						+(((yt2&0x3fff) * w2c       - (xt2&0x3fff) *  w2s)>>15);
					y3r= (((xt3>>14) *    w3c       + (yt3>>14) *     w3s)>>1)
						+(((xt3&0x3fff) * w3c       + (yt3&0x3fff) *  w3s)>>15);
					y3i= (((yt3>>14) *    w3c       - (xt3>>14) *     w3s)>>1)
						+(((yt3&0x3fff) * w3c       - (xt3&0x3fff) *  w3s)>>15);


					x[2*(i+j+k_1 ) + 0] = y0r; x[2*(i+j+k_1 ) + 1] = y0i;
					x[2*(i+j+k_1 + s) + 0] = y1r; x[2*(i+j+k_1 + s) + 1] = y1i;
					x[2*(i+j+k_1 + 2*s) + 0] = y2r; x[2*(i+j+k_1 + 2*s) + 1] = y2i;
					x[2*(i+j+k_1 + 3*s) + 0] = y3r; x[2*(i+j+k_1 + 3*s) + 1] = y3i;
				}
			}
		}

		t += 6 * s;
	}
	for (i = 31, m = 1; (n & (1 << i)) == 0; i--, m++) ;
	s = n >> 2;
	for (i = 0; i < n; i += 4)
	{
		int x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
		int y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;
		x0r = x[2*(i + 0) + 0]; x0i = x[2*(i + 0) + 1];
		x1r = x[2*(i + 1) + 0]; x1i = x[2*(i + 1) + 1];
		x2r = x[2*(i + 2) + 0]; x2i = x[2*(i + 2) + 1];
		x3r = x[2*(i + 3) + 0]; x3i = x[2*(i + 3) + 1];
		y0r = (x0r + x2r) + (x1r + x3r);
		y0i = (x0i + x2i) + (x1i + x3i);
		y1r = (x0r - x2r) + (x1i - x3i);
		y1i = (x0i - x2i) - (x1r - x3r);
		y2r = (x0r + x2r) - (x1r + x3r);
		y2i = (x0i + x2i) - (x1i + x3i);
		y3r = (x0r - x2r) - (x1i - x3i);
		y3i = (x0i - x2i) + (x1r - x3r);
		DIG_REV(i, m, j); // Note: Result is assigned to ТjТ by the macro. 
		y[2*(j + 0) + 0] = y0r; y[2*(j + 0) + 1] = y0i;
		y[2*(j + s) + 0] = y1r; y[2*(j + s) + 1] = y1i;
		y[2*(j + 2*s) + 0] = y2r; y[2*(j + 2*s) + 1] = y2i;
		y[2*(j + 3*s) + 0] = y3r; y[2*(j + 3*s) + 1] = y3i;
	}
}



#ifdef _MANAGED
#pragma managed(pop)
#endif

