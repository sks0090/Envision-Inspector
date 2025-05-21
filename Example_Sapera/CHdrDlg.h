#pragma once
#include "afxdialogex.h"


// CHdrDlg 대화 상자

class CHdrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHdrDlg)

public:
	CHdrDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHdrDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HDR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int m_nWeightMax, m_nWeightMin;
	int m_nWeight;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CSliderCtrl m_ctrlWeight;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditWeight();
};
