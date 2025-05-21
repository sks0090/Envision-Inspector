#pragma once
#include "pch.h"
#include "CChartDlg.h"
#include "My_Chart.h"

class MyImgAnalysis {
	typedef struct {
		int maxValue, minValue;

		double averageValue, stdValue;

		double* xAxisHorizontalProfile;
		double* valueHorizontalProfile;

	}AnalysisStruct;
public:
	MyImgAnalysis();
	~MyImgAnalysis();
public:		// Variables
	AnalysisStruct* m_structAnalysis;

	CChartViewer* m_ChartViewer;

	bool m_bInit;
	bool m_bThreadAnalysis, m_bThreadAnalysisProc;
	bool m_bChart;
	
	int m_nSizeX, m_nSizeY;
	int m_nChartSizeX, m_nChartSizeY;
	
	int row, col;

	unsigned char* m_data8;			// 8bit data
	unsigned short* m_data16;		// 16bit data

	CWinThread* m_ThreadAnalysis;

	CEvent m_eventThreadAnalysis;

public:		// Methods
	// Thread
	static UINT AnalysisThread(LPVOID lParam);		// Img Analysis Thread
	// General
	bool Init(unsigned char *data, int width, int height);
	void Free(void);
	void Analyze(unsigned char* pData, int width, int height);
	void CalStatistic();
	bool addChart(CChartViewer* viewer, int width, int height);
	void drawChart();
	void onSizeChart(UINT nType, int cx, int cy);
	void OnViewPortChanged();
	void updateImageMap();
};