#pragma once
#include "afxdialogex.h"
#include "CommSlave.h"

// CClientDlg 대화 상자

class CClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientDlg)

public:
	CClientDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CClientDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CommSlave		m_Comm;

	CIPAddressCtrl m_IPCtrlServer;
	UINT m_nPort;
	CButton m_chkConnect;

	BOOL		m_bConnected;

public:
	CString ConvertInAddrToCString(const in_addr& addr);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkConnect();
};
