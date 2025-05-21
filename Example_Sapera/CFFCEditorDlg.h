#pragma once
#include "afxdialogex.h"

#include "ChartViewer.h"	// CharDirector
#pragma comment(lib, "chartdir70.lib")

#include "My_Chart.h"

// CFFCEditorDlg 대화 상자

class CFFCEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFFCEditorDlg)

public:
	CFFCEditorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFFCEditorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FFC_EDITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	MyChart* m_cMyChart;

	double* m_xData, *m_yData;
	double* m_yDataProcessed;

	int m_dataLength;
	int m_nChartSizeX, m_nChartSizeY;

	unsigned char* m_fileDataSrc;
	unsigned char* m_fileDataDst;

	bool m_bChart;

	CString m_strFile;

	ULONGLONG m_length;		// file length

	CString m_strFileSelector;
	CString m_strProcessAlgorithm;

	// GUI
	CChartViewer m_ChartViewer;

	CComboBox m_cbFileSelector;
	CComboBox m_cbRowIndex;
	CComboBox m_cbProcessAlgorithm;

	// Check Box
	CButton m_chkEnableProcess;

public:
	bool loadFile();
	void readFile();
	void writeFile();
	bool saveFile();
	void clearChart();
	void calLowpassFilter(int filterSize);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLoadFile();
	afx_msg void OnBnClickedBtnSaveFile();
	afx_msg void OnCbnSelchangeCbFileSelector();
	afx_msg void OnCbnSelchangeCbProcessAlgorithm();
	afx_msg void OnBnClickedChkProcess();
};
