#pragma once
#include "afxdialogex.h"


// ControlFGDlg 대화 상자

class ControlFGDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ControlFGDlg)

public:
	ControlFGDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ControlFGDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CTRL_FG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int m_nProgressTime;

public:
	afx_msg void OnBnClickedBtnVertFlip();
	afx_msg void OnBnClickedBtnHorFlip();
};
