#pragma once
#include "pch.h"
#include <afxsock.h>            // MFC socket extensions
#include "CClient.h"

class CServer;

typedef struct Client_PARAM
{
	SOCKET sock;
	SOCKADDR_IN addr;
	HWND hParentWnd;
	CServer* pServer;

}
CLIENT_PARAM, * PTHREAD_CLIENT_PARAM;

class CServer
{
public:
	CServer(void);
	~CServer(void);

public:
	BOOL		Start(UINT nPort, HWND hWnd);						///< Server Start �Ѵ�.
	void		Stop();											///< Server Stop

	BOOL		IsRunning() { return m_bRunning; }			///< Server �� �۵����ΰ�
	void		SetWnd(HWND hWnd) { m_hWnd = hWnd; }			///< Parent Window Handle ����
	void		SetPort(UINT nPort) { m_nPort = nPort; }			///< Server Port ����

	void		RunServer();

	virtual void OnNewClient(Client_PARAM* pParam);
	void RemoveClientFromList(SOCKET sock);

	int			GetClientCnt() { return (int)m_listClient.GetCount(); }


protected:

	void		Release();

	BOOL		m_bRunning;										///< ���� �������ΰ��� ���� Flag
	UINT		m_nPort;											///< ���� Port

	SOCKET		m_sockServer;										///< Listen socket
	HWND		m_hWnd;											///< Parent window Handle

	CList<CClient*, CClient*> m_listClient;			///< ���ӵǾ� �ִ� CNasClient ����Ʈ
};
