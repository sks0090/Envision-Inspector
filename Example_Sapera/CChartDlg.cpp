// CChartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CChartDlg.h"

//#include "Example_SaperaDlg.h"		// 메인 다이얼로그
#include "CControlCameraDlg.h"

// CChartDlg 대화 상자

IMPLEMENT_DYNAMIC(CChartDlg, CDialogEx)

CChartDlg::CChartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHART, pParent)
{

}

CChartDlg::~CChartDlg()
{
}

void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART, m_ChartViewer);
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialogEx)
	ON_CONTROL(CVN_ViewPortChanged, IDC_CHART, OnViewPortChanged)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CControlCameraDlg* pDlg = (CControlCameraDlg*)GetParent();

	m_cMyChart = new MyChart();
	m_cMyChart->Init(&m_ChartViewer, pDlg->m_xData, pDlg->m_yData, 16384, m_nChartSizeX, m_nChartSizeY);

	//m_xData = m_pMainDlg->m_cMyImgAnalysis->m_structAnalysis->xAxisHorizontalProfile;
	//m_yData = m_pMainDlg->m_cMyImgAnalysis->m_structAnalysis->valueHorizontalProfile;
	//m_length = m_pMainDlg->m_cMyImgAnalysis->m_nSizeX;
	//
	//m_pMainDlg->m_cMyImgAnalysis->addChart(&m_ChartViewer, m_nChartSizeX, m_nChartSizeY);

	pDlg->m_bChart = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// CChartDlg 메시지 처리기
void CChartDlg::OnViewPortChanged()
{
	CControlCameraDlg* pDlg = (CControlCameraDlg*)GetParent();

	if (pDlg->m_bChart) {
		m_cMyChart->OnViewPortChanged();
	}
}


void CChartDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CControlCameraDlg* pDlg = (CControlCameraDlg*)GetParent();

	m_nChartSizeX = cx;
	m_nChartSizeY = cy;
	if (pDlg->m_bChart) {
		m_cMyChart->onSizeChart(nType, cx, cy);
	}
}
