#pragma once
#include "afxdialogex.h"
#include "My_GUI.h"
#include "SapMnger.h"



// DemoLIneaHS2Dlg 대화 상자

class DemoLineaHS2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(DemoLineaHS2Dlg)

public:
	DemoLineaHS2Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DemoLineaHS2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEMO_HS2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stDisplay1;
	CStatic m_stDisplay2;
	CStatic m_stDisplay3;

	MyGUI* m_pGui1;
	MyGUI* m_pGui2;
	//MyGUI* m_pGui3;

	SapBuffer* m_Buffer1, * m_Buffer2;// , * m_Buffer3;

	unsigned char* m_pBuf1, * m_pBuf2;// , * m_pBuf3;

	CButton m_chkStart;

	int m_nMode;

	int m_widthDisplay, m_heightDisplay;
	int m_leftSpeedBtn, m_leftResponsivityBtn;
	int m_topBtns;
	int m_widthBtn;
	int m_heightBtn;

	CStatic m_bitUI;
	CStatic m_bitResponsivityOff;
	CStatic m_bitResponsivityOn;
	CStatic m_bitSpeedOff;
	CStatic m_bitSpeedOn;
	HBITMAP hbit, hbitResponsivityOff, hbitResponsivityOn, hbitSpeedOff, hbitSpeedOn;

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	void InitDemo();

public:
	afx_msg void OnBnClickedChkStart();
	
	afx_msg void OnBnClickedBtnUiOn();
	afx_msg void OnDestroy();
	
	afx_msg void OnClickedBitSpeedOff();
	afx_msg void OnClickedBitResponsivityOff();
};
