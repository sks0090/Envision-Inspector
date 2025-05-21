#include "pch.h"
#include "CClient.h"

CClient::CClient(SOCKET sock, HWND hWnd)
{
	m_sock = sock;
	m_hWnd = hWnd;
}

CClient::~CClient(void)
{
}

BOOL CClient::ProcessPacket(SOCKET sock, Header* pHeader, BYTE* pBuf, int nBufLen, HWND hWnd)
{

	return FALSE;
}

int CClient::Run()
{
	if (m_sock == INVALID_SOCKET)
		return -1;

	return 0;
}

void CClient::SetAddr(SOCKADDR_IN addr)
{
	char str[INET_ADDRSTRLEN];

	m_addr = addr;
	m_strIP = inet_ntop(AF_INET, &addr.sin_addr, str, INET_ADDRSTRLEN);
}

void CClient::Close(void)
{
	if (m_sock == INVALID_SOCKET)
		return;

	closesocket(m_sock);
}
