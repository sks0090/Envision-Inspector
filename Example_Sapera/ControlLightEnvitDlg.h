#pragma once
#include "afxdialogex.h"


// ControlLightEnvitDlg 대화 상자

class ControlLightEnvitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ControlLightEnvitDlg)

public:
	ControlLightEnvitDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ControlLightEnvitDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CTRL_LIGHT_ENVIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChkConnect();
	virtual BOOL OnInitDialog();

public:
	CButton m_chkConnect;

public:
	bool	m_bConnect;
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	CButton m_chkRed;
	CButton m_chkGreen;
	CButton m_chkBlue;
	afx_msg void OnBnClickedChkRed();
	afx_msg void OnBnClickedChkGreen();
	afx_msg void OnBnClickedChkBlue();
};
