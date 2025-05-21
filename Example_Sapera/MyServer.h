#pragma once
#include "pch.h"
#include "cserver.h"

class CServerDlg;

class MyServer : public CServer
{
public:
	MyServer(void);
	~MyServer(void);

	virtual void OnNewClient(CLIENT_PARAM* pParam);

	void SendSnap(void);
	void SendGrabStart(void);
	void SendGrabStop(void);
	void SendGrabCnt(void);

	void SetParent(CServerDlg* pDlg);

	CServerDlg* m_pDlg;
};
