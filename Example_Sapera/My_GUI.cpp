#include "pch.h"
#include "My_GUI.h"

MyGUI::MyGUI() {

}
MyGUI::~MyGUI() {

}

// 8bit 이미지용 DC Initialize
bool MyGUI::Init(CStatic* picbox, unsigned char* data, int width, int height, int channel, bool bSlave, MyGUI* RefGui) {
	m_picbox = picbox;

	m_pDC = m_picbox->GetDC();
	m_memDC.CreateCompatibleDC(m_pDC);		// memory DC 생성
	m_pDC->SetStretchBltMode(COLORONCOLOR);		// 이미지 확대/축소 방식 설정

	m_bitDepth = 8;
	m_imgSizeX = width;
	m_imgSizeY = height;
	m_channel = channel;

	//m_dataView = (unsigned char*)calloc(m_imgSizeX * m_imgSizeY * 3, sizeof(unsigned char));
	//m_dataView = new BYTE[m_imgSizeX * m_imgSizeY * 3];
	m_dataView = (unsigned int*)calloc(m_imgSizeX * m_imgSizeY, sizeof(unsigned int));

	ViewCenterPosX = m_imgSizeX / 2;
	ViewCenterPosY = m_imgSizeY / 2;

	m_bitmap.CreateBitmap(m_imgSizeX, m_imgSizeY, 1, 32, m_dataView);
	m_memDC.SelectObject(m_bitmap);

	UpdateViewRect();

	//magx = magFitX;
	//magy = magFitY;
	magx = magFitMin;
	magy = magFitMin;
	magstep = 1.5;
	scrollStep = 10;

	m_bSlave = bSlave;
	m_RefGui = RefGui;

	// View Thread 생성
	m_bThreadView = true;
	m_bThreadViewProc = false;
	m_ThreadView = AfxBeginThread(ViewThread, this, THREAD_PRIORITY_NORMAL, 0);

	m_bDown = false;
	m_bInit = true;

	Sleep(100);
	Show(data, ViewCenterPosX, ViewCenterPosY);

	return m_bInit;
}

bool MyGUI::Init(CStatic* picbox, SapBuffer* buffer, SapView* view, bool bSlave, MyGUI* RefGui) {
	return true;
}

void MyGUI::Free() {
	m_bThreadView = false;
	m_eventThreadView.SetEvent();
	if (m_bThreadViewProc) {
		Sleep(200);
	}

	free(m_dataView);

	m_bitmap.DeleteObject();

	m_memDC.DeleteDC();

	m_pDC->ReleaseAttribDC();
	m_picbox->ReleaseDC(m_pDC);

	m_bInit = false;
}

void MyGUI::UpdateViewRect(void)
{
	m_picbox->GetClientRect(&rectViewClient);				// View Rect on Window-based coordinate
	m_picbox->GetWindowRect(rectViewWindow);				// View Rect on Client-based coordinate
	m_picbox->GetParent()->ScreenToClient(rectViewWindow);	// Rect on Dialog-based coordinate
	m_viewSizeX = rectViewWindow.right - rectViewWindow.left;
	m_viewSizeY = rectViewWindow.bottom - rectViewWindow.top;

	magFitX = (float)m_viewSizeX / (float)m_imgSizeX;
	magFitY = (float)m_viewSizeY / (float)m_imgSizeY;
	magFitMin = min(magFitX, magFitY);
	//magFitMin = magFitX;
}

UINT MyGUI::ViewThread(LPVOID lParam)
{
	MyGUI* pDlg = (MyGUI*)lParam;
	int row, col, ch;

	WaitForSingleObject(pDlg->m_eventThreadView, INFINITE);
	while (pDlg->m_bThreadView)
	{
		// View 버퍼 업데이트
		if (pDlg->m_bitDepth == 8)	// 8 bit
		{
			for (int i = 0; i < pDlg->m_imgSizeX * pDlg->m_imgSizeY; i++)
			{
				pDlg->m_dataView[i] = (0xFF << 24) | (pDlg->m_data8[i] << 16) | (pDlg->m_data8[i] << 8) | (pDlg->m_data8[i]);	// ARGB 포맷으로 변환
			}
		}
		else
		{
			for (row = 0; row < pDlg->m_imgSizeY; row++) {
				for (col = 0; col < pDlg->m_imgSizeX; col++) {
					for (ch = 0; ch < pDlg->m_channel; ch++) {
						pDlg->m_dataView[(row * pDlg->m_imgSizeX + col) * pDlg->m_channel + ch] = pDlg->m_data16[row * pDlg->m_imgSizeX + col];
					}
				}
			}
		}
		SetBitmapBits(pDlg->m_bitmap, pDlg->m_imgSizeX * pDlg->m_imgSizeY * 4, pDlg->m_dataView);

		
		if (pDlg->m_bDown)	// 마우스 왼쪽 버튼으로 이미지 이동 시
			pDlg->CvtCenterPosToScrollPos(pDlg->MovingViewPosX, pDlg->MovingViewPosY);		// View 이동
		else
			pDlg->CvtCenterPosToScrollPos(pDlg->ViewCenterPosX, pDlg->ViewCenterPosY);

		// 이미지 그리기(Show)
		pDlg->m_pDC->StretchBlt(0, 0, pDlg->rectViewClient.right, pDlg->rectViewClient.bottom, &pDlg->m_memDC, pDlg->ScrollPosX, pDlg->ScrollPosY, pDlg->rectViewClient.right / pDlg->magx, pDlg->rectViewClient.bottom / pDlg->magy, SRCCOPY);	// 이미지 확대/축소 출력

		pDlg->m_bThreadViewProc = false;
		WaitForSingleObject(pDlg->m_eventThreadView, INFINITE);
	}
	return 0;
}

void MyGUI::Show(unsigned char* data, int PosCenterX, int PosCenterY)
{
	if (m_bInit)
	{
		// DC
		//CvtCenterPosToScrollPos(PosCenterX, PosCenterY);
		if (!m_bThreadViewProc)
		{
			m_data8 = data;
			m_bThreadViewProc = true;
			m_eventThreadView.SetEvent();
			//	(*ViewCNT)++;
		}

		// Sapera SDK
		
	}

}

void MyGUI::CvtCenterPosToScrollPos(int PosCenterX, int PosCenterY)
{
	if (PosCenterX < int(float(m_viewSizeX) / 2.0 / magx + 0.5))		// 이미지 축소
		ScrollPosX = 0;
	//else if (m_imgSizeX < PosCenterX + int(float(m_viewSizeX) / 2.0 / magx + 0.5))
	//	ScrollPosX = m_imgSizeX - int(float(m_viewSizeX) / magx + 0.5);
	else  // 이미지 확대
		ScrollPosX = PosCenterX - int(float(m_viewSizeX) / 2.0 / magx + 0.5);

	if (PosCenterY < int(float(m_viewSizeY) / 2.0 / magy + 0.5))		// 이미지 축소
		ScrollPosY = 0;
	//else if (m_imgSizeY < PosCenterY + int(float(m_viewSizeY) / 2.0 / magy + 0.5))
	//	ScrollPosY = m_imgSizeY - int(float(m_viewSizeY) / magy + 0.5);
	else  // 이미지 확대
		ScrollPosY = PosCenterY - int(float(m_viewSizeY) / 2.0 / magy + 0.5);
}

///////////////////////////////////////////////////// Mouse Event /////////////////////////////////////////////////////////
bool MyGUI::OnMouseMove(UINT nFlags, CPoint pointWindow)
{
	if (m_bInit)
	{
		if (isOnImgView(pointWindow))
		{
			// Mouse가 위치한 곳의 image 좌표
			m_MousePosImageX = ViewCenterPosX + int(double((pointWindow.x - rectViewWindow.left)) / double(magx));
			m_MousePosImageY = ViewCenterPosY + int(double((pointWindow.y - rectViewWindow.top)) / double(magy));
			TRACE("image 좌표 : %d, %d\n", m_MousePosImageX, m_MousePosImageY);

			if (m_bDown)		// 마우스 왼쪽 버튼 Down 상태
			{
				if (m_bSlave)
				{
					MovingViewPosX = m_RefGui->ViewCenterPosX + int(float(m_pointDown.x - (pointWindow.x - rectViewWindow.left)) / magx + 0.5);
					MovingViewPosY = m_RefGui->ViewCenterPosY + int(float(m_pointDown.y - (pointWindow.y - rectViewWindow.top)) / magy + 0.5);
				}
				else
				{
					MovingViewPosX = ViewCenterPosX + int(float(m_pointDown.x - (pointWindow.x - rectViewWindow.left)) / magx + 0.5);
					MovingViewPosY = ViewCenterPosY + int(float(m_pointDown.y - (pointWindow.y - rectViewWindow.top)) / magy + 0.5);
				}

				Show(m_data8, ViewCenterPosX + int(float(m_pointDown.x - (pointWindow.x - rectViewWindow.left)) / magx + 0.5), ViewCenterPosY + int(float(m_pointDown.y - (pointWindow.y - rectViewWindow.top)) / magy + 0.5));
			}

			m_posMouseWindow = pointWindow;
			ConvertMouse2ImageCoodinate(pointWindow, &m_posMouseOnImg);
			TRACE("image 좌표2 : %d, %d\n", m_posMouseOnImg.x, m_posMouseOnImg.y);
			if (m_posMouseOnImg.x < m_imgSizeX && m_posMouseOnImg.y < m_imgSizeY) {
				return true;
			}

			return false;
		}
		else
		{
			m_posMouseWindow = pointWindow;
			return false;
		}
	}
	else {
		return false;
	}
}

/// <summary>
/// nFlags : Ctrl 등의 기타 키 입력 여부
/// zDelta : 휠 변화
/// pt : 윌 사용 시, 마우스 포인터 위치
/// </summary>
/// <param name="nFlags"></param>
/// <param name="zDelta"></param>
/// <param name="pt"></param>
void MyGUI::OnMouseWheel(UINT nFlags, short zDelta, CPoint pointWindow)
{
	if (m_bInit)
	{
		CPoint pointClient;
		CPoint pointClientRef;
		CRect rect;
		m_picbox->GetWindowRect(rect);
		pointClient.x = pointWindow.x - rect.left;
		pointClient.y = pointWindow.y - rect.top;
		if (m_bSlave) {
			m_picbox->GetParent()->ScreenToClient(&pointWindow);
			pointClient.x = pointWindow.x - m_RefGui->rectViewWindow.left;
			pointClient.y = pointWindow.y - m_RefGui->rectViewWindow.top;
		}


		if (isOnImgView(pointWindow))
		{
			if (m_posMouseOnImg.x < m_imgSizeX && m_posMouseOnImg.y < m_imgSizeY) {
				if (nFlags & MK_CONTROL)	// Ctrl키가 눌려져 있는 상태(이미지 확대/축소)
				{
					int posx, posy;
					if (zDelta > 0)		// 스크롤 업(확대)
					{
						FindImageCoodiante(pointClient, &posx, &posy);
						magx = magx * magstep;
						magy = magx;
						//if (magx > maxFitX) {
						//	magx = maxFitX;
						//}
						SetImage2Point(posx, posy, pointClient);
					}
					else {	// 스크롤 다운(축소)
						if ((m_viewSizeX > (m_imgSizeX * (magx / magstep))) && (m_viewSizeY > (m_imgSizeY * (magy / magstep))))
						{
							FindImageCoodiante(pointClient, &posx, &posy);
							FitWindow();
							SetImage2Point(posx, posy, pointClient);
						}
						else {
							FindImageCoodiante(pointClient, &posx, &posy);
							magx = magx / magstep;
							magy = magx;

							//if(magx < magFitMin)
							//m_pDC->FillSolidRect(&rectViewClient, RGB(192, 192, 192));		// 이미지 축소 시, 이미지 외부는 black으로 표시

							SetImage2Point(posx, posy, pointClient);
						}


					}
				}		// Ctrl키가 눌려져 있지 않은 상태(이미지 이동)
				else {
					int posx, posy;
					if (zDelta <= 0)		// 스크롤 업
					{
						FindImageCoodiante(pointClient, &posx, &posy);

						ViewCenterPosY = ViewCenterPosY + scrollStep;

						Show(m_data8, ViewCenterPosX, ViewCenterPosY);
					}
					else {	// 스크롤 다운

						FindImageCoodiante(pointClient, &posx, &posy);

						ViewCenterPosY = ViewCenterPosY - scrollStep;

						Show(m_data8, ViewCenterPosX, ViewCenterPosY);
						
					}
				}
			}
		}
	}
}

void MyGUI::OnLButtonDown(UINT nFlags, CPoint pointWindow)
{
	if (m_bInit)
	{
		m_bDown = true;
		MovingViewPosX = ViewCenterPosX;
		MovingViewPosY = ViewCenterPosY;
		m_pointDown.x = pointWindow.x - rectViewWindow.left;	// picbox client point
		m_pointDown.y = pointWindow.y - rectViewWindow.top;		// picbox client point
	}
}

void MyGUI::OnLButtonUp(UINT nFlags, CPoint pointWindow)
{
	int X;
	int Y;
	if (m_bInit)
	{
		if (m_bDown)
		{
			m_bDown = false;
			//UpdataViewMain(vpos_MainX + (oldPoint.x - point.x), vpos_MainY + (oldPoint.y - point.y));

			X = ViewCenterPosX + int(float(m_pointDown.x - (pointWindow.x - rectViewWindow.left)) / magx + 0.5);
			Y = ViewCenterPosY + int(float(m_pointDown.y - (pointWindow.y - rectViewWindow.top)) / magy + 0.5);

			if (X < int(float(m_viewSizeX) / 2.0 / magx + 0.5))		// 이미지 축소
				X = int(float(m_viewSizeX) / 2.0 / magx + 0.5);
			else if (m_imgSizeX < X + int(float(m_viewSizeX) / 2.0 / magx + 0.5))		// 이미지 확대
				X = m_imgSizeX - int(float(m_viewSizeX) / 2.0 / magx + 0.5);

			if (Y < int(float(m_viewSizeY) / 2.0 / magy + 0.5))		// 이미지 축소
				Y = int(float(m_viewSizeY) / 2.0 / magy + 0.5);
			else if (m_imgSizeY < Y + int(float(m_viewSizeY) / 2.0 / magy + 0.5))		// 이미지 확대
				Y = m_imgSizeY - int(float(m_viewSizeY) / 2.0 / magy + 0.5);

			ViewCenterPosX = X;
			ViewCenterPosY = Y;
		}
	}
}

bool MyGUI::isOnImgView(CPoint pointWindow)
{
	// Master View
	if (!m_bSlave) {
		if (pointWindow.x > rectViewWindow.left && pointWindow.x < rectViewWindow.right && pointWindow.y > rectViewWindow.top && pointWindow.y < rectViewWindow.bottom)
		{
			return true;
		}
		else
		{
			OnLButtonUp(0, pointWindow);
			return false;
		}
	}
	else {	// Slave View
		if (pointWindow.x > m_RefGui->rectViewWindow.left && pointWindow.x < m_RefGui->rectViewWindow.right && pointWindow.y > m_RefGui->rectViewWindow.top && pointWindow.y < m_RefGui->rectViewWindow.bottom)
		{
			return true;
		}
		else
		{
			//	TRACE("OFF MouseX%d Y%d RECTX%d Y%d\n", point.x, point.y, rect_View.left, rect_View.top);
			OnLButtonUp(0, pointWindow);
			return false;
		}
	}
}

void MyGUI::OnMouseLeave(void)
{
	if (m_bInit)
	{
		OnLButtonUp(0, m_posMouseWindow);
	}
}

void MyGUI::ConvertMouse2ImageCoodinate(CPoint pt, CPoint *pointOnImg)
{
	if (m_bInit)
	{
		CPoint pointClient;

		pointClient.x = pt.x - rectViewWindow.left;
		pointClient.y = pt.y - rectViewWindow.top;
		pointOnImg->x = ScrollPosX + int(float(pointClient.x) / magx);
		pointOnImg->y = ScrollPosY + int(float(pointClient.y) / magy);
	}
}

void MyGUI::FindImageCoodiante(CPoint pointClient, int* PosX, int* PosY)
{
		*PosX = ScrollPosX + int(float(pointClient.x) / magx + 0.5);
		*PosY = ScrollPosY + int(float(pointClient.y) / magy + 0.5);
}

void MyGUI::SetImage2Point(int PosX, int PosY, CPoint pointClient)
{
	//find center

	int X = PosX - int(float((pointClient.x) - (m_viewSizeX + 1) / 2) / magx + 0.5); //이만큼 벗어남
	int Y = PosY - int(float((pointClient.y) - (m_viewSizeY + 1) / 2) / magy + 0.5);
	ViewCenterPosX = X;
	ViewCenterPosY = Y;

	if (m_bSlave)
	{
		Show(m_data8, m_RefGui->ViewCenterPosX, m_RefGui->ViewCenterPosY);
	}
	else {
		Show(m_data8, ViewCenterPosX, ViewCenterPosY);
	}
	

}

void MyGUI::FitWindow(void)
{
	ViewCenterPosX = m_imgSizeX / 2;
	ViewCenterPosY = m_imgSizeY / 2;

	//magx = magFitX;
	//magy = magFitY;
	magx = magFitMin;
	magy = magFitMin;

	m_pDC->FillSolidRect(&rectViewClient, RGB(192, 192, 192));		// 이미지 축소 시, 이미지 외부는 black으로 표시

	Show(m_data8, ViewCenterPosX, ViewCenterPosY);
}

