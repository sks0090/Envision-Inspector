#pragma once
#include "afxdialogex.h"

#include "CChartDlg.h"

// CControlCameraDlg 대화 상자

typedef struct {
	char entryName[50];
	CString displayName;
} FeatureName;

class CControlCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControlCameraDlg)

public:
	CControlCameraDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CControlCameraDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// classes
	CChartDlg* pFfcChartDlg;

	// General
	bool m_bChart;

	char m_charTriggerMode[50];
	char m_charScanDirection[50];
	char m_charModelName[100];
	char m_charPartNumber[100];
	char m_charFirmware[100];
	char m_charSerialNumber[100];
	char m_charFpnAlgorithm[50];
	
	double m_fTemperature;
	double m_fInputVoltage;

	double* m_xData, *m_yData;

	FeatureName m_nameTdiMode;
	FeatureName m_nameBinningHorizontal;
	FeatureName m_nameBinningVertical;
	FeatureName m_nameAnalogGain;
	FeatureName m_nameActiveUserSet;

	///////////////////////////////////////// GUI ////////////////////////////////////
	// List Control
	CListCtrl m_listCamInfo;
	
	// Button
	CButton m_chkTriggerMode;
	CButton m_chkScanDirection;
	
	// Combo
	CComboBox m_cbTdiMode;
	CComboBox m_cbBinningHorizontal;
	CComboBox m_cbBinningVertical;
	CComboBox m_cbAnalogGain;
	CComboBox m_cbFpnAlgorithm;
	CComboBox m_cbActiveUserSet;
	CComboBox m_cbFileAccess;
	int m_nFileAccessIndex;
	CString m_strFile;

	// Edit Box
	double m_fInternalLineRate;
	int m_nPrnuTarget;

public:
	
	void TDIModeName(char *name);
	void TDIModeName(CString name);
	void BinningHorizontal(char* name);
	void BinningHorizontal(CString name);
	void BinningVertical(char* name);
	void BinningVertical(CString name);
	void AnalogGain(char* name);
	void AnalogGain(CString name);
	void ActiveUserSet(char* name);
	void ActiveUserSet(CString name);
	void GetCamInfo(int nType);	// 0: 1회성, 1: 주기적 by Timer

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedChkTriggerMode();
	afx_msg void OnBnClickedChkScanDirection();
	afx_msg void OnCbnSelchangeCbTdiMode();
	afx_msg void OnCbnSelchangeCbAnalogGain();
	afx_msg void OnBnClickedBtnCalFpn();
	afx_msg void OnBnClickedBtnCalPrnu();
	afx_msg void OnBnClickedBtnClearFfc();
	afx_msg void OnCbnSelchangeCbUserset();
	afx_msg void OnBnClickedBtnSaveUserset();
	afx_msg void OnBnClickedBtnSetLinerate();
	afx_msg void OnCbnSelchangeCbFileAccess();
	afx_msg void OnBnClickedBtnFileDownload();
	afx_msg void OnBnClickedBtnFileUpload();
	afx_msg void OnBnClickedBtnShowChart();
	afx_msg void OnCbnSelchangeCbBinningHorizontal();
	afx_msg void OnCbnSelchangeCbBinningVertical();
	afx_msg void OnCbnSelchangeCbFpnAlgorithm();
};
