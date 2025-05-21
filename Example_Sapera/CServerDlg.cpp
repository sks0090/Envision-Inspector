// CServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CServerDlg.h"
#include "define.h"
#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// CServerDlg 대화 상자

IMPLEMENT_DYNAMIC(CServerDlg, CDialogEx)

CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/, MyServer* pServer, DFStatusMnger* pMnger)
	: CDialogEx(IDD_DIALOG_SERVER, pParent)
	, m_nPort(8080)
{
	m_pServer = pServer;
	m_pDFStatusMnger = pMnger;
}

CServerDlg::~CServerDlg()
{
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_listCtrlClient);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_CHK_START_SERVER, m_btnStart);
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_START_SERVER, &CServerDlg::OnBnClickedChkStartServer)
END_MESSAGE_MAP()


// CServerDlg 메시지 처리기

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CServerDlg::InitCtrl(void)
{
	char* ipString;

	m_listCtrlClient.InsertColumn(0, _T("Client"), LVCFMT_LEFT, 150);
	m_listCtrlClient.InsertColumn(1, _T("Status"), LVCFMT_LEFT, 150);
	m_listCtrlClient.InsertColumn(2, _T("GrabCnt"), LVCFMT_LEFT, 80);
	m_listCtrlClient.InsertColumn(3, _T("Img Mismatch"), LVCFMT_LEFT, 80);
}

void CServerDlg::OnBnClickedChkStartServer()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	UpdateData(TRUE);

	if (m_btnStart.GetCheck())
	{
		m_pServer->SetParent(this);
		if (!m_pServer->Start(m_nPort, GetSafeHwnd()))
		{
			m_btnStart.SetCheck(BST_UNCHECKED);
			AfxMessageBox(_T("Failed to start server"));
		}
		else {
			pMainDlg->m_bStartServer = true;
			m_btnStart.SetWindowTextA(_T("Server Stop"));
		}
	}
	else {
		m_pServer->Stop();
		pMainDlg->m_bStartServer = false;
		m_btnStart.SetWindowTextA(_T("Server Start"));
	}
}

void CServerDlg::AddIP(CString strIP)
{
	m_csRes.Lock();
	
	m_pDFStatusMnger->AddClient((LPCTSTR)strIP);
	m_listCtrlClient.InsertItem(m_listCtrlClient.GetItemCount(), strIP);

	m_csRes.Unlock();
}

void CServerDlg::RemoveIP(CString strIP)
{
	m_csRes.Lock();

	CString strItem;
	int nCnt = m_listCtrlClient.GetItemCount();
	for (int i = 0; i < nCnt; i++)
	{
		strItem = m_listCtrlClient.GetItemText(i, 0);
		if (strItem == strIP)
		{
			m_listCtrlClient.DeleteItem(i);
			break;
		}
	}

	m_pDFStatusMnger->RemoveClient((LPCTSTR)strIP);

	m_csRes.Unlock();

}

void CServerDlg::SetGrabCnt(CString strIP, int nGrabCnt)
{
	m_csRes.Lock();

	CString strCnt;
	strCnt.Format(_T("%d"), nGrabCnt);

	CString strItem;
	int nCnt = m_listCtrlClient.GetItemCount();
	for (int i = 0; i < nCnt; i++)
	{
		strItem = m_listCtrlClient.GetItemText(i, 0);
		if (strItem == strIP)
		{
			m_listCtrlClient.SetItemText(i, 2, strCnt);
			break;
		}
	}
	
	m_pDFStatusMnger->SetGrabCnt((LPCTSTR)strIP, nGrabCnt);

	m_csRes.Unlock();

}

void CServerDlg::SetStatus(CString stIP, int nStatus)
{
	m_csRes.Lock();

	CString strItem;
	int nCnt = m_listCtrlClient.GetItemCount();
	for (int i = 0; i < nCnt; i++)
	{
		strItem = m_listCtrlClient.GetItemText(i, 0);
		if (strItem == stIP)
		{
			m_listCtrlClient.SetItemText(i, 1, GetStatusName(nStatus));
			break;
		}
	}
	m_pDFStatusMnger->SetStatus((LPCTSTR)stIP, nStatus);

	m_csRes.Unlock();
}

void CServerDlg::SetDFStatusMnger(DFStatusMnger* pMnger)
{
	m_pDFStatusMnger = pMnger;
}

LPCTSTR CServerDlg::GetStatusName(int nStatus)
{
	static LPCTSTR StatusName[] = { "READY", "READY_GRAB,", "SNAP", "GRAB", "FREEZE", "WAIT", "ABORT" };

	if (nStatus >= STATUS_CNT)
		return LPCTSTR("");

	return StatusName[nStatus];
}