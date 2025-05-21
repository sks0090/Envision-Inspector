// OnBoardFFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "OnBoardFFCDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// OnBoardFFCDlg 대화 상자

IMPLEMENT_DYNAMIC(OnBoardFFCDlg, CDialogEx)

OnBoardFFCDlg::OnBoardFFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ONBOARD_FFC, pParent)
{

}

OnBoardFFCDlg::~OnBoardFFCDlg()
{

}

void OnBoardFFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_ENABLE_FFC, m_chkEnableFFC);
}

BEGIN_MESSAGE_MAP(OnBoardFFCDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CALIBRATE_BRIGHT, &OnBoardFFCDlg::OnBnClickedBtnCalibrateBright)
	ON_BN_CLICKED(IDC_BTN_LOAD_FFC, &OnBoardFFCDlg::OnBnClickedBtnLoadFfc)
	ON_BN_CLICKED(IDC_BTN_SAVE_FFC, &OnBoardFFCDlg::OnBnClickedBtnSaveFfc)
	ON_BN_CLICKED(IDC_CHK_ENABLE_FFC, &OnBoardFFCDlg::OnBnClickedChkEnableFfc)
	ON_BN_CLICKED(IDC_BTN_CALIBRATE_DARK, &OnBoardFFCDlg::OnBnClickedBtnCalibrateDark)
END_MESSAGE_MAP()


// OnBoardFFCDlg 메시지 처리기
BOOL OnBoardFFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bFlatField = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void OnBoardFFCDlg::OnBnClickedChkEnableFfc()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHK_ENABLE_FFC); // 체크박스 컨트롤 핸들 가져오기
	int state = pCheckBox->GetCheck(); // 상태 확인

	if (state == BST_CHECKED) {
		m_bFlatField = true;
	}
	else if (state == BST_UNCHECKED) {
		m_bFlatField = false;
	}

	pMainDlg->m_SapMnger.GetSapXfer()->Destroy();
	pMainDlg->m_SapMnger.GetSapFlatField()->Enable(m_bFlatField, 1);
	pMainDlg->m_SapMnger.GetSapXfer()->Create();
	pMainDlg->m_SapMnger.GetSapXfer()->Init(TRUE);
}


void OnBoardFFCDlg::OnBnClickedBtnLoadFfc()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CFileDialog dlgFFC(TRUE, _T(""), _T(DEFAULT_FFC_FILENAME), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T(STANDARD_FILTER), this);

	dlgFFC.m_ofn.lpstrTitle = _T("Open Flat Field Correction");
	if (dlgFFC.DoModal() == IDOK)
	{
		// Load flat field correction file
		if (!pMainDlg->m_SapMnger.GetSapFlatField()->Load(CStringA(dlgFFC.GetPathName())))
			return;
	}
}

void OnBoardFFCDlg::OnBnClickedBtnCalibrateDark()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	pMainDlg->OnBnClickedCheckSnap();
	Sleep(2000);

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapFlatField()->SetNumFramesAverage(pMainDlg->m_nBuffer);
	pMainDlg->m_SapMnger.GetSapFlatField()->ComputeOffset(pMainDlg->m_SapMnger.GetSapBuffer());
	QueryPerformanceCounter(&pMainDlg->functionEndTime);
	
	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Dark FFC 수행[%d ms]"), progressTime);
}

void OnBoardFFCDlg::OnBnClickedBtnCalibrateBright()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	pMainDlg->OnBnClickedCheckSnap();
	Sleep(2000);

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapFlatField()->SetNumFramesAverage(pMainDlg->m_nBuffer);
	pMainDlg->m_SapMnger.GetSapFlatField()->ComputeGain(pMainDlg->m_SapMnger.GetSapBuffer(), pMainDlg->m_SapMnger.GetSapFlatFieldDefects(), pMainDlg->m_SapMnger.GetSapData());
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Bright FFC 수행[%d ms]"), progressTime);
}

void OnBoardFFCDlg::OnBnClickedBtnSaveFfc()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CFileDialog dlgFFC(FALSE, _T(""), _T(DEFAULT_FFC_FILENAME), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T(STANDARD_FILTER), this);

	dlgFFC.m_ofn.lpstrTitle = _T("Save Flat Field Correction As");
	if (dlgFFC.DoModal() == IDOK)
	{
		// Save flat field correction file
		pMainDlg->m_SapMnger.GetSapFlatField()->Save(CStringA(dlgFFC.GetPathName()));
	}
}


