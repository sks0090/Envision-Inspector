#include "pch.h"

#include "SapMnger.h"
#ifdef SAPERA
SapMnger::SapMnger(void)
{
	//m_Manager = NULL;
	for (int i = 0; i < 2; i++) {
		m_Acq[i] = NULL;
		m_Buffer[i] = NULL;
		m_Xfer[i] = NULL;
	
		m_FlatField[i] = NULL;
	}

	m_Pro = NULL;
	m_BufferPro = NULL;
	m_AcqDevice = NULL;
}

SapMnger::~SapMnger(void)
{
	Free();
}

bool SapMnger::Init(CString strBoardName, int nResIdx, CString strCCFPath, int nBufferCnt, SapXferCallback pXferCallback, void* pXferContext, SapProCallback pProCallback, void* pProContext)
{
	m_Acq[0] = new SapAcquisition(SapLocation(strBoardName, nResIdx), strCCFPath, SapAcquisition::EventEndOfFrame, NULL, NULL);
	if (m_Acq[0] == NULL)
		return false;
	if (!m_Acq[0]->Create())
		return false;

	m_Acq[0]->GetParameter(CORACQ_PRM_CROP_WIDTH, &m_nSizeX);
	m_Acq[0]->GetParameter(CORACQ_PRM_CROP_HEIGHT, &m_nSizeY);
	m_Acq[0]->GetParameter(CORACQ_PRM_PIXEL_DEPTH, &m_nBitDepth);
	m_Acq[0]->GetParameter(CORACQ_PRM_OUTPUT_FORMAT, &m_OutputFormat);
	m_Acq[0]->GetParameter(CORACQ_PRM_SCAN, &m_CameraType);

	m_Buffer[0] = new SapBufferWithTrash(nBufferCnt, m_Acq[0]);
	if (!m_Buffer[0]->Create())
		return false;

	m_Buffer[0]->GetNumPages(&m_nPlanes);
	m_Buffer[0]->Clear();

	
	m_Xfer[0] = new SapAcqToBuf(m_Acq[0], m_Buffer[0], pXferCallback, pXferContext);
	if (m_Xfer[0] == NULL)
		return false;

	//m_Xfer[0]->SetConnectTimeout(1);
//	m_Xfer[0]->SetAutoConnect(FALSE);
	//BOOL isCapa = m_Xfer[0]->IsCapabilityValid(CORACQ_CAP_CLHS_BIT_TRANSFER_RATE);
	
	BOOL isConnect = m_Xfer[0]->IsConnected();
	if (!m_Xfer[0]->Create())
		return false;

	BOOL isCapa = m_Xfer[0]->IsCapabilityValid(CORACQ_CAP_CLHS_BIT_TRANSFER_RATE);
	isConnect = m_Xfer[0]->IsConnected();

	m_BufferPro = new SapBuffer(nBufferCnt, m_Acq[0]);
	if (!m_BufferPro->Create())
		return false;
	m_BufferPro->Clear();

	m_Pro = new SapMyProcessing(m_Buffer[0], m_BufferPro, pProCallback, pProContext);
	if (!m_Pro->Create())
		return false;

	m_FlatField[0] = new SapFlatField(m_Acq[0]);
	if (!m_FlatField[0]->Create())
		return false;

	return true;
}

bool SapMnger::InitDual(CString *strBoardName, int nResIdx, CString *strCCFPath, int nBufferCnt, SapXferCallback pXferCallback, void* pXferContext, void* pXferContext2, SapProCallback pProCallback, void* pProContext)
{
	int i = 0;

	for (i = 0; i < 2; i++) {
		m_Acq[i] = new SapAcquisition(SapLocation(strBoardName[i], nResIdx), strCCFPath[i], SapAcquisition::EventEndOfFrame, NULL, NULL);
		if (m_Acq[i] == NULL)
			return false;
		if (!m_Acq[i]->Create())
			return false;

		m_Acq[i]->GetParameter(CORACQ_PRM_CROP_WIDTH, &m_nSizeX);
		m_Acq[i]->GetParameter(CORACQ_PRM_CROP_HEIGHT, &m_nSizeY);
		m_Acq[i]->GetParameter(CORACQ_PRM_PIXEL_DEPTH, &m_nBitDepth);
		m_Acq[i]->GetParameter(CORACQ_PRM_OUTPUT_FORMAT, &m_OutputFormat);
		m_Acq[i]->GetParameter(CORACQ_PRM_SCAN, &m_CameraType);

		if (i == 0) {
			m_BufferWhole = new SapBufferWithTrash(nBufferCnt, m_nSizeX * 2, m_nSizeY, m_OutputFormat, SapBuffer::TypeScatterGather);
			if (!m_BufferWhole->Create()) {
				return false;
			}
		}
		m_Buffer[i] = new SapBufferRoi(m_BufferWhole, m_nSizeX * i, 0, m_nSizeX, m_nSizeY);
		if (!m_Buffer[i]->Create())
			return false;
		m_Buffer[i]->Clear();

		m_FlatField[i] = new SapFlatField(m_Acq[i]);
		if (!m_FlatField[i]->Create())
			return false;
	}

	m_Xfer[0] = new SapAcqToBuf(m_Acq[0], m_Buffer[0], pXferCallback, pXferContext);
	if (m_Xfer[0] == NULL)
		return false;
	if (!m_Xfer[0]->Create())
		return false;
	m_Xfer[1] = new SapAcqToBuf(m_Acq[1], m_Buffer[1], pXferCallback, pXferContext2);
	if (m_Xfer[1] == NULL)
		return false;
	if (!m_Xfer[1]->Create())
		return false;

	m_BufferPro = new SapBuffer(nBufferCnt, m_nSizeX * 2, m_nSizeY, m_OutputFormat, SapBuffer::TypeScatterGather);
	if (m_BufferPro == NULL)
		return false;
	if (!m_BufferPro->Create())
		return false;
	m_BufferPro->Clear();

	m_nSizeX = m_nSizeX * 2;

	m_Pro = new SapMyProcessing(m_BufferWhole, m_BufferPro, pProCallback, pProContext);
	if (!m_Pro->Create())
		return false;
	
	return true;
}

void SapMnger::SetSapPro(bool bEnable, int index)
{
	m_Xfer[index]->Init(TRUE);
	m_Xfer[index]->SetAutoEmpty(!bEnable);

	m_Pro->Init();
	m_Pro->SetAutoEmpty(bEnable);
}

void SapMnger::Free(int index)
{
	if (m_Pro != NULL) {
		m_Pro->Destroy();
		delete m_Pro;
		m_Pro = NULL;
	}

	if (m_Xfer[index] != NULL) {
		m_Xfer[index]->Destroy();
		m_Xfer[0]->RemoveAllPairs();
		delete m_Xfer[index];
		m_Xfer[index] = NULL;
	}

	if (m_FlatField[index] != NULL) {
		m_FlatField[index]->Destroy();
		delete m_FlatField[index];
		m_FlatField[index] = NULL;
	}

	if (m_BufferPro != NULL) {
		m_BufferPro->Destroy();
		delete m_BufferPro;
		m_BufferPro = NULL;
	}

	if (m_Buffer[index] != NULL) {
		m_Buffer[index]->Destroy();
		delete m_Buffer[index];
		m_Buffer[index] = NULL;
	}

	if (m_Acq[index] != NULL) {
		m_Acq[index]->Destroy();
		delete m_Acq[index];
		m_Acq[index] = NULL;
	}
}

bool SapMnger::OpenGenICam(CString strBoardName)
{
	m_AcqDevice = new SapAcqDevice(SapLocation(strBoardName, 0));
	if (m_AcqDevice == NULL)
		return false;
	if (!m_AcqDevice->Create())
		return false;
}

void SapMnger::CloseGenICam()
{
	m_AcqDevice->Destroy();
	if (m_AcqDevice) {
		delete m_AcqDevice;
		m_AcqDevice = NULL;
	}
}

bool SapMnger::Snap(int nCnt, int index)
{

	if (m_Xfer[index] == NULL || m_Buffer[index] == NULL)
		return false;

	m_Xfer[index]->Init(TRUE);
	m_Buffer[index]->ResetIndex(); // Grab Buffer Reset
	m_Xfer[index]->Snap(nCnt);

	return true;
}

bool SapMnger::Grab(int index)
{
	
		if (m_Xfer[index] == NULL || m_Buffer[index] == NULL)
			return false;
		
		if (!m_Xfer[index]->Init(TRUE))
		{
			return false;
		}

		if (!m_Xfer[index]->Grab())
		{
			return false;
		}
	

	return true;
}

void SapMnger::ExecutePro()
{
	//m_Pro->ExecuteNext();
	m_Pro->Execute();
}

bool SapMnger::Freeze(int index)
{
	
		if (m_Xfer[index] == NULL || m_Buffer[index] == NULL)
			return false;

		m_Xfer[index]->Freeze();
	

	return true;
}

bool SapMnger::Wait(int nTime, int index)
{
	
		if (m_Xfer[index] == NULL || m_Buffer[index] == NULL)
			return false;

		m_Xfer[index]->Wait(nTime);
	

	return true;
}

bool SapMnger::Abort(int index)
{
	
		if (m_Xfer[index] == NULL || m_Buffer[index] == NULL)
			return false;

		m_Xfer[index]->Abort();
	

	return true;
}

void SapMnger::SaveImg(CString path, bool bProBuf, int bufIndex, int nPlanes, int bDualFG)
{
	if (nPlanes > 1) {
		if (bProBuf)
		{
			m_BufferPro->Save(path, "-format crc", bufIndex, 0);
		}
		else {
			if (!bDualFG) {
				m_Buffer[0]->Save(path, "-format crc", bufIndex, 0);
			}
			else {
				m_BufferWhole->Save(path, "-format crc", bufIndex, 0);
			}
			
		}
	}
	else
	{
		if (bProBuf)
		{
			m_BufferPro->Save(path, "-format tiff", bufIndex, 0);
		}
		else {
			if (!bDualFG) {
				m_Buffer[0]->Save(path, "-format tiff", bufIndex, 0);
			}
			else {
				m_BufferWhole->Save(path, "-format tiff", bufIndex, 0);
			}
			
		}
	}
}

int SapMnger::GetServerCount()
{
	
	return m_Manager->GetServerCount();
}

char* SapMnger::GetServerName(int index)
{
	char str[100];
	//int cnt=100;
	//SapManVersionInfo* pVersionInfo;
	//char infoValueNameFirmware[] = "Firmware";
	//int infoValueSizeFirmware;
	//char* infoValueFirmware = NULL;

	m_Manager->GetServerName(index, str, sizeof(str));
	//if (index > 0) {
	//	m_Manager->GetServerSerialNumber(index, str);
	//	cnt = m_Manager->GetResourceCount(index, SapManager::ResourceAcqDevice);
	//	m_Manager->GetResourceName(index, SapManager::ResourceAcqDevice, 0, str);
	//	// "User Interface GIOs Reservation";  "Power Output #1 Control";  "Firmware";  "ECO Number"; "Hardware ID"; "Firmware ID";
	//	
	//	m_Manager->GetDeviceInfoValueSize(index, infoValueNameFirmware, &infoValueSizeFirmware);
	//	
	//	infoValueFirmware = new char[infoValueSizeFirmware];
	//	m_Manager->ReadDeviceInfoValue(index, infoValueNameFirmware, infoValueFirmware, infoValueSizeFirmware);
	//}

	//int cnt = m_Manager->GetResourceCount(m_strBoardName, m_Manager->ResourceAcq);
	//char name[100];
	//m_Manager->GetResourceName(m_strBoardName, m_Manager->ResourceAcq, 0, name, 100);		// CameraLink HS Mono
	//m_Manager->GetResourceName(m_strBoardName, m_Manager->ResourceAcq, 1, name, 100);		// CameraLink HS Color RGB

	return str;
}

int SapMnger::GetBufIdx(bool bProBuf, bool bDualFG)
{
	if (m_Buffer == NULL)
		return -1;

	if (bProBuf)
	{
		return m_Pro->GetIndex();
	}
	else
	{
		if (!bDualFG) {
			return m_Buffer[0]->GetIndex();
		}
		else {
			return m_Buffer[0]->GetIndex() < m_Buffer[1]->GetIndex() ? m_Buffer[0]->GetIndex() : m_Buffer[1]->GetIndex();
		}
		
	}

}

unsigned char* SapMnger::GetBufData(int index, bool bProBuf, bool bDualFG)
{		
	unsigned char* data8;

	if (bProBuf)
	{
		m_BufferPro->GetParameter(index, CORBUFFER_PRM_ADDRESS, &data8);
	}
	else {
		if (!bDualFG) {
			m_Buffer[0]->GetParameter(index, CORBUFFER_PRM_ADDRESS, &data8);
		}
		else {
			m_BufferWhole->GetParameter(index, CORBUFFER_PRM_ADDRESS, &data8);
		}	
	}

	return data8;
}

float SapMnger::GetFrameRate()
{
	SapXferFrameRateInfo* frameRateInfo = m_Xfer[0]->GetFrameRateStatistics();
	return frameRateInfo->GetLiveFrameRate();
}

// 카메라 설정
bool SapMnger::CheckFeature(char* name, char* value)
{
	char* currValue;
	bool bRet = false;

	currValue = new char[100];

	m_AcqDevice->GetFeatureValue("sensorScanDirection", currValue, 10);

	bRet = strcmp(currValue, value);

	delete[] currValue;

	return bRet;
}

#endif
