// CHdrDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CHdrDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그


// CHdrDlg 대화 상자

IMPLEMENT_DYNAMIC(CHdrDlg, CDialogEx)

CHdrDlg::CHdrDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HDR, pParent)
	, m_nWeight(16383)
{

}

CHdrDlg::~CHdrDlg()
{
}

void CHdrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_nWeight);
	DDX_Control(pDX, IDC_SLIDER_WEIGHT, m_ctrlWeight);
}


BEGIN_MESSAGE_MAP(CHdrDlg, CDialogEx)
	
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_WEIGHT, &CHdrDlg::OnEnChangeEditWeight)
END_MESSAGE_MAP()

// CHdrDlg 메시지 처리기
BOOL CHdrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_nWeightMax = 65536;
	m_nWeightMin = 0;

	m_pMainDlg->m_SapMnger.GetSapAcquisition()->GetCapability(CORACQ_CAP_HDR_WEIGHT_MAX, &m_nWeightMax);
	m_pMainDlg->m_SapMnger.GetSapAcquisition()->GetCapability(CORACQ_CAP_HDR_WEIGHT_MIN, &m_nWeightMin);
	m_nWeight = (m_nWeightMax + m_nWeightMin) / 4;

	// Slider Setting
	m_ctrlWeight.SetRange(m_nWeightMin, m_nWeightMax);
	m_ctrlWeight.SetRangeMin(m_nWeightMin);
	m_ctrlWeight.SetRangeMax(m_nWeightMax);
	m_ctrlWeight.SetLineSize(m_nWeightMax/100);
	m_ctrlWeight.SetPageSize(m_nWeightMax / 100);
	m_ctrlWeight.SetPos(m_nWeight);

	//UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CHdrDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			// ESC 키 이벤트에 대한 처리 추가
			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			// Enter 키 이벤트에 대한 처리 추가
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CHdrDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	CSliderCtrl* pSliderCtrl = (CSliderCtrl*)pScrollBar;

	if (pSliderCtrl->GetDlgCtrlID() == IDC_SLIDER_WEIGHT) {
		m_nWeight = pSliderCtrl->GetPos();
	}

	// Frame Grabber 설정
	if (m_pMainDlg->m_SapMnger.GetOutputFormat() != CORACQ_VAL_OUTPUT_FORMAT_MONO8P2)
	{
		m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_HDR_WEIGHT, m_nWeight, TRUE);
	}

	UpdateData(FALSE);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CHdrDlg::OnEnChangeEditWeight()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	UpdateData(TRUE);

	if (m_nWeight > m_nWeightMax) {
		m_nWeight = m_nWeightMax;
	}
	if (m_nWeight < m_nWeightMin) {
		m_nWeight = m_nWeightMin;
	}

	m_ctrlWeight.SetPos(m_nWeight);

	// Frame Grabber 설정
	if (m_pMainDlg->m_SapMnger.GetOutputFormat() != CORACQ_VAL_OUTPUT_FORMAT_MONO8P2)
	{
		m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_HDR_WEIGHT, m_nWeight, TRUE);
	}

	UpdateData(FALSE);
	
}
