// CControlCameraDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CControlCameraDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// CControlCameraDlg 대화 상자

IMPLEMENT_DYNAMIC(CControlCameraDlg, CDialogEx)

CControlCameraDlg::CControlCameraDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONTROL_CAMERA, pParent)
	, m_fInternalLineRate(0)
	, m_nPrnuTarget(180)
{

}

CControlCameraDlg::~CControlCameraDlg()
{
}

void CControlCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_TRIGGER_MODE, m_chkTriggerMode);
	DDX_Control(pDX, IDC_CHK_SCAN_DIRECTION, m_chkScanDirection);
	DDX_Control(pDX, IDC_CB_TDI_MODE, m_cbTdiMode);
	DDX_Control(pDX, IDC_LIST_CAM_INFO, m_listCamInfo);
	DDX_Control(pDX, IDC_CB_ANALOG_GAIN, m_cbAnalogGain);
	DDX_Control(pDX, IDC_CB_USERSET, m_cbActiveUserSet);
	DDX_Text(pDX, IDC_EDIT_INTERNAL_LINERATE, m_fInternalLineRate);
	DDX_Control(pDX, IDC_CB_FILE_ACCESS, m_cbFileAccess);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_nPrnuTarget);
	DDX_Control(pDX, IDC_CB_BINNING_HORIZONTAL, m_cbBinningHorizontal);
	DDX_Control(pDX, IDC_CB_BINNING_VERTICAL, m_cbBinningVertical);
	DDX_Control(pDX, IDC_CB_FPN_ALGORITHM, m_cbFpnAlgorithm);
}


BEGIN_MESSAGE_MAP(CControlCameraDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_TRIGGER_MODE, &CControlCameraDlg::OnBnClickedChkTriggerMode)
	ON_BN_CLICKED(IDC_CHK_SCAN_DIRECTION, &CControlCameraDlg::OnBnClickedChkScanDirection)
	ON_CBN_SELCHANGE(IDC_CB_TDI_MODE, &CControlCameraDlg::OnCbnSelchangeCbTdiMode)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_CB_ANALOG_GAIN, &CControlCameraDlg::OnCbnSelchangeCbAnalogGain)
	ON_BN_CLICKED(IDC_BTN_CAL_FPN, &CControlCameraDlg::OnBnClickedBtnCalFpn)
	ON_BN_CLICKED(IDC_BTN_CAL_PRNU, &CControlCameraDlg::OnBnClickedBtnCalPrnu)
	ON_BN_CLICKED(IDC_BTN_CLEAR_FFC, &CControlCameraDlg::OnBnClickedBtnClearFfc)
	ON_CBN_SELCHANGE(IDC_CB_USERSET, &CControlCameraDlg::OnCbnSelchangeCbUserset)
	ON_BN_CLICKED(IDC_BTN_SAVE_USERSET, &CControlCameraDlg::OnBnClickedBtnSaveUserset)
	ON_BN_CLICKED(IDC_BTN_SET_LINERATE, &CControlCameraDlg::OnBnClickedBtnSetLinerate)
	ON_CBN_SELCHANGE(IDC_CB_FILE_ACCESS, &CControlCameraDlg::OnCbnSelchangeCbFileAccess)
	ON_BN_CLICKED(IDC_BTN_FILE_DOWNLOAD, &CControlCameraDlg::OnBnClickedBtnFileDownload)
	ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD, &CControlCameraDlg::OnBnClickedBtnFileUpload)
	ON_BN_CLICKED(IDC_BTN_SHOW_CHART, &CControlCameraDlg::OnBnClickedBtnShowChart)
	ON_CBN_SELCHANGE(IDC_CB_BINNING_HORIZONTAL, &CControlCameraDlg::OnCbnSelchangeCbBinningHorizontal)
	ON_CBN_SELCHANGE(IDC_CB_BINNING_VERTICAL, &CControlCameraDlg::OnCbnSelchangeCbBinningVertical)
	ON_CBN_SELCHANGE(IDC_CB_FPN_ALGORITHM, &CControlCameraDlg::OnCbnSelchangeCbFpnAlgorithm)
END_MESSAGE_MAP()


// CControlCameraDlg 메시지 처리기
BOOL CControlCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	CString str;

	m_bChart = false;

	// Camera Info
	m_listCamInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listCamInfo.InsertColumn(0, _T("Parameter"), LVCFMT_CENTER, 90);
	m_listCamInfo.InsertColumn(1, _T("Value"), LVCFMT_CENTER, 200);

	m_listCamInfo.InsertItem(0, "Part Number");
	m_listCamInfo.InsertItem(1, "Firmware");
	m_listCamInfo.InsertItem(2, "Serial Number");
	m_listCamInfo.InsertItem(3, "Temperature");
	m_listCamInfo.InsertItem(4, "Input Voltage");

	GetCamInfo(0);

	// Temperature 측정을 위한 TIMER
	SetTimer(1, 1000, NULL);	// 이벤트 아이디 : 1, 1000ms 마다 호출

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CControlCameraDlg::PreTranslateMessage(MSG* pMsg)
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

void CControlCameraDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		GetCamInfo(1);
		break;
	case 2:

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CControlCameraDlg::GetCamInfo(int nType)
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	CString str;
	CString strText;

	if (nType == 0) {
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("DeviceModelName", m_charModelName, sizeof(m_charModelName));

		if (strncmp(m_charModelName, "HS2", 3) == 0) {		// Linea HS2
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("deviceManufacturerPartNumber", m_charPartNumber, sizeof(m_charPartNumber));	// Part Number
			
		}
		else {		// Linea HS, Falcon4
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("deviceManufacturersPartNumber", m_charPartNumber, sizeof(m_charPartNumber));
		}
		str.Format(_T("%s"), m_charPartNumber);
		m_listCamInfo.SetItem(0, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("DeviceVersion", m_charFirmware, sizeof(m_charFirmware));
		str.Format(_T("%s"), m_charFirmware);
		m_listCamInfo.SetItem(1, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("DeviceSerialNumber", m_charSerialNumber, sizeof(m_charSerialNumber));
		str.Format(_T("%s"), m_charSerialNumber);
		m_listCamInfo.SetItem(2, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("DeviceTemperature", &m_fTemperature);
		str.Format(_T("%.1f 'C"), m_fTemperature);
		m_listCamInfo.SetItem(3, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("deviceInputVoltage", &m_fInputVoltage);
		str.Format(_T("%.1f V"), m_fInputVoltage);
		m_listCamInfo.SetItem(4, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		// Trigger Mode
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("TriggerMode", m_charTriggerMode, sizeof(m_charTriggerMode));
		m_chkTriggerMode.SetWindowText(m_charTriggerMode);
		if (m_pMainDlg->m_SapMnger.GetCameraType() == CORACQ_VAL_SCAN_LINE) {		// Line Scan
			if (!strcmp(m_charTriggerMode, "External")) {
				m_chkTriggerMode.SetCheck(BST_CHECKED);
			}
		}
		else {		// Area Scan
			if (!strcmp(m_charTriggerMode, "On")) {
				m_chkTriggerMode.SetCheck(BST_CHECKED);
			}
		}

		if (m_pMainDlg->m_SapMnger.GetCameraType() == CORACQ_VAL_SCAN_LINE) {
			// Scan Direction
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("sensorScanDirection", m_charScanDirection, sizeof(m_charScanDirection));
			m_chkScanDirection.SetWindowText(m_charScanDirection);
			if (!strcmp(m_charScanDirection, "Reverse")) {
				m_chkScanDirection.SetCheck(BST_CHECKED);
			}

			// TDI Mode
			m_cbTdiMode.AddString(_T("TDI Mono"));
			m_cbTdiMode.AddString(_T("TDI Low-Mono"));
			m_cbTdiMode.AddString(_T("TDI HDR Mono"));
			m_cbTdiMode.AddString(_T("TDI HFW Mode"));
			m_cbTdiMode.AddString(_T("Area Mode"));
			m_cbTdiMode.AddString(_T("Are Extended"));


			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("sensorTDIModeSelection", m_nameTdiMode.entryName, sizeof(m_nameTdiMode.entryName));
			TDIModeName(m_nameTdiMode.entryName);
			for (int i = 0; i < m_cbTdiMode.GetCount(); i++)
			{
				m_cbTdiMode.GetLBText(i, strText);
				if (strText == m_nameTdiMode.displayName)
				{
					m_cbTdiMode.SetCurSel(i);
					break;
				}
			}

			// Binning
			m_cbBinningHorizontal.AddString(_T("1"));
			m_cbBinningHorizontal.AddString(_T("2"));
			m_cbBinningHorizontal.AddString(_T("4"));
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("BinningHorizontal", m_nameBinningHorizontal.entryName, sizeof(m_nameBinningHorizontal.entryName));
			BinningHorizontal(m_nameBinningHorizontal.entryName);
			for (int i = 0; i < m_cbBinningHorizontal.GetCount(); i++)
			{
				m_cbBinningHorizontal.GetLBText(i, strText);
				if (strText == m_nameBinningHorizontal.displayName)
				{
					m_cbBinningHorizontal.SetCurSel(i);
					break;
				}
			}
			m_cbBinningVertical.AddString(_T("1"));
			m_cbBinningVertical.AddString(_T("2"));
			m_cbBinningVertical.AddString(_T("4"));
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("BinningVertical", m_nameBinningVertical.entryName, sizeof(m_nameBinningVertical.entryName));
			BinningVertical(m_nameBinningVertical.entryName);
			for (int i = 0; i < m_cbBinningVertical.GetCount(); i++)
			{
				m_cbBinningVertical.GetLBText(i, strText);
				if (strText == m_nameBinningVertical.displayName)
				{
					m_cbBinningVertical.SetCurSel(i);
					break;
				}
			}
			
			// Analog Gain
			m_cbAnalogGain.AddString(_T("1"));
			m_cbAnalogGain.AddString(_T("2"));
			m_cbAnalogGain.AddString(_T("4"));
			m_cbAnalogGain.AddString(_T("8"));
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("AnalogGain", m_nameAnalogGain.entryName, sizeof(m_nameAnalogGain.entryName));
			AnalogGain(m_nameAnalogGain.entryName);
			for (int i = 0; i < m_cbAnalogGain.GetCount(); i++)
			{
				m_cbAnalogGain.GetLBText(i, strText);
				if (strText == m_nameAnalogGain.displayName)
				{
					m_cbAnalogGain.SetCurSel(i);
					break;
				}
			}
		}
		else {		// Area Scan
			float fGain = 0 ;
			m_chkScanDirection.EnableWindow(FALSE);
			m_cbTdiMode.EnableWindow(FALSE);
			// Analog Gain
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("GainSelector", "AnalogAll");
			m_cbAnalogGain.AddString(_T("1.0"));
			m_cbAnalogGain.AddString(_T("1.5"));
			m_cbAnalogGain.AddString(_T("2.0"));
			m_cbAnalogGain.AddString(_T("2.5"));
			m_cbAnalogGain.AddString(_T("3.0"));
			m_cbAnalogGain.AddString(_T("3.5"));
			m_cbAnalogGain.AddString(_T("4.0"));
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("Gain", &fGain);
			str.Format("%.1f", fGain);
			for (int i = 0; i < m_cbAnalogGain.GetCount(); i++)
			{
				m_cbAnalogGain.GetLBText(i, strText);
				if (strText == str)
				{
					m_cbAnalogGain.SetCurSel(i);
					break;
				}
			}
		}

		// FPN Algorithm
		m_cbFpnAlgorithm.AddString(_T("Standard"));
		m_cbFpnAlgorithm.AddString(_T("DarkCurrent"));
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("flatfieldCorrectionAlgorithmFPN", m_charFpnAlgorithm, sizeof(m_charFpnAlgorithm));
		for (int i = 0; i < m_cbFpnAlgorithm.GetCount(); i++) {
			m_cbFpnAlgorithm.GetLBText(i, strText);
			if (strText == m_charFpnAlgorithm)
			{
				m_cbFpnAlgorithm.SetCurSel(i);
				break;
			}
		}

		// Actove UserSet
		m_cbActiveUserSet.AddString(_T("Factory"));
		m_cbActiveUserSet.AddString(_T("UserSet1"));
		m_cbActiveUserSet.AddString(_T("UserSet2"));
		m_cbActiveUserSet.AddString(_T("UserSet3"));
		m_cbActiveUserSet.AddString(_T("UserSet4"));
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("UserSetDefaultSelector", m_nameActiveUserSet.entryName, sizeof(m_nameActiveUserSet.entryName));
		//m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("UserSetDefaultSelector", m_nameActiveUserSet.entryName, sizeof(m_nameActiveUserSet.entryName));
		ActiveUserSet(m_nameActiveUserSet.entryName);
		for (int i = 0; i < m_cbActiveUserSet.GetCount(); i++)
		{
			m_cbActiveUserSet.GetLBText(i, strText);
			if (strText == m_nameActiveUserSet.displayName)
			{
				m_cbActiveUserSet.SetCurSel(i);
				break;
			}
		}

		// Internal Line Rate
		if (m_pMainDlg->m_SapMnger.GetCameraType() == CORACQ_VAL_SCAN_LINE) {		// Line Rate
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("AcquisitionLineRate", &m_fInternalLineRate);
		}
		else {	// Frame Rate
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("AcquisitionFrameRate", &m_fInternalLineRate);
		}

		// Camera File Access
		int filecount;
		char filename[100];

		m_cbFileAccess.ResetContent();
		m_cbFileAccess.Clear();
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFileCount(&filecount);
		for (int i = 0; i < filecount; i++)
		{
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFileNameByIndex(i, filename, 256);
			m_cbFileAccess.AddString(filename);
		}
		m_nFileAccessIndex = 2;
		m_cbFileAccess.SetCurSel(m_nFileAccessIndex);
		m_cbFileAccess.GetWindowText(m_strFile);
	}

	if (nType == 1) {
		if (m_pMainDlg->m_SapMnger.GetCameraType() == CORACQ_VAL_SCAN_LINE) {		// Line Rate
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("refreshTemperature", TRUE);		// TDI only
			m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("refreshVoltage", TRUE);
		}
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("DeviceTemperature", &m_fTemperature);
		str.Format(_T("%.1f"), m_fTemperature);
		m_listCamInfo.SetItem(3, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("deviceInputVoltage", &m_fInputVoltage);
		str.Format(_T("%.1f"), m_fInputVoltage);
		m_listCamInfo.SetItem(4, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
	}
}

void CControlCameraDlg::TDIModeName(char *name) {
	if (!strcmp(name, "Tdi")) {
		strcpy_s(m_nameTdiMode.entryName, "Tdi");
		m_nameTdiMode.displayName = "TDI Mono";
	}
	else if (!strcmp(name, "TdiLow")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiLow");
		m_nameTdiMode.displayName = "TDI Low-Mono";
	}
	else if (!strcmp(name, "TdiHdr")) {				// Linea HS2 HDR
		strcpy_s(m_nameTdiMode.entryName, "TdiHdr");
		m_nameTdiMode.displayName = "TDI HDR Mono";
	}
	else if (!strcmp(name, "Tdi2Array")) {				// Linea HS HDR
		strcpy_s(m_nameTdiMode.entryName, "Tdi2Array");
		m_nameTdiMode.displayName = "TDI HDR Mono";
	}
	else if (!strcmp(name, "TdiHfw")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiHfw");
		m_nameTdiMode.displayName = "TDI HFW Mode";
	}
	else if (!strcmp(name, "TdiArea")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiArea");
		m_nameTdiMode.displayName = "Area Mode";
	}
	else if (!strcmp(name, "TdiMultiArea")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiMultiArea");
		m_nameTdiMode.displayName = "Are Extended";
	}
}

void CControlCameraDlg::TDIModeName(CString name) {
	if (!strcmp(name, "TDI Mono")) {
		strcpy_s(m_nameTdiMode.entryName, "Tdi");
		m_nameTdiMode.displayName = "TDI Mono";
	}
	else if (!strcmp(name, "TDI Low-Mono")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiLow");
		m_nameTdiMode.displayName = "TDI Low-Mono";
	}
	else if (!strcmp(name, "TDI HDR Mono")) {
		if (!strcmp(m_charPartNumber, "H2-HM-16K100H-00-B")) {
			strcpy_s(m_nameTdiMode.entryName, "TdiHdr");	// Linea HS2
		}
		else 
		{
			strcpy_s(m_nameTdiMode.entryName, "Tdi2Array");	// Linea HS
		}	
		m_nameTdiMode.displayName = "TDI HDR Mono";
	}
	else if (!strcmp(name, "TDI HFW Mode")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiHfw");
		m_nameTdiMode.displayName = "TDI HFW Mode";
	}
	else if (!strcmp(name, "Area Mode")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiArea");
		m_nameTdiMode.displayName = "Area Mode";
	}
	else if (!strcmp(name, "Are Extended")) {
		strcpy_s(m_nameTdiMode.entryName, "TdiMultiArea");
		m_nameTdiMode.displayName = "Are Extended";
	}
}

void CControlCameraDlg::BinningHorizontal(char* name) {
	if (!strcmp(name, "One")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "One");
		m_nameBinningHorizontal.displayName = "1";
	}
	else if (!strcmp(name, "Two")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "Two");
		m_nameBinningHorizontal.displayName = "2";
	}
	else if (!strcmp(name, "Four")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "Four");
		m_nameBinningHorizontal.displayName = "4";
	}
	else if (!strcmp(name, "Eight")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "Eight");
		m_nameBinningHorizontal.displayName = "8";
	}
}

void CControlCameraDlg::BinningHorizontal(CString name) {
	if (!strcmp(name, "1")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "One");
		m_nameBinningHorizontal.displayName = "1";
	}
	else if (!strcmp(name, "2")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "Two");
		m_nameBinningHorizontal.displayName = "2";
	}
	else if (!strcmp(name, "4")) {
		strcpy_s(m_nameBinningHorizontal.entryName, "Four");
		m_nameBinningHorizontal.displayName = "4";
	}
}

void CControlCameraDlg::BinningVertical(char* name) {
	if (!strcmp(name, "One")) {
		strcpy_s(m_nameBinningVertical.entryName, "One");
		m_nameBinningVertical.displayName = "1";
	}
	else if (!strcmp(name, "Two")) {
		strcpy_s(m_nameBinningVertical.entryName, "Two");
		m_nameBinningVertical.displayName = "2";
	}
	else if (!strcmp(name, "Four")) {
		strcpy_s(m_nameBinningVertical.entryName, "Four");
		m_nameBinningVertical.displayName = "4";
	}
	else if (!strcmp(name, "Eight")) {
		strcpy_s(m_nameBinningVertical.entryName, "Eight");
		m_nameBinningVertical.displayName = "8";
	}
}

void CControlCameraDlg::BinningVertical(CString name) {
	if (!strcmp(name, "1")) {
		strcpy_s(m_nameBinningVertical.entryName, "One");
		m_nameBinningVertical.displayName = "1";
	}
	else if (!strcmp(name, "2")) {
		strcpy_s(m_nameBinningVertical.entryName, "Two");
		m_nameBinningVertical.displayName = "2";
	}
	else if (!strcmp(name, "4")) {
		strcpy_s(m_nameBinningVertical.entryName, "Four");
		m_nameBinningVertical.displayName = "4";
	}
}

void CControlCameraDlg::AnalogGain(char* name) {
	if (!strcmp(name, "One")) {
		strcpy_s(m_nameAnalogGain.entryName, "One");
		m_nameAnalogGain.displayName = "1";
	}
	else if (!strcmp(name, "Two")) {
		strcpy_s(m_nameAnalogGain.entryName, "Two");
		m_nameAnalogGain.displayName = "2";
	}
	else if (!strcmp(name, "Four")) {				
		strcpy_s(m_nameAnalogGain.entryName, "Four");
		m_nameAnalogGain.displayName = "4";
	}
	else if (!strcmp(name, "Eight")) {
		strcpy_s(m_nameAnalogGain.entryName, "Eight");
		m_nameAnalogGain.displayName = "8";
	}
}

void CControlCameraDlg::AnalogGain(CString name) {
	if (!strcmp(name, "1")) {
		strcpy_s(m_nameAnalogGain.entryName, "One");
		m_nameAnalogGain.displayName = "1";
	}
	else if (!strcmp(name, "2")) {
		strcpy_s(m_nameAnalogGain.entryName, "Two");
		m_nameAnalogGain.displayName = "2";
	}
	else if (!strcmp(name, "4")) {
		strcpy_s(m_nameAnalogGain.entryName, "Four");
		m_nameAnalogGain.displayName = "4";
	}
	else if (!strcmp(name, "8")) {
		strcpy_s(m_nameAnalogGain.entryName, "Eight");
		m_nameAnalogGain.displayName = "8";
	}
}


void CControlCameraDlg::ActiveUserSet(char* name) {
	if (!strcmp(name, "Factory")) {
		strcpy_s(m_nameActiveUserSet.entryName, "Factory");
		m_nameActiveUserSet.displayName = "Factory";
	}
	else if (!strcmp(name, "UserSet1")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet1");
		m_nameActiveUserSet.displayName = "UserSet1";
	}
	else if (!strcmp(name, "UserSet2")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet2");
		m_nameActiveUserSet.displayName = "UserSet2";
	}
	else if (!strcmp(name, "UserSet3")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet3");
		m_nameActiveUserSet.displayName = "UserSet3";
	}
	else if (!strcmp(name, "UserSet4")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet4");
		m_nameActiveUserSet.displayName = "UserSet4";
	}
}

void CControlCameraDlg::ActiveUserSet(CString name) {
	if (!strcmp(name, "Factory")) {
		strcpy_s(m_nameActiveUserSet.entryName, "Factory");
		m_nameActiveUserSet.displayName = "Factory";
	}
	else if (!strcmp(name, "UserSet1")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet1");
		m_nameActiveUserSet.displayName = "UserSet1";
	}
	else if (!strcmp(name, "UserSet2")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet2");
		m_nameActiveUserSet.displayName = "UserSet2";
	}
	else if (!strcmp(name, "UserSet3")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet3");
		m_nameActiveUserSet.displayName = "UserSet3";
	}
	else if (!strcmp(name, "UserSet4")) {
		strcpy_s(m_nameActiveUserSet.entryName, "UserSet4");
		m_nameActiveUserSet.displayName = "UserSet4";
	}
}

void CControlCameraDlg::OnBnClickedChkTriggerMode()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	if (m_chkTriggerMode.GetCheck())
	{
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("TriggerMode", "External");
	}
	else {
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("TriggerMode", "Internal");	
	}
	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("TriggerMode", m_charTriggerMode, sizeof(m_charTriggerMode));
	m_chkTriggerMode.SetWindowText(m_charTriggerMode);
	DisplayStatus(_T("Trigger Mode 변경 : %s[%d ms]"), m_charTriggerMode, progressTime);
}




void CControlCameraDlg::OnBnClickedChkScanDirection()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	if (m_chkScanDirection.GetCheck())
	{
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorScanDirection", "Reverse");
	}
	else {
		m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorScanDirection", "Forward");
	}
	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("sensorScanDirection", m_charScanDirection, sizeof(m_charScanDirection));
	m_chkScanDirection.SetWindowText(m_charScanDirection);
	DisplayStatus(_T("Scan Direction 변경 : %s[%d ms]"), m_charScanDirection, progressTime);
}

void CControlCameraDlg::OnCbnSelchangeCbTdiMode()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;
	char CurrTdiMode[50];

	m_cbTdiMode.GetWindowText(m_nameTdiMode.displayName);
	TDIModeName(m_nameTdiMode.displayName);

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("sensorTDIModeSelection", CurrTdiMode, sizeof(CurrTdiMode));
	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);

	m_pMainDlg->m_SapMnger.GetSapXfer()->Destroy();
	m_pMainDlg->m_SapMnger.GetSapBuffer()->Destroy();

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("sensorTDIModeSelection", m_nameTdiMode.entryName);

	if (!strcmp(CurrTdiMode, "TdiArea"))	// 현재 Arae mode
	{
		if (strcmp(m_nameTdiMode.entryName, "TdiArea")) {	// TDI mode로 변경

			m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_SCAN, CORACQ_VAL_SCAN_LINE);

			m_pMainDlg->m_nSizeY = 1000;
		}
	}
	else // 현재 TDI mode
	{
		if (!strcmp(m_nameTdiMode.entryName, "TdiArea")) {	// Area mode로 변경

			m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_SCAN, CORACQ_VAL_SCAN_AREA);

			m_pMainDlg->m_nSizeY = 128;
		}
	}

	

	m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_CROP_HEIGHT, m_pMainDlg->m_nSizeY);
	m_pMainDlg->m_SapMnger.GetSapAcquisition()->SetParameter(CORACQ_PRM_VACTIVE, m_pMainDlg->m_nSizeY);
	
	m_pMainDlg->m_SapMnger.GetSapBuffer()->SetHeight(m_pMainDlg->m_nSizeY);
	m_pMainDlg->m_SapMnger.GetSapBufferPro()->SetHeight(m_pMainDlg->m_nSizeY);

	m_pMainDlg->m_SapMnger.GetSapBuffer()->Create();
	m_pMainDlg->m_SapMnger.GetSapXfer()->Create();

	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("sensorTDIModeSelection", m_nameTdiMode.entryName, sizeof(m_nameTdiMode.entryName));
	DisplayStatus(_T("TDI Mode 변경 : %s[%d ms]"), m_nameTdiMode.displayName, progressTime);
}

void CControlCameraDlg::OnCbnSelchangeCbBinningHorizontal()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	m_cbBinningHorizontal.GetWindowText(m_nameBinningHorizontal.displayName);
	BinningHorizontal(m_nameBinningHorizontal.displayName);
	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);
	
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AcquisitionStop", TRUE);
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("BinningHorizontal", m_nameBinningHorizontal.entryName);
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AcquisitionStart", TRUE);

	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	if (m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("BinningHorizontal", m_nameBinningHorizontal.entryName, sizeof(m_nameBinningHorizontal.entryName)))
	{
		DisplayStatus(_T("Binning Horizontal 변경 : %s[%d ms]"), m_nameBinningHorizontal.displayName, progressTime);
	}
	else {
		DisplayStatus(_T("Binning Horizontal 변경 실패[%d ms]"), m_nameBinningHorizontal.displayName, progressTime);
	}
}


void CControlCameraDlg::OnCbnSelchangeCbBinningVertical()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	m_cbBinningVertical.GetWindowText(m_nameBinningVertical.displayName);
	BinningVertical(m_nameBinningVertical.displayName);
	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AcquisitionStop", TRUE);
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("BinningVertical", m_nameBinningVertical.entryName);
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AcquisitionStart", TRUE);

	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	if (m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("BinningVertical", m_nameBinningVertical.entryName, sizeof(m_nameBinningVertical.entryName)))
	{
		DisplayStatus(_T("Binning Vertical 변경 : %s[%d ms]"), m_nameBinningVertical.displayName, progressTime);
	}
	else {
		DisplayStatus(_T("Binning Vertical 변경 실패[%d ms]"), m_nameBinningVertical.displayName, progressTime);
	}
}

void CControlCameraDlg::OnCbnSelchangeCbAnalogGain()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	m_cbAnalogGain.GetWindowText(m_nameAnalogGain.displayName);
	AnalogGain(m_nameAnalogGain.displayName);
	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AnalogGain", m_nameAnalogGain.entryName);

	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	if (m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("AnalogGain", m_nameAnalogGain.entryName, sizeof(m_nameAnalogGain.entryName)))
	{
		DisplayStatus(_T("Analog Gain 변경 : %s[%d ms]"), m_nameAnalogGain.displayName, progressTime);
	}
	else {
		DisplayStatus(_T("Analog Gain 변경 실패[%d ms]"), m_nameAnalogGain.displayName, progressTime);
	}
}

void CControlCameraDlg::OnBnClickedBtnClearFfc()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCalibrationClearCoefficient", 1);
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Clear FFC Coefficient[%d ms]"), progressTime);
}

void CControlCameraDlg::OnCbnSelchangeCbFpnAlgorithm()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;
	CString tempStr;

	m_cbFpnAlgorithm.GetWindowText(tempStr);
	strcpy_s(m_charFpnAlgorithm, sizeof(m_charFpnAlgorithm), CT2A(tempStr));
	QueryPerformanceCounter(&m_pMainDlg->functionStartTime);

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCorrectionAlgorithmFPN", m_charFpnAlgorithm);

	QueryPerformanceCounter(&m_pMainDlg->functionEndTime);
	progressTime = (m_pMainDlg->functionEndTime.QuadPart - m_pMainDlg->functionStartTime.QuadPart) * 1000.f / m_pMainDlg->m_perfFrequency.QuadPart;

	if (m_pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("flatfieldCorrectionAlgorithmFPN", m_charFpnAlgorithm, sizeof(m_charFpnAlgorithm)))
	{
		DisplayStatus(_T("FPN Algorithm 변경 : %s[%d ms]"), m_charFpnAlgorithm, progressTime);
	}
	else {
		DisplayStatus(_T("Algorithm 변경 실패[%d ms]"), m_charFpnAlgorithm, progressTime);
	}
}

void CControlCameraDlg::OnBnClickedBtnCalFpn()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCalibrationFPN", 1);
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Calibrate FPN[%d ms]"), progressTime);
}


void CControlCameraDlg::OnBnClickedBtnCalPrnu()
{
	UpdateData(TRUE);

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCorrectionAlgorithm", "Target");	// Calibration Algorithm
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCalibrationTarget", m_nPrnuTarget);	//Calibration Target

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("flatfieldCalibrationPRNU", 1);
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Calibrate PRNU[%d ms]"), progressTime);

	// Save PRNU
	//pMainDlg->m_AcqDevice->SetFeatureValue("flatfieldCorrectionCurrentActiveSet", m_nameActiveUserSet.entryName);
	//pMainDlg->m_AcqDevice->SetFeatureValue("flatfieldCalibrationSave", 1);
}



void CControlCameraDlg::OnCbnSelchangeCbUserset()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_cbActiveUserSet.GetWindowText(m_nameActiveUserSet.displayName);
	ActiveUserSet(m_nameActiveUserSet.displayName);

	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("UserSetDefaultSelector", m_nameActiveUserSet.entryName);
	m_pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("UserSetSelector", m_nameActiveUserSet.entryName);
}


void CControlCameraDlg::OnBnClickedBtnSaveUserset()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("UserSetSave", 1);
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Save UserSet - %s[%d ms]"), m_nameActiveUserSet.displayName, progressTime);
}


void CControlCameraDlg::OnBnClickedBtnSetLinerate()
{
	UpdateData(TRUE);

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	int progressTime;

	QueryPerformanceCounter(&pMainDlg->functionStartTime);
	pMainDlg->m_SapMnger.GetSapAcqDevice()->SetFeatureValue("AcquisitionLineRate", m_fInternalLineRate);
	QueryPerformanceCounter(&pMainDlg->functionEndTime);

	pMainDlg->m_SapMnger.GetSapAcqDevice()->GetFeatureValue("AcquisitionLineRate", &m_fInternalLineRate);

	progressTime = (pMainDlg->functionEndTime.QuadPart - pMainDlg->functionStartTime.QuadPart) * 1000.f / pMainDlg->m_perfFrequency.QuadPart;
	DisplayStatus(_T("Set Internal LIne Rate - %.1f Hz[%d ms]"), m_fInternalLineRate, progressTime);

	UpdateData(FALSE);
}


void CControlCameraDlg::OnCbnSelchangeCbFileAccess()
{
	m_nFileAccessIndex = m_cbFileAccess.GetCurSel();
	m_cbFileAccess.GetWindowText(m_strFile);
}


void CControlCameraDlg::OnBnClickedBtnFileDownload()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CString str;
	\
		if (pMainDlg->m_SapMnger.GetSapAcqDevice()->ReadFile(m_nFileAccessIndex, m_strFile))
		{
			DisplayStatus(_T("Download File Complete : %s"), m_strFile);
		}
		else
		{
			DisplayStatus(_T("Download File Fail : %s"), m_strFile);
		}
}


void CControlCameraDlg::OnBnClickedBtnFileUpload()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CString strFile;
	// CCF 선택
	TCHAR szFilter[] = _T("All Files(*.*) | *.*;|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	strFile = dlg.GetPathName();

	if (pMainDlg->m_SapMnger.GetSapAcqDevice()->WriteFile(strFile, m_nFileAccessIndex))
	{
		DisplayStatus(_T("Upload File Complete : %s"), strFile);
	}
	else
	{
		DisplayStatus(_T("Upload File Fail : %s"), strFile);
	}
}


void CControlCameraDlg::OnBnClickedBtnShowChart()
{
	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CString strFile;
	int row, col;
	int rowLength = 4;
	int coefficientOffset = 4;
	int coefficientLenght = 2;


	// Coefficient 파일 선택
	TCHAR szFilter[] = _T("All Files(*.*) | *.*;|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	strFile = dlg.GetPathName();

	CFile fp;
	fp.Open(strFile, CFile::modeRead);
	ULONGLONG length = fp.GetLength();

	unsigned char* fileData;
	int* realData;
	fileData = new unsigned char[length];
	realData = new int[pMainDlg->m_nSizeX * rowLength];

	m_xData = new double[pMainDlg->m_nSizeX];
	m_yData = new double[pMainDlg->m_nSizeX];

	fp.Read(fileData, length);

	int index = 0;
	for (row = 0; row < rowLength; row++) {
		for (col = 0; col < pMainDlg->m_nSizeX; col++) {
			realData[row * rowLength + col] = (256 * fileData[coefficientOffset + 2 * index + 1]) + fileData[coefficientOffset + 2 * index];

			if (row == 0) {
				m_xData[col] = col;
				m_yData[col] = realData[row * rowLength + col];
			}
			
			index = index + 1;
		}
	}

	// Chart Dlg Open
	pFfcChartDlg = new CChartDlg();
	pFfcChartDlg->Create(IDD_DIALOG_CHART, this);
	pFfcChartDlg->ShowWindow(SW_SHOW);
}



