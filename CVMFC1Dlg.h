
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
#define NUM_OF_ROI 3
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
};
