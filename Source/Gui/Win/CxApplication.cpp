/**
 * \file  CxApplication.cpp
 * \brief application
 */


#include <xLib/Gui/CxApplication.h>

#include <shellapi.h>
#include <xLib/Gui/CxResources.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
//DONE: инициализируем статик члены
HINSTANCE CxApplication::_m_hInstance = NULL;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bInit
/*static*/
BOOL CxApplication::bInit(HINSTANCE hInstance, const tString &csCmdLine) {
    /*DEBUG*/xASSERT_RET(NULL == _m_hInstance, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != hInstance,    FALSE);

    //TODO: - bFilterCmdLine
    //TODO: - cdCmdLine

    BOOL bRes = FALSE;

    _m_hInstance = hInstance;

    //-------------------------------------
    //используем с ресурсами
    bRes = CxResources::bInit();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: hGetInstance
/*static*/
HINSTANCE CxApplication::hGetInstance() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hInstance, NULL);

    return _m_hInstance;
}
//---------------------------------------------------------------------------
//DONE: bGetCmdLine
/*static*/
BOOL CxApplication::bGetCmdLine(std::vector<std::wstring> *pvecwsCmdLine) {
    /*DEBUG*/xASSERT_RET(NULL != pvecwsCmdLine, FALSE);

    BOOL    bRes        = FALSE;
    LPWSTR *pwszArglist = NULL;
    INT     iArgs       = - 1;

    pwszArglist = ::CommandLineToArgvW(::GetCommandLineW(), &iArgs);
    /*DEBUG*/xASSERT_RET(NULL != pwszArglist, FALSE);

    pvecwsCmdLine->clear();
    for (INT i = 0; i < iArgs; ++ i) {
        pvecwsCmdLine->push_back(pwszArglist[i]);
    }

    ::LocalFree(pwszArglist);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: vProcessMessages
/*static*/
VOID CxApplication::vProcessMessages() {
    MSG msgMsg = {0};

    while (::PeekMessage(&msgMsg, NULL, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msgMsg);
        ::DispatchMessage (&msgMsg);
    }
}
//---------------------------------------------------------------------------
//DONE: bRun (runs the window (waits for messages and processes them))
/*static*/
BOOL CxApplication::bRun() {
    BOOL bRes   = FALSE;
    INT  iRes   = - 1;
    MSG  msgMsg = {0}; //Here messages to the application are saved

    ////if (TRUE == _m_bIsFrame) {
        while (iRes = ::GetMessage(&msgMsg, NULL, 0, 0 )) {
            /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

            ::TranslateMessage(&msgMsg);
            ::DispatchMessage (&msgMsg);
            ////if (!IsDialogMessage (hDialog, & msgMsg))
            ////    {
            ////    TranslateMessage ( & msgMsg );
            ////    DispatchMessage ( & msgMsg );
            ////    }
        }

    ////} else {

    ////}

    return TRUE;    //static_cast<INT>(msgMsg.wParam)


    /*
    HACCEL hAccelTable = NULL;
    hAccelTable = ::LoadAccelerators(hInstance, (LPCTSTR)IDC_SMPLULFRAMEWND);

    MSG msg = {0};

    while (::GetMessage(&msg, NULL, 0, 0)) {
        if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
    */

    /*
    *** Dialog ***

    ////MSG msg = {0};

    ////while (::IsWindow(dlgMain.hGetHandle()) && ::GetMessage(&msg, NULL, 0, 0)) {
    ////    ::TranslateMessage(&msg);
    ////    ::DispatchMessage(&msg);
    ////}
    */
}
//---------------------------------------------------------------------------
//DONE: (Test to see if we are already running.)
/*static*/
BOOL CxApplication::bIsRunning(const tString &csInstanceName) {
    HANDLE hMutex = ::CreateMutex(NULL, TRUE, csInstanceName.c_str());
    xCHECK_RET(ERROR_ALREADY_EXISTS != ::GetLastError(), FALSE);

    /*DEBUG*/xASSERT_RET(NULL != hMutex, FALSE);
    ::CloseHandle(hMutex);    hMutex = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: vTerminate
/*static*/
VOID CxApplication::vTerminate() {
    //::PostQuitMessage(WM_QUIT);
    ::PostQuitMessage(WM_NULL);
}
//---------------------------------------------------------------------------



VOID CxApplication::vCreateWnd() {
    BOOL bRes = FALSE;


    ////CWndMain frMain;
    ////frMain._m_sClassName = "aaa";
    ////bRes = frMain.bCreate(IDC_SMPLULFRAMEWND, NULL, "MyFrameWnd", 400, 400, 600, 400, 0, 0, IDI_SMPLULFRAMEWND, IDI_SMALL, 1);
    ////bRes = frMain.bShow  (SW_SHOW);
    ////bRes = frMain.bUpdate();
}



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxApplication
CxApplication::CxApplication() {
    //LOG();
    /*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
//DONE: ~CxApplication
CxApplication::~CxApplication() {
    //LOG();
    /*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
