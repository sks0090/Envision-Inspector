#pragma once
#include "afxdialogex.h"


// CServerClientDlg 대화 상자

class CServerClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerClientDlg)

public:
	CServerClientDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CServerClientDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVER_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
