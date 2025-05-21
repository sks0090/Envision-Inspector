#pragma once
#include "afxdialogex.h"

#include "MyServer.h"
#include "DFStatusMnger.h"

class MyServer;

// CServerDlg 대화 상자

class CServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent, MyServer* pServer, DFStatusMnger* pMnger);   // 표준 생성자입니다.
	virtual ~CServerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	MyServer* m_pServer;
	DFStatusMnger* m_pDFStatusMnger;
	CCriticalSection	m_csRes;

	// GUI
	CButton m_btnStart;
	int m_nPort;
	CListCtrl m_listCtrlClient;


public:
	void InitCtrl(void);
	void AddIP(CString strIP);
	void RemoveIP(CString strIP);
	void SetGrabCnt(CString strIP, int nGrabCnt);
	void SetStatus(CString stIP, int nStatus);
	LPCTSTR GetStatusName(int nStatus);
	void SetDFStatusMnger(DFStatusMnger* pMnger);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkStartServer();	
};
