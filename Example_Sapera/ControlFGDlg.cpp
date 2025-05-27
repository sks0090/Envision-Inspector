// ControlFGDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "ControlFGDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// ControlFGDlg 대화 상자

IMPLEMENT_DYNAMIC(ControlFGDlg, CDialogEx)

ControlFGDlg::ControlFGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CTRL_FG, pParent)
{

}

ControlFGDlg::~ControlFGDlg()
{
}

void ControlFGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ControlFGDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_VERT_FLIP, &ControlFGDlg::OnBnClickedBtnVertFlip)
	ON_BN_CLICKED(IDC_BTN_HOR_FLIP, &ControlFGDlg::OnBnClickedBtnHorFlip)
END_MESSAGE_MAP()


// ControlFGDlg 메시지 처리기


void ControlFGDlg::OnBnClickedBtnVertFlip()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	int flipMode = 0;
	flipMode = m_pMainDlg->m_SapMnger.GetSapXfer()->GetPair(0)->GetFlipMode();

	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	m_pMainDlg->m_SapMnger.GetSapXfer()->Disconnect();
	if (flipMode == 0)
		m_pMainDlg->m_SapMnger.GetSapXfer()->GetPair(0)->SetFlipMode(CORXFER_VAL_FLIP_VERT);
	else
		m_pMainDlg->m_SapMnger.GetSapXfer()->GetPair(0)->SetFlipMode(CORXFER_VAL_FLIP_OFF);

	m_pMainDlg->m_SapMnger.GetSapXfer()->Connect();
	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	m_nProgressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;


	flipMode = m_pMainDlg->m_SapMnger.GetSapXfer()->GetPair(0)->GetFlipMode();


	if (flipMode == 2)
		DisplayStatus(_T("Vertical Flip 변경 : Vertical[%d ms]"), m_nProgressTime);
	else
		DisplayStatus(_T("Vertical Flip 변경 : None[%d ms]"), m_nProgressTime);
}


void ControlFGDlg::OnBnClickedBtnHorFlip()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int flipMode = 0;

	if (flipMode == 0)
	{
		//Horizontal flip 적용 
		m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetFlipMode(SapAcquisition::FlipHorizontal);
	}
	else
	{
		//Horizontal flip 해제 
		m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetFlipMode(SapAcquisition::FlipNone);
	}

}
