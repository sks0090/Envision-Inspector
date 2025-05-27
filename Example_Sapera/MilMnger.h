#pragma once
#define MIL

#ifdef MIL
#include "Mil.h"

#define		GRAB_FRAME_NUM		6

class MilMnger
{
public:
	MilMnger(void);
	~MilMnger(void);

public:
	///////////////////////////////////////// MIL ���� /////////////////////////////////////////
	MIL_ID MilApplication;
	MIL_ID MilSystem;
	MIL_ID MilDigitizer;
	MIL_ID MilBufferDisplay;
	MIL_ID MilDisplay;

	//MIL_ID MilBufferGrab[GRAB_FRAME_NUM];
	MIL_ID* MilBufferGrab;

public:
	/////////////////////////////////////// �Ϲ� ���� /////////////////////////////////////////
	int		m_nSizeX;					// ���� width
	int		m_nSizeY;					// ���� height
	int		m_nBitDepth;

public:
	///////////////////////////////////////// Methods /////////////////////////////////////////
	int GetSystemCount();
	char* GetSystemName(int index);
	bool Init(CString boardName, int sysIndex, int digIndex, int nBufferCnt, CString dcfPath, int bufferCnt, void* pXferCallback, void* pXferContext);
	void Free(int nBufferCnt);

	bool Snap(int nCnt = 1);
	bool Grab();

public:
	//int GetImgSizeX() { return  m_nSizeX; }
	//int GetImgSizeY() { return  m_nSizeY; }
	//int GetImgBitDepth() { return m_nBitDepth; }
};

#endif