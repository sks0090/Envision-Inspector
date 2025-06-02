
// Example_SaperaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Example_Sapera.h"
#include "Example_SaperaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hComm = (HANDLE)-1;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExampleSaperaDlg 대화 상자



CExampleSaperaDlg::CExampleSaperaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMPLE_SAPERA_DIALOG, pParent)
	, m_nBuffer(4)
	, m_nGrabFrame(1)
	, m_nPlaneIndex(0)
	, m_nRunCnt(0)
	,m_ServerDlg(this, &m_MyServer, &m_DFStatusMnger)
	,m_ClientDlg(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExampleSaperaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SDK, m_cbSDK);
	DDX_Control(pDX, IDC_CB_FG, m_cbFG);
	DDX_Text(pDX, IDC_EDIT_BUF_NUM, m_nBuffer);
	DDX_Text(pDX, IDC_EDIT_FRAME_NUM, m_nGrabFrame);
	DDX_Control(pDX, IDC_LIST_STATUS, m_listStatus);
	DDX_Control(pDX, IDC_CHECK_INIT_FREE, m_InitFree);
	DDX_Control(pDX, IDC_CHECK_SNAP, m_Snap);
	DDX_Control(pDX, IDC_CHECK_START_STOP, m_StartStop);
	DDX_Control(pDX, IDC_EDIT_GRAB_CNT, m_GrabCnt);
	DDX_Control(pDX, IDC_CHECK_PROC, m_Processing);
	DDX_Control(pDX, IDC_EDIT_TRASH_CNT, m_TrashCnt);
	DDX_Control(pDX, IDC_EDIT_PROC_CNT, m_ProcCnt);
	DDX_Control(pDX, IDC_EDIT_XFER_CYCLE, m_XferCycle);
	DDX_Control(pDX, IDC_EDIT_PRO_CYCLE, m_ProCycle);
	DDX_Control(pDX, IDC_ST_DISPLAY, m_ctrlDisplay);
	DDX_Control(pDX, IDC_BTN_FIT_DISPLAY, m_btnFitDisplay);
	DDX_Control(pDX, IDC_EDIT_BUF_INDEX, m_BufIndex);
	DDX_Text(pDX, IDC_EDIT_PLANE_INDEX, m_nPlaneIndex);
	DDX_Check(pDX, IDC_CHK_DUAL_FG, m_bChkDualFG);
	DDX_Control(pDX, IDC_EDIT_FRAME_RATE, m_FrameRate);
	DDX_Control(pDX, IDC_EDIT_COPY_TIME, m_CopyTime);
	DDX_Control(pDX, IDC_CHECK_LONGRUN, m_btnLongrun);
	DDX_Control(pDX, IDC_EDIT_RUN_CNT, m_RunCnt);
}

BEGIN_MESSAGE_MAP(CExampleSaperaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_MESSAGE(WM_UPDATE_MSG, &CExampleSaperaDlg::OnUpdateMsg)
	ON_CBN_SELCHANGE(IDC_CB_SDK, &CExampleSaperaDlg::OnCbnSelchangeCbSdk)
	ON_CBN_SELCHANGE(IDC_CB_FG, &CExampleSaperaDlg::OnCbnSelchangeCbFg)
	ON_BN_CLICKED(IDC_CHECK_INIT_FREE, &CExampleSaperaDlg::OnBnClickedCheckInitFree)
	ON_BN_CLICKED(IDC_CHECK_SNAP, &CExampleSaperaDlg::OnBnClickedCheckSnap)
	ON_BN_CLICKED(IDC_CHECK_START_STOP, &CExampleSaperaDlg::OnBnClickedCheckStartStop)
	ON_BN_CLICKED(IDC_BTN_SAVE_IMG, &CExampleSaperaDlg::OnBnClickedBtnSaveImg)
	ON_BN_CLICKED(IDC_CHECK_PROC, &CExampleSaperaDlg::OnBnClickedCheckProc)
	ON_COMMAND(ID_FILE_DIAGNOSTICTOOL, &CExampleSaperaDlg::OnFileDiagnostictool)	
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BTN_FIT_DISPLAY, &CExampleSaperaDlg::OnBnClickedBtnFitDisplay)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSELEAVE()
	ON_COMMAND(ID_FILE_EXIT, &CExampleSaperaDlg::OnFileExit)
	ON_COMMAND(ID_IMAGEPROCESSING_CONTRAST, &CExampleSaperaDlg::OnImageprocessingContrast)
	ON_COMMAND(ID_IMAGEANALYSIS_STATISTIC, &CExampleSaperaDlg::OnImageanalysisStatistic)
	ON_COMMAND(ID_ONBOARDPROCESSING_HDR, &CExampleSaperaDlg::OnOnboardprocessingHdr)
	ON_BN_CLICKED(IDC_BTN_PREV, &CExampleSaperaDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CExampleSaperaDlg::OnBnClickedBtnNext)
	ON_EN_CHANGE(IDC_EDIT_BUF_INDEX, &CExampleSaperaDlg::OnEnChangeEditBufIndex)
	ON_BN_CLICKED(IDC_BTN_PREV2, &CExampleSaperaDlg::OnBnClickedBtnPrev2)
	ON_BN_CLICKED(IDC_BTN_NEXT2, &CExampleSaperaDlg::OnBnClickedBtnNext2)
	ON_COMMAND(ID_FILE_IMAGEFILELOAD, &CExampleSaperaDlg::OnFileImagefileload)
	ON_COMMAND(ID_CONTROL_FFCCOEFFICIENTEDITOR, &CExampleSaperaDlg::OnControlFfccoefficienteditor)
	ON_BN_CLICKED(IDC_CHECK_LONGRUN, &CExampleSaperaDlg::OnBnClickedCheckLongrun)
	ON_COMMAND(ID_CONTROL_SERVER, &CExampleSaperaDlg::OnControlServer)
	ON_COMMAND(ID_CONTROL_CLIENT, &CExampleSaperaDlg::OnControlClient)
	ON_COMMAND(ID_CAMERA_LINEAHS, &CExampleSaperaDlg::OnCameraLineaHS)
	ON_COMMAND(ID_CAMERA_FALCON4, &CExampleSaperaDlg::OnCameraFalcon4)
	ON_COMMAND(ID_ONBOARDPROCESSING_FLATFIELDCORRECTION, &CExampleSaperaDlg::OnOnboardprocessingFlatfieldcorrection)
	ON_BN_CLICKED(IDC_CHK_DUAL_FG, &CExampleSaperaDlg::OnBnClickedChkDualFg)
	ON_COMMAND(ID_DEMO_LINEAHS2, &CExampleSaperaDlg::OnDemoLineahs2)
	ON_COMMAND(ID_LIGHT_ENVIT, &CExampleSaperaDlg::OnControlLightEnvit)
	ON_COMMAND(ID_CONTROL_FRAMEGRABBER32803, &CExampleSaperaDlg::OnControlFramegrabber32803)
END_MESSAGE_MAP()


// CExampleSaperaDlg 메시지 처리기

BOOL CExampleSaperaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	InitCtrl();

	UpdateStatus(0);
	GetDlgItem(IDC_CB_FG)->EnableWindow(FALSE);

	return FALSE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExampleSaperaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExampleSaperaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExampleSaperaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExampleSaperaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_bInit)
	{
		m_InitFree.SetCheck(BST_UNCHECKED);
		OnBnClickedCheckInitFree();
	}
}

void CExampleSaperaDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	int posDisplayX=165, posDisplayY=70;
	int heightListStatus = 100;
	int sizeBtnFitDisplay = 64;  
	int sizeBtnMoveCurrBuf = 32;
	int gap = 8;

	// Display
	m_nWidthPicCtrl = cx - posDisplayX - gap;
	m_nHeightPicCtrl = cy - posDisplayY - heightListStatus - gap;
	if (m_ctrlDisplay.GetSafeHwnd()) {
		m_ctrlDisplay.MoveWindow(posDisplayX, posDisplayY, m_nWidthPicCtrl, m_nHeightPicCtrl);	

		if (m_InitFree.GetCheck()) {
			m_pMyGuiMain->UpdateViewRect();
		}

		if (m_bInit) {
			m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);
		}
	}
	

	// Buttons
	if (m_btnFitDisplay.GetSafeHwnd()) {
		m_btnFitDisplay.MoveWindow(cx - sizeBtnFitDisplay -gap, 0, sizeBtnFitDisplay, sizeBtnFitDisplay);
	}

	// 현재 Buffer Index
	if (GetDlgItem(IDC_BTN_PREV)->GetSafeHwnd()) {
		GetDlgItem(IDC_BTN_PREV)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf*3) - gap, 0, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
		GetDlgItem(IDC_EDIT_BUF_INDEX)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf * 3) - gap + sizeBtnMoveCurrBuf, 0, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
		GetDlgItem(IDC_BTN_NEXT)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf * 3) - gap + sizeBtnMoveCurrBuf * 2, 0, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
	}
	if (GetDlgItem(IDC_BTN_PREV2)->GetSafeHwnd()) {
		GetDlgItem(IDC_BTN_PREV2)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf * 3) - gap, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
		GetDlgItem(IDC_EDIT_PLANE_INDEX)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf * 3) - gap + sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
		GetDlgItem(IDC_BTN_NEXT2)->MoveWindow(cx - sizeBtnFitDisplay - (sizeBtnMoveCurrBuf * 3) - gap + sizeBtnMoveCurrBuf * 2, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf, sizeBtnMoveCurrBuf);
	}

	// Status List
	if (m_listStatus.GetSafeHwnd()) {
		m_listStatus.MoveWindow(posDisplayX, posDisplayY + m_nHeightPicCtrl + gap, m_nWidthPicCtrl, heightListStatus - gap);
	}
}

BOOL CExampleSaperaDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}

/// <summary>
////////////////////////////////////////////////////// Mouse Event ///////////////////////////////////////////////////
/// </summary>
/// <param name="nFlags"></param>
/// <param name="zDelta"></param>
/// <param name="pt"></param>
/// <returns></returns>

BOOL CExampleSaperaDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_bInit) {	
		m_pMyGuiMain->OnMouseWheel(nFlags, zDelta, pt);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CExampleSaperaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//TRACE("mouse move : %d, %d\n", point.x, point.y);
	//	m_pMyGuiMain->m_posMouse = point;
	CRect rect;
	POINT coordinateMouse;

	CString msg;
	bool bRun = false;

	//if (m_bInit) {
	if (!m_bChkDualFG) {
		if (m_nGrabCnt[0] > 0) {
			bRun = true;
		}
	}
	else {
		if (m_nGrabCnt[0] > 0 && m_nGrabCnt[1] > 0) {
			bRun = true;
		}
	}

	if(bRun) {
		if (m_pMyGuiMain->OnMouseMove(nFlags, point))
		{

			if (m_pDstBuf8 == NULL)
			{
				msg.Format(_T("Envision Inspector - x : %d, y : %d, Value : %d"), m_pMyGuiMain->m_imageCoordinateMouse.x, m_pMyGuiMain->m_imageCoordinateMouse.y, 0);
			}
			else
			{
				if (m_pSrcBuf8[(m_nSizeX * m_nSizeY * m_nPlaneIndex) + (m_nSizeX * m_pMyGuiMain->m_imageCoordinateMouse.y) + m_pMyGuiMain->m_imageCoordinateMouse.x] >= 0) {
					//msg.Format(_T("Envision Inspector - x : %d, y : %d, Value : %d"), m_pMyGuiMain->m_imageCoordinateMouse.x, m_pMyGuiMain->m_imageCoordinateMouse.y, m_pDstBuf8[m_nSizeX * m_pMyGuiMain->m_imageCoordinateMouse.y + m_pMyGuiMain->m_imageCoordinateMouse.x]);
					msg.Format(_T("Envision Inspector - x : %d, y : %d, Value : %d"), m_pMyGuiMain->m_imageCoordinateMouse.x, m_pMyGuiMain->m_imageCoordinateMouse.y, m_pSrcBuf8[m_nSizeX * m_pMyGuiMain->m_imageCoordinateMouse.y + m_pMyGuiMain->m_imageCoordinateMouse.x]);
				}
			}

			SetWindowText(msg);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CExampleSaperaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bInit)
	{
		m_pMyGuiMain->OnLButtonDown(nFlags, point);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CExampleSaperaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bInit)
	{
		m_pMyGuiMain->OnLButtonUp(nFlags, point);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CExampleSaperaDlg::OnMouseLeave()
{
	if (m_bInit)
	{
		m_pMyGuiMain->OnMouseLeave();
	}

	CDialogEx::OnMouseLeave();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CExampleSaperaDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			// ESC 키 이벤트에 대한 처리 추가
			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			// Enter 키 이벤트에 대한 처리 추가
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DisplayStatus(const TCHAR* fmt, ...)
{
	CString strMsg;
	va_list args = NULL;
	va_start(args, fmt);
	strMsg.FormatV(fmt, args);
	va_end(args);

	CExampleSaperaDlg* pDlg = (CExampleSaperaDlg*)AfxGetApp()->GetMainWnd();
	if (pDlg && pDlg->GetSafeHwnd() && ::IsWindow(pDlg->GetSafeHwnd()))
	{
		pDlg->SendMessage(WM_UPDATE_MSG, (WPARAM)(LPSTR)(LPCTSTR)strMsg, 1);
	}
}

LRESULT CExampleSaperaDlg::OnUpdateMsg(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR szMsg = (LPCTSTR)wParam;
	int messageType = int(lParam);

	CString strMsg;
	CString str;

	switch (messageType)
	{
	case 0:		// Grab Callback 시, 업데이트
		str.Format("%d", m_nGrabCnt[0]);
		m_GrabCnt.SetWindowText(str);
		str.Format("%d", m_nTrashCnt[0]);
		m_TrashCnt.SetWindowText(str);
		str.Format("%d", m_nProcCnt[0]);
		m_ProcCnt.SetWindowText(str);
		str.Format("%d", m_nRunCnt);
		m_RunCnt.SetWindowText(str);

		str.Format("%.2f", m_fFrameRate);
		m_FrameRate.SetWindowText(str);
		str.Format("%.2f", m_fXferCycle);
		m_XferCycle.SetWindowText(str);
		
		//SetDlgItemInt(IDC_EDIT_XFER_CYCLE, m_nXferCycle);
		//SetDlgItemInt(IDC_EDIT_PRO_CYCLE, m_nProCycle);
		//SetDlgItemInt(IDC_EDIT_BUF_INDEX, m_nBufIndex);
		
		break;
	case 1:
		SYSTEMTIME systemTime;
		::GetLocalTime(&systemTime);
		strMsg.Format(_T("%04d%02d%02d %02d:%02d:%02d:%03d> %s"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds,
			szMsg);

		m_listStatus.InsertString(0, strMsg);

		if (m_listStatus.GetCount() > 1000)
		{
			m_listStatus.DeleteString(1000);
		}
		break;
	default:
		break;
	}

	return 0;
}

/// <summary>
/// //////////////////////////////////////////////////////// Custom Functions//////////////////////////////////////////////
/// </summary>
/// <returns></returns>

bool CExampleSaperaDlg::InitCtrl()
{
	int countFG;
	CString str;
	
	SetWindowText("Envision Inspector");

	// SDKs
	m_cbSDK.AddString("SaperaLT");
	m_cbSDK.AddString("MIL");
	m_cbSDK.SetFocus();

	// 시간 체크 설정
	QueryPerformanceFrequency(&m_perfFrequency);
	xferStartTime.QuadPart = 0;
	xferEndTime.QuadPart = 0;
	proStartTime.QuadPart = 0;
	proEndTime.QuadPart = 0;

	// 상태 체크
	m_bInit = false;
	m_bGrab = false;
	m_bCamControl = false;
	m_bProcessing = false;
	m_bLongrun = false;
	m_bStartServer = false;
	m_bStartClient = false;
	m_bContrast = false;
	m_bHDR = false;
	m_bImgStatistic = false;
	m_bProfileHorizontal = false;
	m_bDemoLineaHS2 = false;

	// Info
	m_nFG = 1;
	m_nPlanes = 1;
	m_nGrabCnt[0] = 0;
	m_nGrabCnt[1] = 0;
	m_nBufIndex = 0;
	str.Format("%d", m_nBufIndex);
	m_BufIndex.SetWindowText(str);
	m_nBufProIndex = 0;

	// Thread 처리 여부
	m_bUpdateUI = false;

	this->ShowWindow(SW_SHOWMAXIMIZED);
	this->UpdateWindow();

	return true;
}

bool CExampleSaperaDlg::FreeCtrl()
{
	// My ImgAnalysis
	if (m_bImgStatistic) {
		OnImageanalysisStatistic();
	}

	if (m_bContrast) {
		OnImageprocessingContrast();
	}

	if (m_bCamControl)
	{
		//OnControlCamera();
	}

	if (m_bHDR)
	{
		OnOnboardprocessingHdr();
	}

	return true;
}

bool CExampleSaperaDlg::Init()
{
	CString strTemp;
	bool bInit = false;

	UpdateData(TRUE);
	
	// CCF 선택
	TCHAR szFilter[] = _T("ccf file(*.ccf) | *.ccf;|*.*||");
	CFileDialog dlg(TRUE, _T("*.ccf"), _T("ccf"), OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return bInit;
	}

	m_strCamFilePath[0] = dlg.GetPathName();
	strTemp.Format("Envision Inspector - %s", m_strCamFilePath[0]);
	SetWindowText(strTemp);		// 제목 표시줄

	HWND hWnd = GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd();
	if (m_strSDK == "SaperaLT")
	{
		m_structCallbackContext[0].dlg = this;
		m_structCallbackContext[0].index = 0;

		bInit = m_SapMnger.Init(m_strBoardName[0], 0, m_strCamFilePath[0], m_nBuffer, XferCallback, (void*)&m_structCallbackContext[0], ProCallback, (void*)&m_structCallbackContext[0]);
		if (!bInit) {
			return false;
		}
		
		// 이미지 버퍼 정보
		m_nSizeX = m_SapMnger.GetImgSizeX();
		m_nSizeY = m_SapMnger.GetImgSizeY();
		
		m_nBitDepth = m_SapMnger.GetImgBitDepth();

		m_nBufIndex = m_SapMnger.GetBufIdx(false, m_bChkDualFG);
		m_pSrcBuf8 = m_SapMnger.GetBufData(m_nBufIndex, false, m_bChkDualFG);
		m_pDstBuf8 = m_SapMnger.GetBufData(m_nBufIndex, true, m_bChkDualFG);
	}
	else if (m_strSDK == "MIL")
	{
		
	}
	else
	{
		
	}

	return bInit;
}

bool CExampleSaperaDlg::InitDualFG()
{
	CString strTemp;
	bool bInit = false;

	UpdateData(TRUE);

	for (int i = 0; i < 2; i++) {
		// CCF 선택
		TCHAR szFilter[] = _T("ccf file(*.ccf) | *.ccf;|*.*||");
		CFileDialog dlg(TRUE, _T("*.ccf"), _T("ccf"), OFN_HIDEREADONLY, szFilter);
		if (IDOK != dlg.DoModal())
		{
			return bInit;
		}

		m_strCamFilePath[i] = dlg.GetPathName();
		strTemp.Format("Envision Inspector - %s", m_strCamFilePath[0]);
		SetWindowText(strTemp);		// 제목 표시줄
	}

	HWND hWnd = GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd();
	if (m_strSDK == "SaperaLT")
	{
		for (int i = 0; i < 2; i++) {
			m_structCallbackContext[i].dlg = this;
			m_structCallbackContext[i].index = i;
		}
		if (!strcmp(m_strBoardName[0], "Xtium3-CLHS_PX8_2")) {
			m_strBoardName[1] = "Xtium3-CLHS_PX8_1";
		}
		else {
			m_strBoardName[1] = "Xtium3-CLHS_PX8_2";
		}
		bInit = m_SapMnger.InitDual(m_strBoardName, 0, m_strCamFilePath, m_nBuffer, XferCallback, (void*)&m_structCallbackContext[0], (void*)&m_structCallbackContext[1], ProCallback, (void*)&m_structCallbackContext[0]);
		if (!bInit) {
			return false;
		}

		// 이미지 버퍼 정보
		m_nSizeX = m_SapMnger.GetImgSizeX();
		m_nSizeY = m_SapMnger.GetImgSizeY();

		m_nBitDepth = m_SapMnger.GetImgBitDepth();

		m_nBufIndex = m_SapMnger.GetBufIdx(false, m_bChkDualFG);
		m_pSrcBuf8 = m_SapMnger.GetBufData(m_nBufIndex, false, m_bChkDualFG);
		m_pDstBuf8 = m_SapMnger.GetBufData(m_nBufIndex, true, m_bChkDualFG);
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}

	return bInit;
}

bool CExampleSaperaDlg::InitClass()
{
	// My GUI
	m_pMyGuiMain = new MyGUI();
	m_pMyGuiMain->Init(&m_ctrlDisplay, m_pDstBuf8, m_nSizeX, m_nSizeY, 1, false);

	return true;
}

void CExampleSaperaDlg::Free(int index)
{
	int progressTime;

	QueryPerformanceCounter(&functionStartTime);
	if (m_strSDK == "SaperaLT")
	{
		m_SapMnger.Free(index);
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}
	QueryPerformanceCounter(&functionEndTime);
	progressTime = (functionEndTime.QuadPart - functionStartTime.QuadPart) * 1000.f / m_perfFrequency.QuadPart;
	DisplayStatus(_T("Free : %s[%d ms]"), m_strSDK, progressTime);
}

bool CExampleSaperaDlg::FreeClass()
{
	m_pMyGuiMain->Free();
	delete m_pMyGuiMain;
	m_pMyGuiMain = NULL;

	return true;
}

void CExampleSaperaDlg::UpdateStatus(int status) {
	// 0: Free, 1: Init 2:Grabbing
	switch (status) {
	case 0:
		m_nGrabCnt[0] = 0;
		m_nGrabCnt[1] = 0;
		m_nProcCnt[0] = 0;
		m_nProcCnt[1] = 0;

		m_bInit = false;

		if (m_bProcessing)
		{
			m_Processing.SetCheck(BST_UNCHECKED);
			OnBnClickedCheckProc();
		}
		// 비활성화/활성화 설정
		GetDlgItem(IDC_EDIT_BUF_NUM)->EnableWindow(TRUE);
		m_InitFree.SetWindowTextA(_T("Init"));

		break;
	case 1:	// Init
		m_nGrabCnt[0] = 0;
		m_nGrabCnt[1] = 0;
		m_nProcCnt[0] = 0;
		m_nProcCnt[1] = 0;

		m_bInit = true;
		m_bGrab = false;

		m_InitFree.SetWindowTextA(_T("Free"));
		break;
	case 2:

		m_bGrab = true;
		break;
	}

	// 비활성화/활성화 설정
	GetDlgItem(IDC_CB_SDK)->EnableWindow(!m_bInit);
	GetDlgItem(IDC_EDIT_BUF_NUM)->EnableWindow(!m_bInit);
	GetDlgItem(IDC_CHK_DUAL_FG)->EnableWindow(!m_bInit);
	
	GetDlgItem(IDC_CHECK_PROC)->EnableWindow(!m_bGrab);

	UpdateData(FALSE);
}

void CExampleSaperaDlg::XferCallback(SapXferCallbackInfo* pInfo)
{
	StructCallbackContext *structCallbackContext = (StructCallbackContext *)pInfo->GetContext();

	structCallbackContext->dlg->Xfer_Callback(pInfo, structCallbackContext->index);
}

void CExampleSaperaDlg::ProCallback(SapProCallbackInfo* pInfo)
{
	StructCallbackContext* structCallbackContext = (StructCallbackContext*)pInfo->GetContext();

	structCallbackContext->dlg->Pro_Callback(pInfo, structCallbackContext->index);
}

void CExampleSaperaDlg::Xfer_Callback(SapXferCallbackInfo* pInfo, int index)
{
	CString str;
	bool bRun = false;
	int tempSum = 0;
	
	if (pInfo->IsTrash())
	{
		++m_nTrashCnt[index];
	}

	// Refresh view
	else
	{
		++m_nGrabCnt[index];

		if (!m_bChkDualFG) {
			bRun = true;
		}
		else {

			if (m_nGrabCnt[0] == m_nGrabCnt[1]) {
				bRun = true;
			}
			else if (m_nGrabCnt[0] < m_nGrabCnt[1]) {
				if (index == 0) {
					bRun = true;
				}
			}
			else if (m_nGrabCnt[0] > m_nGrabCnt[1]) {
				if (index == 1) {
					bRun = true;
				}
			}
		}

		if (bRun) {
			QueryPerformanceCounter(&xferEndTime);
			if (m_nGrabCnt[index] > 0) {
				m_fXferCycle = (float)(xferEndTime.QuadPart - xferStartTime.QuadPart) * 1000.f / (float)m_perfFrequency.QuadPart;
				m_fMaxXferCycle = max(m_fXferCycle, m_fMaxXferCycle);
			}

			m_nBufIndex = m_SapMnger.GetBufIdx(false, m_bChkDualFG);

			m_pSrcBuf8 = m_SapMnger.GetBufData(m_nBufIndex, false, m_bChkDualFG);

			// Callback 시점에 여러 이벤트 발생
			if (m_bDemoLineaHS2) {
				if (m_nRunCnt%2 == 0) {
					memcpy(m_pDemoLineaHS2Dlg->m_pBuf1, m_pSrcBuf8, m_nSizeX * m_nSizeY);
					m_pDemoLineaHS2Dlg->m_pGui1->Show(m_pDemoLineaHS2Dlg->m_pBuf1, m_pDemoLineaHS2Dlg->m_pGui1->ViewCenterPosX, m_pDemoLineaHS2Dlg->m_pGui1->ViewCenterPosY);			// View
				}
				else if (m_nRunCnt % 2 == 1) {
					tempSum = 0;
					
					for (int row = 0; row < (m_nSizeY / 3); row++) {
						for (int col = 0; col < m_nSizeX; col++) {
							tempSum = m_pSrcBuf8[(3 * (row + 336) + 0) * m_nSizeX + col] + m_pSrcBuf8[((3 * (row)) + 1) * m_nSizeX + col] + m_pSrcBuf8[((3 * (row+ 168)) + 2) * m_nSizeX + col];
							//
							if (tempSum > 255) {
								m_pDemoLineaHS2Dlg->m_pBuf2[(row) * m_nSizeX + col] = 255;
							}
							else {
								m_pDemoLineaHS2Dlg->m_pBuf2[(row) * m_nSizeX + col] = tempSum;
							}
						}
					}
					m_pDemoLineaHS2Dlg->m_pGui2->Show(m_pDemoLineaHS2Dlg->m_pBuf2, m_pDemoLineaHS2Dlg->m_pGui2->ViewCenterPosX, m_pDemoLineaHS2Dlg->m_pGui2->ViewCenterPosY);			// View
				}
				//else {
				//	for (int row = 0; row < m_nSizeY / 2-200; row++) {
				//		for (int col = 0; col < m_nSizeX; col++) {
				//			m_pDemoLineaHS2Dlg->m_pBuf3[row * m_nSizeX + col] = (int)(m_pSrcBuf8[(2 * (row+168)) * m_nSizeX + col] + m_pSrcBuf8[(2 * row + 1) * m_nSizeX + col])/2;
				//		}
				//	}
				//	m_pDemoLineaHS2Dlg->m_pGui3->Show(m_pDemoLineaHS2Dlg->m_pBuf3, m_pDemoLineaHS2Dlg->m_pGui3->ViewCenterPosX, m_pDemoLineaHS2Dlg->m_pGui3->ViewCenterPosY);			// View
				//}

				m_eventRunDemo.SetEvent();
			}
			else {
				if (!m_bProcessing)
				{
					QueryPerformanceCounter(&functionStartTime);
					//m_pDstBuf8 = m_SapMnger.GetBufData(m_nBufIndex, true, m_bChkDualFG);
					if (m_bContrast) {
						m_MyImgProcessing.GetHistogram(m_pSrcBuf8, m_nSizeX, m_nSizeY);
						m_MyImgProcessing.SetHistogramEQ(m_pDstBuf8, m_pSrcBuf8, m_nSizeX, m_nSizeY);
					}
					else {
						memcpy(m_pDstBuf8, m_pSrcBuf8, m_nSizeX * m_nSizeY);
					}
					QueryPerformanceCounter(&functionEndTime);
					m_fCopyTime = (float)(functionEndTime.QuadPart - functionStartTime.QuadPart) * 1000.f / (float)m_perfFrequency.QuadPart;

					if (m_bImgStatistic) {
						// Image Statistic 수행
						m_MyImgAnalysis.Analyze(m_pSrcBuf8, m_nSizeX, m_nSizeY);
					}
				}

				// Get Frame Rate
				m_fFrameRate = m_SapMnger.GetFrameRate();

				if (m_bProcessing)
				{
					m_SapMnger.ExecutePro();
				}
				else {
					if (m_bGrab) {
	
						m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);			// View
					}

					if (!m_bUpdateUI)
					{
						m_bUpdateUI = true;
						m_eventUpdateUI.SetEvent();		// UI update
					}
				}

				QueryPerformanceCounter(&xferStartTime);
			}
		}
	}
}

void CExampleSaperaDlg::Pro_Callback(SapProCallbackInfo* pInfo, int index)
{
	QueryPerformanceCounter(&proEndTime);
	if (m_nProcCnt[index] > 1) {
		m_fProCycle = (proEndTime.QuadPart - proStartTime.QuadPart) * 1000.f / m_perfFrequency.QuadPart;
		m_fMaxProCycle = max(m_fProCycle, m_fMaxProCycle);
	}

	++m_nProcCnt[index];

	m_nBufProIndex = m_SapMnger.GetBufIdx(true, m_bChkDualFG);
	m_pDstBuf8 = m_SapMnger.GetBufData(m_nBufProIndex, true, m_bChkDualFG);

	if (m_bImgStatistic) {
		// Image Statistic 수행
		m_MyImgAnalysis.Analyze(m_pSrcBuf8, m_nSizeX, m_nSizeY);
	}

	if (m_bGrab) {
		m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);			// View
	}

	if (!m_bUpdateUI)
	{
		m_bUpdateUI = true;
		m_eventUpdateUI.SetEvent();		// UI update
	}

	QueryPerformanceCounter(&proStartTime);
}

bool CExampleSaperaDlg::Snap(int num, int index)
{
	bool bRes = false;

	m_nGrabCnt[index] = 0;
	m_nTrashCnt[index] = 0;
	m_nProcCnt[index] = 0;
	m_fXferCycle = 0;
	m_fProCycle = 0;
	m_fMaxXferCycle = 0;
	m_fMaxProCycle = 0;
	m_Snap.SetWindowTextA(_T("Acquiring..."));

	if (m_strSDK == "SaperaLT")
	{
		bRes = m_SapMnger.Snap(num, index);
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}


	

	return bRes;
}

bool CExampleSaperaDlg::GrabStart(int index)
{
	bool bRes = false;

	if (m_strSDK == "SaperaLT")
	{
		bRes = m_SapMnger.Grab(index);
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}

	return bRes;
}

bool CExampleSaperaDlg::GrabStop(int index)
{
	bool bRes = false;

	if (m_strSDK == "SaperaLT")
	{
		bRes = m_SapMnger.Freeze(index);
		if (bRes) {
			m_SapMnger.Wait(100, index);
			m_SapMnger.Abort(index);
		}
		
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}

	return bRes;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CExampleSaperaDlg::OnCbnSelchangeCbSdk()
{
	int countFG;
	char *nameFG;
	int i;

	m_cbSDK.GetWindowTextA(m_strSDK);

	m_cbFG.ResetContent();
	m_cbFG.Clear();
	if (m_strSDK == "SaperaLT")
	{
		// Get Dalsa Frame Grabber List
		countFG = m_SapMnger.GetServerCount();
		for (i = 0; i < countFG; i++) {
			nameFG = m_SapMnger.GetServerName(i);
			m_cbFG.AddString(CA2T(nameFG));
		}
	}
	else if (m_strSDK == "MIL")
	{
		// Get Zebra Frame grabber List
		countFG = m_MilMnger.GetSystemCount();
		for (i = 0; i < countFG; i++) {
			nameFG = m_MilMnger.GetSystemName(i);
			m_cbFG.AddString(CA2T(nameFG));
		}
	}
	else
	{

	}

	m_cbFG.SetCurSel(countFG - 1);
	m_cbFG.GetWindowText(m_strBoardName[0]);

	GetDlgItem(IDC_CB_FG)->EnableWindow(TRUE);
}

void CExampleSaperaDlg::OnCbnSelchangeCbFg()
{
	m_cbFG.GetWindowText(m_strBoardName[0]);
}


void CExampleSaperaDlg::OnBnClickedCheckInitFree()
{
	UpdateData(TRUE);

	if (m_InitFree.GetCheck())
	{
		// SDK & FG Init
		if (!m_bChkDualFG) {
			m_nFG = 1;
			if (!Init())
			{
				m_InitFree.SetCheck(BST_UNCHECKED);
				return;
			}
		} else {
			m_nFG = 2;

			if (!InitDualFG())
			{
				m_InitFree.SetCheck(BST_UNCHECKED);
				return;
			}
		}

		InitClass();

		UpdateStatus(1);

		// GUi 업데이트 Thread 생성
		m_pThreadUpdateUI = AfxBeginThread(UpdateUIThread, this, THREAD_PRIORITY_NORMAL, 0);

		DisplayStatus(_T("%s 할당 완료 - 할당 버퍼 개수 : %d"), m_strSDK, m_nBuffer);
	}
	else
	{
		UpdateStatus(0);

		FreeCtrl();

		FreeClass();

		Free(0);
		if (m_bChkDualFG) {
			Free(1);
		}

		DisplayStatus(_T("%s 해제 완료"), m_strSDK);
	}
}

void CExampleSaperaDlg::OnBnClickedChkDualFg()
{

}

void CExampleSaperaDlg::OnBnClickedCheckSnap()
{
	bool bRes = false;

	if (!(m_bStartServer || m_bStartClient || m_bLongrun))
	{
		UpdateData(TRUE);
	}

	if (m_Snap.GetCheck())
	{
		for (int i = 0; i < m_nFG; i++) {
			bRes = Snap(m_nGrabFrame, i);
		}
		if (bRes)
		{
			if (!m_bLongrun)
			{
				DisplayStatus(_T("Snap 완료"));
			}
			m_Snap.SetCheck(BST_UNCHECKED);
		}
		else
		{
			DisplayStatus(_T("Snap 실패"));
			m_Snap.SetCheck(BST_UNCHECKED);
		}
		m_Snap.SetWindowTextA(_T("Snap"));
	}
	
}


void CExampleSaperaDlg::OnBnClickedCheckStartStop()
{
	bool bRes = false;

	if (!(m_bStartServer || m_bStartClient || m_bLongrun))
	{
		UpdateData(TRUE);
	}

	if (m_StartStop.GetCheck())
	{
		for(int i = 0; i < m_nFG; i++) {
			m_nGrabCnt[i] = 0;
			m_nTrashCnt[i] = 0;
			m_nProcCnt[i] = 0;
			m_fXferCycle = 0;
			m_fProCycle = 0;
			m_fMaxXferCycle = 0;
			m_fMaxProCycle = 0;

			GrabStart(i);
		}

		m_bGrab = true;
		m_StartStop.SetWindowTextA(_T("Grab Stop"));
		DisplayStatus(_T("Grab Start"));
	}
	else
	{
		for (int i = 0; i < m_nFG; i++) {
			GrabStop(i);
		}
		Sleep(200);

		// grab stop 후, 마지막 획득 영상 업데이트
		m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);
		if (m_bImgStatistic) {
			//m_MyImgAnalysis.Analyze(m_pDstBuf8, m_nSizeX, m_nSizeY);
			m_MyImgAnalysis.Analyze(m_pSrcBuf8, m_nSizeX, m_nSizeY);
		}

		m_bGrab = false;
		m_bUpdateUI = true;
		m_eventUpdateUI.SetEvent();		// UI update

		m_StartStop.SetWindowTextA(_T("Grab Start"));
		DisplayStatus(_T("Grab Stop"));
	}
}


void CExampleSaperaDlg::OnBnClickedBtnSaveImg()
{
	SYSTEMTIME systemTime;
	::GetLocalTime(&systemTime);

	CString strMonthFolder;
	strMonthFolder.Format(_T("%04d_%02d_%02d"), systemTime.wYear, systemTime.wMonth, systemTime.wDay);

	CFileFind finder;
	if (!finder.FindFile(strMonthFolder))
	{
		CreateDirectory(strMonthFolder, NULL);

	}

	CString strImgFile;

	 if (m_MyImgAnalysis.m_bInit)
	{
		if (m_nPlanes > 1) {
			strImgFile.Format(_T("%s\\Img_ave%.2f_%02d%02d%02d.crc"), strMonthFolder, m_MyImgAnalysis.m_structAnalysis->averageValue, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);			
		}
		else {
			strImgFile.Format(_T("%s\\Img_ave%.2f_%02d%02d%02d.tif"), strMonthFolder, m_MyImgAnalysis.m_structAnalysis->averageValue, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		}
	}
	else {
		if (m_nPlanes > 1) {
			strImgFile.Format(_T("%s\\Img_%d_%02d%02d%02d.crc"), strMonthFolder, m_nBufIndex, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		}
		else {
			strImgFile.Format(_T("%s\\Img_%d_%02d%02d%02d.tif"), strMonthFolder, m_nBufIndex, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		}
	}

	 if (m_strSDK == "SaperaLT")
	 {
		 m_SapMnger.SaveImg(strImgFile, m_bProcessing, m_nBufIndex, m_nPlanes, m_bChkDualFG);
	 }
	 else if (m_strSDK == "MIL")
	 {

	 }
	 else
	 {

	 }

	DisplayStatus(_T("이미지 저장 완료"));
}


void CExampleSaperaDlg::OnBnClickedCheckProc()
{
	UpdateData(TRUE);

	if (m_Processing.GetCheck())
	{
		m_bProcessing = true;

		DisplayStatus(_T("Sapera Pro On"));
	}
	else
	{
		m_bProcessing = false;

		DisplayStatus(_T("Sapera Pro Off"));
	}

	if (m_strSDK == "SaperaLT")
	{
		if (!m_bChkDualFG) {
			m_SapMnger.SetSapPro(m_bProcessing, 0);
		}
		else {
			m_SapMnger.SetSapPro(m_bProcessing, 0);
			m_SapMnger.SetSapPro(m_bProcessing, 1);
		}
	}
	else if (m_strSDK == "MIL")
	{

	}
	else
	{

	}

	
}

void CExampleSaperaDlg::OnBnClickedCheckLongrun()
{
	UpdateData(TRUE);

	if (m_btnLongrun.GetCheck())
	{
		m_bLongrun = true;
		// GUi 업데이트 Thread 생성
		m_pThreadLongrun = AfxBeginThread(LongrunThread, this, THREAD_PRIORITY_NORMAL, 0);

		m_btnLongrun.SetWindowTextA("Longrun Stop");
	}
	else
	{
		m_bLongrun = false;
		m_btnLongrun.SetWindowTextA("Longrun Start");
	}
	
}

void CExampleSaperaDlg::OnBnClickedBtnFitDisplay()
{
	if (m_pMyGuiMain->m_bInit)
	{
		m_ctrlDisplay.Invalidate();
		m_ctrlDisplay.UpdateWindow();
		m_pMyGuiMain->FitWindow();
	}
}


void CExampleSaperaDlg::OnBnClickedBtnPrev()
{
	CString str;
	UpdateData(TRUE);

	m_nBufIndex--;

	if (m_nBufIndex < 0) {
		m_nBufIndex = m_nBuffer - 1;
	}

	str.Format("%d", m_nBufIndex);
	m_BufIndex.SetWindowText(str);
}


void CExampleSaperaDlg::OnBnClickedBtnNext()
{
	CString str;
	UpdateData(TRUE);

	m_nBufIndex++;

	if (m_nBufIndex >= m_nBuffer) {
		m_nBufIndex = 0;
	}

	str.Format("%d", m_nBufIndex);
	m_BufIndex.SetWindowText(str);
}

// Buffer Index 변경 이벤트
void CExampleSaperaDlg::OnEnChangeEditBufIndex()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString strValue;

	UpdateData(TRUE);
	
	if (m_bInit) {
		if (!m_bGrab) {
			m_BufIndex.GetWindowText(strValue);
			m_nBufIndex = _ttoi(strValue);
			if (m_nBufIndex >= 0 && m_nBufIndex < m_nBuffer) {
				m_pDstBuf8 = m_SapMnger.GetBufData(m_nBufIndex, false, m_bChkDualFG);
				m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);
				
				if (m_bImgStatistic) {
					m_MyImgAnalysis.Analyze(m_pSrcBuf8, m_nSizeX, m_nSizeY);
					Sleep(100);
					if (!m_bUpdateUI)
					{
						m_bUpdateUI = true;
						m_eventUpdateUI.SetEvent();		// UI update
					}
				}
			}
		}
	}
}


void CExampleSaperaDlg::OnBnClickedBtnPrev2()
{
	UpdateData(TRUE);

	m_nPlaneIndex--;

	if (m_nPlaneIndex < 0) {
		m_nPlaneIndex = m_nPlanes - 1;
	}

	m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);
	

	UpdateData(FALSE);
}


void CExampleSaperaDlg::OnBnClickedBtnNext2()
{
	UpdateData(TRUE);

	m_nPlaneIndex++;

	if (m_nPlaneIndex >= m_nPlanes) {
		m_nPlaneIndex = 0;
	}

	m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);

	UpdateData(FALSE);
}

/// <summary>
/// //////////////////////////////////////////////////////////// Thread Methods ////////////////////////////////////////////////////////
/// </summary>
/// <param name="lParam"></param>
/// <returns></returns>
UINT CExampleSaperaDlg::UpdateUIThread(LPVOID lParam)
{
	CExampleSaperaDlg* pDlg = (CExampleSaperaDlg*)lParam;
	CString str;

	while (pDlg->m_bInit)
	{
		if (pDlg->m_bUpdateUI) {
			// Main 다이얼로그
			str.Format("%d", pDlg->m_nGrabCnt[0]);
			pDlg->m_GrabCnt.SetWindowText(str);
			str.Format("%d", pDlg->m_nTrashCnt[0]);
			pDlg->m_TrashCnt.SetWindowText(str);
			str.Format("%d", pDlg->m_nProcCnt[0]);
			pDlg->m_ProcCnt.SetWindowText(str);
			str.Format("%d", pDlg->m_nRunCnt);
			pDlg->m_RunCnt.SetWindowText(str);

			//pDlg->m_bUpdateUI = true;
			if (!pDlg->m_bProcessing) {
				str.Format("%d", pDlg->m_nBufIndex);
			}
			else {
				str.Format("%d", pDlg->m_nBufProIndex);
			}
			
			pDlg->m_BufIndex.SetWindowText(str);

			str.Format("%.2f", pDlg->m_fFrameRate);
			pDlg->m_FrameRate.SetWindowText(str);
			str.Format("%.2f", pDlg->m_fCopyTime);
			pDlg->m_CopyTime.SetWindowText(str);
			str.Format("%.2f", pDlg->m_fMaxXferCycle);
			pDlg->m_XferCycle.SetWindowText(str);
			str.Format("%.2f", pDlg->m_fMaxProCycle);
			pDlg->m_ProCycle.SetWindowText(str);

			// ImgStatistic 다이얼로그
			if (pDlg->m_bImgStatistic) {
				str.Format(_T("%d"), pDlg->m_MyImgAnalysis.m_structAnalysis->maxValue);
				pDlg->m_pImgStatisticDlg->m_listImgInfo.SetItem(0, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				str.Format(_T("%d"), pDlg->m_MyImgAnalysis.m_structAnalysis->minValue);
				pDlg->m_pImgStatisticDlg->m_listImgInfo.SetItem(1, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				str.Format(_T("%.1f"), pDlg->m_MyImgAnalysis.m_structAnalysis->averageValue);
				pDlg->m_pImgStatisticDlg->m_listImgInfo.SetItem(2, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				str.Format(_T("%.1f"), pDlg->m_MyImgAnalysis.m_structAnalysis->stdValue);
				pDlg->m_pImgStatisticDlg->m_listImgInfo.SetItem(3, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			}
		}
		pDlg->m_bUpdateUI = false;
		// 현재 쓰레드 카운터를 가져옴
		WaitForSingleObject(pDlg->m_eventUpdateUI, INFINITE);
	}

	return 0;
}

UINT CExampleSaperaDlg::DemoThread(LPVOID lParam)
{
	CExampleSaperaDlg* pDlg = (CExampleSaperaDlg*)lParam;
	CString str;
	int progressTime;

	pDlg->m_SapMnger.OpenGenICam(pDlg->m_strBoardName[0]);
	pDlg->ConnectEnvit();

	pDlg->ControlEnvit();
	pDlg->OnOffEnvit(0, false);
	pDlg->OnOffEnvit(1, true);
	pDlg->OnOffEnvit(2, false);
	pDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorTDIModeSelection", "Tdi");

	pDlg->m_nRunCnt = 0;
	while (pDlg->m_bDemo)
	{
		
		for (int i = 0; i < pDlg->m_nFG; i++) {
			pDlg->Snap(1, i);
		}
		Sleep(200);

		pDlg->m_eventRunDemoMotion.SetEvent();

		WaitForSingleObject(pDlg->m_eventRunDemo, INFINITE);
		for (int i = 0; i < pDlg->m_nFG; i++) {
			pDlg->GrabStop(i);
		}
		Sleep(300);
		pDlg->m_nRunCnt++;

		//QueryPerformanceCounter(&pDlg->functionStartTime);
		if (pDlg->m_nRunCnt%2 == 0) {
			pDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorTDIModeSelection", "Tdi");
			if(pDlg->m_pDemoLineaHS2Dlg->m_nMode == 0){
			pDlg->OnOffEnvit(1, true);
			pDlg->OnOffEnvit(2, false); // Andy
			}
		}
		else if (pDlg->m_nRunCnt % 2 == 1) {
			pDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorTDIModeSelection", "Tdi3Array");
			
			pDlg->OnOffEnvit(1, false);
			pDlg->OnOffEnvit(2, true);
		}
		//else {
		//	pDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorTDIModeSelection", "TdiHfw");
		//}
		//QueryPerformanceCounter(&pDlg->functionEndTime);
		//progressTime = (float)(pDlg->functionEndTime.QuadPart - pDlg->functionStartTime.QuadPart) * 1000.f / (float)pDlg->m_perfFrequency.QuadPart;
		//DisplayStatus(_T("Demo Cnt : %d[time : %dms]"), pDlg->m_nRunCnt, progressTime);
		Sleep(300);
	}

	pDlg->OnOffEnvit(0, false);
	pDlg->OnOffEnvit(1, false);
	pDlg->OnOffEnvit(2, false);

	pDlg->DisconnectEnvit();
	pDlg->m_SapMnger.CloseGenICam();

	return 0;
}

UINT CExampleSaperaDlg::DemoThreadMotion(LPVOID lParam)
{
	CExampleSaperaDlg* pDlg = (CExampleSaperaDlg*)lParam;

	while (pDlg->m_bDemoMotion)
	{
		WaitForSingleObject(pDlg->m_eventRunDemoMotion, INFINITE);
		Sleep(500);
		if (!pDlg->m_bDemoMotion) {
			break;
		}
#ifdef ACSC
		// Motion 제어
		if (pDlg->m_nRunCnt % 2 == 0) {
			if (pDlg->m_pDemoLineaHS2Dlg->m_nMode == 0) {
				acsc_RunBuffer(hComm, 3, NULL, NULL);
			}
			else {
				acsc_RunBuffer(hComm, 4, NULL, NULL);
			}
		}
		else {
			acsc_RunBuffer(hComm, 4, NULL, NULL);
		}
#endif
	}

	return 0;
}

UINT CExampleSaperaDlg::LongrunThread(LPVOID lParam)
{
	CExampleSaperaDlg* pDlg = (CExampleSaperaDlg*)lParam;
	
	pDlg->LongrunTest();
	

	return 1;
}

void CExampleSaperaDlg::LongrunTest()
{
	CString str;
	float averageValue = 0;

	DisplayStatus(_T("Start Longrun Test"));

	m_nRunCnt = 0;
	while (m_bLongrun)
	{
		m_nRunCnt++;
		/////////////////////////////////////// Snap Start ////////////////////////////////////////
		m_nGrabCnt[0] = 0;
		m_nGrabCnt[1] = 0;
		m_Snap.SetCheck(BST_CHECKED);
		OnBnClickedCheckSnap();
		if (m_bStartServer)
		{
			m_MyServer.SendSnap();
		}

		///////////////////////////////// 그랩 완료를 위해 대기 ///////////////////////////////////
		Sleep(5000);
		

		////////////////////////////////////// Check GrabCnt ///////////////////////////////////////
		if (m_nGrabFrame != m_nGrabCnt[0]) {
			m_bLongrun = false;
			DisplayStatus(_T("Grab Cnt is not mached. GrabCnt=%d"), m_nGrabCnt[0]);
		}

		////////////////////////////// Check Image Average Brightness //////////////////////////////
		if (m_bImgStatistic) {
			for (int i = 0; i < m_nBuffer; i++) {
				m_nBufIndex = i;
				str.Format("%d", m_nBufIndex);
				m_BufIndex.SetWindowText(str);

				Sleep(300);

				if (i == 0) {
					averageValue = m_MyImgAnalysis.m_structAnalysis->averageValue;
				}
				else {
					if (abs(averageValue - m_MyImgAnalysis.m_structAnalysis->averageValue) > 1)
					{
						m_bLongrun = false;
						DisplayStatus(_T("Aveage Value is not mached. BufIndex=%d"), i);
					}
				}
			}
		}

		// check Grab Cnt
		if (m_bStartServer)
		{
			m_MyServer.SendGrabCnt();
			Sleep(500);

			// check All's status are GrabReady status
			//if (!m_DFStatusMnger.IsAllGrabReadyStatus())
			//{
			//	m_bLongrun = false;
			//	DisplayStatus(_T("Slaves have some problem about grabStop"));
			//}

			// check all's grab cnt are same
			if (!m_DFStatusMnger.IsAllGrabCntSame(m_nGrabCnt[0]))
			{
				m_bLongrun = false;
				DisplayStatus(_T("All's cnt of grab aren't same"));
			}
		}

		// Run 인터벌
		//Sleep(1000);
	}

	m_btnLongrun.SetCheck(BST_UNCHECKED);
	m_btnLongrun.SetWindowTextA("Longrun Start");
	DisplayStatus(_T("Finish Longrun Test"));
}

///////////////////////////////////////////////////////// <summary>			 /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// MENU 이벤트 처리기 /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// </summary>		 /////////////////////////////////////////////////////////

/// <summary>
/// File
/// </summary>
void CExampleSaperaDlg::OnFileImagefileload()
{
	// Image file 선택
	CString strFilePath[100];
	int fileCnt = 0;
	TCHAR szFilter[] = _T("image(*.bmp, *.tif, *.jpg, *.png) | *.bmp; *.tif; *.jpg; *.png | ALL Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	POSITION pos = dlg.GetStartPosition();
	while (pos)
	{
		strFilePath[fileCnt] = dlg.GetNextPathName(pos);
		fileCnt++;
	}

	// Sapera 할당
	//m_Buffer = new SapBuffer(strFilePath[0]);
	//m_Buffer->Create();
	//m_Buffer->Clear();
	//m_nSizeX = m_Buffer->GetWidth();
	//m_nSizeY = m_Buffer->GetHeight();
	//m_BufferPro = new SapBuffer(strFilePath[0]);
	//m_BufferPro->Create();
	//m_BufferPro->Clear();
	//for (int i = 0; i < fileCnt; i++) {
	//	m_Buffer[i].Load(strFilePath[fileCnt]);
	//}

	InitClass();

	//m_Buffer->Load(strFilePath[0], "-format auto", -1, 0);
	//m_BufferPro->Copy(m_Buffer);
	//m_BufferPro->GetParameter(0, CORBUFFER_PRM_ADDRESS, &m_pDstBuf8);
	
	m_nGrabCnt[0] = 1;
	m_bInit = true;

	m_pMyGuiMain->Show(m_pDstBuf8, m_pMyGuiMain->ViewCenterPosX, m_pMyGuiMain->ViewCenterPosY);			// View

	
}

void CExampleSaperaDlg::OnFileDiagnostictool()
{
	m_pDiagnosticDlg = new CDiagnosticDlg;
	m_pDiagnosticDlg->Create(IDD_DIALOG_DIAGNOSTIC, this);
	m_pDiagnosticDlg->ShowWindow(SW_SHOWNORMAL);
}

void CExampleSaperaDlg::OnFileExit()
{
	PostQuitMessage(0);
}

/// <summary>
/// Control
/// </summary>
void CExampleSaperaDlg::OnCameraLineaHS()
{
	CMenu* hMenu = GetMenu();

	if (hMenu->GetMenuState(ID_CAMERA_LINEAHS, MF_BYCOMMAND) != MF_CHECKED) {

		if (m_bInit) {
			// 카메라 설정
			if (m_SapMnger.OpenGenICam(m_strBoardName[0])) {
				
				m_pControlCameraDlg = new CControlCameraDlg;
				m_pControlCameraDlg->Create(IDD_DIALOG_CONTROL_CAMERA, this);
				m_pControlCameraDlg->ShowWindow(SW_SHOWNORMAL);

				m_bCamControl = true;

				hMenu->CheckMenuItem(ID_CAMERA_LINEAHS, MF_CHECKED);
			}
			else
			{
				AfxMessageBox(_T("Fail to Open GenICam"));
			}
		}
	}
	else {
		if (m_pControlCameraDlg != nullptr) {
			m_pControlCameraDlg->DestroyWindow();
			delete m_pControlCameraDlg;
			m_pControlCameraDlg = nullptr;
		}

		m_SapMnger.CloseGenICam();

		m_bCamControl = false;

		hMenu->CheckMenuItem(ID_CAMERA_LINEAHS, MF_UNCHECKED);
	}
}

void CExampleSaperaDlg::OnCameraFalcon4()
{
	CMenu* hMenu = GetMenu();

	if (hMenu->GetMenuState(ID_CAMERA_FALCON4, MF_BYCOMMAND) != MF_CHECKED) {

		if (m_bInit) {
			// 카메라 설정
			if (m_SapMnger.OpenGenICam(m_strBoardName[0])) {
				
			}

			m_pControlFalcon4Dlg = new ControlFalcon4Dlg;
			m_pControlFalcon4Dlg->Create(IDD_DIALOG_CTRL_FALCON4, this);
			m_pControlFalcon4Dlg->ShowWindow(SW_SHOWNORMAL);

			m_bCamControl = true;

			hMenu->CheckMenuItem(ID_CAMERA_FALCON4, MF_CHECKED);
		}
	}
	else {
		if (m_pControlFalcon4Dlg != nullptr) {
			m_pControlFalcon4Dlg->DestroyWindow();
			delete m_pControlFalcon4Dlg;
			m_pControlFalcon4Dlg = nullptr;
		}

		m_SapMnger.CloseGenICam();

		m_bCamControl = false;

		hMenu->CheckMenuItem(ID_CAMERA_FALCON4, MF_UNCHECKED);
	}
}


void CExampleSaperaDlg::OnControlFramegrabber32803()
{
	m_pControlFGDlg = new ControlFGDlg;
	m_pControlFGDlg->Create(IDD_DIALOG_CTRL_FG, this);
	m_pControlFGDlg->ShowWindow(SW_SHOWNORMAL);
}

void CExampleSaperaDlg::OnControlFfccoefficienteditor()
{
	m_pFFCEditorDlg = new CFFCEditorDlg;
	m_pFFCEditorDlg->Create(IDD_DIALOG_FFC_EDITOR, this);
	m_pFFCEditorDlg->ShowWindow(SW_SHOWNORMAL);
}


void CExampleSaperaDlg::OnControlServer()
{
	if (m_ServerDlg.GetSafeHwnd() == NULL) {
		m_ServerDlg.Create(IDD_DIALOG_SERVER, this);
	}

	m_ServerDlg.ShowWindow(SW_SHOWNORMAL);
}


void CExampleSaperaDlg::OnControlClient()
{
	if (m_ClientDlg.GetSafeHwnd() == NULL) {
		m_ClientDlg.Create(IDD_DIALOG_CLIENT, this);
	}

	m_ClientDlg.ShowWindow(SW_SHOWNORMAL);
}

void CExampleSaperaDlg::OnControlLightEnvit()
{
	m_pControlLightEnvitDlg = new ControlLightEnvitDlg;
	m_pControlLightEnvitDlg->Create(IDD_DIALOG_CTRL_LIGHT_ENVIT, this);
	m_pControlLightEnvitDlg->ShowWindow(SW_SHOWNORMAL);
}

/// <summary>
/// OnBoardProcess
/// </summary>
void CExampleSaperaDlg::OnOnboardprocessingHdr()
{
	CMenu* hMenu = GetMenu();

	m_SapMnger.GetSapXfer()->Disconnect();
	
	if (hMenu->GetMenuState(ID_ONBOARDPROCESSING_HDR, MF_BYCOMMAND) != MF_CHECKED) {
		m_pHdrDlg = new CHdrDlg;
		m_pHdrDlg->Create(IDD_DIALOG_HDR, this);
		m_pHdrDlg->ShowWindow(SW_SHOWNORMAL);
	
		// Frame Grabber 설정
		if (m_SapMnger.GetOutputFormat() != CORACQ_VAL_OUTPUT_FORMAT_MONO8P2)
		{
			m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_HDR_WEIGHT, m_pHdrDlg->m_nWeight, TRUE);
			m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_HDR_ENABLE, 1, TRUE);
		}
	
		m_bHDR = true;
	
		hMenu->CheckMenuItem(ID_ONBOARDPROCESSING_HDR, MF_CHECKED);
		DisplayStatus(_T("HDR 설정 완료"));
	}
	else {
		if (m_pHdrDlg != nullptr) {
			m_pHdrDlg->DestroyWindow();
			delete m_pHdrDlg;
			m_pHdrDlg = nullptr;
		}
	
		// Frame Grabber 설정
		if (m_SapMnger.GetOutputFormat() != CORACQ_VAL_OUTPUT_FORMAT_MONO8P2)
		{
			m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_HDR_ENABLE, 0, TRUE);
		}
	
		m_bHDR = false;
	
		hMenu->CheckMenuItem(ID_ONBOARDPROCESSING_HDR, MF_UNCHECKED);
		DisplayStatus(_T("TDI Mono 설정 완료"));
	}
	
	m_SapMnger.GetSapXfer()->Connect();
}


void CExampleSaperaDlg::OnOnboardprocessingFlatfieldcorrection()
{
	m_pOnBoardFFCDlg = new OnBoardFFCDlg;
	m_pOnBoardFFCDlg->Create(IDD_DIALOG_ONBOARD_FFC, this);
	m_pOnBoardFFCDlg->ShowWindow(SW_SHOWNORMAL);
}

/// <summary>
/// Image Processing
/// </summary>

void CExampleSaperaDlg::OnImageprocessingContrast()
{
	CMenu* hMenu = GetMenu();

	if (hMenu->GetMenuState(ID_IMAGEPROCESSING_CONTRAST, MF_BYCOMMAND) != MF_CHECKED) {
		m_bContrast = true;
	
		m_SapMnger.GetSapPro()->setPro("contrast", m_bContrast);
		
		hMenu->CheckMenuItem(ID_IMAGEPROCESSING_CONTRAST, MF_CHECKED);
	}
	else {
		m_bContrast = false;
	
		m_SapMnger.GetSapPro()->setPro("contrast", m_bContrast);
	
		hMenu->CheckMenuItem(ID_IMAGEPROCESSING_CONTRAST, MF_UNCHECKED);
	}
}

/// <summary>
/// Image Analysis
/// </summary>
void CExampleSaperaDlg::OnImageanalysisStatistic()
{
	CMenu* hMenu = GetMenu();

	if (!m_bImgStatistic)
	{
		// Image Analysis Class 할당
		//m_MyImgAnalysis = new MyImgAnalysis();
		m_MyImgAnalysis.Init(m_pSrcBuf8, m_nSizeX, m_nSizeY);
		Sleep(500);		// Analysis 계산을 위한 딜레이

		// Image Analysis Dialog 할당
		m_pImgStatisticDlg = new CImgStatisticDlg;
		m_pImgStatisticDlg->Create(IDD_DIALOG_IMG_STATISTIC, this);
		m_pImgStatisticDlg->ShowWindow(SW_SHOWNORMAL);

		if (!m_bUpdateUI)
		{
			m_bUpdateUI = true;
			m_eventUpdateUI.SetEvent();		// UI update
		}

		m_bImgStatistic = true;
		hMenu->CheckMenuItem(ID_IMAGEANALYSIS_STATISTIC, MF_CHECKED);
		DisplayStatus(_T("Image Analysis 활성화"));
	}
	else
	{
		// Image Analysis Class 해제
		m_MyImgAnalysis.Free();
		
		// Image Analysis Dialog 해제
		if (m_pImgStatisticDlg != nullptr) {
			m_pImgStatisticDlg->DestroyWindow();
			delete m_pImgStatisticDlg;
			m_pImgStatisticDlg = nullptr;
		}

		m_bImgStatistic = false;
		hMenu->CheckMenuItem(ID_IMAGEANALYSIS_STATISTIC, MF_UNCHECKED);
		DisplayStatus(_T("Image Analysis 비활성화"));
	}
}

/// Demo
void CExampleSaperaDlg::OnDemoLineahs2()
{
	m_pDemoLineaHS2Dlg = new DemoLineaHS2Dlg;
	m_pDemoLineaHS2Dlg->Create(IDD_DIALOG_DEMO_HS2, this);
	m_pDemoLineaHS2Dlg->ShowWindow(SW_SHOWNORMAL);
	
	// Motion 연결
	int Port = 701;
#ifdef ACSC
	hComm = acsc_OpenCommEthernetTCP("10.0.0.100", Port);
#endif
	m_bDemoLineaHS2 = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CExampleSaperaDlg::ConnectEnvit()
{
	// 시리얼 통신(조명 제어)
	CString str = "COM10";
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_CommEnvit = new CPYH_Comm("\\\\.\\" + str, "19200", "None", "8 Bit", "1 Bit");	// initial Comm port
	if (m_CommEnvit->Create(GetSafeHwnd()) != 0)	//통신포트를 열고 윈도우의 핸들을 넘긴다.
	{
		//AfxMessageBox("연결되었습니다.");
		m_CommEnvit->Clear();

		return true;
	}
	else
	{
		AfxMessageBox("Envit EGB 소스에 연결 실패하였습니다.");
		return false;
	}
}

bool CExampleSaperaDlg::DisconnectEnvit()
{
	m_CommEnvit->Close();
	m_CommEnvit->HandleClose();
	delete m_CommEnvit;
	m_CommEnvit = NULL;

	return true;
}

bool CExampleSaperaDlg::ControlEnvit(int r, int g, int b)
{
	m_comData[0] = 1;
	m_comData[1] = 1;
	m_comData[2] = 2;
	m_comData[3] = 204;

	// Red
	m_comData[4] = 1;
	//m_comData[5] = 44;
	//m_comData[6] = 1;
	//m_comData[7] = 3;
	m_comData[5] = r%256;
	m_comData[6] = (int)(r/256);
	m_comData[7] = 3;
	m_comData[8] = 255;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	// Green
	m_comData[4] = 2;
	m_comData[5] = g%256;
	m_comData[6] = (int)(g / 256);
	m_comData[7] = 3;
	m_comData[8] = 178;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	// Blue
	//1023: 3-255-3-3-32
	// 256 : 3-0-1-3-207
	// 255 : 3-255-0-3-49
	// 16 : 3-16-0-3-222
	// 15 : 3-15-0-3-193
	// 10 : 3-10-0-3-196
	// 6 : 3-6-0-3-206
	// 5 : 3-5-0-3-203
	// 4 : 3-4-0-3-202
	// 3 : 3-3-0-3-205
	// 2 : 3-2-0-3-204
	// 1 : 3-1-0-3-207
	// 0 : 3-0-0-3-206
	m_comData[4] = 3;
	m_comData[5] = b%256;
	m_comData[6] = (int)(b / 256);
	m_comData[7] = 3;
	m_comData[8] = 88;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	return true;
}

bool CExampleSaperaDlg::ControlEnvit()
{
	m_setBitDepth[0] = 1;
	m_setBitDepth[1] = 1;
	m_setBitDepth[2] = 2;
	m_setBitDepth[3] = 245;
	m_setBitDepth[4] = 1;
	m_setBitDepth[5] = 3;
	m_setBitDepth[6] = 245;
	m_CommEnvit->Send((LPCTSTR)m_setBitDepth, 7);

	m_comData[0] = 1;
	m_comData[1] = 1;
	m_comData[2] = 2;
	m_comData[3] = 204;

	// Red
	m_comData[4] = 1;
	m_comData[5] = 44;
	m_comData[6] = 1;
	m_comData[7] = 3;
	m_comData[8] = 255;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	// Green
	m_comData[4] = 2;
	m_comData[5] = 160;
	m_comData[6] = 0;
	m_comData[7] = 3;
	m_comData[8] = 111;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	// Blue
	m_comData[4] = 3;
	m_comData[5] = 64;
	m_comData[6] = 0;
	m_comData[7] = 3;
	m_comData[8] = 142;
	Sleep(30);
	m_CommEnvit->Send((LPCTSTR)m_comData, 9);

	return true;
}

bool CExampleSaperaDlg::OnOffEnvit(int index, bool bOn)
{
	m_onOff[0] = 1;
	m_onOff[1] = 1;
	m_onOff[2] = 2;
	m_onOff[3] = 193;

	if (bOn) {	// On
		if (index == 0) {		// Red
			m_onOff[4] = 1;
			m_onOff[5] = 1;
			m_onOff[6] = 3;
			m_onOff[7] = 192;
			Sleep(10);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);
		}
		else if (index == 1) {		// Green
			m_onOff[4] = 2;
			m_onOff[5] = 1;
			m_onOff[6] = 3;
			m_onOff[7] = 195;
			Sleep(20);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);
		}
		else {		// Blue
			m_onOff[4] = 3;
			m_onOff[5] = 1;
			m_onOff[6] = 3;
			m_onOff[7] = 194;
			Sleep(20);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);
		}
	}
	else {		 // Off
		if (index == 0) {		// Red

			m_onOff[4] = 1;
			m_onOff[5] = 0;
			m_onOff[6] = 3;
			m_onOff[7] = 193;
			Sleep(20);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);
		}
		else if (index == 1) {		// Green
			m_onOff[4] = 2;
			m_onOff[5] = 0;
			m_onOff[6] = 3;
			m_onOff[7] = 194;
			Sleep(20);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);

		}
		else {		// Blue
			m_onOff[4] = 3;
			m_onOff[5] = 0;
			m_onOff[6] = 3;
			m_onOff[7] = 195;
			Sleep(20);
			m_CommEnvit->Send((LPCTSTR)m_onOff, 8);
		}
	}
	return true;
}

