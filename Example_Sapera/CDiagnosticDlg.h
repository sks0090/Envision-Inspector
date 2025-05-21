#pragma once
#include "afxdialogex.h"

#include "manuser.h"			// Coreco FG 제어를 위한 Header ex) Diagnostic Tool info

// CDiagnosticDlg 대화 상자

class CDiagnosticDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDiagnosticDlg)

public:
	CDiagnosticDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDiagnosticDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIAGNOSTIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 생성된 메시지 맵 함수
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	// GUI 변수
	CListCtrl m_listFGinfo;
	CListCtrl m_listLanesStat;

	// Frame Grabber
	CORSERVER hServer;

	
	
	CORSTATUS status;

	UINT32 nbPCIeLanes, nbCLHSLLanes;
	UINT32 nbGen;
	CORHW_DEVICE_PARAMETER_GET_TEMPERATURE_DATA nbTemperature;
	CORHW_DEVICE_PARAMETER_GET_USER_DEVICE_INFO_VALUE_OUT m_deviceInfo;
	char strFirmwareVersion[100];
	UINT32 countCRCError;
	UINT32 countEncodingError;

public:		// Methods
	// General
	CORSTATUS getDiagnosticInfo();
	CORSTATUS getLanesStatistic();

	// GUI
	afx_msg void OnBnClickedBtnRefresh();
};
