// CDiagnosticDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CDiagnosticDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그

// CDiagnosticDlg 대화 상자

IMPLEMENT_DYNAMIC(CDiagnosticDlg, CDialogEx)

CDiagnosticDlg::CDiagnosticDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIAGNOSTIC, pParent)
{

}

CDiagnosticDlg::~CDiagnosticDlg()
{
}

void CDiagnosticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DIAGNOSTIC, m_listFGinfo);
	DDX_Control(pDX, IDC_LIST_LANES_STAT, m_listLanesStat);
}


BEGIN_MESSAGE_MAP(CDiagnosticDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CDiagnosticDlg::OnBnClickedBtnRefresh)
END_MESSAGE_MAP()


// CDiagnostic 메시지 처리기
int CDiagnosticDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CDiagnosticDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CDiagnosticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;

	m_listFGinfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listFGinfo.InsertColumn(0, _T("Name"), LVCFMT_CENTER, 100);
	m_listFGinfo.InsertColumn(1, _T("Value"), LVCFMT_CENTER, 200);

	m_listLanesStat.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listLanesStat.InsertColumn(0, _T("Index"), LVCFMT_CENTER, 100);
	m_listLanesStat.InsertColumn(1, _T("CRC Error"), LVCFMT_CENTER, 200);
	m_listLanesStat.InsertColumn(2, _T("64b/66b Error"), LVCFMT_CENTER, 200);

	// Frame Grabber Diagnostic 정보 가져오기
	getDiagnosticInfo();

	getLanesStatistic();

	m_listFGinfo.InsertItem(0, "PCie");
	m_listFGinfo.InsertItem(1, "Temperature");
	m_listFGinfo.InsertItem(2, "Serial Number");
	m_listFGinfo.InsertItem(3, "Firmware version");

	for (int laneIndex = 0; laneIndex < nbCLHSLLanes; laneIndex++)
	{
		str.Format(_T("%d"), laneIndex);
		m_listLanesStat.InsertItem(laneIndex, str);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CORSTATUS CDiagnosticDlg::getDiagnosticInfo()
{
	CExampleSaperaDlg* m_pMainDlg = (CExampleSaperaDlg*)GetParent();
	
	CORCMD_DEVICE_PARAMETER parameters = { 0 };

	status = CORSTATUS_OK;

	 nbGen = 0;
	 nbPCIeLanes = 0;

	CString str;

	CorManGetServerByName(m_pMainDlg->m_strBoardName[0], &hServer);

	parameters.deviceIndex = 0;     // Not Used.
	parameters.prmSize = 0;         // Not Used.

	// PCIe Info
	parameters.prmIndex = CORHW_USER_DEVICE_PRM_GET_PCIE_BUS_BIT_TRANSFER_RATE;
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ, &parameters, sizeof(parameters), &nbGen, sizeof(nbGen));
	parameters.prmIndex = CORHW_USER_DEVICE_PRM_GET_PCIE_BUS_NB_LANES;
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ, &parameters, sizeof(parameters), &nbPCIeLanes, sizeof(nbPCIeLanes));

	// Temperature Info
	parameters.prmIndex = CORHW_USER_DEVICE_PRM_GET_TEMPERATURE;
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ, &parameters, sizeof(parameters), &nbTemperature, sizeof(nbTemperature));

	// Serial Number
	parameters.prmIndex = CORHW_USER_DEVICE_PRM_GET_USER_DEVICE_INFO_VALUE;
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ, &parameters, sizeof(parameters), &m_deviceInfo, sizeof(m_deviceInfo));
	//CorManReadDeviceInfoValue(hServer, )

	str.Format(_T("Gen %d x%d"), nbGen, nbPCIeLanes);
	m_listFGinfo.SetItem(0, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
	str.Format(_T("%.2f 'C"), (float)nbTemperature.value/1000.0);
	m_listFGinfo.SetItem(1, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

	UpdateData(FALSE);

	return status;
}

CORSTATUS CDiagnosticDlg::getLanesStatistic()
{
	CORCMD_DEVICE_PARAMETER parametersDevice = { 0 };
	CORCMD_DEVICE_PARAMETER_GET_LANES_STATS parametersLanesStats = { 0 };
	
	nbCLHSLLanes = 0;
	countCRCError = 0;
	countEncodingError = 0;

	CString str;
	
	status = CORSTATUS_OK;

	// Get Lanes 수
	parametersDevice.deviceIndex = 0;     // Not Used.
	parametersDevice.prmIndex = CORHW_USER_DEVICE_PRM_GET_NB_LANES;
	parametersDevice.prmSize = 0;         // Not Used.
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ, &parametersDevice, sizeof(parametersDevice), &nbCLHSLLanes, sizeof(nbCLHSLLanes));

	// Reset Lanes Statistics
	parametersDevice.deviceIndex = 0;     // Not Used.
	parametersDevice.prmIndex = CORHW_USER_DEVICE_PRM_RESET_LANES_STATS;
	parametersDevice.prmSize = 0;         // Not Used.
	status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_WRITE, &parametersDevice, sizeof(parametersDevice), NULL, 0);

	// Get Lanes Statistics
	parametersLanesStats.prm.prmIndex = CORHW_USER_DEVICE_PRM_GET_LANES_STATS;
	for (int laneIndex = 0; laneIndex < nbCLHSLLanes; laneIndex++)
	{
		parametersLanesStats.prm.deviceIndex = laneIndex; // Lane number to get stats from

		// CRC Error Check
		countCRCError = 0;
		parametersLanesStats.prm.prmSize = sizeof(countCRCError);
		parametersLanesStats.data.statIndex = CORHW_DEVICE_PARAMETER_LANES_CRC_ERROR_COUNT;
		status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ_EX, &parametersLanesStats, sizeof(parametersLanesStats), &countCRCError, sizeof(countCRCError));

		// 64b/66b Error Check
		countEncodingError = 0;
		parametersLanesStats.prm.prmSize = sizeof(countEncodingError);
		parametersLanesStats.data.statIndex = CORHW_DEVICE_PARAMETER_LANES_ENCODING_ERROR_COUNT;
		status = CorManControl(hServer, CORCMD_USER_DEVICE_PARAMETER_READ_EX, &parametersLanesStats, sizeof(parametersLanesStats), &countEncodingError, sizeof(countEncodingError));

		// list Control에 추가
		
		str.Format(_T("%d"), countCRCError);
		m_listLanesStat.SetItem(laneIndex, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), countEncodingError);
		m_listLanesStat.SetItem(laneIndex, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
	}

	UpdateData(FALSE);

	return status;
}

void CDiagnosticDlg::OnBnClickedBtnRefresh()
{
	getDiagnosticInfo();

	getLanesStatistic();

	UpdateData(FALSE);
}
