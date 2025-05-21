#include "pch.h"
#include "My_Chart.h"

MyChart::MyChart() {

}
MyChart::~MyChart() {

}

// Initialize
bool MyChart::Init(CChartViewer* chartViewer, double* xData, double* yData, int length, int xChartSize, int yChartSize)
{
	m_ChartViewer = chartViewer;
	m_xData = xData;
	m_yData = yData;
	m_nChartSizeX = xChartSize;
	m_nChartSizeY = yChartSize;

	m_length = length;

	m_bTitle = false;
	m_bAxisName = false;
	m_bInit = true;

	drawChart();

	return m_bInit;
}

bool MyChart::Init(CChartViewer* chartViewer,int xChartSize, int yChartSize)
{
	m_ChartViewer = chartViewer;
	m_nChartSizeX = xChartSize;
	m_nChartSizeY = yChartSize;

	m_bTitle = false;
	m_bAxisName = false;
	m_bInit = true;

	drawChart();

	return m_bInit;
}

void MyChart::Free()
{
	//for (auto pDlg : m_ChartDlgs)
	//{
	//	if (pDlg != nullptr)
	//	{
	//		pDlg->DestroyWindow();
	//		delete pDlg;
	//	}
	//}
	//m_ChartDlgs.clear();
    m_bInit = false;
}

void MyChart::setTitle(char* title)
{
	m_title = title;
	m_bTitle = true;
}

void MyChart::setAxisName(char* xAxisName, char* yAxisName)
{
	m_xAxisName = xAxisName;
	m_yAxisName = yAxisName;
	m_bAxisName = true;
}

void MyChart::updateData(double* xData, double* yData)
{
	m_xData = xData;
	m_yData = yData;

	drawChart();
}

void MyChart::drawChart()
{
	if (m_bInit)
	{
		int m_margin = 64;

		XYChart* xyChart = new XYChart(m_nChartSizeX, m_nChartSizeY, 0xf0f0ff, 0, 1);
		xyChart->setRoundedFrame(0xffffff);

		xyChart->setPlotArea(m_margin, m_margin/2, m_nChartSizeX - (m_margin * 2), m_nChartSizeY - (m_margin * 2), Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

		// As the data can lie outside the plotarea in a zoomed chart, we need to enable clipping.
		xyChart->setClipping();

		// Á¦¸ñ
		if (m_bTitle)
		{
			xyChart->addTitle(m_title, "Arial Bold Italic", strlen(m_title));
		}

		// Add a legend box at the top of the plot area with 9pts Arial Bold font with flow layout.
		xyChart->addLegend(50, 33, false, "Arial Bold", 9)->setBackground(Chart::Transparent, Chart::Transparent);

		// Set axes width to 2 pixels
		xyChart->yAxis()->setWidth(2);
		xyChart->xAxis()->setWidth(2);

		if (m_bAxisName) {
			// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
			xyChart->xAxis()->setTitle(m_xAxisName, "Arial", 10, 0x555555);
			xyChart->yAxis()->setTitle(m_yAxisName, "Arial", 10, 0x555555);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		// Add data to chart
		///////////////////////////////////////////////////////////////////////////////////////
		// Add a line layer for the lines, using a line width of 2 pixels
		LineLayer* layer = xyChart->addLineLayer();
		layer->setLineWidth(3);

		layer->setFastLineMode();

		layer->setXData(DoubleArray(m_xData, m_length));
		layer->addDataSet(DoubleArray(m_yData, m_length), 0xff0000);

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

void MyChart::onSizeChart(UINT nType, int cx, int cy)
{
	if (m_bInit) {
		m_nChartSizeX = cx;
		m_nChartSizeY = cy;
		drawChart();
	}
}

void MyChart::OnViewPortChanged()
{
	if (m_ChartViewer->needUpdateChart())
		drawChart();
	if (m_ChartViewer->needUpdateImageMap())
		updateImageMap();
}

void MyChart::updateImageMap()
{
	// Include tool tip for the chart
	if (0 == m_ChartViewer->getImageMapHandler())
	{
		m_ChartViewer->setImageMap(m_ChartViewer->getChart()->getHTMLImageMap("", "",
			"title='[{dataSetName}] {x|mmm dd, yyyy}: USD {value|2}'"));
	}
}