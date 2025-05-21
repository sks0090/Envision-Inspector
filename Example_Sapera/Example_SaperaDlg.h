
// Example_SaperaDlg.h: 헤더 파일
//

#pragma once
//#define MVVIEWER
//#define ACSC

#include "SapMnger.h"
#include "MilMnger.h"


#ifdef ACSC
#include "ACSC.h"			// Motion
#endif

// Dialogs
#include "CDiagnosticDlg.h"		// Diagnostic Tool 다이얼로그
#include "CControlCameraDlg.h"	// Control - Camera - LineaHS 다이얼로그
#include "ControlFalcon4Dlg.h"	// Control - Camera - Falcon4 다이얼로그
#include "CFFCEditorDlg.h"			// Control - FFC Editor 다이얼로그
#include "OnBoardFFCDlg.h"		// Control - Frame Grabber 다이얼로그
#include "ControlLightEnvitDlg.h"
#include "CHdrDlg.h"			// On-board Processing - HDR 다이얼로그
#include "CImgStatisticDlg.h"	// Image Analysis - Statistic 다이얼로그
#include "CServerDlg.h"			// Server
#include "CClientDlg.h"			// Client
#include "DemoLineaHS2Dlg.h"	// Demo - Linea HS2

// Customs
#include "My_GUI.h"
#include "My_ImgAnalysis.h"
#include "My_Chart.h"
#include "MyServer.h"
#include "MyClient.h"
#include "DFStatusMnger.h"
#include "SapMyProcessing.h"
#include "My_ImgProcessing.h"
#include "SerialPort.h"

#define WM_UPDATE_MSG       WM_USER + 1				// UI 업데이트

typedef struct
{
	int index;
	CExampleSaperaDlg* dlg;
}StructCallbackContext;

// CExampleSaperaDlg 대화 상자
class CExampleSaperaDlg : public CDialogEx
{
// 생성입니다.
public:
	CExampleSaperaDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMPLE_SAPERA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	///////////////////////////////////////// GUI 변수 /////////////////////////////////////////	
	// Dialog
	CDiagnosticDlg* m_pDiagnosticDlg;
	CControlCameraDlg* m_pControlCameraDlg;
	ControlFalcon4Dlg* m_pControlFalcon4Dlg;
	CFFCEditorDlg* m_pFFCEditorDlg;
	CServerDlg m_ServerDlg;
	CClientDlg m_ClientDlg;
	CHdrDlg* m_pHdrDlg;
	OnBoardFFCDlg* m_pOnBoardFFCDlg;
	CImgStatisticDlg* m_pImgStatisticDlg;
	ControlLightEnvitDlg* m_pControlLightEnvitDlg;

	DemoLineaHS2Dlg* m_pDemoLineaHS2Dlg;
	
	// Display
	CStatic m_ctrlDisplay;

	// Combo Box
	CComboBox m_cbSDK;
	CComboBox m_cbFG;

	// Buttons
	CButton m_btnFitDisplay;

	// Edit Control
	int m_nBuffer;
	int m_nGrabFrame;
	int m_nPlaneIndex;
	int m_nPlanes;

	CEdit m_TrashCnt;
	CEdit m_GrabCnt;
	CEdit m_ProcCnt;
	CEdit m_RunCnt;
	CEdit m_BufIndex;
	CEdit m_FrameRate;
	CEdit m_CopyTime;
	CEdit m_XferCycle;
	CEdit m_ProCycle;

	// List Box
	CListBox m_listStatus;

	// Button
	CButton m_InitFree;
	CButton m_Snap;
	CButton m_StartStop;
	CButton m_Processing;
	CButton m_btnLongrun;

	// Check Box
	BOOL m_bChkDualFG;

	///////////////////////////////////////// 일반 변수 /////////////////////////////////////////
	// Custom Classes
	MyGUI			*m_pMyGuiMain;
	MyImgAnalysis	m_MyImgAnalysis;
	MyServer		m_MyServer;
	DFStatusMnger	m_DFStatusMnger;
	My_ImgProcessing m_MyImgProcessing;
	
	// SDK classes
	SapMnger		m_SapMnger;
	MilMnger		m_MilMnger;

	// Structs
	StructCallbackContext m_structCallbackContext[2];

	CString			m_strSDK;
	CString			m_strBoardName[2];		// 프레임 그래버 이름
	CString			m_strCamFilePath[2];		// CCF 경로

	// 이미지 정보
	int		m_nFG;
	int		m_nSizeX;					// 버퍼 width
	int		m_nSizeY;					// 버퍼 height
	int		m_nBitDepth;

	int		m_nWidthPicCtrl, m_nHeightPicCtrl;		// Picture Control 가로/세로 크기

	int m_nTrashCnt[2];
	int m_nGrabCnt[2];
	int m_nProcCnt[2];
	int m_nRunCnt;
	int m_nBufIndex, m_nBufProIndex;
	
	float m_fFrameRate;
	float m_fCopyTime;
	float m_fXferCycle;
	float m_fProCycle;

	unsigned char * m_pSrcBuf8, * m_pDstBuf8;

	bool			m_bInit;
	bool			m_bGrab;
	bool			m_bCamControl;
	bool			m_bProcessing;
	bool			m_bLongrun;
	bool			m_bStartServer;
	bool			m_bStartClient;
	bool			m_bContrast;
	bool			m_bHDR;
	bool			m_bImgStatistic;
	bool			m_bProfileHorizontal;
	bool			m_bDemoLineaHS2;
	bool			m_bDemo;
	bool			m_bDemoMotion;

	bool			m_bUpdateUI;		// GUI 업데이트 중인지 여부

	// Threads
	CWinThread* m_pThreadUpdateUI;
	CWinThread* m_pThreadLongrun;
	CWinThread* m_pThreadDemo;
	CWinThread* m_pThreadDemoMotion;

	// Event
	CEvent m_eventUpdateUI;
	CEvent m_eventRunDemo;
	CEvent m_eventRunDemoMotion;

	// 시간 측정
	LARGE_INTEGER		m_perfFrequency;
	LARGE_INTEGER		xferStartTime, xferEndTime;
	LARGE_INTEGER		proStartTime, proEndTime;
	LARGE_INTEGER		functionStartTime, functionEndTime;

	float m_fMaxXferCycle;
	float m_fMaxProCycle;

	// 조명 제어
	CPYH_Comm* m_CommEnvit;
	byte m_comData[9];
	byte m_onOff[8];
	byte m_setBitDepth[7];

public:		
	///////////////////////////////////////// 일반 Methods /////////////////////////////////////////
	bool	InitCtrl();
	bool	FreeCtrl();

	bool	Init();
	bool	InitDualFG();
	void	Free(int index = 0);
	bool	InitClass();
	bool	FreeClass();

	bool	Snap(int num, int index = 0);
	bool	GrabStart(int index = 0);
	bool	GrabStop(int index = 0);

	bool	ConnectEnvit();
	bool	DisconnectEnvit();
	bool	ControlEnvit(int r, int g, int b);
	bool	ControlEnvit();
	bool	OnOffEnvit(int index, bool bOn);		// index : 0(Red), 1(Green), 2(Blue)

	void LongrunTest();

	void UpdateStatus(int status);

	// Thread Method
	static UINT UpdateUIThread(LPVOID lParam);
	static UINT LongrunThread(LPVOID lParam);
	static UINT UpdateImgStatisticThread(LPVOID lParam);
	static UINT DemoThread(LPVOID lParam);
	static UINT DemoThreadMotion(LPVOID lParam);

	// Event Callback Method
	static void XferCallback(SapXferCallbackInfo* pInfo);
	static void ProCallback(SapProCallbackInfo* pInfo);
	void Xfer_Callback(SapXferCallbackInfo* pInfo, int index);
	void Pro_Callback(SapProCallbackInfo* pInfo, int index);

	///////////////////////////////////////// GUI Event Methods /////////////////////////////////////////
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnUpdateMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	// Menu
	afx_msg void OnFileImagefileload();
	afx_msg void OnFileDiagnostictool();
	afx_msg void OnFileExit();
	afx_msg void OnControlFfccoefficienteditor();
	afx_msg void OnControlServer();
	afx_msg void OnControlClient();
	afx_msg void OnOnboardprocessingHdr();
	afx_msg void OnImageprocessingContrast();
	afx_msg void OnImageanalysisStatistic();
	afx_msg void OnControlLightEnvit();

	// Widgets
	afx_msg void OnCbnSelchangeCbFg();
	afx_msg void OnBnClickedCheckInitFree();
	afx_msg void OnBnClickedCheckSnap();
	afx_msg void OnBnClickedCheckStartStop();
	afx_msg void OnBnClickedBtnSaveImg();
	afx_msg void OnBnClickedCheckProc();
	afx_msg void OnBnClickedBtnFitDisplay();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnEnChangeEditBufIndex();
	afx_msg void OnBnClickedBtnPrev2();
	afx_msg void OnBnClickedBtnNext2();	
	afx_msg void OnBnClickedCheckLongrun();
	afx_msg void OnCameraLineaHS();
	afx_msg void OnCameraFalcon4();
	afx_msg void OnCbnSelchangeCbSdk();
	afx_msg void OnOnboardprocessingFlatfieldcorrection();
	afx_msg void OnBnClickedChkDualFg();
	afx_msg void OnDemoLineahs2();
	
};

void DisplayStatus(const TCHAR* fmt, ...);