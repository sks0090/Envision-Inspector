#include "pch.h"
#include "CServerDlg.h"
#include "MyClient.h"
#include "MyServer.h"

MyServer::MyServer(void)
{
	m_pDlg = NULL;
}

MyServer::~MyServer(void)
{
}

void MyServer::OnNewClient(CLIENT_PARAM* pParam)
{
	SOCKET sockClient = pParam->sock;
	HWND hWnd = pParam->hParentWnd;
	SOCKADDR_IN addr = pParam->addr;

	delete pParam;

	MyClient Client(sockClient, hWnd);
	Client.SetParent(m_pDlg);
	Client.SetAddr(addr);
	m_listClient.AddTail(&Client);
	char str[100];
	inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
	m_pDlg->AddIP(CString(str));

	Client.Run();

	if (sockClient != INVALID_SOCKET)
		closesocket(sockClient);

	RemoveClientFromList(sockClient);
	if (m_pDlg && m_pDlg->GetSafeHwnd())
	{
		inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
		m_pDlg->RemoveIP(CString(str));
	}
}

void MyServer::SendSnap(void)
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos)
	{
		MyClient* pClient = (MyClient*)m_listClient.GetNext(pos);
		if (pClient == NULL)
		{
			continue;
		}

		pClient->SendSnap();
	}
}

void MyServer::SendGrabStart(void)
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos)
	{
		MyClient* pClient = (MyClient*)m_listClient.GetNext(pos);
		if (pClient == NULL)
		{
			continue;
		}

		pClient->SendGrabStart();
	}
}

void MyServer::SendGrabStop(void)
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos)
	{
		MyClient* pClient = (MyClient*)m_listClient.GetNext(pos);
		if (pClient == NULL)
		{
			continue;
		}

		pClient->SendGrabStop();
	}
}

void MyServer::SendGrabCnt(void)
{
	POSITION pos = m_listClient.GetHeadPosition();
	while (pos)
	{
		MyClient* pClient = (MyClient*)m_listClient.GetNext(pos);
		if (pClient == NULL)
		{
			continue;
		}

		pClient->SendGrabCnt();
	}

}

void MyServer::SetParent(CServerDlg* pDlg)
{
	m_pDlg = pDlg;
}
