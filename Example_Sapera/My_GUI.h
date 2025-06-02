#pragma once
#include "pch.h"

#include "SapClassBasic.h"

// image coordinate : 이미지 좌표
// client coordinate : 다이얼로그 기준 좌표
// Window coordinate : 전체 화면 기준 좌표
class MyGUI {
public:		// Variables
	CPoint m_clientCoordinateMouse;			// client coordinate for Mouse
	CPoint m_imageCoordinateMouse;			// image coordinate for Mouse
	CPoint m_pointDown;

	CRect m_windowCoordinateViewRect;				// window coordinate Rect for picture box
	CRect m_clientCoordinateViewRect;				// client coordinate Rect for picture box

	CDC m_memDC;
	CBitmap m_cBitmap;
	void* m_pBits;		// DIB Section 생성용 포인터

	bool m_bInit;
	bool m_bDown;
	bool m_bSlave;
	bool m_bThreadView, m_bThreadViewProc;

	int m_bitDepth;
	int  m_nImgSizeX, m_nImgSizeY, m_nChannel;	// Image 크기
	int m_viewSizeX, m_viewSizeY;			// View 크기
	int ViewCenterPosX, ViewCenterPosY;		// VIew의 중앙 이미지 좌표
	int MovingViewPosX, MovingViewPosY;		// 마우스 왼쪽 버튼 누르고 끈 위치
	int ScrollPosX, ScrollPosY;				// View의 왼쪽위 모서리 위치에 대한 이미지 좌표
	int m_MousePosImageX, m_MousePosImageY;

	int row, col;

	float magFitMin, magFitX, magFitY;
	float maxFit;
	float magx, magy;
	float magstep;
	float scrollStep;

	//unsigned char* m_dataView;		// View 이미지 data
	unsigned int* m_dataView;
	unsigned char* m_pView;
	unsigned char* m_data8;			// 8bit data
	unsigned short* m_data16;		// 16bit data
	
	// view 시간 간격 측정 to set 60 fps
	LARGE_INTEGER		m_frequency;
	LARGE_INTEGER		m_viewStartTime, m_viewEndTime;

	MyGUI* m_RefGui;

	CWinThread* m_ThreadView;

	CEvent m_eventThreadView;	

	// GUI
	CStatic* m_picbox;

public:		// Methods
	MyGUI();
	~MyGUI();
	// Thread
	static UINT ViewThread(LPVOID lParam);		// View Thread
	// Mouse Event
	bool OnMouseMove(UINT nFlags, CPoint pointWindow);					// 아우스 움직임 이벤트 처리기
	void OnMouseWheel(UINT nFlags, short zDelta, CPoint pointWindow);		// 마우스 휠 이벤트 처리기
	void OnMouseLeave(void);							// 마우스 위치가 현재 dialog를 벗어난 경우
	void OnLButtonDown(UINT nFlags, CPoint pointWindow);		// 마우스 왼쪽 버튼 down
	void OnLButtonUp(UINT nFlags, CPoint pointWindow);		// 마우스 왼쪽 버튼 up
	// General
	bool Init(CStatic* picbox, unsigned char* data, int width, int height, int channel, bool bSlave, MyGUI* RefGui = NULL);		// DC 이용
	bool Init(CStatic* picbox, SapBuffer* buffer, SapView* view, bool bSlave, MyGUI* RefGui);
	void Free(void);
	void UpdateViewRect(void);
	void Show(unsigned char* data, int PosCenterX, int PosCenterY);
	bool isOnImgView(CPoint pointWindow);		// pointWindow가 이미지 위에 있는지 여부 확인
	void CvtCenterPosToScrollPos(int PosX, int PosY);
	void ConvertMouse2ImageCoodinate(CPoint point, CPoint *pointOnImg);		// Window 좌표를 이미지 픽셀 좌표로 변환
	void FindImageCoodiante(CPoint point, int* PosX, int* PosY);
	void SetImage2Point(int PosX, int PosY, CPoint point);
	
	void FitWindow(void);		// View 꽉 채우기
};