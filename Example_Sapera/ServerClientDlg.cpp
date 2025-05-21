// ServerClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Example_Sapera.h"
#include "afxdialogex.h"
#include "ServerClientDlg.h"


// CServerClientDlg 대화 상자

IMPLEMENT_DYNAMIC(CServerClientDlg, CDialogEx)

CServerClientDlg::CServerClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERVER_CLIENT, pParent)
{

}

CServerClientDlg::~CServerClientDlg()
{
}

void CServerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerClientDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerClientDlg 메시지 처리기
