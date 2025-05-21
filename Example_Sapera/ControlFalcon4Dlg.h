#pragma once
#include "afxdialogex.h"


// ControlFalcon4Dlg 대화 상자

class ControlFalcon4Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(ControlFalcon4Dlg)

public:
	ControlFalcon4Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ControlFalcon4Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CTRL_FALCON4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkLutEnable;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkLutEnable();
	afx_msg void OnBnClickedBtnLoadLut();	
};
