#pragma once
#include "pch.h"
#include "ChartViewer.h"	// CharDirector
#pragma comment(lib, "chartdir70.lib")

class MyChart
{
public:
	CChartViewer *m_ChartViewer;

	int m_nChartSizeX, m_nChartSizeY;
	int m_length;

	double *m_xData, *m_yData;

	char* m_title;
	char *m_xAxisName, *m_yAxisName;

	bool m_bInit;
	bool m_bTitle;
	bool m_bAxisName;

public:
	MyChart();
	~MyChart();
	bool Init(CChartViewer* chartViewer, double* xData, double* yData, int length, int xChartSize, int yChartSize);
	bool Init(CChartViewer* chartViewer, int xChartSize, int yChartSize);
	void Free();
	void setTitle(char* title);
	void setAxisName(char* xAxisName, char* yAxisName);
	void updateData(double* xData, double* yData);
	void drawChart();
	void onSizeChart(UINT nType, int cx, int cy);
	void OnViewPortChanged();
	void updateImageMap();
};

