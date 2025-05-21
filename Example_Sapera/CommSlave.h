#pragma once
#include "pch.h"
#include <afxsock.h>            // MFC socket extensions
#include "DataPacketDefine.h"

class CExampleSaperaDlg;

class CommSlave
{
public:
	CommSlave(CExampleSaperaDlg* pDlg);
	~CommSlave(void);
	
	
	CExampleSaperaDlg* m_pMainDlg;
	SOCKET		m_sock;
	CString		m_strServerIP;
	int			m_nPort;
	BOOL		m_bRun;
	BYTE		m_SendBuf[1024];
	
	
	BOOL Start(LPCTSTR szIP, int nPort);
	void Run(void);
	
	BOOL ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_Snap(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabStart(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabStop(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabCnt(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	void Stop(void);
};
