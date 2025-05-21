#pragma once
class My_ImgProcessing
{
public:
	int row, col;

	int histogram[255];

public:
	bool GetHistogram( unsigned char* img, int wd, int hg);
	bool SetHistogramEQ(unsigned char* outImg, unsigned char* inImg, int wd, int hg);
};
