#include "pch.h"
#include "CServerDlg.h"
#include "MyClient.h"
#include "define.h"
#include "Example_SaperaDlg.h"

MyClient::MyClient(SOCKET sock, HWND hWnd) : CClient(sock, hWnd)
{
	//	m_sock = sock;
	//	m_hWnd = hWnd;
	m_pDlg = NULL;
}

MyClient::~MyClient(void)
{
}

void MyClient::SetParent(CServerDlg* pDlg)
{
	m_pDlg = pDlg;
}


BOOL MyClient::ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen, HWND hWnd)
{
	int nRet = FALSE;

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

BOOL MyClient::Process_Snap(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("[%s] Recv GrabStart Packet"), m_strIP);

	m_pDlg->SetStatus(m_strIP, STATUS_SNAP);

	return TRUE;

}

BOOL MyClient::Process_GrabStart(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("[%s] Recv GrabStart Packet"), m_strIP);

	m_pDlg->SetStatus(m_strIP, STATUS_GRAB);

	return TRUE;

}
BOOL MyClient::Process_GrabStop(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	//	DisplayStatus(_T("[%s] Recv GrabStop Packet"), m_strIP);

	m_pDlg->SetStatus(m_strIP, STATUS_READY_GRAB);

	return TRUE;
}

BOOL MyClient::Process_GrabCnt(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen)
{
	int nGrabCnt = 0;
	memcpy(&nGrabCnt, pBuf + sizeof(Header), sizeof(int));

	m_pDlg->SetGrabCnt(m_strIP, nGrabCnt);

	//	DisplayStatus(_T("[%s] Recv GrabCnt[%d]"), m_strIP, nGrabCnt);

	return TRUE;
}

int MyClient::Run()
{
	if (m_sock == INVALID_SOCKET)
		return -1;

	const int BUFFER_LEN = 1024;

	BYTE RecvBuf[BUFFER_LEN];
	int nRecvBytes = 0;
	int nRet;
	Header header;
	memset(&header, 0, sizeof(Header));

	// Recv
	while (1)
	{
		nRet = recv(m_sock, (char*)RecvBuf, BUFFER_LEN - nRecvBytes, 0);		// 패킷 수신까지 대기
		if (nRet == SOCKET_ERROR)
		{
			DisplayStatus("Disconnected");
			return -1;
		}
		else if (nRet == 0)
		{
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
				ProcessPacket(m_sock, &header, RecvBuf, header.PacketSize, m_hWnd);

				nRecvBytes -= header.PacketSize;
				memmove(RecvBuf, RecvBuf + header.PacketSize, nRecvBytes);
			}
			else
				break;
		}
	}

	return 0;
}

void MyClient::SendGrabCnt(void)
{
	Header header;
	header.PacketCode = PACKET_CODE_GRAB_CNT;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	int nRet = send(m_sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in SendGrabCnt"));
		return;
	}

}

void MyClient::SendSnap(void)
{
	Header header;
	header.PacketCode = PACKET_CODE_SNAP;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	int nRet = send(m_sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in SendGrabStart"));
		return;
	}
}

void MyClient::SendGrabStart(void)
{
	Header header;
	header.PacketCode = PACKET_CODE_GRAB_START;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	int nRet = send(m_sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in SendGrabStart"));
		return;
	}
}

void MyClient::SendGrabStop(void)
{
	Header header;
	header.PacketCode = PACKET_CODE_GRAB_STOP;
	header.PacketSize = sizeof(header);
	memcpy(m_SendBuf, &header, sizeof(header));

	int nRet = send(m_sock, (char*)m_SendBuf, header.PacketSize, 0);
	if (nRet == SOCKET_ERROR)
	{
		DisplayStatus(_T("Failed to send in SendGrabStop"));
		return;
	}
}
