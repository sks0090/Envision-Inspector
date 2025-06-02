#pragma once
#include "pch.h"

#include "SapClassBasic.h"

// image coordinate : �̹��� ��ǥ
// client coordinate : ���̾�α� ���� ��ǥ
// Window coordinate : ��ü ȭ�� ���� ��ǥ
class MyGUI {
public:		// Variables
	CPoint m_clientCoordinateMouse;			// client coordinate for Mouse
	CPoint m_imageCoordinateMouse;			// image coordinate for Mouse
	CPoint m_pointDown;

	CRect m_windowCoordinateViewRect;				// window coordinate Rect for picture box
	CRect m_clientCoordinateViewRect;				// client coordinate Rect for picture box

	CDC m_memDC;
	CBitmap m_cBitmap;
	void* m_pBits;		// DIB Section ������ ������

	bool m_bInit;
	bool m_bDown;
	bool m_bSlave;
	bool m_bThreadView, m_bThreadViewProc;

	int m_bitDepth;
	int  m_nImgSizeX, m_nImgSizeY, m_nChannel;	// Image ũ��
	int m_viewSizeX, m_viewSizeY;			// View ũ��
	int ViewCenterPosX, ViewCenterPosY;		// VIew�� �߾� �̹��� ��ǥ
	int MovingViewPosX, MovingViewPosY;		// ���콺 ���� ��ư ������ �� ��ġ
	int ScrollPosX, ScrollPosY;				// View�� ������ �𼭸� ��ġ�� ���� �̹��� ��ǥ
	int m_MousePosImageX, m_MousePosImageY;

	int row, col;

	float magFitMin, magFitX, magFitY;
	float maxFit;
	float magx, magy;
	float magstep;
	float scrollStep;

	//unsigned char* m_dataView;		// View �̹��� data
	unsigned int* m_dataView;
	unsigned char* m_pView;
	unsigned char* m_data8;			// 8bit data
	unsigned short* m_data16;		// 16bit data
	
	// view �ð� ���� ���� to set 60 fps
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
	bool OnMouseMove(UINT nFlags, CPoint pointWindow);					// �ƿ콺 ������ �̺�Ʈ ó����
	void OnMouseWheel(UINT nFlags, short zDelta, CPoint pointWindow);		// ���콺 �� �̺�Ʈ ó����
	void OnMouseLeave(void);							// ���콺 ��ġ�� ���� dialog�� ��� ���
	void OnLButtonDown(UINT nFlags, CPoint pointWindow);		// ���콺 ���� ��ư down
	void OnLButtonUp(UINT nFlags, CPoint pointWindow);		// ���콺 ���� ��ư up
	// General
	bool Init(CStatic* picbox, unsigned char* data, int width, int height, int channel, bool bSlave, MyGUI* RefGui = NULL);		// DC �̿�
	bool Init(CStatic* picbox, SapBuffer* buffer, SapView* view, bool bSlave, MyGUI* RefGui);
	void Free(void);
	void UpdateViewRect(void);
	void Show(unsigned char* data, int PosCenterX, int PosCenterY);
	bool isOnImgView(CPoint pointWindow);		// pointWindow�� �̹��� ���� �ִ��� ���� Ȯ��
	void CvtCenterPosToScrollPos(int PosX, int PosY);
	void ConvertMouse2ImageCoodinate(CPoint point, CPoint *pointOnImg);		// Window ��ǥ�� �̹��� �ȼ� ��ǥ�� ��ȯ
	void FindImageCoodiante(CPoint point, int* PosX, int* PosY);
	void SetImage2Point(int PosX, int PosY, CPoint point);
	
	void FitWindow(void);		// View �� ä���
};