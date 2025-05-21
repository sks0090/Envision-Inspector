#pragma once
#include "afxdialogex.h"

#include "ChartViewer.h"	// CharDirector
#pragma comment(lib, "chartdir70.lib")

#include "My_Chart.h"

// CChartDlg 대화 상자

class CChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChartDlg)

public:
	CChartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChartDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	MyChart* m_cMyChart;
	CChartViewer m_ChartViewer;

	int m_nChartSizeX, m_nChartSizeY;

	double* m_xData;
	double* m_yData;

	int m_length;
	
public:
	afx_msg void OnViewPortChanged();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
