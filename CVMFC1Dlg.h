
// CVMFC1Dlg.h: 헤더 파일
//

#pragma once


// CCVMFC1Dlg 대화 상자
class CCVMFC1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CCVMFC1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CVMFC1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
#define NUM_OF_BARS 6
#define NUM_OF_ROI 24

#define SERO 0
#define SERO_W 50
#define SERO_H 105

#define GARO 1
#define GARO_W 100
#define GARO_H 50

#define OK 1
#define FAIL 0

	int rois[NUM_OF_ROI][5] = {
	SERO,201,95,SERO_W,SERO_H,
	SERO,590,13,SERO_W,SERO_H,
	SERO,990,113,SERO_W,SERO_H,
	SERO,302,209,SERO_W,SERO_H,
	SERO,585,230,SERO_W,SERO_H,
	SERO,860,219,SERO_W,SERO_H,
	SERO,307,441,SERO_W,SERO_H,
	SERO,581,429,SERO_W,SERO_H,
	SERO,845,446,SERO_W,SERO_H,
	SERO,205,502,SERO_W,SERO_H,
	SERO,579,606,SERO_W,SERO_H,
	SERO,963,523,SERO_W,SERO_H,

	GARO,248,29,GARO_W,GARO_H,
	GARO,443,71,GARO_W,GARO_H,
	GARO,672,84,GARO_W,GARO_H,
	GARO,886,49,GARO_W,GARO_H,
	GARO,241,350,GARO_W,GARO_H,
	GARO,434,362,GARO_W,GARO_H,
	GARO,648,364,GARO_W,GARO_H,
	GARO,853,367,GARO_W,GARO_H,
	GARO,255,625,GARO_W,GARO_H,
	GARO,446,620,GARO_W,GARO_H,
	GARO,656,615,GARO_W,GARO_H,
	GARO,853,640,GARO_W,GARO_H,

	};

	const char* source_window[NUM_OF_ROI];
	//int m_ok_num[NUM_OF_ROI];
	int m_ok_fail[NUM_OF_ROI];
	Rect m_roi[NUM_OF_ROI];
	CRect m_rect[NUM_OF_ROI];
	CRect m_txt_rect[NUM_OF_ROI];
	char m_is_clicked[NUM_OF_ROI] = { 0 };
	CPoint m_prev_pos[NUM_OF_ROI];
	Vec3b m_colour[NUM_OF_ROI];

	char m_focus_btn_clicked_flag=0;
	char m_shade_btn_clicked_flag=0;
	Mat m_matImage, src_gray, canny_output[NUM_OF_ROI]; // 이미지 정보를 담고 있는 객체.
	int thresh;
	BITMAPINFO* m_pBitmapInfo; // Bitmap 정보를 담고 있는 구조체.

	void CreateBitmapInfo(int w, int h, int bpp); // Bitmap 정보를 생성하는 함수.
	void DrawImage(); // 그리는 작업을 수행하는 함수.
	afx_msg void OnBnClickedBtnImageLoad();

	VideoCapture* capture;
	//Mat mat_frame;
	//CImage cimage_mfc;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedOk();
private:
	int DrawImageRoi();
	int DrawImageShade();
	int DrawContour();
	int ScanLine();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnShade();
	float calcBlurriness(const Mat& src);
	int blur_detect(Mat src);
	
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
//protected:
	//afx_msg LRESULT OnDevicechange(WPARAM wParam, LPARAM lParam);
};
