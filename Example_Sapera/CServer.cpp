#include "pch.h"
#include "CServer.h"
#include "Example_SaperaDlg.h"

CServer::CServer(void)
{
	m_bRunning = FALSE;
	m_nPort = 0;

	m_sockServer = INVALID_SOCKET;
	m_hWnd = NULL;
}

CServer::~CServer(void)
{
	Stop();
}

void CServer::Release()
{
	if (m_sockServer != INVALID_SOCKET)
	{
		closesocket(m_sockServer);
		m_sockServer = INVALID_SOCKET;
	}
}

UINT ThreadStart(LPVOID param)
{
	CServer* pServer = (CServer*)param;
	if (pServer == NULL)
		return -1;

	pServer->RunServer();

	return 1;
}

UINT ThreadClientProcess(LPVOID param)
{
	CLIENT_PARAM* pParam = (CLIENT_PARAM*)param;
	pParam->pServer->OnNewClient(pParam);


	return 1;
}

void CServer::OnNewClient(CLIENT_PARAM* pParam)
{
	SOCKET sockClient = pParam->sock;
	HWND hWnd = pParam->hParentWnd;
	SOCKADDR_IN addr = pParam->addr;

	delete pParam;

	CClient Client(sockClient, hWnd);
	Client.SetAddr(addr);
	m_listClient.AddTail(&Client);

	Client.Run();

	RemoveClientFromList(sockClient);

	if (sockClient != INVALID_SOCKET)
		closesocket(sockClient);
}

void CServer::RemoveClientFromList(SOCKET socket)
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos)
	{
		CClient* pClient = m_listClient.GetAt(pos);
		if (pClient == NULL)
		{
			m_listClient.GetNext(pos);
			continue;
		}

		if (pClient->GetSocket() == socket)
		{
			m_listClient.RemoveAt(pos);
			return;
		}
	}
}


void CServer::RunServer()
{
	m_bRunning = TRUE;

	while (1)
	{
		SOCKADDR_IN addr;
		int nLen = sizeof(addr);
		SOCKET sockClient = accept(m_sockServer, (SOCKADDR*)&addr, &nLen);
		if (sockClient == INVALID_SOCKET)
		{
			if (m_sockServer == INVALID_SOCKET)
				break;
			else
				continue;
		}

		int option = 0;
		setsockopt(sockClient, IPPROTO_TCP, TCP_NODELAY, (const char*)option, sizeof(option));

		Client_PARAM* pParam = new Client_PARAM;
		if (pParam == NULL)
		{
			DisplayStatus(_T("Not enouph memory[CServer::RunServer]"));
			continue;
		}
		pParam->sock = sockClient;
		pParam->addr = addr;
		pParam->hParentWnd = m_hWnd;
		pParam->pServer = this;

		AfxBeginThread(ThreadClientProcess, (LPVOID)pParam);
	}

	m_bRunning = FALSE;
}

BOOL CServer::Start(UINT nPort, HWND hWnd)
{
	if (m_bRunning)
		return TRUE;

	m_nPort = nPort;
	m_hWnd = hWnd;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {		// 윈도우 소켓 API 초기화
		return FALSE;
	}

	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockServer == INVALID_SOCKET)
		return FALSE;

	int nRet;

	// bind
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	nRet = ::bind(m_sockServer, (SOCKADDR*)&addr, sizeof(addr));
	if (nRet == SOCKET_ERROR)
	{
		Release();
		return FALSE;
	}

	int option = 1;
	setsockopt(m_sockServer, SOL_SOCKET, SO_REUSEADDR, (char*)(&option), sizeof(option));

	nRet = ::listen(m_sockServer, SOMAXCONN);
	if (nRet == SOCKET_ERROR)
	{
		Release();
		return FALSE;
	}

	AfxBeginThread(ThreadStart, this);

	DisplayStatus(_T("Server Started."));

	return TRUE;
}

void CServer::Stop()
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (m_listClient.GetCount() > 0)
	{
		CClient* pClient = m_listClient.RemoveHead();
		if (pClient == NULL)
			continue;

		pClient->Close();
	}

	int nCnt = 0;
	while (1)
	{
		if (++nCnt > 10)
			break;

		if (m_listClient.GetCount() <= 0)
			break;

		Sleep(100);
	}

	if (!m_bRunning)
		return;

	if (m_sockServer != INVALID_SOCKET)
	{
		closesocket(m_sockServer);
		m_sockServer = INVALID_SOCKET;
	}

	Sleep(100);
	DisplayStatus(_T("Server finished."));
}