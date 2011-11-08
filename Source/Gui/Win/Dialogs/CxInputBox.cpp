/**
 * \file  CxInputBox.cpp
 * \brief input box
 */


#include <xLib/Gui/Win/Dialogs/CxInputBox.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxInputBox::CxInputBox() :
    _m_sText     (),
    _m_hWndMain  (NULL),
    _m_hBtnOk    (NULL),
    _m_hBtnCancel(NULL),
    _m_hStaPrompt(NULL),
    _m_hEdtText  (NULL)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxInputBox::~CxInputBox() {

}
//---------------------------------------------------------------------------
CxInputBox::EModalResult
CxInputBox::mrShowModal(
    const std::string_t &csCaption,
    const std::string_t &csPrompt,
    const std::string_t &csText
)
{
    /*DEBUG*/// csCaption - n/a
    /*DEBUG*/// csPrompt  - n/a
    /*DEBUG*/// csText    - n/a

    HINSTANCE hInstance = ::GetModuleHandle(NULL);
    /*DEBUG*/xASSERT_RET(NULL != hInstance, mrCancel);

    WNDCLASS wndClass = {0};

    wndClass.style         = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = (WNDPROC)_ms_pWndProc;
    wndClass.hInstance     = hInstance;
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW/* + 1*/);
    wndClass.lpszClassName = xT("CxInputBox");
    wndClass.hIcon         = ::LoadIcon(NULL, IDI_QUESTION);
    wndClass.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
    wndClass.cbWndExtra    = 4;    //4�����

    BOOL bRes = ::RegisterClass(&wndClass);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, CxInputBox::mrCancel);

    //-------------------------------------
    //_m_hWndMain
    INT iWidth  = 240;
    INT iHeight = 125;
    INT x       = ::GetSystemMetrics(SM_CXSCREEN) / 2;
    INT y       = ::GetSystemMetrics(SM_CYSCREEN) / 2;

    _m_hWndMain = ::CreateWindow(
                            xT("CxInputBox"),
                            csCaption.c_str(),
                            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
                            x - iWidth  / 2,
                            y - iHeight / 2,
                            iWidth,
                            iHeight,
                            NULL,
                            NULL,
                            hInstance,
                            NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hWndMain, mrCancel);

    ::SetWindowLong(_m_hWndMain, 0, (LONG)this);

    //-------------------------------------
    //_m_hStaPrompt
    _m_hStaPrompt = ::CreateWindow(
                            xT("STATIC"),
                            csPrompt.c_str(),
                            WS_CHILD | WS_VISIBLE | ES_LEFT,
                            8,   8,
                            216, 20,
                            _m_hWndMain,
                            (HMENU)ID_staPrompt,
                            hInstance,
                            NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hStaPrompt, mrCancel);

    //-------------------------------------
    //_m_hEdtText
    _m_hEdtText = ::CreateWindow(
                            xT("EDIT"),
                            csText.c_str(),
                            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD,
                            8,   8+20+8,
                            216, 20,
                            _m_hWndMain,
                            (HMENU)ID_edtText,
                            hInstance,
                            NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hEdtText, mrCancel);

    //-------------------------------------
    //_m_hBtnOk
    _m_hBtnOk = ::CreateWindow(
                            xT("BUTTON"),
                            xT("OK"),
                            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            40, 62,
                            75, 25,
                            _m_hWndMain,
                            (HMENU)ID_btnOK,
                            hInstance,
                            NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hBtnOk, mrCancel);

    //-------------------------------------
    //_m_hBtnCancel
    _m_hBtnCancel = ::CreateWindow(
                            xT("BUTTON"),
                            xT("Cancel"),
                            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                            40+75+4, 62,
                            75,      25,
                            _m_hWndMain,
                            (HMENU)ID_btnCancel,
                            hInstance,
                            NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hBtnCancel, mrCancel);

    //-------------------------------------
    //_m_hWndMain
    ::ShowWindow(_m_hWndMain, SW_SHOW);
    ::UpdateWindow(_m_hWndMain);

    //��������� _m_hWndMain
    {
        HWND hCurrWnd = ::GetForegroundWindow();
        INT  iMyTID   = ::GetCurrentThreadId();
        INT  iCurrTID = ::GetWindowThreadProcessId(hCurrWnd, 0);

        ::AttachThreadInput  (iMyTID, iCurrTID, TRUE);
        ::SetForegroundWindow(_m_hWndMain);
        ::AttachThreadInput  (iMyTID, iCurrTID, FALSE);

        ////::AnimateWindow(_m_hWndMain, 800, AW_ACTIVATE  | AW_BLEND /*| AW_CENTER*/);
    }

    //��������� _m_hEdtText
    ::SetFocus(_m_hEdtText);

    //-------------------------------------
    //������� ���������
    MSG  msgMsg  = {0};
    BOOL bIsDone = FALSE;

    while (!bIsDone) {
        if (::PeekMessage(&msgMsg, NULL, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msgMsg.message) {
                bIsDone = TRUE;
            }
            else {
                ::TranslateMessage(&msgMsg);
                ::DispatchMessage (&msgMsg);
            }
        }
    }

    ::DestroyWindow(_m_hWndMain);
    bRes = ::UnregisterClass(xT("CxInputBox"), hInstance);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, CxInputBox::mrCancel);

    return static_cast<EModalResult>(msgMsg.wParam);
}
//---------------------------------------------------------------------------
std::string_t
CxInputBox::sGetText() {
    return _m_sText;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
LRESULT CALLBACK
CxInputBox::_ms_pWndProc(
    HWND   hWnd,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    if (WM_COMMAND == uiMsg) {
        CxInputBox *pibThis = (CxInputBox *)::GetWindowLong(hWnd, 0);
        /*DEBUG*/xASSERT_RET(NULL != pibThis, 0);

        switch (wParam) {
            case ID_btnOK: {
                INT iTextSize = ::GetWindowTextLength(pibThis->_m_hEdtText) + sizeof('\0');
                /*DEBUG*/

                pibThis->_m_sText.resize(iTextSize);

                UINT uiTextSize = ::GetDlgItemText(hWnd, ID_edtText, &pibThis->_m_sText.at(0), pibThis->_m_sText.size());

                //�������� ������ �� '\0'
                pibThis->_m_sText = std::string_t(pibThis->_m_sText, 0, uiTextSize);

                ::PostQuitMessage(mrOk);
                return 0;
            }
            case ID_btnCancel: {
                pibThis->_m_sText.clear();

                ::PostQuitMessage(mrCancel);
                return 0;
            }
        }

        return 0;
    }

    if (WM_CLOSE == uiMsg) {
        ::PostQuitMessage(mrCancel);

        return 0;
    }

    return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
