#ifndef _SAPMYPROCESSING_H_
#define _SAPMYPROCESSING_H_

//	SapMyProcessing.h : header file
//

#include "SapClassBasic.h"
//#include "Example_SaperaDlg.h"
#include "My_ImgProcessing.h"

//
// SapMyProcessing class declaration
//
class SapMyProcessing : public SapProcessing
{
public:
	// Constructor/Destructor
	SapMyProcessing(SapBuffer *pBuffers, SapBuffer *pBuffersPro, SapProCallback pCallback, void *pContext);
	virtual ~SapMyProcessing();

protected:
	virtual BOOL Run();

	SapAcquisition *m_Acq;
	SapBuffer      *m_BuffersPro; 
	
public:
	My_ImgProcessing m_MyImgProcessing;

	bool m_bContrast;

	int row, col;

	int minValue, maxValue;

	float averageValue;	

public:
	bool setPro(char* proName, bool bPro);
	void setAnalysis(int min, int max, float average);

public:
	bool ProcessImage(UINT8* pDst, UINT8* pSrc, int width, int height);
	void ContrastEnhance(UINT8* pDst, UINT8* pSrc, int width, int height);
}; 

#endif	// _SAPMYPROCESSING_H_

