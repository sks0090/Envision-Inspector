#include "pch.h"

#include "MilMnger.h"
#ifdef MIL
MilMnger::MilMnger() {
	MilApplication = NULL;
	MilSystem = NULL;
	MilDigitizer = NULL;
	MilBufferDisplay = NULL;
	MilDisplay = NULL;

	
	MilBufferGrab = M_NULL;
	
}

MilMnger::~MilMnger() {
//	Free();
}

int MilMnger::GetSystemCount()
{
	// Alloc MILApplication
	MIL_ID ret = MappAlloc(M_DEFAULT, &MilApplication);
	if (ret == M_NULL)
	{
		AfxMessageBox(_T("MappAlloc return NULL"));
		return false;
	}

	int systemNum;
	systemNum = MappInquire(MilApplication, M_INSTALLED_SYSTEM_DEVICE_COUNT + 0, M_NULL);
	
	return systemNum;
}

char* MilMnger::GetSystemName(int index)
{
	char systemName[100];

	MappInquire(MilApplication, M_INSTALLED_SYSTEM_DESCRIPTOR + index, systemName);

	return systemName;
}

bool MilMnger::Init(CString boardName, int sysIndex, int digIndex, int nBufferCnt, CString dcfPath, int bufferCnt, void* pXferCallback, void* pXferContext)
{
	MIL_ID ret;
	int digNum = 0;

	// alloc MILSystem
	ret = MsysAlloc(boardName, M_DEV0, M_DEFAULT, &MilSystem);
	if (ret == M_NULL)
	{
		AfxMessageBox(_T("MilSystem return NULL"));
		return false;
	}

	digNum = MsysInquire(MilSystem, M_DIGITIZER_NUM, M_NULL);

	// alloc digitizer
	ret = MdigAlloc(MilSystem, M_DEV0, dcfPath, M_DEFAULT, &MilDigitizer);
	if (ret == M_NULL)
	{
		AfxMessageBox(_T("MilDigitizer return NULL"));
		return false;
	}

	m_nSizeX = MdigInquire(MilDigitizer, M_SIZE_X, M_NULL);
	m_nSizeY = MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL);
	

	if (!strcmp(boardName, "M_SYSTEM_SOLIOS") || !strcmp(boardName, "M_SYSTEM_RADIENTEVCL")) {
		// Camera Link의 경우만 적용
		MIL_TEXT_CHAR temp[1000];
		MdigInquire(MilDigitizer, M_GC_CLPROTOCOL_DEVICE_ID + 0, temp);				// GenIcam Protocal ID 가져오기
		MdigControl(MilDigitizer, M_GC_CLPROTOCOL_DEVICE_ID, M_PTR_TO_DOUBLE(temp));	// GenIcam Protocal ID 가져오기
		MdigControl(MilDigitizer, M_GC_CLPROTOCOL, M_ENABLE);						// GenICam Enable
	}

	MilBufferGrab = new MIL_ID[nBufferCnt];
	for (int i = 0; i < nBufferCnt; i++)
	{
		MbufAlloc2d(MilSystem, m_nSizeX, m_nSizeY, 8 + M_UNSIGNED, M_IMAGE + M_GRAB, &MilBufferGrab[i]);
	}

	// alloc display buffer
	ret = MbufAlloc2d(MilSystem, m_nSizeX, m_nSizeY, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &MilBufferDisplay);

	// alloc display
	//MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilDisplay);

	//MdispSelectWindow(MilDisplay, MilBufferDisplay, GetDlgItem(IDC_ST_DISPLAY)->GetSafeHwnd());
	//MdispControl(MilDisplay, M_SCALE_DISPLAY, M_ENABLE);

	return true;
}

void MilMnger::Free(int nBufferCnt)
{
	if (MilBufferDisplay) { MbufFree(MilBufferDisplay); MilBufferDisplay = M_NULL; }
	if (MilDisplay) { MdispFree(MilDisplay); MilDisplay = M_NULL; }

	// alloc buffer
	for (int i = 0; i < nBufferCnt; i++)
	{
		if (MilBufferGrab[i])
		{
			MbufFree(MilBufferGrab[i]);
			MilBufferGrab[i] = M_NULL;
		}
	}

	if (MilDigitizer) { MdigFree(MilDigitizer); MilDigitizer = M_NULL; }
	if (MilSystem) { MsysFree(MilSystem); MilSystem = M_NULL; }
	if (MilApplication) { MappFree(MilApplication); MilApplication = M_NULL; }
}

bool MilMnger::Snap(int nCnt)
{
	return true;
}

bool MilMnger::Grab()
{
	return true;
}

#endif
