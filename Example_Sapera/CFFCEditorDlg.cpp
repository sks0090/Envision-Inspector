// CFFCEditorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "CFFCEditorDlg.h"

#include "Example_SaperaDlg.h"		// 메인 다이얼로그


// CFFCEditorDlg 대화 상자

IMPLEMENT_DYNAMIC(CFFCEditorDlg, CDialogEx)

CFFCEditorDlg::CFFCEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FFC_EDITOR, pParent)
	, m_bChart(false)
{

}

CFFCEditorDlg::~CFFCEditorDlg()
{
}

void CFFCEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART, m_ChartViewer);
	DDX_Control(pDX, IDC_CB_FILE_SELECTOR, m_cbFileSelector);
	DDX_Control(pDX, IDC_CB_ROW_INDEX, m_cbRowIndex);
	DDX_Control(pDX, IDC_CB_PROCESS_ALGORITHM, m_cbProcessAlgorithm);
	DDX_Control(pDX, IDC_CHK_PROCESS, m_chkEnableProcess);
}


BEGIN_MESSAGE_MAP(CFFCEditorDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_LOAD_FILE, &CFFCEditorDlg::OnBnClickedBtnLoadFile)
	ON_BN_CLICKED(IDC_BTN_SAVE_FILE, &CFFCEditorDlg::OnBnClickedBtnSaveFile)
	ON_CBN_SELCHANGE(IDC_CB_FILE_SELECTOR, &CFFCEditorDlg::OnCbnSelchangeCbFileSelector)
	ON_CBN_SELCHANGE(IDC_CB_PROCESS_ALGORITHM, &CFFCEditorDlg::OnCbnSelchangeCbProcessAlgorithm)
	ON_BN_CLICKED(IDC_CHK_PROCESS, &CFFCEditorDlg::OnBnClickedChkProcess)
END_MESSAGE_MAP()


// CFFCEditorDlg 메시지 처리기


BOOL CFFCEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();
	
	//Combo Box 초기화
	m_cbFileSelector.AddString("FPN");
	m_cbFileSelector.AddString("PRNU");
	m_cbFileSelector.AddString("LUT");
	m_cbFileSelector.SetCurSel(0);
	m_cbFileSelector.GetWindowText(m_strFileSelector);

	CString strTemp;
	for (int i = 0; i < 4; i++) {
		strTemp.Format("#%d", i + 1);
		m_cbRowIndex.AddString(strTemp);
	}
	m_cbRowIndex.SetCurSel(0);

	m_cbProcessAlgorithm.AddString("Lowpass Filter-3");
	m_cbProcessAlgorithm.AddString("Lowpass Filter-5");
	m_cbProcessAlgorithm.AddString("Lowpass Filter-9");
	m_cbProcessAlgorithm.SetCurSel(0);
	m_cbProcessAlgorithm.GetWindowTextA(m_strProcessAlgorithm);

	// Chart 초기화
	m_dataLength = pMainDlg->m_nSizeX > 0 ?				pMainDlg->m_nSizeX : 16384;
	m_xData = new double[m_dataLength];					memset(m_xData, 10, m_dataLength * sizeof(double));
	m_yData = new double[m_dataLength];					memset(m_yData, 10, m_dataLength * sizeof(double));
	m_yDataProcessed = new double[m_dataLength];		memset(m_yDataProcessed, 10, m_dataLength * sizeof(double));
	

	//m_cMyChart = new MyChart();
	//m_cMyChart->Init(&m_ChartViewer, m_xData, m_yData, m_dataLength, m_nChartSizeX, m_nChartSizeY);	
	//
	//m_bChart = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

bool CFFCEditorDlg::loadFile()
{
	int row, col;

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	// Coefficient 파일 선택
	TCHAR szFilter[] = _T("All Files(*.*) | *.*;|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal())
	{
		return false;
	}

	m_strFile = dlg.GetPathName();

	CFile fp;
	fp.Open(m_strFile, CFile::modeRead);
	m_length = fp.GetLength();

	m_fileDataSrc = new unsigned char[m_length];
	

	fp.Read(m_fileDataSrc, m_length);

	return true;
}

void CFFCEditorDlg::readFile()
{
	int rowLength = 4;
	int dataLength = 16384;
	int coefficientOffset = 4;
	int coefficientLenght = 2;
	int row, col;

	float* ffcCoefficient;

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	ffcCoefficient = new float[dataLength * rowLength];

	int index = 0;
	for (row = 0; row < rowLength; row++) {
		for (col = 0; col < dataLength; col++) {
			ffcCoefficient[row * rowLength + col] = (256 * m_fileDataSrc[coefficientOffset + 2 * index + 1]) + m_fileDataSrc[coefficientOffset + 2 * index];
			if (!strcmp(m_strFileSelector, "PRNU"))
			{
				ffcCoefficient[row * rowLength + col] = ffcCoefficient[row * rowLength + col] / 8192.0;
			}

			if (row == 0) {
				m_xData[col] = col;
				m_yData[col] = ffcCoefficient[row * rowLength + col];
			}

			index = index + 1;
		}
	}

	delete[] ffcCoefficient;
}

void CFFCEditorDlg::writeFile()
{
	int rowLength = 4;
	int dataLength = 16384;
	int coefficientOffset = 4;
	int coefficientLenght = 2;
	int row, col;

	int* ffcCoefficient;

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	m_fileDataDst = new unsigned char[m_length];
	ffcCoefficient = new int[dataLength * rowLength];

	int index = 0;
	m_fileDataDst[0] = 2;
	m_fileDataDst[1] = 2;
	m_fileDataDst[2] = 2;
	m_fileDataDst[3] = 2;
	for (row = 0; row < rowLength; row++) {
		for (col = 0; col < dataLength; col++) {
			ffcCoefficient[row * rowLength + col] = (256 * m_fileDataSrc[coefficientOffset + 2 * index + 1]) + m_fileDataSrc[coefficientOffset + 2 * index];
			
			if (row == 0) {
				if (!strcmp(m_strFileSelector, "PRNU"))
				{
					ffcCoefficient[row * rowLength + col] = (int)(m_yDataProcessed[col] * 8192);
				}
				else {
					ffcCoefficient[row * rowLength + col] = (int)(m_yDataProcessed[col]);
				}
			}

			m_fileDataDst[coefficientOffset + 2 * index] = (int)(ffcCoefficient[row * rowLength + col] & 255);
			m_fileDataDst[coefficientOffset + 2 * index + 1] = (int)(ffcCoefficient[row * rowLength + col] / 256);

			index = index + 1;
		}
	}

	delete[] ffcCoefficient;
}

bool CFFCEditorDlg::saveFile()
{
	CString strFile;
	int row, col;

	CExampleSaperaDlg* pMainDlg = (CExampleSaperaDlg*)GetParent();

	CFile fp;

	strFile.Format("%s_processed", m_strFile);
	fp.Open(strFile, CFile::modeCreate | CFile::modeReadWrite);

	fp.Write(m_fileDataDst, m_length);

	fp.Close();

	return true;
}

void CFFCEditorDlg::clearChart() {

}


void CFFCEditorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_nChartSizeX = cx - 20;
	m_nChartSizeY = cy - 10;
	if (m_bChart) {
		m_cMyChart->onSizeChart(nType, m_nChartSizeX, m_nChartSizeY);
	}
}


void CFFCEditorDlg::OnBnClickedBtnLoadFile()
{
	loadFile();

	readFile();

	if (!m_bChart) {
		m_cMyChart = new MyChart();
		if (!strcmp(m_strFileSelector, "FPN")) {
			m_cMyChart->setTitle("FPN Coefficient");
		}
		else {
			m_cMyChart->setTitle("PRNU Coefficient");
		}

		m_cMyChart->setAxisName("Pixel #", "coefficient");

		m_cMyChart->Init(&m_ChartViewer, m_xData, m_yData, m_dataLength, m_nChartSizeX, m_nChartSizeY);

		m_bChart = true;
	}
	else {
		if (!strcmp(m_strFileSelector, "FPN")) {
			m_cMyChart->setTitle("FPN Coefficient");
		}
		else {
			m_cMyChart->setTitle("PRNU Coefficient");
		}

		m_cMyChart->updateData(m_xData, m_yData);
	}

	//m_cMyChart->drawChart();
	
}

void CFFCEditorDlg::OnBnClickedBtnSaveFile()
{
	writeFile();

	saveFile();

}

void CFFCEditorDlg::OnCbnSelchangeCbFileSelector()
{
	m_cbFileSelector.GetWindowText(m_strFileSelector);
}


void CFFCEditorDlg::OnCbnSelchangeCbProcessAlgorithm()
{
	m_cbProcessAlgorithm.GetWindowTextA(m_strProcessAlgorithm);
}


void CFFCEditorDlg::OnBnClickedChkProcess()
{
	UpdateData(TRUE);

	if (m_chkEnableProcess.GetCheck())
	{
		if (m_strProcessAlgorithm == "Lowpass Filter-3")
		{
			calLowpassFilter(3);
		}
		else if (m_strProcessAlgorithm == "Lowpass Filter-5")
		{
			calLowpassFilter(5);
		}
		else if (m_strProcessAlgorithm == "Lowpass Filter-9")
		{
			calLowpassFilter(9);
		}
		
		m_cMyChart->Init(&m_ChartViewer, m_xData, m_yDataProcessed, m_dataLength, m_nChartSizeX, m_nChartSizeY);

		m_chkEnableProcess.SetWindowTextA(_T("Enable Process"));
	}
	else
	{
		m_cMyChart->Init(&m_ChartViewer, m_xData, m_yData, m_dataLength, m_nChartSizeX, m_nChartSizeY);

		m_chkEnableProcess.SetWindowTextA(_T("Disable Process"));
	}
}

void CFFCEditorDlg::calLowpassFilter(int filterSize)
{
	int rowLength = 4;
	int dataLength = 16384;
	int coefficientOffset = 4;
	int coefficientLenght = 2;
	int row, col;
	int i;

	float sum = 0;

	for (col = 0; col < dataLength; col++) {
		
		if (col<filterSize / 2 || col > dataLength - 1 - filterSize / 2)
		{
			m_yDataProcessed[col] = m_yData[col];
		}
		else {
			sum = 0;
			for (i = 0; i < filterSize; i++)
			{
				sum += m_yData[col - filterSize / 2 + i];
			}
			m_yDataProcessed[col] = sum/filterSize;
		}
	}
}
