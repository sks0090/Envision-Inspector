#pragma once
#define SAPERA

#ifdef SAPERA
#include "SapClassBasic.h"
#include "SapMyProcessing.h"

class SapMnger
{
public:
	SapMnger(void);
	~SapMnger(void);

public:
	///////////////////////////////////////// Sapera 변수 /////////////////////////////////////////
	SapManager* m_Manager;						// Manager
	SapAcquisition *m_Acq[2];					// Frame grabber
	SapBuffer *m_Buffer[2];						// Buffer
	SapBuffer* m_BufferWhole;					
	SapTransfer* m_Xfer[2];						// Transfer	
	SapAcqDevice* m_AcqDevice;					// Camera

	SapMyProcessing* m_Pro;						// Processing
	SapBuffer* m_BufferPro;						// Processing Buffer

	SapFlatField* m_FlatField[2];
	SapFlatFieldDefects* m_FlatFieldDefects[2];

	SapData m_SapData;

	///////////////////////////////////////// 일반 변수 /////////////////////////////////////////
	int		m_nSizeX;					// 버퍼 width
	int		m_nSizeY;					// 버퍼 height
	int		m_nBitDepth;
	int		m_nPlanes;					// plane 수
	UINT32	m_OutputFormat;				// CORBUFFER_VAL_FORMAT_MONO8, CORBUFFER_VAL_FORMAT_MONO16, CORBUFFER_VAL_FORMAT_RGBP8
	UINT32 m_CameraType;				// CORACQ_VAL_SCAN_AREA, CORACQ_VAL_SCAN_LINE

public:
	bool Init(CString strBoardName, int nResIdx, CString strCCFPath, int nBufferCnt,
		SapXferCallback pXferCallback = NULL, void* pXferContext = NULL, SapProCallback pProCallback = NULL, void* pProContext = NULL);
	bool InitDual(CString *strBoardName, int nResIdx, CString *strCCFPath, int nBufferCnt,
		SapXferCallback pXferCallback = NULL, void* pXferContext = NULL, void* pXferContext2 = NULL, SapProCallback pProCallback = NULL, void* pProContext = NULL);
	void SetSapPro(bool bEnable, int index);
	void Free(int index=0);

	bool OpenGenICam(CString strBoardName);
	void CloseGenICam();

	bool Snap(int nCnt = 1, int index=0);
	bool Grab(int index=0);
	void ExecutePro();
	bool Freeze(int index);
	bool Wait(int nTime, int index = 0);
	bool Abort(int index = 0);
	void SaveImg(CString path, bool bProBuf, int bufIndex, int nPlanes, int bDualFG);

public:
	int GetImgSizeX() { return  m_nSizeX; }
	int GetImgSizeY() { return  m_nSizeY; }
	int GetImgBitDepth() { return m_nBitDepth; }
	int GetBufPlanes() { return m_nPlanes; }
	UINT32 GetOutputFormat() { return m_OutputFormat; }
	UINT32 GetCameraType() { return m_CameraType; }

	SapAcqDevice* GetSapAcqDevice() { return m_AcqDevice; }
	SapAcquisition* GetSapAcquisition(int index=0) { return m_Acq[index]; }
	SapBuffer* GetSapBuffer(int index = 0) { return m_Buffer[index]; }
	SapBuffer* GetSapBufferPro(int index = 0) { return m_BufferPro; }
	SapTransfer* GetSapXfer(int index = 0) { return m_Xfer[index]; }
	SapMyProcessing* GetSapPro(int index = 0) { return m_Pro; }
	SapFlatField* GetSapFlatField(int index = 0) { return m_FlatField[index]; }
	SapFlatFieldDefects* GetSapFlatFieldDefects(int index = 0) { return m_FlatFieldDefects[index]; }
	SapData GetSapData() { return m_SapData; }
	

public:
	int GetServerCount();
	char* GetServerName(int index);

	int GetBufIdx(bool bProBuf, bool bDualFG);
	unsigned char* GetBufData(int index, bool bProBuf, bool bDualFG);
	float GetFrameRate();

	// Camera Feature 관련
	bool CheckFeature(char* name, char* value);
};

#endif
