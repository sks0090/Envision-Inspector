// ControlLightEnvitDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "ControlLightEnvitDlg.h"

#include "Example_SaperaDlg.h"

// ControlLightEnvitDlg 대화 상자

IMPLEMENT_DYNAMIC(ControlLightEnvitDlg, CDialogEx)

ControlLightEnvitDlg::ControlLightEnvitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CTRL_LIGHT_ENVIT, pParent)
	, m_nRed(100)
	, m_nGreen(100)
	, m_nBlue(100)
{

}

ControlLightEnvitDlg::~ControlLightEnvitDlg()
{
}

void ControlLightEnvitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_CONNECT, m_chkConnect);
	DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_nGreen);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_nBlue);
	DDX_Control(pDX, IDC_CHK_RED, m_chkRed);
	DDX_Control(pDX, IDC_CHK_GREEN, m_chkGreen);
	DDX_Control(pDX, IDC_CHK_BLUE, m_chkBlue);
}


BEGIN_MESSAGE_MAP(ControlLightEnvitDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_CONNECT, &ControlLightEnvitDlg::OnBnClickedChkConnect)
	ON_BN_CLICKED(IDC_CHK_RED, &ControlLightEnvitDlg::OnBnClickedChkRed)
	ON_BN_CLICKED(IDC_CHK_GREEN, &ControlLightEnvitDlg::OnBnClickedChkGreen)
	ON_BN_CLICKED(IDC_CHK_BLUE, &ControlLightEnvitDlg::OnBnClickedChkBlue)
END_MESSAGE_MAP()


// ControlLightEnvitDlg 메시지 처리기
BOOL ControlLightEnvitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bConnect = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ControlLightEnvitDlg::OnBnClickedChkConnect()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (m_chkConnect.GetCheck())
	{
		pMainDlg->ConnectEnvit();
		m_bConnect = true;
		m_chkConnect.SetWindowText("Disconnect");
	}
	else {
		pMainDlg->DisconnectEnvit();
		m_bConnect = false;
		m_chkConnect.SetWindowText("Connect");
	}
}

void ControlLightEnvitDlg::OnBnClickedChkRed()
{
	UpdateData(TRUE);

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (m_chkRed.GetCheck())
	{
		pMainDlg->ControlEnvit(m_nRed, m_nGreen, m_nBlue);
		pMainDlg->OnOffEnvit(0, true);
	}
	else {
		pMainDlg->OnOffEnvit(0, false);
	}
}

void ControlLightEnvitDlg::OnBnClickedChkGreen()
{
	UpdateData(TRUE);

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (m_chkGreen.GetCheck())
	{
		pMainDlg->ControlEnvit(m_nRed, m_nGreen, m_nBlue);
		pMainDlg->OnOffEnvit(1, true);
	}
	else {
		pMainDlg->OnOffEnvit(1, false);
	}
}

void ControlLightEnvitDlg::OnBnClickedChkBlue()
{
	UpdateData(TRUE);

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (m_chkBlue.GetCheck())
	{
		pMainDlg->ControlEnvit(m_nRed, m_nGreen, m_nBlue);
		pMainDlg->OnOffEnvit(2, true);
	}
	else {
		pMainDlg->OnOffEnvit(2, false);
	}
}
