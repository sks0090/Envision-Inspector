#pragma once
#include "pch.h"

using namespace std;
#include <afxwin.h>
#include <afxstr.h>
#include <map>

enum DF_CLIENT_STATUS
{
	DF_CLIENT_READY = 0,
	DF_CLIENT_GRAB,
	DF_CLIENT_GRAB_STOP
};

struct DF_CLIENT_INFO
{
	CString szName;
	int nStatus;
	int nGrabCnt;
	int nDiffCaseCnt;		// Master의 카운트와 다른 경우의 횟수
};

class DFStatusMnger
{
public:
	DFStatusMnger(void);
	~DFStatusMnger(void);

	BOOL AddClient(CString szName);
	void RemoveClient(CString szName);

	BOOL SetStatus(CString szName, int nStatus);
	BOOL SetGrabCnt(CString szName, int nGrabCnt);

	int	 GetStatus(CString szName);
	int	 GetGrabCnt(CString szName);

	void Release();

protected:
	map<CString, DF_CLIENT_INFO*> m_mapClients;
public:
	BOOL IsAllGrabStatus(void);
	BOOL IsAllGrabReadyStatus(void);
	BOOL IsAllGrabCntSame(int nMasterGrabCnt = -1);
};

