
// CVMFC1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CVMFC1.h"
#include "CVMFC1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCVMFC1Dlg 대화 상자


CCVMFC1Dlg::CCVMFC1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CVMFC1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
	m_rect[0].SetRect(205, 300, 205+100, 300+200);  //x,y,x2,y2
	m_rect[1].SetRect(740, 514, 740+150, 514+50);
	m_rect[2].SetRect(90, 300, 90+100, 300+200);

	m_ok_num[0] = 40;
	m_ok_num[1] = 4;
	m_ok_num[2] = 20;
}

void CCVMFC1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCVMFC1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE_LOAD, &CCVMFC1Dlg::OnBnClickedBtnImageLoad)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, &CCVMFC1Dlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDOK, &CCVMFC1Dlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCVMFC1Dlg 메시지 처리기

#define WIDTH 1280
#define HEIGHT 720


//#define WIDTH 1920//800
//#define HEIGHT 1080//600


BOOL CCVMFC1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL,0,0, WIDTH+40, HEIGHT+100, SWP_NOMOVE | SWP_NOZORDER);

	CWnd* pCtrl = GetDlgItem(IDC_PC_VIEW);
	pCtrl->SetWindowPos(NULL, 0, 0, WIDTH, HEIGHT, SWP_NOMOVE | SWP_NOZORDER);

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCVMFC1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//	CDialogEx::OnPaint();
		m_matImage = imread("ims_elec2.jpg", IMREAD_UNCHANGED);
		CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
		DrawImage();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCVMFC1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCVMFC1Dlg::CreateBitmapInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete[]m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}

void CCVMFC1Dlg::DrawImage()
{
	CClientDC dc(GetDlgItem(IDC_PC_VIEW));

	CRect rect;
	GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

int CCVMFC1Dlg::DrawImageRoi()
{
	CClientDC dc(GetDlgItem(IDC_PC_VIEW));

	CRect rect;
	GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 2, RGB(51, 255, 255));
	brush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(&pen);
	dc.SelectObject(&brush);
	
	
	for (int i = 0; i < NUM_OF_ROI; i++)
	{
		dc.Rectangle(m_rect[i]);
	}
	

	return 0;
}

int CCVMFC1Dlg::DrawContour()
{
	CClientDC dc(GetDlgItem(IDC_PC_VIEW));

	for (int i = 0; i < NUM_OF_ROI; i++)
	{
		m_roi[i].x = m_rect[i].left;
		m_roi[i].y = m_rect[i].top;
		m_roi[i].width = m_rect[i].right - m_rect[i].left;
		m_roi[i].height = m_rect[i].bottom - m_rect[i].top;

		Mat imCrop = m_matImage(m_roi[i]);
		// Display Cropped Image
	//	imshow("Image", imCrop);
		cvtColor(imCrop, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, src_gray, Size(3, 3));
		thresh = 100;
		Canny(src_gray, canny_output[i], thresh, thresh * 2);
#define HJ_DEBUG_ONLY 0
#if HJ_DEBUG_ONLY
		const char* source_window[] = { "Source", "Source2", "Source3", };
		namedWindow(source_window[i]);
		imshow(source_window[i], canny_output[i]);
#endif
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(canny_output[i], contours, hierarchy, RETR_EXTERNAL/*RETR_TREE*/, /*CHAIN_APPROX_TC89_KCOS*//*CHAIN_APPROX_NONE*//*CHAIN_APPROX_TC89_L1*/CHAIN_APPROX_SIMPLE);
		CString a;

#if HJ_DEBUG_ONLY
		a.Format(_T("C=%d, x=%d, y=%d"), contours.size(), m_roi[i].x, m_roi[i].y);
#else
		if (contours.size() > m_ok_num[i])
			a.Format(_T("OK"));
		else
			a.Format(_T("Fail"));
#endif
		dc.DrawText(a, -1, &m_rect[i], DT_CENTER | DT_WORDBREAK);
	}
	return 0;
}

void CCVMFC1Dlg::OnBnClickedBtnImageLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	capture = new VideoCapture(0);
	if (!capture->isOpened())
	{
		MessageBox(_T("캠을 열수 없습니다. \n"));
	}
	capture->set(CAP_PROP_FRAME_WIDTH, WIDTH);
	capture->set(CAP_PROP_FRAME_HEIGHT, HEIGHT);
	/*for (int i = 0; i < 100; i++)
		capture->read(m_matImage);*/
	//1초 타이머
#define TIMER_1SEC 1000
#define TIMER_HALF_SEC 500
#define TIMER_FAST_SEC 30
	SetTimer(1000, TIMER_FAST_SEC, NULL);
}


void CCVMFC1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(1000);
	destroyAllWindows();
	capture->release();
}


void CCVMFC1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//mat_frame가 입력 이미지입니다. 
	capture->read(m_matImage);
	CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
	//DrawImage();
	DrawImageRoi();
	DrawContour();
	CDialogEx::OnTimer(nIDEvent);
}


void CCVMFC1Dlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1000);
	destroyAllWindows();
	capture->release();
	m_matImage = imread("ims_elec2.jpg", IMREAD_UNCHANGED);
	CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
	DrawImage();
}


void CCVMFC1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	KillTimer(1000);
	destroyAllWindows();
	capture->release();
	CDialogEx::OnOK();
}




void CCVMFC1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*if (point.x >= m_rect[0].left &&
		point.y >= m_rect[0].top &&
		point.x <= m_rect[0].right &&
		point.y <= m_rect[0].bottom
		)*/

	for (int i = 0; i < NUM_OF_ROI; i++)
	{
		if (m_rect[i].PtInRect(point))
		{
			m_is_clicked[i] = 1;
			m_prev_pos[i] = point;
			SetCapture(); // 마우스가 화면에서 벗어나도 이동
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCVMFC1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < NUM_OF_ROI; i++)
	{
		if (m_is_clicked[i] == 1)
		{
			m_is_clicked[i] = 0;
			ReleaseCapture();  // 마우스가 화면에서 벗어나도 이동하는걸 풀어줌
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CCVMFC1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < NUM_OF_ROI; i++)
	{
		if (m_is_clicked[i] == 1)
		{
			CPoint move_pos = point - m_prev_pos[i];

			/*
			m_rect[0].left += move_pos.x;
			m_rect[0].top += move_pos.y;
			m_rect[0].right += move_pos.x;
			m_rect[0].bottom += move_pos.y;
			*/
			m_rect[i] += move_pos;

			m_prev_pos[i] = point;

			//Invalidate();
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
