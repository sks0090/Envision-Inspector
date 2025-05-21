#include "pch.h"
#include "DFStatusMnger.h"
#include "define.h"

DFStatusMnger::DFStatusMnger(void)
{
}

DFStatusMnger::~DFStatusMnger(void)
{
	Release();
}

void DFStatusMnger::Release()
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;
	for (iter = m_mapClients.begin(); iter != m_mapClients.end(); iter++)
	{
		DF_CLIENT_INFO* pInfo = iter->second;
		if (pInfo)
		{
			delete pInfo;
			pInfo = NULL;
		}
	}
}

BOOL DFStatusMnger::AddClient(CString szName)
{
	DF_CLIENT_INFO* pInfo = new DF_CLIENT_INFO;
	if (pInfo == NULL)
		return FALSE;

	memset(pInfo, 0, sizeof(DF_CLIENT_INFO));
	m_mapClients.insert(map<CString, DF_CLIENT_INFO*>::value_type(szName, pInfo));
	return TRUE;
}

void DFStatusMnger::RemoveClient(CString szName)
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;

	iter = m_mapClients.find(szName);
	if (iter == m_mapClients.end())
		return;

	delete iter->second;

	m_mapClients.erase(szName);
}

BOOL DFStatusMnger::SetStatus(CString szName, int nStatus)
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;

	iter = m_mapClients.find(szName);
	if (iter == m_mapClients.end())
		return FALSE;

	(iter->second)->nStatus = nStatus;

	return TRUE;
}

BOOL DFStatusMnger::SetGrabCnt(CString szName, int nGrabCnt)
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;

	iter = m_mapClients.find(szName);
	if (iter == m_mapClients.end())
		return FALSE;

	(iter->second)->nGrabCnt = nGrabCnt;

	return TRUE;
}

int DFStatusMnger::GetStatus(CString szName)
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;

	iter = m_mapClients.find(szName);
	if (iter == m_mapClients.end())
		return -1;


	DF_CLIENT_INFO* pInfo = (DF_CLIENT_INFO*)iter->second;
	if (pInfo == NULL)
		return -1;

	return pInfo->nStatus;
}

int DFStatusMnger::GetGrabCnt(CString szName)
{
	map<CString, DF_CLIENT_INFO*>::iterator iter;

	iter = m_mapClients.find(szName);
	if (iter == m_mapClients.end())
		return -1;

	DF_CLIENT_INFO* pInfo = (DF_CLIENT_INFO*)iter->second;
	if (pInfo == NULL)
		return -1;

	return pInfo->nGrabCnt;
}

BOOL DFStatusMnger::IsAllGrabStatus(void)
{
	int nGrabStatusCnt = 0;
	map<CString, DF_CLIENT_INFO*>::iterator iter;
	for (iter = m_mapClients.begin(); iter != m_mapClients.end(); iter++)
	{
		DF_CLIENT_INFO* pInfo = iter->second;
		if (pInfo == NULL)
			continue;

		if (pInfo->nStatus == STATUS_GRAB)
			++nGrabStatusCnt;
	}

	if (nGrabStatusCnt == m_mapClients.size())
		return TRUE;

	return FALSE;
}

BOOL DFStatusMnger::IsAllGrabReadyStatus(void)
{
	int nGrabStatusCnt = 0;
	map<CString, DF_CLIENT_INFO*>::iterator iter;
	for (iter = m_mapClients.begin(); iter != m_mapClients.end(); iter++)
	{
		DF_CLIENT_INFO* pInfo = iter->second;
		if (pInfo == NULL)
			continue;

		if (pInfo->nStatus == STATUS_READY_GRAB)
			++nGrabStatusCnt;
	}

	if (nGrabStatusCnt == m_mapClients.size())
		return TRUE;

	return FALSE;
}

BOOL DFStatusMnger::IsAllGrabCntSame(int nMasterGrabCnt)
{
	BOOL bAllSame = TRUE;

	map<CString, DF_CLIENT_INFO*>::iterator iter;
	for (iter = m_mapClients.begin(); iter != m_mapClients.end(); iter++)
	{
		DF_CLIENT_INFO* pInfo = iter->second;
		if (pInfo == NULL)
			continue;

		if (nMasterGrabCnt != -1 && pInfo->nGrabCnt != nMasterGrabCnt)
		{
			++pInfo->nDiffCaseCnt;
			bAllSame = FALSE;
		}
	}

	return bAllSame;
}
