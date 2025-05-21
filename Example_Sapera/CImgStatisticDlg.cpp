// CImgStatisticDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CImgStatisticDlg.h"
#include "Example_SaperaDlg.h"		// 메인 다이얼로그


// CImgStatisticDlg 대화 상자

IMPLEMENT_DYNAMIC(CImgStatisticDlg, CDialogEx)

CImgStatisticDlg::CImgStatisticDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMG_STATISTIC, pParent)
{

}

CImgStatisticDlg::~CImgStatisticDlg()
{
}

void CImgStatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMG_INFO, m_listImgInfo);
	DDX_Control(pDX, IDC_CHART_PROFILE, m_ChartViewer);
}


BEGIN_MESSAGE_MAP(CImgStatisticDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CONTROL(CVN_ViewPortChanged, IDC_CHART_PROFILE, OnViewPortChanged)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CImgStatisticDlg 메시지 처리기


int CImgStatisticDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CImgStatisticDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CImgStatisticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listImgInfo.InsertColumn(0, _T("Name"), LVCFMT_CENTER, 100);
	m_listImgInfo.InsertColumn(1, _T("Value"), LVCFMT_CENTER, 200);

	m_listImgInfo.InsertItem(0, "Max");
	m_listImgInfo.InsertItem(1, "Min");
	m_listImgInfo.InsertItem(2, "Average");
	m_listImgInfo.InsertItem(3, "STD");
	
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_xData = m_pMainDlg->m_MyImgAnalysis.m_structAnalysis->xAxisHorizontalProfile;
	m_yData = m_pMainDlg->m_MyImgAnalysis.m_structAnalysis->valueHorizontalProfile;
	m_length = m_pMainDlg->m_MyImgAnalysis.m_nSizeX;
	
	m_pMainDlg->m_MyImgAnalysis.addChart(&m_ChartViewer, m_nChartSizeX, m_nChartSizeY);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CImgStatisticDlg::OnViewPortChanged()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent()->GetParent();

	m_pMainDlg->m_MyImgAnalysis.OnViewPortChanged();
}

void CImgStatisticDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_nChartSizeX = cx-300;
	m_nChartSizeY = cy;

	m_pMainDlg->m_MyImgAnalysis.onSizeChart(nType, cx, cy);
}
