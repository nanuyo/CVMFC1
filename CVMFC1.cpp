
// CVMFC1.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "CVMFC1.h"
#include "CVMFC1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCVMFC1App

BEGIN_MESSAGE_MAP(CCVMFC1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCVMFC1App 생성

CCVMFC1App::CCVMFC1App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CCVMFC1App 개체입니다.

CCVMFC1App theApp;


// CCVMFC1App 초기화

BOOL CCVMFC1App::InitInstance()
{
	CWinApp::InitInstance();
	

	CCVMFC1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	


	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

