#pragma once
#include "pch.h"
#include <afxsock.h>            // MFC socket extensions
#include "DataPacketDefine.h"

class CClient
{
public:
	CClient(SOCKET sock, HWND hWnd);
	~CClient(void);

	virtual int Run();

	SOCKET GetSocket() { return m_sock; }

protected:
	virtual BOOL ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen, HWND hWnd);


	SOCKET			m_sock;
	HWND			m_hWnd;
	SOCKADDR_IN		m_addr;

	char			m_SendBuf[1024];
	CString			m_strIP;
public:
	void SetAddr(SOCKADDR_IN addr);
	void Close(void);
};
