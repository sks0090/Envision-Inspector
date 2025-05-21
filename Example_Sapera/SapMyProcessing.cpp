//	SapMyProcessing.cpp : implementation file
//
#include "pch.h"
#include "SapMyProcessing.h"

#include <math.h>


// Constructor/Destructor
SapMyProcessing::SapMyProcessing(SapBuffer *pBuffers, SapBuffer *pBuffersPro, SapProCallback pCallback, void *pContext)
: SapProcessing(pBuffers, pCallback, pContext)
{ 
	int width = m_pBuffers->GetWidth();

	m_BuffersPro  = pBuffersPro; 
	
	m_bContrast = false;
}

SapMyProcessing::~SapMyProcessing()
{
   if (m_bInitOK) 
 		Destroy();
}
//
// Processing Control
//
// Do image inversion
BOOL SapMyProcessing::Run()
{
	int width = m_pBuffers->GetWidth();
	int height = m_pBuffers->GetHeight();
	int pixelDepth = m_pBuffers->GetPixelDepth();
	int bytePerPixel = m_pBuffers->GetBytesPerPixel();
	
	void* pSrcbuf, * pDestbuf;
	UINT8* pSrc, * pDst;

	// Get source and destination buffer address
	m_BuffersPro->Next();
	m_BuffersPro->GetAddress(m_BuffersPro->GetIndex(), &pDestbuf);
	
	// This is CORRECT,  the current source buffer index is SapProcessing object buffer index
	m_pBuffers->GetAddress(GetIndex(), &pSrcbuf);

	pSrc = (UINT8*)pSrcbuf;
	pDst = (UINT8*)pDestbuf;

	minValue = 0;
	maxValue = 255;
	averageValue = 128;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////// Processing ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//memcpy(pDst, pSrc, width * height);

	if (m_bContrast) {
		//ProcessImage(pDst, pSrc, width, height);
		//ContrastEnhance(pDst, pSrc, width, height);
		m_MyImgProcessing.GetHistogram(pSrc, width, height);
		m_MyImgProcessing.SetHistogramEQ(pDst, pSrc, width, height);
	}
	else {
		// No Processing, Just copy
		for (int iByte = 0; iByte < width * height; iByte++)
		{
			//*pDst = 255 - *pSrc ;
			*pDst = *pSrc;
			pDst++;
			pSrc++;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

bool SapMyProcessing::ProcessImage(UINT8* pDst, UINT8* pSrc, int width, int height)
{
	for (int iByte = 0; iByte < width * height; iByte++)
	{
		//*pDst = maxValue - *pSrc ;
		*pDst = 255 - *pSrc;
		pDst++;
		pSrc++;
	}

	return true;
}

void SapMyProcessing::ContrastEnhance(UINT8* pDst, UINT8* pSrc, int width, int height)
{
	//float maxValue = 0;
	//float minValue = 255;
	//float sum = 0;
	//float average = 0;	
	
	// Min/Max 찾기
	//for (int iByte = 0; iByte < width * height; iByte++)
	//{
	//	if (maxValue < *pSrc)
	//	{
	//		maxValue = *pSrc;
	//	}
	//	if (minValue > *pSrc)
	//	{
	//		minValue = *pSrc;
	//	}
	//	sum = sum + *pSrc;
	//	pSrc++;
	//}
	//average = sum / (float)(width * height);
	//// 평균으로터 10% 편차
	//maxValue = average + (average * 0.05);
	//minValue = average - (average * 0.05);
	//
	//pSrc = pSrc - width * height;

	// 처리
	for (int iByte = 0; iByte < width * height; iByte++)
	{
		*pDst = (int)((float)((*pSrc - minValue) / (maxValue - minValue)) * 255.0);
		if (*pDst > 255)
			*pDst = 255;
		if (*pDst < 0)
			*pDst = 0;
		pDst++;
		pSrc++;
	}
}

bool SapMyProcessing::setPro(char* proName, bool bPro)
{
	if (!strcmp(proName, "contrast"))
	{
		m_bContrast = bPro;
	}

	return m_bContrast;
}

void SapMyProcessing::setAnalysis(int min, int max, float average)
{
	minValue = min;
	maxValue = max;
	averageValue = average;
}