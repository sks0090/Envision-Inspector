// DemoLineaHS2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "DemoLineaHS2Dlg.h"

#include "Example_SaperaDlg.h"

// DemoLineaHS2Dlg 대화 상자

IMPLEMENT_DYNAMIC(DemoLineaHS2Dlg, CDialogEx)

DemoLineaHS2Dlg::DemoLineaHS2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEMO_HS2, pParent)
{

}

DemoLineaHS2Dlg::~DemoLineaHS2Dlg()
{
}

void DemoLineaHS2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_DISPLAY1, m_stDisplay1);
	DDX_Control(pDX, IDC_ST_DISPLAY2, m_stDisplay2);
	DDX_Control(pDX, IDC_ST_DISPLAY3, m_stDisplay3);
	DDX_Control(pDX, IDC_CHK_START, m_chkStart);
	DDX_Control(pDX, IDC_BIT_UI, m_bitUI);
	DDX_Control(pDX, IDC_BIT_RESPONSIVITY_OFF, m_bitResponsivityOff);
	DDX_Control(pDX, IDC_BIT_RESPONSIVITY_ON, m_bitResponsivityOn);
	DDX_Control(pDX, IDC_BIT_SPEED_OFF, m_bitSpeedOff);
	DDX_Control(pDX, IDC_BIT_SPEED_ON, m_bitSpeedOn);
}


BEGIN_MESSAGE_MAP(DemoLineaHS2Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_START, &DemoLineaHS2Dlg::OnBnClickedChkStart)
	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_UI_ON, &DemoLineaHS2Dlg::OnBnClickedBtnUiOn)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_BIT_SPEED_OFF, &DemoLineaHS2Dlg::OnClickedBitSpeedOff)
	ON_STN_CLICKED(IDC_BIT_RESPONSIVITY_OFF, &DemoLineaHS2Dlg::OnClickedBitResponsivityOff)
END_MESSAGE_MAP()


// DemoLIneaHS2Dlg 메시지 처리기


BOOL DemoLineaHS2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RECT rect;
	CRect rWnd;

	// 4k 3840x2160
	m_widthDisplay = 3840;
	m_heightDisplay = 2160;
	m_leftSpeedBtn = 1316;
	m_leftResponsivityBtn = 3186;
	m_topBtns = 560;
	m_widthBtn = 499;
	m_heightBtn = 105;
	
	// FHD 1920x1080
	//m_widthDisplay = 1920;
	//m_heightDisplay = 1080;
	//m_leftSpeedBtn = 659;
	//m_leftResponsivityBtn = 1593;
	//m_topBtns = 281;
	//m_widthBtn = 250;
	//m_heightBtn = 53;

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	rect.left = 0;
	rect.right = m_widthDisplay;
	rect.top = 0;
	rect.bottom = m_heightDisplay;
	
	// 창 크기 조정
	MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

	// 4k
	int width = 1670, height = 1179;
	int left = 157, top = 695, gap = 174;

	// FHD
	//int width = 830, height = 590;		// FHD
	//int left = 78, top = 348, gap = 87;

	// Display 1
	if (GetDlgItem(IDC_ST_DISPLAY1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_ST_DISPLAY1)->GetWindowRect(rWnd);
		rWnd.left = left;
		rWnd.top = top;
		rWnd.right = rWnd.left + width;
		rWnd.bottom = rWnd.top + height;
		GetDlgItem(IDC_ST_DISPLAY1)->MoveWindow(rWnd);
	}
	// Display2
	if (GetDlgItem(IDC_ST_DISPLAY2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_ST_DISPLAY2)->GetWindowRect(rWnd);
		rWnd.left = left + width + gap;
		rWnd.top = top;
		rWnd.right = rWnd.left + width;
		rWnd.bottom = rWnd.top + height;
		GetDlgItem(IDC_ST_DISPLAY2)->MoveWindow(rWnd);
	}
	if (GetDlgItem(IDC_CHK_START)->GetSafeHwnd())
	{
		GetDlgItem(IDC_CHK_START)->GetWindowRect(rWnd);
		rWnd.left = 0;
		rWnd.top = 0;
		rWnd.right = 300;
		rWnd.bottom = 300;
		GetDlgItem(IDC_CHK_START)->MoveWindow(rWnd);
	}

	if (GetDlgItem(IDC_BTN_UI_ON)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BTN_UI_ON)->GetWindowRect(rWnd);
		rWnd.left = 300;
		rWnd.top = 0;
		rWnd.right = 600;
		rWnd.bottom = 300;
		GetDlgItem(IDC_BTN_UI_ON)->MoveWindow(rWnd);
	}

	m_nMode = 0;

	InitDemo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL DemoLineaHS2Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (pMainDlg->m_bInit) {
		m_pGui1->OnMouseWheel(nFlags, zDelta, pt);
		m_pGui2->OnMouseWheel(nFlags, zDelta, pt);
		//m_pGui3->OnMouseWheel(nFlags, zDelta, pt);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void DemoLineaHS2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (pMainDlg->m_bInit)
	{
		m_pGui1->OnLButtonDown(nFlags, point);
		m_pGui2->OnLButtonDown(nFlags, point);
		//m_pGui3->OnLButtonDown(nFlags, point);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DemoLineaHS2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (pMainDlg->m_bInit)
	{
		m_pGui1->OnLButtonUp(nFlags, point);
		m_pGui2->OnLButtonUp(nFlags, point);
		//m_pGui3->OnLButtonUp(nFlags, point);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

void DemoLineaHS2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CRect rect;
	POINT coordinateMouse;

	CString msg;
	bool bRun = false;

	//if (m_bInit) {
	if (!pMainDlg->m_bChkDualFG) {
		if (pMainDlg->m_nGrabCnt[0] > 0) {
			bRun = true;
		}
	}
	else if (pMainDlg->m_nRunCnt > 0) {
		bRun = true;
	}
	else {
		if (pMainDlg->m_nGrabCnt[0] > 0 && pMainDlg->m_nGrabCnt[1] > 0) {
			bRun = true;
		}
	}
	if (bRun) {
		m_pGui1->OnMouseMove(nFlags, point);
		m_pGui2->OnMouseMove(nFlags, point);
		//m_pGui3->OnMouseMove(nFlags, point);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////// Run Demo ///////////////////////////////////////////////
void DemoLineaHS2Dlg::InitDemo()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int countFG;
	char* nameFG;

	pMainDlg->m_nFG = 2;
	pMainDlg->m_strSDK = "SaperaLT";
	pMainDlg->m_bChkDualFG = true;
	pMainDlg->UpdateData(FALSE);
	

	// Get Dalsa Frame Grabber List
	countFG = pMainDlg->m_SapMnger.GetServerCount();
	for (int i = 0; i < countFG; i++) {
		nameFG = pMainDlg->m_SapMnger.GetServerName(i);
		pMainDlg->m_cbFG.AddString(CA2T(nameFG));
	}

	pMainDlg->m_cbFG.SetCurSel(countFG - 1);
	pMainDlg->m_cbFG.GetWindowText(pMainDlg->m_strBoardName[0]);

	// Init
	pMainDlg->InitDualFG();
	
	m_Buffer1 = new SapBuffer(1, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY, CORDATA_FORMAT_MONO8, SapBuffer::TypeScatterGather);
	m_Buffer2 = new SapBuffer(1, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY/3, CORDATA_FORMAT_MONO8, SapBuffer::TypeScatterGather);
	//m_Buffer3 = new SapBuffer(1, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY/2, CORDATA_FORMAT_MONO8, SapBuffer::TypeScatterGather);

	m_Buffer1->Create();
	m_Buffer2->Create();
	//m_Buffer3->Create();

	m_Buffer1->Clear();
	m_Buffer2->Clear();
	//m_Buffer3->Clear();

	m_Buffer1->GetParameter(0, CORBUFFER_PRM_ADDRESS, &m_pBuf1);
	m_Buffer2->GetParameter(0, CORBUFFER_PRM_ADDRESS, &m_pBuf2);
	//m_Buffer3->GetParameter(0, CORBUFFER_PRM_ADDRESS, &m_pBuf3);

	// My GUI
	m_pGui1 = new MyGUI();
	m_pGui2 = new MyGUI();
	//m_pGui3 = new MyGUI();

	m_pGui1->Init(&m_stDisplay1, m_pBuf1, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY, 1, false);
	m_pGui2->Init(&m_stDisplay2, m_pBuf2, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY/3, 1, false);
	//m_pGui3->Init(&m_stDisplay3, m_pBuf3, pMainDlg->m_nSizeX, pMainDlg->m_nSizeY/2, 1, false);

	pMainDlg->m_bInit = true;

}

void DemoLineaHS2Dlg::OnBnClickedChkStart()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	if (m_chkStart.GetCheck())
	{
		pMainDlg->m_bDemo = true;
		pMainDlg->m_bDemoMotion = true;
		// UI
		m_bitUI.MoveWindow(0, 0, m_widthDisplay, m_heightDisplay);
		hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_UI));
		m_bitUI.SetBitmap(hbit);

		// Buttons
		m_bitSpeedOff.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitResponsivityOn.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitSpeedOn.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitResponsivityOff.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);

		hbitSpeedOn = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SPEED_ON));
		hbitSpeedOff = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_SPEED_OFF));
		hbitResponsivityOn = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RESPONSIVITY_ON));
		hbitResponsivityOff = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_RESPONSIVITY_OFF));

		m_bitSpeedOn.SetBitmap(hbitSpeedOn);
		m_bitResponsivityOff.SetBitmap(hbitResponsivityOff);

		// Demo Thread 생성
		pMainDlg->m_pThreadDemo = AfxBeginThread(pMainDlg->DemoThread, pMainDlg, THREAD_PRIORITY_NORMAL, 0);
		Sleep(200);
		
		// Demo Thread 생성
		pMainDlg->m_pThreadDemoMotion = AfxBeginThread(pMainDlg->DemoThreadMotion, pMainDlg, THREAD_PRIORITY_NORMAL, 0);
		Sleep(200);
	}
	else {
		pMainDlg->m_bDemo = false;
		pMainDlg->m_bDemoMotion = false;
		pMainDlg->m_eventRunDemo.SetEvent();
		pMainDlg->m_eventRunDemoMotion.SetEvent();
		m_bitUI.MoveWindow(0, 0, 10, 10);
	}
}


void DemoLineaHS2Dlg::OnBnClickedBtnUiOn()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	// UI
	m_bitUI.MoveWindow(0, 0, m_widthDisplay, m_heightDisplay);
	//hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_UI));
	m_bitUI.SetBitmap(hbit);

	if (m_nMode == 0) {
		m_bitSpeedOn.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitResponsivityOff.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitSpeedOn.SetBitmap(hbitSpeedOn);
		m_bitResponsivityOff.SetBitmap(hbitResponsivityOff);
	}
	else {
		m_bitSpeedOff.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
		m_bitResponsivityOn.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);		
		m_bitSpeedOff.SetBitmap(hbitSpeedOff);
		m_bitResponsivityOn.SetBitmap(hbitResponsivityOn);
	}
	
	//m_Buffer1->Save("고속 이미지.tif", "-format tiff", 0, 0);
	//m_Buffer2->Save("고감도 이미지.tif", "-format tiff", 0, 0);
}

void DemoLineaHS2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


void DemoLineaHS2Dlg::OnClickedBitSpeedOff()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_nMode = 0;

	// UI
	m_bitUI.MoveWindow(0, 0, m_widthDisplay, m_heightDisplay);
	//hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_UI));
	m_bitUI.SetBitmap(hbit);


	m_bitSpeedOn.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
	m_bitResponsivityOff.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);
	m_bitSpeedOn.SetBitmap(hbitSpeedOn);
	m_bitResponsivityOff.SetBitmap(hbitResponsivityOff);
}


void DemoLineaHS2Dlg::OnClickedBitResponsivityOff()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_nMode = 1;

	// UI
	m_bitUI.MoveWindow(0, 0, m_widthDisplay, m_heightDisplay);
	//hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_UI));
	m_bitUI.SetBitmap(hbit);

	m_bitSpeedOff.MoveWindow(m_leftSpeedBtn, m_topBtns, m_widthBtn, m_heightBtn);
	m_bitResponsivityOn.MoveWindow(m_leftResponsivityBtn, m_topBtns, m_widthBtn, m_heightBtn);
	m_bitSpeedOff.SetBitmap(hbitSpeedOff);
	m_bitResponsivityOn.SetBitmap(hbitResponsivityOn);
}
