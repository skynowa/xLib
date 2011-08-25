/**
 * \file  CxWindowImpl.cpp
 * \brief windows
 */


#include <xLib/Gui/CxWindowImpl.h>

#include <xLib/Gui/xCommon.h>
#include <xLib/GUI/CxApplication.h>
#include <xLib/CxString.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxWindowImpl
CxWindowImpl::CxWindowImpl() :
    CxWindow       (),
    _m_bIsDestroyed(FALSE),
    m_vecpContainer()
{
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName = xCXWINDOW_CONTROL_CLASS + tString(_T("_")) + CxString::sCreateGUID();
    _m_ulStyle    = xCXFRAME_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx  = xCXFRAME_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft      = CW_USEDEFAULT;
    _m_iTop       = CW_USEDEFAULT;
    _m_iWidth     = xCXFRAME_DEFAULT_WIDTH;
    _m_iHeight    = xCXFRAME_DEFAULT_HEIGHT;

    _m_bIsControl = FALSE;
}
//---------------------------------------------------------------------------
//TODO: - ~CxWindowImpl
CxWindowImpl::~CxWindowImpl() {
    _m_bRes = _bUnregisterClass(_m_sClassName);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - bCreate
BOOL CxWindowImpl::bCreate(INT iID, HWND hParent, const tString &csText,
                            INT iLeft, INT iTop, INT iWidth, INT iHeight,
                            ULONG ulStyle, ULONG ulExStyle)
{
    //-------------------------------------
    //регистрируем класс окна
    WNDCLASSEX wcex = {0};

    wcex.cbSize         = sizeof(WNDCLASSEX);                                                                        //размер структуры в байтах
    wcex.style            = CS_HREDRAW | CS_VREDRAW;                                                                    //стиль класса окна
    wcex.lpfnWndProc    = xreinterpret_cast<WNDPROC>(_s_pWndProc);                                                    //указатель на функцию окна
    wcex.cbClsExtra        = 0;                                                                                        //дополнительная память в байтах для класса окна
    wcex.cbWndExtra        = 0;                                                                                        //дополнительная память в байтах для каждого окна этого класса
    wcex.hInstance        = CxApplication::hGetInstance();                                                            //дескриптор экземпляра приложения
    wcex.hIcon            = ::LoadIcon(CxApplication::hGetInstance(), static_cast<LPCTSTR>(NULL)/*siIconID*/);        //дескриптор пиктограммы приложения
    wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);                                                            //дескриптор курсора приложения
    wcex.hbrBackground    = reinterpret_cast<HBRUSH>( (COLOR_WINDOW + reinterpret_cast<HBRUSH>(3)/*siBGColor*/) );    //дескриптор кисти для закраски фона окна
    wcex.lpszMenuName    = reinterpret_cast<LPCTSTR>(iID);                                                            //указатель на строку  с именем меню окна
    wcex.lpszClassName    = _m_sClassName.c_str();                                                                    //указатель на строку  с именем класса окна
    wcex.hIconSm        = ::LoadIcon(CxApplication::hGetInstance(), static_cast<LPCTSTR>(0)/*siIconSmID*/);            //дескриптор малой пиктограммы

    _m_bRes = _bRegisterClass(&wcex);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //создаем окно
    _m_bRes = CxWindow::bCreate(iID, hParent, _m_sClassName, csText,
                             iLeft, iTop, iWidth, iHeight,
                             _m_ulStyle | ulStyle,
                             /*WS_EX_CLIENTEDGE | WS_EX_APPWINDOW*/_m_ulStyleEx | ulExStyle,
                             (LPVOID)this);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //если это дочернее окно, то дизэйблим родительское
    ////if (NULL != _m_hParentWnd) {
    ////    bRes = ::EnableWindow(_m_hParentWnd, FALSE);
    ////      /*DEBUG*/xASSERT_RET(0 == bRes, FALSE);
    ////}

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCreateRes
BOOL CxWindowImpl::bCreateRes(INT iID, HWND hParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,         FALSE);
    /*DEBUG*///xASSERT_RET(NULL != hParent, FALSE);

    _m_bRes = CxWindowImpl::bCreate(iID, hParent,
                                    CxResources::sGetText    (iID),
                                    CxResources::iGetLeft    (iID), CxResources::iGetTop   (iID),
                                    CxResources::iGetWidth   (iID), CxResources::iGetHeight(iID),
                                    CxResources::ulGetStyle  (iID),
                                    CxResources::ulGetStyleEx(iID));
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bShowModal
BOOL CxWindowImpl::bShowModal() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    MSG msgMsg = {0};

    _m_bRes = bShow(SW_SHOW);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    for (_m_bIsDestroyed = FALSE; !_m_bIsDestroyed && ::GetMessage(&msgMsg, NULL, 0, 0); ) {
        ::TranslateMessage(&msgMsg);
        ::DispatchMessage (&msgMsg);
    }

    return _m_bIsDestroyed;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    сообщения
*
*****************************************************************************/


/****************************************************************************
*    события
*
*****************************************************************************/




//---------------------------------------------------------------------------
//TODO: Карта сообщений
xBEGIN_MSG_MAP(CxWindowImpl)
    ////xMSG(WM_CREATE,  vOnCreate)
    ////xMSG(WM_PAINT,   vOnPaint);
    ////xMSG(WM_COMMAND, vOnCommand);
    ////xMSG(WM_NOTIFY,  vOnNotify);
    ////xMSG(WM_SIZE,    vOnSize);
    ////xMSG(WM_CLOSE,   vOnClose);
    ////xMSG(WM_DESTROY, vOnDestroy);

    xMSG(WM_NULL                        , vOnNull)
    xMSG(WM_CREATE                      , vOnCreate)
    xMSG(WM_DESTROY                     , vOnDestroy)
    xMSG(WM_MOVE                        , vOnMove)
    xMSG(WM_SIZE                        , vOnSize)
    xMSG(WM_ACTIVATE                    , vOnActivate)
    xMSG(WM_SETFOCUS                    , vOnSetFocus)
    xMSG(WM_KILLFOCUS                   , vOnKillFocus)
    xMSG(WM_ENABLE                      , vOnEnable)
    xMSG(WM_SETREDRAW                   , vOnSetreDraw)
    xMSG(WM_SETTEXT                     , vOnSetText)
    xMSG(WM_GETTEXT                     , vOnGetText)
    xMSG(WM_GETTEXTLENGTH               , vOnGetTextlength)
    xMSG(WM_PAINT                       , vOnPaint)
    xMSG(WM_CLOSE                       , vOnClose)

#ifndef _WIN32_WCE
    xMSG(WM_QUERYENDSESSION             , vOnQueryEndSession)
    xMSG(WM_QUERYOPEN                   , vOnQueryOpen)
    xMSG(WM_ENDSESSION                  , vOnEndSession)
#endif

    xMSG(WM_QUIT                        , vOnQuit)
    ////xMSG(WM_ERASEBKGND                  , vOnEraseBkGnd)
    xMSG(WM_SYSCOLORCHANGE              , vOnSysColorChange)
    xMSG(WM_SHOWWINDOW                  , vOnShowWindow)
    xMSG(WM_WININICHANGE                , vOnWininiChange)

#if(WINVER >= 0x0400)
    xMSG(WM_SETTINGCHANGE               , vOnSettingChange)
#endif /* WINVER >= 0x0400 */

    xMSG(WM_DEVMODECHANGE               , vOnDevModeChange)
    xMSG(WM_ACTIVATEAPP                 , vOnActivateApp)
    xMSG(WM_FONTCHANGE                  , vOnFontChange)
    xMSG(WM_TIMECHANGE                  , vOnTimeChange)
    xMSG(WM_CANCELMODE                  , vOnCancelMode)
    xMSG(WM_SETCURSOR                   , vOnSetCursor)
    xMSG(WM_MOUSEACTIVATE               , vOnMouseActivate)
    xMSG(WM_CHILDACTIVATE               , vOnChildActivate)
    xMSG(WM_QUEUESYNC                   , vOnQueueSync)
    xMSG(WM_GETMINMAXINFO               , vOnGetMinMaxInfo)
    xMSG(WM_PAINTICON                   , vOnPaintIcon)
    xMSG(WM_ICONERASEBKGND              , vOnIconEraseBkGnd)
    xMSG(WM_NEXTDLGCTL                  , vOnNextDlgCtl)
    xMSG(WM_SPOOLERSTATUS               , vOnSpoolerStatus)
    xMSG(WM_DRAWITEM                    , vOnDrawItem)
    xMSG(WM_MEASUREITEM                 , vOnMeasureItem)
    xMSG(WM_DELETEITEM                  , vOnDeleteItem)
    xMSG(WM_VKEYTOITEM                  , vOnVKeyToItem)
    xMSG(WM_CHARTOITEM                  , vOnCharToItem)
    xMSG(WM_SETFONT                     , vOnSetFont)
    xMSG(WM_GETFONT                     , vOnGetFont)
    xMSG(WM_SETHOTKEY                   , vOnSetHotKey)
    xMSG(WM_GETHOTKEY                   , vOnGetHotKey)
    xMSG(WM_QUERYDRAGICON               , vOnQueryDragIcon)
    xMSG(WM_COMPAREITEM                 , vOnCompareItem)

#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
    xMSG(WM_GETOBJECT                   , vOnGetObject)
#endif
#endif /* WINVER >= 0x0500 */

    xMSG(WM_COMPACTING                  , vOnCompacting)
    xMSG(WM_COMMNOTIFY                  , vOnCommNotify)  /* no longer suported */
    xMSG(WM_WINDOWPOSCHANGING           , vOnWindowPosChanging)
    xMSG(WM_WINDOWPOSCHANGED            , vOnWindowPosChanged)
    xMSG(WM_POWER                       , vOnPower)
    xMSG(WM_COPYDATA                    , vOnCopyData)
    xMSG(WM_CANCELJOURNAL               , vOnCancelJournal)

#if(WINVER >= 0x0400)
    xMSG(WM_NOTIFY                      , vOnNotify)
    xMSG(WM_INPUTLANGCHANGEREQUEST      , vOnInputLangChangeRequest)
    xMSG(WM_INPUTLANGCHANGE             , vOnInputLangChange)
    xMSG(WM_TCARD                       , vOnTCard)
    xMSG(WM_HELP                        , vOnHelp)
    xMSG(WM_USERCHANGED                 , vOnUserChanged)
    xMSG(WM_NOTIFYFORMAT                , vOnNotifyFormat)
    xMSG(WM_CONTEXTMENU                 , vOnContextMenu)
    xMSG(WM_STYLECHANGING               , vOnStyleChanging)
    xMSG(WM_STYLECHANGED                , vOnStyleChanged)
    xMSG(WM_DISPLAYCHANGE               , vOnDisplayChange)
    xMSG(WM_GETICON                     , vOnGetIcon)
    xMSG(WM_SETICON                     , vOnSetIcon)
#endif /* WINVER >= 0x0400 */

    ////xMSG(WM_NCCREATE                    , vOnNcCreate)
    ////xMSG(WM_NCDESTROY                   , vOnNcDestroy)
    ////xMSG(WM_NCCALCSIZE                  , vOnNcCalcSize)
    ////xMSG(WM_NCHITTEST                   , vOnNcHitTest)
    ////xMSG(WM_NCPAINT                     , vOnNcPaint)
    ////xMSG(WM_NCACTIVATE                  , vOnNcActivate)
    xMSG(WM_GETDLGCODE                  , vOnGetDlgCode)

#ifndef _WIN32_WCE
    xMSG(WM_SYNCPAINT                   , vOnSyncPaint)
#endif

    ////xMSG(WM_NCMOUSEMOVE                 , vOnNcMouseMove)
    ////xMSG(WM_NCLBUTTONDOWN               , vOnNcLButtonDown)
    ////xMSG(WM_NCLBUTTONUP                 , vOnNcLButtonUp)
    ////xMSG(WM_NCLBUTTONDBLCLK             , vOnNcLButtonDblClk)
    ////xMSG(WM_NCRBUTTONDOWN               , vOnNcRButtonDown)
    ////xMSG(WM_NCRBUTTONUP                 , vOnNcRButtonUp)
    ////xMSG(WM_NCRBUTTONDBLCLK             , vOnNcRButtonDblClk)
    ////xMSG(WM_NCMBUTTONDOWN               , vOnNcMButtonDown)
    ////xMSG(WM_NCMBUTTONUP                 , vOnNcMButtonUp)
    ////xMSG(WM_NCMBUTTONDBLCLK             , vOnNcMButtonDblClk)

#if(_WIN32_WINNT >= 0x0500)
    ////xMSG(WM_NCxButtonDOWN               , vOnNCxButtonDown)
    ////xMSG(WM_NCxButtonUP                 , vOnNCxButtonUp)
    ////xMSG(WM_NCxButtonDBLCLK             , vOnNCxButtonDblClk)
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_INPUT_DEVICE_CHANGE         , vOnInputDeviceChange)
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_INPUT                       , vOnInput)
#endif /* _WIN32_WINNT >= 0x0501 */

    ////xMSG(WM_KEYFIRST                    , vOnKeyFirst)
    ////xMSG(WM_KEYDOWN                     , vOnKeyDown)
    ////xMSG(WM_KEYUP                       , vOnKeyUp)
    ////xMSG(WM_CHAR                        , vOnChar)
    ////xMSG(WM_DEADCHAR                    , vOnDeadChar)
    ////xMSG(WM_SYSKEYDOWN                  , vOnSysKeyDown)
    ////xMSG(WM_SYSKEYUP                    , vOnSysKeyUp)
    ////xMSG(WM_SYSCHAR                     , vOnSysChar)
    ////xMSG(WM_SYSDEADCHAR                 , vOnSysDeadChar)

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_UNICHAR                     , vOnUniChar)
    xMSG(WM_KEYLAST                     , vOnKeyLast)
#else
    xMSG(WM_KEYLAST                     , vOnKeyLast)
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
    xMSG(WM_IME_STARTCOMPOSITION        , vOnImeStartComposition)
    xMSG(WM_IME_ENDCOMPOSITION          , vOnImeEndComposition)
    xMSG(WM_IME_COMPOSITION             , vOnImeComposition)
    xMSG(WM_IME_KEYLAST                 , vOnImeKeyLast)
#endif /* WINVER >= 0x0400 */

    xMSG(WM_INITDIALOG                  , vOnInitdialog)
    xMSG(WM_COMMAND                     , vOnCommand)
    ////xMSG(WM_SYSCOMMAND                  , vOnSysCommand)
    xMSG(WM_TIMER                       , vOnTimer)
    xMSG(WM_HSCROLL                     , vOnHScroll)
    xMSG(WM_VSCROLL                     , vOnVScroll)
    xMSG(WM_INITMENU                    , vOnInitMenu)
    xMSG(WM_INITMENUPOPUP               , vOnInitMenuPopup)
    xMSG(WM_MENUSELECT                  , vOnMenuSelect)
    xMSG(WM_MENUCHAR                    , vOnMenuChar)
    xMSG(WM_ENTERIDLE                   , vOnEnterIdle)

#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
    xMSG(WM_MENURBUTTONUP               , vOnMenuRButtonUp)
    xMSG(WM_MENUDRAG                    , vOnMenuDrag)
    xMSG(WM_MENUGETOBJECT               , vOnMenuGetObject)
    xMSG(WM_UNINITMENUPOPUP             , vOnUnInitMenuPopup)
    xMSG(WM_MENUCOMMAND                 , vOnMenuCommand)

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
    xMSG(WM_CHANGEUISTATE               , vOnChangeUiState)
    xMSG(WM_UPDATEUISTATE               , vOnUpdateUiState)
    xMSG(WM_QUERYUISTATE                , vOnQueryUiState)
#endif /* _WIN32_WINNT >= 0x0500 */
#endif

#endif
#endif /* WINVER >= 0x0500 */

    xMSG(WM_CTLCOLORMSGBOX              , vOnCtlColorMsgBox)
    xMSG(WM_CTLCOLOREDIT                , vOnCtlColorEdit)
    xMSG(WM_CTLCOLORLISTBOX             , vOnCtlColorListbox)
    xMSG(WM_CTLCOLORBTN                 , vOnCtlColorBtn)
    xMSG(WM_CTLCOLORDLG                 , vOnCtlColorDlg)
    xMSG(WM_CTLCOLORSCROLLBAR           , vOnCtlColorScrollBar)
    xMSG(WM_CTLCOLORSTATIC              , vOnCtlColorStatic)
    xMSG(WM_MOUSEFIRST                  , vOnMouseFirst)
    xMSG(WM_MOUSEMOVE                   , vOnMouseMove)
    xMSG(WM_LBUTTONDOWN                 , vOnLButtonDown)
    xMSG(WM_LBUTTONUP                   , vOnLButtonUp)
    xMSG(WM_LBUTTONDBLCLK               , vOnLButtonDblClk)
    xMSG(WM_RBUTTONDOWN                 , vOnRButtonDown)
    xMSG(WM_RBUTTONUP                   , vOnRButtonUp)
    xMSG(WM_RBUTTONDBLCLK               , vOnRButtonDblClk)
    xMSG(WM_MBUTTONDOWN                 , vOnMButtonDown)
    xMSG(WM_MBUTTONUP                   , vOnMButtonUp)
    xMSG(WM_MBUTTONDBLCLK               , vOnMButtonDblClk)

#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
    xMSG(WM_MOUSEWHEEL                  , vOnMouseWheel)
#endif

#if (_WIN32_WINNT >= 0x0500)
    xMSG(WM_XBUTTONDOWN                 , vOnXButtonDown)
    xMSG(WM_XBUTTONUP                   , vOnXButtonUp)
    xMSG(WM_XBUTTONDBLCLK               , vOnXButtonDblClk)
#endif

#if (_WIN32_WINNT >= 0x0600)
    xMSG(WM_MOUSEHWHEEL                 , vOnMouseHWheel)
#endif

    xMSG(WM_MOUSELAST                   , vOnMouseLast)
    xMSG(WM_PARENTNOTIFY                , vOnParentNotify)
    xMSG(WM_ENTERMENULOOP               , vOnEnterMenuLoop)
    xMSG(WM_EXITMENULOOP                , vOnExitMenuLoop)

#if(WINVER >= 0x0400)
    xMSG(WM_NEXTMENU                    , vOnNextMenu)
    xMSG(WM_SIZING                      , vOnSizing)
    xMSG(WM_CAPTURECHANGED              , vOnCaptureChanged)
    xMSG(WM_MOVING                      , vOnMoving)
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
    xMSG(WM_POWERBROADCAST              , vOnPowerBroadcast)
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
    xMSG(WM_DEVICECHANGE                , vOnDeviceChange)
#endif /* WINVER >= 0x0400 */

    xMSG(WM_MDICREATE                   , vOnMdiCreate)
    xMSG(WM_MDIDESTROY                  , vOnMdiDestroy)
    xMSG(WM_MDIACTIVATE                 , vOnMdiActivate)
    xMSG(WM_MDIRESTORE                  , vOnMdiRestore)
    xMSG(WM_MDINEXT                     , vOnMdiNext)
    xMSG(WM_MDIMAXIMIZE                 , vOnMdiMaximize)
    xMSG(WM_MDITILE                     , vOnMdiTile)
    xMSG(WM_MDICASCADE                  , vOnMdiCascade)
    xMSG(WM_MDIICONARRANGE              , vOnMdiIconArrange)
    xMSG(WM_MDIGETACTIVE                , vOnMdiGetActive)
    xMSG(WM_MDISETMENU                  , vOnMdiSetMenu)
    xMSG(WM_ENTERSIZEMOVE               , vOnEnterSizeMove)
    xMSG(WM_EXITSIZEMOVE                , vOnExitSizeMove)
    xMSG(WM_DROPFILES                   , vOnDropFiles)
    xMSG(WM_MDIREFRESHMENU              , vOnMdiRefreshMenu)

#if(WINVER >= 0x0400)
    xMSG(WM_IME_SETCONTEXT              , vOnImeSetContext)
    xMSG(WM_IME_NOTIFY                  , vOnImeNotify)
    xMSG(WM_IME_CONTROL                 , vOnImeControl)
    xMSG(WM_IME_COMPOSITIONFULL         , vOnImeCompositionFull)
    xMSG(WM_IME_SELECT                  , vOnImeSelect)
    xMSG(WM_IME_CHAR                    , vOnImeChar)
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
    xMSG(WM_IME_REQUEST                 , vOnImeRequest)
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
    xMSG(WM_IME_KEYDOWN                 , vOnImeKeyDown)
    xMSG(WM_IME_KEYUP                   , vOnImeKeyUp)
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
    xMSG(WM_MOUSEHOVER                  , vOnMouseHover)
    xMSG(WM_MOUSELEAVE                  , vOnMouseLeave)
#endif

#if(WINVER >= 0x0500)
    xMSG(WM_NCMOUSEHOVER                , vOnNcMouseHover)
    xMSG(WM_NCMOUSELEAVE                , vOnNcMouseLeave)
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_WTSSESSION_CHANGE           , vOnWtsSessionChange)
    xMSG(WM_TABLET_FIRST                , vOnTabletFirst)
    xMSG(WM_TABLET_LAST                 , vOnTabletLast)
#endif /* _WIN32_WINNT >= 0x0501 */

    xMSG(WM_CUT                         , vOnCut)
    xMSG(WM_COPY                        , vOnCopy)
    xMSG(WM_PASTE                       , vOnPaste)
    xMSG(WM_CLEAR                       , vOnClear)
    xMSG(WM_UNDO                        , vOnUndo)
    xMSG(WM_RENDERFORMAT                , vOnRenderFormat)
    xMSG(WM_RENDERALLFORMATS            , vOnRenderAllFormats)
    xMSG(WM_DESTROYCLIPBOARD            , vOnDestroyClipboard)
    xMSG(WM_DRAWCLIPBOARD               , vOnDrawClipboard)
    xMSG(WM_PAINTCLIPBOARD              , vOnPaintClipboard)
    xMSG(WM_VSCROLLCLIPBOARD            , vOnVScrollClipboard)
    xMSG(WM_SIZECLIPBOARD               , vOnSizeClipboard)
    xMSG(WM_ASKCBFORMATNAME             , vOnAskCBFormatName)
    xMSG(WM_CHANGECBCHAIN               , vOnChangeCBChain)
    xMSG(WM_HSCROLLCLIPBOARD            , vOnHScrollClipboard)
    xMSG(WM_QUERYNEWPALETTE             , vOnQueryNewPalette)
    xMSG(WM_PALETTEISCHANGING           , vOnPaletteIsChanging)
    xMSG(WM_PALETTECHANGED              , vOnPaletteChanged)
    xMSG(WM_HOTKEY                      , vOnHotKey)

#if(WINVER >= 0x0400)
    xMSG(WM_PRINT                       , vOnPrint)
    xMSG(WM_PRINTCLIENT                 , vOnPrintClient)
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
    xMSG(WM_APPCOMMAND                  , vOnAppCommand)
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_THEMECHANGED                , vOnThemeChanged)
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
    xMSG(WM_CLIPBOARDUPDATE             , vOnClipboardUpdate)
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
    xMSG(WM_DWMCOMPOSITIONCHANGED       , vOnDwmCompositionChanged)
    xMSG(WM_DWMNCRENDERINGCHANGED       , vOnDwmNcRenderingChanged)
    xMSG(WM_DWMCOLORIZATIONCOLORCHANGED , vOnDwmColorizationColorChanged)
    xMSG(WM_DWMWINDOWMAXIMIZEDCHANGE    , vOnDwmWindowMaximizedChange)
#endif /* _WIN32_WINNT >= 0x0600 */

#if(WINVER >= 0x0600)
    xMSG(WM_GETTITLEBARINFOEX           , vOnGetTitleBarInfoEx)
#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0400)
    xMSG(WM_HANDHELDFIRST               , vOnHandHeldFirst)
    xMSG(WM_HANDHELDLAST                , vOnHandHeldFast)
    xMSG(WM_AFXFIRST                    , vOnAfxFirst)
    xMSG(WM_AFXLAST                     , vOnAfxLast)
#endif /* WINVER >= 0x0400 */

    xMSG(WM_PENWINFIRST                 , vOnPenWinFirst)
    xMSG(WM_PENWINLAST                  , vOnPenWinLast)

#if(WINVER >= 0x0400)
    xMSG(WM_APP                         , vOnApp)
#endif /* WINVER >= 0x0400 */

    xMSG(WM_USER                        , vOnUser)
xEND_MSG_MAP(CxWindow)
//---------------------------------------------------------------------------
//TODO: - vOnNull
/*virtual*/
VOID CxWindowImpl::vOnNull                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCreate
/*virtual*/
VOID CxWindowImpl::vOnCreate                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDestroy
/*virtual*/
VOID CxWindowImpl::vOnDestroy                      (WPARAM wParam, LPARAM lParam) {
    LOG();

    _m_bIsDestroyed = TRUE;

    if (NULL == _m_hParentWnd) {    //TODO: а если у главного окна есть родитель?
        CxApplication::vTerminate();

        return;
    }

    HWND hRes = NULL;

    /*DEBUG*/xASSERT_DO(NULL != _m_hParentWnd, return);

    _m_bRes = ::EnableWindow(_m_hParentWnd, TRUE);
    /*DEBUG*///--xASSERT_DO(FALSE != _m_bRes, return);

    hRes = ::SetActiveWindow(_m_hParentWnd);
    /*DEBUG*///--xASSERT_DO(NULL != hRes, return);

    _m_bRes = ::UpdateWindow(_m_hParentWnd);
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

    _m_bRes = bClose();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - vOnMove
/*virtual*/
VOID CxWindowImpl::vOnMove                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSize
/*virtual*/
VOID CxWindowImpl::vOnSize                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnActivate
/*virtual*/
VOID CxWindowImpl::vOnActivate                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetFocus
/*virtual*/
VOID CxWindowImpl::vOnSetFocus                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnKillFocus
/*virtual*/
VOID CxWindowImpl::vOnKillFocus                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEnable
/*virtual*/
VOID CxWindowImpl::vOnEnable                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetreDraw
/*virtual*/
VOID CxWindowImpl::vOnSetreDraw                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetText
/*virtual*/
VOID CxWindowImpl::vOnSetText                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetText
/*virtual*/
VOID CxWindowImpl::vOnGetText                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetTextlength
/*virtual*/
VOID CxWindowImpl::vOnGetTextlength                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaint
/*virtual*/
VOID CxWindowImpl::vOnPaint                        (WPARAM wParam, LPARAM lParam) {
    //LOG();

    PAINTSTRUCT ps  = {0};
    HDC         hdc = NULL;

    hdc = ::BeginPaint(_m_hWnd, &ps);
    //TODO: Add any drawing code here...
    ::EndPaint(_m_hWnd, &ps);
}
//---------------------------------------------------------------------------
//TODO: - vOnClose
/*virtual*/
VOID CxWindowImpl::vOnClose                        (WPARAM wParam, LPARAM lParam) {
    LOG();

    bDestroy();
}

//---------------------------------------------------------------------------
#ifndef _WIN32_WCE
//---------------------------------------------------------------------------
//TODO: - vOnQueryEndSession
/*virtual*/
VOID CxWindowImpl::vOnQueryEndSession              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnQueryOpen
/*virtual*/
VOID CxWindowImpl::vOnQueryOpen                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEndSession
/*virtual*/
VOID CxWindowImpl::vOnEndSession                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
//TODO: - vOnQuit
/*virtual*/
VOID CxWindowImpl::vOnQuit                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEraseBkGnd
/*virtual*/
VOID CxWindowImpl::vOnEraseBkGnd                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSysColorChange
/*virtual*/
VOID CxWindowImpl::vOnSysColorChange               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnShowWindow
/*virtual*/
VOID CxWindowImpl::vOnShowWindow                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnWininiChange
/*virtual*/
VOID CxWindowImpl::vOnWininiChange                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnSettingChange
/*virtual*/
VOID CxWindowImpl::vOnSettingChange                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnDevModeChange
/*virtual*/
VOID CxWindowImpl::vOnDevModeChange                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnActivateApp
/*virtual*/
VOID CxWindowImpl::vOnActivateApp                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnFontChange
/*virtual*/
VOID CxWindowImpl::vOnFontChange                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnTimeChange
/*virtual*/
VOID CxWindowImpl::vOnTimeChange                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCancelMode
/*virtual*/
VOID CxWindowImpl::vOnCancelMode                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetCursor
/*virtual*/
VOID CxWindowImpl::vOnSetCursor                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMouseActivate
/*virtual*/
VOID CxWindowImpl::vOnMouseActivate                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnChildActivate
/*virtual*/
VOID CxWindowImpl::vOnChildActivate                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnQueueSync
/*virtual*/
VOID CxWindowImpl::vOnQueueSync                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetMinMaxInfo
/*virtual*/
VOID CxWindowImpl::vOnGetMinMaxInfo                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaintIcon
/*virtual*/
VOID CxWindowImpl::vOnPaintIcon                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnIconEraseBkGnd
/*virtual*/
VOID CxWindowImpl::vOnIconEraseBkGnd               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNextDlgCtl
/*virtual*/
VOID CxWindowImpl::vOnNextDlgCtl                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSpoolerStatus
/*virtual*/
VOID CxWindowImpl::vOnSpoolerStatus                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDrawItem
/*virtual*/
VOID CxWindowImpl::vOnDrawItem                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMeasureItem
/*virtual*/
VOID CxWindowImpl::vOnMeasureItem                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDeleteItem
/*virtual*/
VOID CxWindowImpl::vOnDeleteItem                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnVKeyToItem
/*virtual*/
VOID CxWindowImpl::vOnVKeyToItem                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnXXXXXXXXX
/*virtual*/
VOID CxWindowImpl::vOnCharToItem                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetFont
/*virtual*/
VOID CxWindowImpl::vOnSetFont                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetFont
/*virtual*/
VOID CxWindowImpl::vOnGetFont                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetHotKey
/*virtual*/
VOID CxWindowImpl::vOnSetHotKey                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetHotKey
/*virtual*/
VOID CxWindowImpl::vOnGetHotKey                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnQueryDragIcon
/*virtual*/
VOID CxWindowImpl::vOnQueryDragIcon                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCompareItem
/*virtual*/
VOID CxWindowImpl::vOnCompareItem                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
//---------------------------------------------------------------------------
//TODO: - vOnGetObject
/*virtual*/
VOID CxWindowImpl::vOnGetObject                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif
#endif /* WINVER >= 0x0500 */

//---------------------------------------------------------------------------
//TODO: - vOnCompacting
/*virtual*/
VOID CxWindowImpl::vOnCompacting                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCommNotify
/*virtual*/
VOID CxWindowImpl::vOnCommNotify                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}  /* no longer suported */
//---------------------------------------------------------------------------
//TODO: - vOnWindowPosChanging
/*virtual*/
VOID CxWindowImpl::vOnWindowPosChanging            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnWindowPosChanged
/*virtual*/
VOID CxWindowImpl::vOnWindowPosChanged             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPower
/*virtual*/
VOID CxWindowImpl::vOnPower                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCopyData
/*virtual*/
VOID CxWindowImpl::vOnCopyData                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCancelJournal
/*virtual*/
VOID CxWindowImpl::vOnCancelJournal                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnNotify
/*virtual*/
VOID CxWindowImpl::vOnNotify                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnInputLangChangeRequest
/*virtual*/
VOID CxWindowImpl::vOnInputLangChangeRequest       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnInputLangChange
/*virtual*/
VOID CxWindowImpl::vOnInputLangChange              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnTCard
/*virtual*/
VOID CxWindowImpl::vOnTCard                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnHelp
/*virtual*/
VOID CxWindowImpl::vOnHelp                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnUserChanged
/*virtual*/
VOID CxWindowImpl::vOnUserChanged                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNotifyFormat
/*virtual*/
VOID CxWindowImpl::vOnNotifyFormat                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnContextMenu
/*virtual*/
VOID CxWindowImpl::vOnContextMenu                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnStyleChanging
/*virtual*/
VOID CxWindowImpl::vOnStyleChanging                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnStyleChanged
/*virtual*/
VOID CxWindowImpl::vOnStyleChanged                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDisplayChange
/*virtual*/
VOID CxWindowImpl::vOnDisplayChange                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetIcon
/*virtual*/
VOID CxWindowImpl::vOnGetIcon                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSetIcon
/*virtual*/
VOID CxWindowImpl::vOnSetIcon                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnNcCreate
/*virtual*/
VOID CxWindowImpl::vOnNcCreate                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcDestroy
/*virtual*/
VOID CxWindowImpl::vOnNcDestroy                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcCalcSize
/*virtual*/
VOID CxWindowImpl::vOnNcCalcSize                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcHitTest
/*virtual*/
VOID CxWindowImpl::vOnNcHitTest                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcPaint
/*virtual*/
VOID CxWindowImpl::vOnNcPaint                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcActivate
/*virtual*/
VOID CxWindowImpl::vOnNcActivate                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnGetDlgCode
/*virtual*/
VOID CxWindowImpl::vOnGetDlgCode                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}

#ifndef _WIN32_WCE
//---------------------------------------------------------------------------
//TODO: - vOnSyncPaint
/*virtual*/
VOID CxWindowImpl::vOnSyncPaint                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
//TODO: - vOnNcMouseMove
/*virtual*/
VOID CxWindowImpl::vOnNcMouseMove                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcLButtonDown
/*virtual*/
VOID CxWindowImpl::vOnNcLButtonDown               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcLButtonUp
/*virtual*/
VOID CxWindowImpl::vOnNcLButtonUp                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcLButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnNcLButtonDblClk              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcRButtonDown
/*virtual*/
VOID CxWindowImpl::vOnNcRButtonDown                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcRButtonUp
/*virtual*/
VOID CxWindowImpl::vOnNcRButtonUp                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcRButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnNcRButtonDblClk              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcMButtonDown
/*virtual*/
VOID CxWindowImpl::vOnNcMButtonDown                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcMButtonUp
/*virtual*/
VOID CxWindowImpl::vOnNcMButtonUp                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcMButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnNcMButtonDblClk              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(_WIN32_WINNT >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnNCxButtonDown
/*virtual*/
VOID CxWindowImpl::vOnNCxButtonDown                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNCxButtonUp
/*virtual*/
VOID CxWindowImpl::vOnNCxButtonUp                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNCxButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnNCxButtonDblClk              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnInputDeviceChange
/*virtual*/
VOID CxWindowImpl::vOnInputDeviceChange            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnInput
/*virtual*/
VOID CxWindowImpl::vOnInput                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

//---------------------------------------------------------------------------
//TODO: - vOnKeyFirst
/*virtual*/
VOID CxWindowImpl::vOnKeyFirst                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnKeyDown
/*virtual*/
VOID CxWindowImpl::vOnKeyDown                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnKeyUp
/*virtual*/
VOID CxWindowImpl::vOnKeyUp                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnChar
/*virtual*/
VOID CxWindowImpl::vOnChar                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDeadChar
/*virtual*/
VOID CxWindowImpl::vOnDeadChar                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSysKeyDown
/*virtual*/
VOID CxWindowImpl::vOnSysKeyDown                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSysKeyUp
/*virtual*/
VOID CxWindowImpl::vOnSysKeyUp                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSysChar
/*virtual*/
VOID CxWindowImpl::vOnSysChar                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSysDeadChar
/*virtual*/
VOID CxWindowImpl::vOnSysDeadChar                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnUniChar
/*virtual*/
VOID CxWindowImpl::vOnUniChar                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnKeyLast
/*virtual*/
VOID CxWindowImpl::vOnKeyLast                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
#else
//---------------------------------------------------------------------------
//TODO: - vOnKeyLast
/*virtual*/
VOID CxWindowImpl::vOnKeyLast                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnImeStartComposition
/*virtual*/
VOID CxWindowImpl::vOnImeStartComposition          (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeEndComposition
/*virtual*/
VOID CxWindowImpl::vOnImeEndComposition            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeComposition
/*virtual*/
VOID CxWindowImpl::vOnImeComposition               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeKeyLast
/*virtual*/
VOID CxWindowImpl::vOnImeKeyLast                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnInitdialog
/*virtual*/
VOID CxWindowImpl::vOnInitdialog                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCommand
/*virtual*/
VOID CxWindowImpl::vOnCommand                      (WPARAM wParam, LPARAM lParam) {
    LOG();

    for (UINT i = 0; i < m_vecpContainer.uiGetSize(); ++ i) {
        INT iId1 = LOWORD(wParam);
        INT iId2 = m_vecpContainer.pwndGet(i)->iGetID();

        if (iId1 != iId2) {
            continue;
        }

        //-------------------------------------
        //уведомления для CxStatic
        if (xCXSTATIC_CONTROL_CLASS == m_vecpContainer.pwndGet(i)->sGetClassName()) {
            switch (HIWORD(wParam))    {
                case STN_CLICKED:    iMsgBox(_T("STN_CLICKED"));    break;
                case STN_DBLCLK:    iMsgBox(_T("STN_DBLCLK"));    break;
                case STN_DISABLE:    iMsgBox(_T("STN_DISABLE"));    break;
                case STN_ENABLE:    iMsgBox(_T("STN_ENABLE"));    break;
            }

            return;
        }

        //-------------------------------------
        //уведомления для CxButton, CxGroupBox, CxCheckBox, CxRadioButton
        if (xCXBUTTON_CONTROL_CLASS == m_vecpContainer.pwndGet(i)->sGetClassName()) {
            switch (HIWORD(wParam))    {
                case BN_CLICKED:    m_vecpContainer.pwndGet(i)->vOnClick    ();    break;
                case BN_DBLCLK:        m_vecpContainer.pwndGet(i)->vOnDbClick  ();    break;
                case BN_KILLFOCUS:    m_vecpContainer.pwndGet(i)->vOnKillFocus();    break;
                case BN_SETFOCUS:    m_vecpContainer.pwndGet(i)->vOnSetFocus ();    break;
            }

            return;
        }
    } //for
}
//---------------------------------------------------------------------------
//TODO: - vOnSysCommand
/*virtual*/
VOID CxWindowImpl::vOnSysCommand                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnTimer
/*virtual*/
VOID CxWindowImpl::vOnTimer                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnHScroll
/*virtual*/
VOID CxWindowImpl::vOnHScroll                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnVScroll
/*virtual*/
VOID CxWindowImpl::vOnVScroll                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnInitMenu
/*virtual*/
VOID CxWindowImpl::vOnInitMenu                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnInitMenuPopup
/*virtual*/
VOID CxWindowImpl::vOnInitMenuPopup                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMenuSelect
/*virtual*/
VOID CxWindowImpl::vOnMenuSelect                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMenuChar
/*virtual*/
VOID CxWindowImpl::vOnMenuChar                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEnterIdle
/*virtual*/
VOID CxWindowImpl::vOnEnterIdle                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
//---------------------------------------------------------------------------
//TODO: - vOnMenuRButtonUp
/*virtual*/
VOID CxWindowImpl::vOnMenuRButtonUp                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMenuDrag
/*virtual*/
VOID CxWindowImpl::vOnMenuDrag                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMenuGetObject
/*virtual*/
VOID CxWindowImpl::vOnMenuGetObject                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnUnInitMenuPopup
/*virtual*/
VOID CxWindowImpl::vOnUnInitMenuPopup              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMenuCommand
/*virtual*/
VOID CxWindowImpl::vOnMenuCommand                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnChangeUiState
/*virtual*/
VOID CxWindowImpl::vOnChangeUiState                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnUpdateUiState
/*virtual*/
VOID CxWindowImpl::vOnUpdateUiState                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnQueryUiState
/*virtual*/
VOID CxWindowImpl::vOnQueryUiState                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0500 */
#endif

#endif
#endif /* WINVER >= 0x0500 */

//---------------------------------------------------------------------------
//TODO: - vOnCtlColorMsgBox
/*virtual*/
VOID CxWindowImpl::vOnCtlColorMsgBox               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorEdit
/*virtual*/
VOID CxWindowImpl::vOnCtlColorEdit                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorListbox
/*virtual*/
VOID CxWindowImpl::vOnCtlColorListbox              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorBtn
/*virtual*/
VOID CxWindowImpl::vOnCtlColorBtn                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorDlg
/*virtual*/
VOID CxWindowImpl::vOnCtlColorDlg                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorScrollBar
/*virtual*/
VOID CxWindowImpl::vOnCtlColorScrollBar            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCtlColorStatic
/*virtual*/
VOID CxWindowImpl::vOnCtlColorStatic               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMouseFirst
/*virtual*/
VOID CxWindowImpl::vOnMouseFirst                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMouseMove
/*virtual*/
VOID CxWindowImpl::vOnMouseMove                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnLButtonDown
/*virtual*/
VOID CxWindowImpl::vOnLButtonDown                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnLButtonUp
/*virtual*/
VOID CxWindowImpl::vOnLButtonUp                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnLButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnLButtonDblClk                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnRButtonDown
/*virtual*/
VOID CxWindowImpl::vOnRButtonDown                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnRButtonUp
/*virtual*/
VOID CxWindowImpl::vOnRButtonUp                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnRButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnRButtonDblClk                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMButtonDown
/*virtual*/
VOID CxWindowImpl::vOnMButtonDown                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMButtonUp
/*virtual*/
VOID CxWindowImpl::vOnMButtonUp                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnMButtonDblClk                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnMouseWheel
/*virtual*/
VOID CxWindowImpl::vOnMouseWheel                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

#if (_WIN32_WINNT >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnXButtonDown
/*virtual*/
VOID CxWindowImpl::vOnXButtonDown                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnXButtonUp
/*virtual*/
VOID CxWindowImpl::vOnXButtonUp                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnXButtonDblClk
/*virtual*/
VOID CxWindowImpl::vOnXButtonDblClk                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

#if (_WIN32_WINNT >= 0x0600)
//---------------------------------------------------------------------------
//TODO: - vOnMouseHWheel
/*virtual*/
VOID CxWindowImpl::vOnMouseHWheel                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
//TODO: - vOnMouseLast
/*virtual*/
VOID CxWindowImpl::vOnMouseLast                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnParentNotify
/*virtual*/
VOID CxWindowImpl::vOnParentNotify                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEnterMenuLoop
/*virtual*/
VOID CxWindowImpl::vOnEnterMenuLoop                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnExitMenuLoop
/*virtual*/
VOID CxWindowImpl::vOnExitMenuLoop                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnNextMenu
/*virtual*/
VOID CxWindowImpl::vOnNextMenu                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSizing
/*virtual*/
VOID CxWindowImpl::vOnSizing                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCaptureChanged
/*virtual*/
VOID CxWindowImpl::vOnCaptureChanged               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMoving
/*virtual*/
VOID CxWindowImpl::vOnMoving                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnPowerBroadcast
/*virtual*/
VOID CxWindowImpl::vOnPowerBroadcast               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnDeviceChange
/*virtual*/
VOID CxWindowImpl::vOnDeviceChange                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnMdiCreate
/*virtual*/
VOID CxWindowImpl::vOnMdiCreate                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiDestroy
/*virtual*/
VOID CxWindowImpl::vOnMdiDestroy                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiActivate
/*virtual*/
VOID CxWindowImpl::vOnMdiActivate                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiRestore
/*virtual*/
VOID CxWindowImpl::vOnMdiRestore                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiNext
/*virtual*/
VOID CxWindowImpl::vOnMdiNext                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiMaximize
/*virtual*/
VOID CxWindowImpl::vOnMdiMaximize                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiTile
/*virtual*/
VOID CxWindowImpl::vOnMdiTile                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiCascade
/*virtual*/
VOID CxWindowImpl::vOnMdiCascade                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiIconArrange
/*virtual*/
VOID CxWindowImpl::vOnMdiIconArrange               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiGetActive
/*virtual*/
VOID CxWindowImpl::vOnMdiGetActive                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiSetMenu
/*virtual*/
VOID CxWindowImpl::vOnMdiSetMenu                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnEnterSizeMove
/*virtual*/
VOID CxWindowImpl::vOnEnterSizeMove                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnExitSizeMove
/*virtual*/
VOID CxWindowImpl::vOnExitSizeMove                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDropFiles
/*virtual*/
VOID CxWindowImpl::vOnDropFiles                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMdiRefreshMenu
/*virtual*/
VOID CxWindowImpl::vOnMdiRefreshMenu               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnImeSetContext
/*virtual*/
VOID CxWindowImpl::vOnImeSetContext                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeNotify
/*virtual*/
VOID CxWindowImpl::vOnImeNotify                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeControl
/*virtual*/
VOID CxWindowImpl::vOnImeControl                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeCompositionFull
/*virtual*/
VOID CxWindowImpl::vOnImeCompositionFull           (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeSelect
/*virtual*/
VOID CxWindowImpl::vOnImeSelect                    (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeChar
/*virtual*/
VOID CxWindowImpl::vOnImeChar                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnImeRequest
/*virtual*/
VOID CxWindowImpl::vOnImeRequest                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnImeKeyDown
/*virtual*/
VOID CxWindowImpl::vOnImeKeyDown                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnImeKeyUp
/*virtual*/
VOID CxWindowImpl::vOnImeKeyUp                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
//---------------------------------------------------------------------------
//TODO: - vOnMouseHover
/*virtual*/
VOID CxWindowImpl::vOnMouseHover                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnMouseLeave
/*virtual*/
VOID CxWindowImpl::vOnMouseLeave                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif

#if(WINVER >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnNcMouseHover
/*virtual*/
VOID CxWindowImpl::vOnNcMouseHover                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnNcMouseLeave
/*virtual*/
VOID CxWindowImpl::vOnNcMouseLeave                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnWtsSessionChange
/*virtual*/
VOID CxWindowImpl::vOnWtsSessionChange             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnTabletFirst
/*virtual*/
VOID CxWindowImpl::vOnTabletFirst                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnTabletLast
/*virtual*/
VOID CxWindowImpl::vOnTabletLast                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

//---------------------------------------------------------------------------
//TODO: - vOnCut
/*virtual*/
VOID CxWindowImpl::vOnCut                          (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnCopy
/*virtual*/
VOID CxWindowImpl::vOnCopy                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaste
/*virtual*/
VOID CxWindowImpl::vOnPaste                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnClear
/*virtual*/
VOID CxWindowImpl::vOnClear                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnUndo
/*virtual*/
VOID CxWindowImpl::vOnUndo                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnRenderFormat
/*virtual*/
VOID CxWindowImpl::vOnRenderFormat                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnRenderAllFormats
/*virtual*/
VOID CxWindowImpl::vOnRenderAllFormats             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDestroyClipboard
/*virtual*/
VOID CxWindowImpl::vOnDestroyClipboard             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDrawClipboard
/*virtual*/
VOID CxWindowImpl::vOnDrawClipboard                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaintClipboard
/*virtual*/
VOID CxWindowImpl::vOnPaintClipboard               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnVScrollClipboard
/*virtual*/
VOID CxWindowImpl::vOnVScrollClipboard             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnSizeClipboard
/*virtual*/
VOID CxWindowImpl::vOnSizeClipboard                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnAskCBFormatName
/*virtual*/
VOID CxWindowImpl::vOnAskCBFormatName              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnChangeCBChain
/*virtual*/
VOID CxWindowImpl::vOnChangeCBChain                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnHScrollClipboard
/*virtual*/
VOID CxWindowImpl::vOnHScrollClipboard             (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnQueryNewPalette
/*virtual*/
VOID CxWindowImpl::vOnQueryNewPalette              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaletteIsChanging
/*virtual*/
VOID CxWindowImpl::vOnPaletteIsChanging            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPaletteChanged
/*virtual*/
VOID CxWindowImpl::vOnPaletteChanged               (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnHotKey
/*virtual*/
VOID CxWindowImpl::vOnHotKey                       (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnPrint
/*virtual*/
VOID CxWindowImpl::vOnPrint                        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPrintClient
/*virtual*/
VOID CxWindowImpl::vOnPrintClient                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
//---------------------------------------------------------------------------
//TODO: - vOnAppCommand
/*virtual*/
VOID CxWindowImpl::vOnAppCommand                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnThemeChanged
/*virtual*/
VOID CxWindowImpl::vOnThemeChanged                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
//---------------------------------------------------------------------------
//TODO: - vOnClipboardUpdate
/*virtual*/
VOID CxWindowImpl::vOnClipboardUpdate              (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
//---------------------------------------------------------------------------
//TODO: - vOnDwmCompositionChanged
/*virtual*/
VOID CxWindowImpl::vOnDwmCompositionChanged        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDwmNcRenderingChanged
/*virtual*/
VOID CxWindowImpl::vOnDwmNcRenderingChanged        (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDwmColorizationColorChanged
/*virtual*/
VOID CxWindowImpl::vOnDwmColorizationColorChanged  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnDwmWindowMaximizedChange
/*virtual*/
VOID CxWindowImpl::vOnDwmWindowMaximizedChange     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* _WIN32_WINNT >= 0x0600 */

#if(WINVER >= 0x0600)
//---------------------------------------------------------------------------
//TODO: - vOnGetTitleBarInfoEx
/*virtual*/
VOID CxWindowImpl::vOnGetTitleBarInfoEx            (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnHandHeldFirst
/*virtual*/
VOID CxWindowImpl::vOnHandHeldFirst                (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnHandHeldFast
/*virtual*/
VOID CxWindowImpl::vOnHandHeldFast                 (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnAfxFirst
/*virtual*/
VOID CxWindowImpl::vOnAfxFirst                     (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnAfxLast
/*virtual*/
VOID CxWindowImpl::vOnAfxLast                      (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnPenWinFirst
/*virtual*/
VOID CxWindowImpl::vOnPenWinFirst                  (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
//TODO: - vOnPenWinLast
/*virtual*/
VOID CxWindowImpl::vOnPenWinLast                   (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------

#if(WINVER >= 0x0400)
//---------------------------------------------------------------------------
//TODO: - vOnApp
/*virtual*/
VOID CxWindowImpl::vOnApp                          (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------
#endif /* WINVER >= 0x0400 */

//---------------------------------------------------------------------------
//TODO: - vOnUser
/*
 * NOTE: All Message Numbers below 0x0400 are RESERVED.
 *
 * Private Window Messages Start Here:
 */
/*virtual*/
VOID CxWindowImpl::vOnUser                         (WPARAM wParam, LPARAM lParam) {
    LOG();
}
//---------------------------------------------------------------------------




/****************************************************************************
*    private
*
*****************************************************************************/
