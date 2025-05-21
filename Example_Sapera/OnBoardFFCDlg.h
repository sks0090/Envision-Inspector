#pragma once
#include "afxdialogex.h"


// OnBoardFFCDlg 대화 상자
#define DEFAULT_FFC_FILENAME			"FFC.tif"
#define STANDARD_FILTER					"TIFF Files (*.tif)|*.tif|CRC Files (*.crc)|*.crc||"

class OnBoardFFCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OnBoardFFCDlg)

public:
	OnBoardFFCDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~OnBoardFFCDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ONBOARD_FFC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CButton m_chkEnableFFC;

	bool m_bFlatField;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCalibrateBright();
	afx_msg void OnBnClickedBtnLoadFfc();
	afx_msg void OnBnClickedBtnSaveFfc();
	afx_msg void OnBnClickedChkEnableFfc();
	afx_msg void OnBnClickedBtnCalibrateDark();
};
