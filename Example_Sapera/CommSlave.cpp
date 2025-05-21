#include "pch.h"
#include "CommSlave.h"
#include "Example_SaperaDlg.h"

CommSlave::CommSlave(CExampleSaperaDlg* pDlg)
{
	m_pMainDlg = pDlg;
	m_sock = INVALID_SOCKET;
}

CommSlave::~CommSlave(void)
{
	//Stop();
}

UINT ThreadRun(LPVOID param)
{
	CommSlave* pComm = (CommSlave*)param;
	pComm->Run();

	return 1;
}

BOOL CommSlave::Start(LPCTSTR szIP, int nPort)
{
	m_strServerIP = szIP;
	m_nPort = nPort;

	AfxBeginThread(ThreadRun, this);

	return TRUE;
}

void CommSlave::Stop(void)
{
	if (m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
	}
}

void CommSlave::Run(void)
{
	m_bRun = TRUE;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {		// 윈도우 소켓 API 초기화
		return ;
	}

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed to create socket"));
		m_bRun = FALSE;
		return;
	}

	int option = 0;
	setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (const char*)option, sizeof(option));

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(m_nPort);
	//serveraddr.sin_addr.s_addr = inet_addr(m_strServerIP);
	inet_pton(AF_INET, m_strServerIP, &serveraddr.sin_addr);

	int retval = connect(m_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Failed to connect socket"));
		m_bRun = FALSE;
		return;
	}
	DisplayStatus(_T("connected to the server"));

	// 데이터 통신에 사용할 변수
	const int BUFFER_LEN = 1024;

	BYTE RecvBuf[BUFFER_LEN];
	int nRecvBytes = 0;
	int nRet;
	Header header;
	memset(&header, 0, sizeof(Header));

	// Recv
	while (1)
	{
		nRet = recv(m_sock, (char*)RecvBuf, BUFFER_LEN - nRecvBytes, 0);
		if (nRet == SOCKET_ERROR)
		{
			DisplayStatus(_T("socket error"));
			break;
		}
		else if (nRet == 0)
		{
			DisplayStatus(_T("socket disconnected"));
			break;
		}
	
		nRecvBytes += nRet;
	
		if (nRecvBytes < sizeof(Header))
		{
			continue;
		}
	
	
		while (1)
		{
			if (nRecvBytes < sizeof(Header))
				break;
	
			memcpy(&header, RecvBuf, sizeof(header));
			if (nRecvBytes >= header.PacketSize)
			{
				ProcessPacket(m_sock, &header, RecvBuf, header.PacketSize);
	
				nRecvBytes -= header.PacketSize;
				memmove(RecvBuf, RecvBuf + header.PacketSize, nRecvBytes);
			}
			else
				break;
		}
	}

	closesocket(m_sock);
	m_sock = INVALID_SOCKET;

	m_bRun = FALSE;
}

BOOL CommSlave::ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	switch (pHeader->PacketCode)
	{
	case PACKET_CODE_GRAB_CNT:
		Process_GrabCnt(sock, pHeader, pBuf, nBufLen);
		break;

	case PACKET_CODE_GRAB_START:
		Process_GrabStart(sock, pHeader, pBuf, nBufLen);
		break;

	case PACKET_CODE_GRAB_STOP:
		Process_GrabStop(sock, pHeader, pBuf, nBufLen);
		break;

	case PACKET_CODE_SNAP:
		Process_Snap(sock, pHeader, pBuf, nBufLen);
		break;

	default:
		break;
	}

	return TRUE;
}

BOOL CommSlave::Process_Snap(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("Recv GrabStart Packet"));
	m_pMainDlg->m_Snap.SetCheck(BST_CHECKED);
	m_pMainDlg->OnBnClickedCheckSnap();

	Header header;
	header.PacketCode = pHeader->PacketCode;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	DWORD dwStart = GetTickCount();
	int nRet = send(sock, (char*)m_SendBuf, header.PacketSize, 0);
	DWORD dwEnd = GetTickCount();

	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in Process_GrabCnt"));
		return FALSE;
	}

	return TRUE;
}

BOOL CommSlave::Process_GrabStart(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("Recv GrabStart Packet"));
	m_pMainDlg->m_StartStop.SetCheck(BST_CHECKED);
	m_pMainDlg->OnBnClickedCheckStartStop();

	Header header;
	header.PacketCode = pHeader->PacketCode;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	DWORD dwStart = GetTickCount();
	int nRet = send(sock, (char*)m_SendBuf, header.PacketSize, 0);
	DWORD dwEnd = GetTickCount();

	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in Process_GrabCnt"));
		return FALSE;
	}

	return TRUE;
}

BOOL CommSlave::Process_GrabStop(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("Recv GrabStop Packet"));
	m_pMainDlg->m_StartStop.SetCheck(BST_UNCHECKED);
	m_pMainDlg->OnBnClickedCheckStartStop();

	Header header;
	header.PacketCode = pHeader->PacketCode;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	int nRet = send(sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in Process_GrabCnt"));
		return FALSE;
	}

	return TRUE;
}

BOOL CommSlave::Process_GrabCnt(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	int nGrabCnt = m_pMainDlg->m_nGrabCnt[0];

	Header header;
	header.PacketCode = pHeader->PacketCode;
	header.PacketSize = sizeof(header) + sizeof(nGrabCnt);
	memcpy(m_SendBuf, &header, sizeof(header));
	memcpy(m_SendBuf + sizeof(Header), &nGrabCnt, sizeof(nGrabCnt));

	int nRet = send(sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in Process_GrabCnt"));
		return FALSE;
	}

	return TRUE;
}
