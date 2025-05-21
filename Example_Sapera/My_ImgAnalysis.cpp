#include "pch.h"
#include "My_ImgAnalysis.h"

MyImgAnalysis::MyImgAnalysis()
{
}

MyImgAnalysis::~MyImgAnalysis() {

}

bool MyImgAnalysis::Init(unsigned char* data, int width, int height)
{
	m_nSizeX = width;
	m_nSizeY = height;
	m_data8 = data;
	
	m_structAnalysis = new AnalysisStruct;

	m_structAnalysis->xAxisHorizontalProfile = new double[m_nSizeX];		memset(m_structAnalysis->xAxisHorizontalProfile, 0, m_nSizeX * sizeof(double));
	m_structAnalysis->valueHorizontalProfile = new double[m_nSizeX];			memset(m_structAnalysis->valueHorizontalProfile, 0, m_nSizeX * sizeof(double));

	// Analysis Thread 생성
	m_bThreadAnalysis = true;
	m_bThreadAnalysisProc = false;
	m_ThreadAnalysis = AfxBeginThread(AnalysisThread, this, THREAD_PRIORITY_NORMAL, 0);
	Sleep(100);

	m_bChart = false;
	m_bInit = true;

	Analyze(m_data8, m_nSizeX, m_nSizeY);

	return m_bInit;
}

void MyImgAnalysis::Free() {
	m_bThreadAnalysis = false;
	if (m_bThreadAnalysisProc) {
		//Sleep(100);
	}
	m_eventThreadAnalysis.SetEvent();

	delete[] m_structAnalysis->xAxisHorizontalProfile;
	delete[] m_structAnalysis->valueHorizontalProfile;

	delete m_structAnalysis;
	
	m_bChart = false;
	m_bInit = false;
}

UINT MyImgAnalysis::AnalysisThread(LPVOID lParam)
{
	MyImgAnalysis* pDlg = (MyImgAnalysis*)lParam;

	WaitForSingleObject(pDlg->m_eventThreadAnalysis, INFINITE);
	while (pDlg->m_bThreadAnalysis)
	{
		// 영상 통계 계산
		pDlg->CalStatistic();

		// Horizontal Profile 그래프
		pDlg->drawChart();

		pDlg->m_bThreadAnalysisProc = false;
		WaitForSingleObject(pDlg->m_eventThreadAnalysis, INFINITE);
	}
	return 0;
}

void MyImgAnalysis::Analyze(unsigned char* pData, int width, int height)
{
	if (m_bInit)
	{
		if (!m_bThreadAnalysisProc)
		{
			m_data8 = pData;
			m_bThreadAnalysisProc = true;
			m_eventThreadAnalysis.SetEvent();
		}
	}
}

void MyImgAnalysis::CalStatistic()
{
	double sum = 0;

	m_structAnalysis->maxValue = 0;
	m_structAnalysis->minValue = 255;

	// 최대/최소, 평균 계산
	for (row = 0; row < m_nSizeY; row++) {
		for (col = 0; col < m_nSizeX; col++) {
			if (m_structAnalysis->maxValue < m_data8[row * m_nSizeX + col])
			{
				m_structAnalysis->maxValue = m_data8[row * m_nSizeX + col];
			}
			if (m_structAnalysis->minValue > m_data8[row * m_nSizeX + col])
			{
				m_structAnalysis->minValue = m_data8[row * m_nSizeX + col];
			}
			sum += m_data8[row * m_nSizeX + col];

			// Horizontal Profile
			if (row == 0) {
				m_structAnalysis->xAxisHorizontalProfile[col] = col;
				m_structAnalysis->valueHorizontalProfile[col] = 0;
				m_structAnalysis->valueHorizontalProfile[col] += m_data8[row * m_nSizeX + col];
			}
			else {	
				m_structAnalysis->valueHorizontalProfile[col] += m_data8[row * m_nSizeX + col];
			}
		}
	}
	m_structAnalysis->averageValue = sum / (double)(m_nSizeX * m_nSizeY);

	sum = 0;
	// 표준편차 계산
	for (row = 0; row < m_nSizeY; row++) {
		for (col = 0; col < m_nSizeX; col++) {
			sum += (m_structAnalysis->averageValue - m_data8[row * m_nSizeX + col]) * (m_structAnalysis->averageValue - m_data8[row * m_nSizeX + col]);

			if (row == 0) {
				m_structAnalysis->valueHorizontalProfile[col] = m_structAnalysis->valueHorizontalProfile[col] / m_nSizeY;
			}
		}
	}
	m_structAnalysis->stdValue = sqrt(sum / (double)(m_nSizeY * m_nSizeX));
}

bool MyImgAnalysis::addChart(CChartViewer* viewer, int width, int height)
{
	m_ChartViewer = viewer;
	m_nChartSizeX = width;
	m_nChartSizeY = height;

	m_bChart = true;

	drawChart();

	return m_bChart;
}

void MyImgAnalysis::drawChart()
{
	if (m_bChart)
	{
		int m_margin = 64;

		XYChart* xyChart = new XYChart(m_nChartSizeX, m_nChartSizeY, 0xf0f0ff, 0, 1);
		xyChart->setRoundedFrame(0xffffff);

		xyChart->setPlotArea(m_margin, m_margin, m_nChartSizeX - (m_margin*2), m_nChartSizeY - (m_margin*2 ), Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

		// As the data can lie outside the plotarea in a zoomed chart, we need to enable clipping.
		xyChart->setClipping();

		// 제목
		xyChart->addTitle("Horizontal Profile", "Arial Bold Italic", 12);

		// Add a legend box at the top of the plot area with 9pts Arial Bold font with flow layout.
		xyChart->addLegend(50, 33, false, "Arial Bold", 9)->setBackground(Chart::Transparent, Chart::Transparent);

		// Set axes width to 2 pixels
		xyChart->yAxis()->setWidth(2);
		xyChart->xAxis()->setWidth(2);

		// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
		xyChart->xAxis()->setTitle("Horizontal Pixels", "Arial", 10, 0x555555);
		xyChart->yAxis()->setTitle("DN", "Arial", 10, 0x555555);

		///////////////////////////////////////////////////////////////////////////////////////
		// Add data to chart
		///////////////////////////////////////////////////////////////////////////////////////
		// Add a line layer for the lines, using a line width of 2 pixels
		LineLayer* layer = xyChart->addLineLayer();
		layer->setLineWidth(3);

		layer->setFastLineMode();

		layer->setXData(DoubleArray(m_structAnalysis->xAxisHorizontalProfile, m_nSizeX));
		layer->addDataSet(DoubleArray(m_structAnalysis->valueHorizontalProfile, m_nSizeX), 0xff0000);

		///////////////////////////////////////////////////////////////////////////////////////
		// Configure axis scale and labelling
		///////////////////////////////////////////////////////////////////////////////////////
		m_ChartViewer->syncDateAxisWithViewPort("x", xyChart->xAxis());

		xyChart->xAxis()->setTickDensity(75);

		///////////////////////////////////////////////////////////////////////////////////////
		// Output the chart
		///////////////////////////////////////////////////////////////////////////////////////
		delete m_ChartViewer->getChart();
		m_ChartViewer->setChart(xyChart);
	}
}

void MyImgAnalysis::onSizeChart(UINT nType, int cx, int cy)
{
	if (m_bChart) {
		m_nChartSizeX = cx;
		m_nChartSizeY = cy;
		drawChart();
	}
}

void MyImgAnalysis::OnViewPortChanged()
{
	if (m_ChartViewer->needUpdateChart())
		drawChart();
	if (m_ChartViewer->needUpdateImageMap())
		updateImageMap();
}

void MyImgAnalysis::updateImageMap()
{
	// Include tool tip for the chart
	if (0 == m_ChartViewer->getImageMapHandler())
	{
		m_ChartViewer->setImageMap(m_ChartViewer->getChart()->getHTMLImageMap("", "",
			"title='[{dataSetName}] {x|mmm dd, yyyy}: USD {value|2}'"));
	}
}

