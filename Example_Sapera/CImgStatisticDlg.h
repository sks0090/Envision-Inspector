#pragma once
#include "afxdialogex.h"
#include "CChartDlg.h"

#include "ChartViewer.h"	// CharDirector
#pragma comment(lib, "chartdir70.lib")

// CImgStatisticDlg 대화 상자

class CImgStatisticDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImgStatisticDlg)

public:
	CImgStatisticDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImgStatisticDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMG_STATISTIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listImgInfo;

	CChartViewer m_ChartViewer;

	int m_nChartSizeX, m_nChartSizeY;

	double* m_xData;
	double* m_yData;

	int m_length;

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnViewPortChanged();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
