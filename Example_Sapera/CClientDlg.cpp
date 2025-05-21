// CClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CClientDlg.h"
#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// CClientDlg 대화 상자

IMPLEMENT_DYNAMIC(CClientDlg, CDialogEx)

CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLIENT, pParent)
	, m_nPort(8080)
	, m_Comm((CExampleSaperaDlg *)pParent)
{
	m_bConnected = FALSE;
}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPCtrlServer);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_CHK_CONNECT, m_chkConnect);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_CONNECT, &CClientDlg::OnBnClickedChkConnect)
END_MESSAGE_MAP()


// CClientDlg 메시지 처리기
BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_IPCtrlServer.SetAddress(192,168,100,39);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CClientDlg::OnBnClickedChkConnect()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	UpdateData(TRUE);

	if (m_chkConnect.GetCheck())
	{
		DWORD dwAddress;
		m_IPCtrlServer.GetAddress(dwAddress);

		in_addr addr;
		addr.S_un.S_addr = htonl(dwAddress);

		CString strIP = ConvertInAddrToCString(addr);
		if (m_Comm.Start(strIP, m_nPort))
		{
			pMainDlg->m_bStartClient = true;
			m_chkConnect.SetWindowTextA(_T("Disconnect"));
		}
		else {
			m_chkConnect.SetCheck(BST_UNCHECKED);
		}
	}
	else
	{
		m_Comm.Stop();
		pMainDlg->m_bStartClient = false;

		m_chkConnect.SetWindowTextA(_T("Connect"));
	}
}

CString CClientDlg::ConvertInAddrToCString(const in_addr& addr)
{
	char ipString[INET_ADDRSTRLEN] = { 0 }; // IPv4 문자열 저장용 버퍼

	// inet_ntop 호출
	if (inet_ntop(AF_INET, &addr, ipString, sizeof(ipString)) == nullptr)
	{
		return _T("Invalid Address");
	}

	// CString으로 변환
	return CString(ipString);
}

