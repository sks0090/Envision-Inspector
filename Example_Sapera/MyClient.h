#pragma once
#include "pch.h"
#include "CClient.h"
#include "DataPacketDefine.h"

class CServerDlg;

class MyClient : public CClient
{
public:
	MyClient(SOCKET sock, HWND hWnd);
	~MyClient(void);

	virtual int Run();

	void SendSnap(void);
	void SendGrabStart(void);
	void SendGrabStop(void);
	void SendGrabCnt(void);

	void SetParent(CServerDlg* pDlg);

protected:
	virtual BOOL ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen, HWND hWnd);

	BOOL Process_Snap(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabStart(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabStop(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);
	BOOL Process_GrabCnt(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen);


	CServerDlg* m_pDlg;


};
