// ControlFalcon4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "ControlFalcon4Dlg.h"

#include "Example_SaperaDlg.h"
#include <stdio.h>


// ControlFalcon4Dlg 대화 상자

IMPLEMENT_DYNAMIC(ControlFalcon4Dlg, CDialogEx)

ControlFalcon4Dlg::ControlFalcon4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CTRL_FALCON4, pParent)
{

}

ControlFalcon4Dlg::~ControlFalcon4Dlg()
{
}

void ControlFalcon4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_LUT_ENABLE, m_chkLutEnable);
}


BEGIN_MESSAGE_MAP(ControlFalcon4Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_LUT_ENABLE, &ControlFalcon4Dlg::OnBnClickedChkLutEnable)
	ON_BN_CLICKED(IDC_BTN_LOAD_LUT, &ControlFalcon4Dlg::OnBnClickedBtnLoadLut)
END_MESSAGE_MAP()


// ControlFalcon4Dlg 메시지 처리기

BOOL ControlFalcon4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	char strTemp[50];

	// LUT
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("lutMode", strTemp, sizeof(strTemp));
	m_chkLutEnable.SetWindowText(strTemp);
	if (!strcmp(strTemp, "Active")) {
		m_chkLutEnable.SetCheck(BST_CHECKED);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ControlFalcon4Dlg::OnBnClickedChkLutEnable()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;
	char strTemp[50];

	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	if (m_chkLutEnable.GetCheck())
	{
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("lutMode", "Active");
	}
	else {
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("lutMode", "Off");
	}
	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("lutMode", strTemp, sizeof(strTemp));
	m_chkLutEnable.SetWindowText(strTemp);
	DisplayStatus(_T("LUT 설정 : %s[%d ms]"), strTemp, progressTime);
}


void ControlFalcon4Dlg::OnBnClickedBtnLoadLut()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	FILE* pFile;
	errno_t err;
	CString strFile;
	int i;

	int lutData[1024];

	// Coefficient 파일 선택
	TCHAR szFilter[] = _T("Image Set File (*.txt)|*.txt|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	strFile = dlg.GetPathName();

	
	err = fopen_s(&pFile, strFile, "r");
	if ( err != 0 || pFile == NULL) {
		AfxMessageBox("올바른 파일을 선택해 주세요");
		return;
	}

	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	// 파일 내용 읽기
	i = 0;
	while (fscanf_s(pFile, "%d", &lutData[i]) == 1) {
		// LUT 설정
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("LUTIndex", i);
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("LUTValue", lutData[i]);

		i++;
	}
	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);

	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("LUT Load & 설정 : %s[%d ms]"), strFile, progressTime);

	fclose(pFile);
}
