#include "pch.h"
#include "My_ImgProcessing.h"
#include <memory.h>

bool My_ImgProcessing::GetHistogram( unsigned char* img, int wd, int hg)
{
	memset(histogram, 0, sizeof(histogram));
	for (row = 0; row < hg; row++) {
		for (col = 0; col < wd; col++) {
			histogram[img[row * wd + col]]++;
		}
	}

	return true;
}

bool My_ImgProcessing::SetHistogramEQ(unsigned char* outImg, unsigned char* inImg, int wd, int hg)
{
	int i;
	int cdf8[256];
	int lut8[256];
	int cdfMin = 255;

	// cdf 계산
	cdf8[0] = histogram[0];
	for (i = 1; i < 255; i++)
	{
		cdf8[i] = histogram[i] + cdf8[i - 1];
	}

	// min cdf 계산
	for (i = 1; i < 255; i++)
	{
		if (cdf8[i] != 0) {
			cdfMin = cdf8[i];
			break;
		}
	}

	// lut 계산
	for (i = 1; i < 255; i++)
	{
		lut8[i] = (cdf8[i] - cdfMin) * 255 / (wd * hg - cdfMin);
		if (lut8[i] < 0)
		{
			lut8[i] = 0;
		}
	}

	// Histogram equalize
	for (row = 0; row < hg; row++) {
		for (col = 0; col < wd; col++) {
			outImg[row * wd + col] = lut8[inImg[row * wd + col]];
		}
	}

	return true;
}