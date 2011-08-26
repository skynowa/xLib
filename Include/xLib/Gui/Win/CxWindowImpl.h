/**
 * \file  CxWindowImpl.h
 * \brief window
 */


#ifndef XLib_Gui_CxWindowImplH
#define XLib_Gui_CxWindowImplH
//---------------------------------------------------------------------------
#include <xLib/Gui/CxWindow.h>
#include <xLib/Gui/CxWndsContainer.h>
//---------------------------------------------------------------------------
class CxWindowImpl : 
    public CxWindow 
    /// window
{
    public:
        CxWndsContainer     m_vecpContainer;        //контейнер для дочерних окон

                            CxWindowImpl();
        virtual            ~CxWindowImpl();

        BOOL                bCreate     (INT iID, HWND hParent, const tString &csWndName,
                                         INT iLeft, INT iTop, INT iWidth, INT iHeight,
                                         ULONG ulStyle, ULONG ulExStyle);
        BOOL                bCreateRes  (INT iID, HWND hParent);
        BOOL                bShowModal  ();

        //-------------------------------------
        //сообщения

        //-------------------------------------
        //события
                            xDECLARE_MSG_MAP                ();

        virtual VOID        vOnNull                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCreate                       (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDestroy                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMove                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSize                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnActivate                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetFocus                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnKillFocus                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEnable                       (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetreDraw                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetText                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetText                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetTextlength                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaint                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnClose                        (WPARAM wParam, LPARAM lParam);

    #ifndef _WIN32_WCE
        virtual VOID        vOnQueryEndSession              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnQueryOpen                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEndSession                   (WPARAM wParam, LPARAM lParam);
    #endif

        virtual VOID        vOnQuit                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEraseBkGnd                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysColorChange               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnShowWindow                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnWininiChange                 (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnSettingChange                (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

        virtual VOID        vOnDevModeChange                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnActivateApp                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnFontChange                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnTimeChange                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCancelMode                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetCursor                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMouseActivate                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnChildActivate                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnQueueSync                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetMinMaxInfo                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaintIcon                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnIconEraseBkGnd               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNextDlgCtl                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSpoolerStatus                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDrawItem                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMeasureItem                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDeleteItem                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnVKeyToItem                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCharToItem                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetFont                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetFont                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetHotKey                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetHotKey                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnQueryDragIcon                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCompareItem                  (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0500)
    #ifndef _WIN32_WCE
        virtual VOID        vOnGetObject                    (WPARAM wParam, LPARAM lParam);
    #endif
    #endif /* WINVER >= 0x0500 */

        virtual VOID        vOnCompacting                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCommNotify                   (WPARAM wParam, LPARAM lParam);  /* no longer suported */
        virtual VOID        vOnWindowPosChanging            (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnWindowPosChanged             (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPower                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCopyData                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCancelJournal                (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnNotify                       (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnInputLangChangeRequest       (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnInputLangChange              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnTCard                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnHelp                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnUserChanged                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNotifyFormat                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnContextMenu                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnStyleChanging                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnStyleChanged                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDisplayChange                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetIcon                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSetIcon                      (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

        virtual VOID        vOnNcCreate                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcDestroy                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcCalcSize                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcHitTest                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcPaint                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcActivate                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnGetDlgCode                   (WPARAM wParam, LPARAM lParam);

    #ifndef _WIN32_WCE
        virtual VOID        vOnSyncPaint                    (WPARAM wParam, LPARAM lParam);
    #endif

        virtual VOID        vOnNcMouseMove                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcLButtonDown                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcLButtonUp                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcLButtonDblClk              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcRButtonDown                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcRButtonUp                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcRButtonDblClk              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcMButtonDown                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcMButtonUp                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcMButtonDblClk              (WPARAM wParam, LPARAM lParam);

    #if(_WIN32_WINNT >= 0x0500)
        virtual VOID        vOnNCxButtonDown                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNCxButtonUp                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNCxButtonDblClk              (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0500 */

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnInputDeviceChange          (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnInput                        (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

        virtual VOID        vOnKeyFirst                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnKeyDown                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnKeyUp                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnChar                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDeadChar                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysKeyDown                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysKeyUp                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysChar                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysDeadChar                  (WPARAM wParam, LPARAM lParam);

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnUniChar                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnKeyLast                      (WPARAM wParam, LPARAM lParam);
    #else
        virtual VOID        vOnKeyLast                      (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

    #if(WINVER >= 0x0400)
        virtual VOID        vOnImeStartComposition         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeEndComposition           (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeComposition              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeKeyLast                  (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

        virtual VOID        vOnInitdialog                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCommand                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSysCommand                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnTimer                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnHScroll                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnVScroll                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnInitMenu                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnInitMenuPopup                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMenuSelect                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMenuChar                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEnterIdle                    (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0500)
    #ifndef _WIN32_WCE
        virtual VOID        vOnMenuRButtonUp                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMenuDrag                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMenuGetObject                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnUnInitMenuPopup              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMenuCommand                  (WPARAM wParam, LPARAM lParam);

    #ifndef _WIN32_WCE
    #if(_WIN32_WINNT >= 0x0500)
        virtual VOID        vOnChangeUiState                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnUpdateUiState                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnQueryUiState                 (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0500 */
    #endif

    #endif
    #endif /* WINVER >= 0x0500 */

        virtual VOID        vOnCtlColorMsgBox               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorEdit                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorListbox              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorBtn                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorDlg                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorScrollBar            (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCtlColorStatic               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMouseFirst                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMouseMove                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnLButtonDown                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnLButtonUp                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnLButtonDblClk                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnRButtonDown                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnRButtonUp                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnRButtonDblClk                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMButtonDown                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMButtonUp                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMButtonDblClk                (WPARAM wParam, LPARAM lParam);

    #if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
        virtual VOID        vOnMouseWheel                   (WPARAM wParam, LPARAM lParam);
    #endif

    #if (_WIN32_WINNT >= 0x0500)
        virtual VOID        vOnXButtonDown                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnXButtonUp                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnXButtonDblClk                (WPARAM wParam, LPARAM lParam);
    #endif

    #if (_WIN32_WINNT >= 0x0600)
        virtual VOID        vOnMouseHWheel                  (WPARAM wParam, LPARAM lParam);
    #endif

        virtual VOID        vOnMouseLast                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnParentNotify                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEnterMenuLoop                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnExitMenuLoop                 (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnNextMenu                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSizing                       (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCaptureChanged               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMoving                       (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

    #if(WINVER >= 0x0400)
        virtual VOID        vOnPowerBroadcast               (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

    #if(WINVER >= 0x0400)
        virtual VOID        vOnDeviceChange                 (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

        virtual VOID        vOnMdiCreate                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiDestroy                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiActivate                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiRestore                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiNext                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiMaximize                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiTile                      (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiCascade                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiIconArrange               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiGetActive                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiSetMenu                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnEnterSizeMove                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnExitSizeMove                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDropFiles                    (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMdiRefreshMenu               (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnImeSetContext               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeNotify                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeControl                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeCompositionFull          (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeSelect                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeChar                     (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

    #if(WINVER >= 0x0500)
        virtual VOID        vOnImeRequest                  (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0500 */

    #if(WINVER >= 0x0400)
        virtual VOID        vOnImeKeyDown                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnImeKeyUp                    (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

    #if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
        virtual VOID        vOnMouseHover                   (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnMouseLeave                   (WPARAM wParam, LPARAM lParam);
    #endif

    #if(WINVER >= 0x0500)
        virtual VOID        vOnNcMouseHover                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnNcMouseLeave                 (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0500 */

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnWtsSessionChange            (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnTabletFirst                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnTabletLast                  (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

        virtual VOID        vOnCut                          (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnCopy                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaste                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnClear                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnUndo                         (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnRenderFormat                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnRenderAllFormats             (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDestroyClipboard             (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDrawClipboard                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaintClipboard               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnVScrollClipboard             (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnSizeClipboard                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnAskCBFormatName              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnChangeCBChain                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnHScrollClipboard             (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnQueryNewPalette              (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaletteIsChanging            (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPaletteChanged               (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnHotKey                       (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnPrint                        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPrintClient                  (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

    #if(_WIN32_WINNT >= 0x0500)
        virtual VOID        vOnAppCommand                   (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0500 */

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnThemeChanged                 (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

    #if(_WIN32_WINNT >= 0x0501)
        virtual VOID        vOnClipboardUpdate              (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0501 */

    #if(_WIN32_WINNT >= 0x0600)
        virtual VOID        vOnDwmCompositionChanged        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDwmNcRenderingChanged        (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDwmColorizationColorChanged  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnDwmWindowMaximizedChange     (WPARAM wParam, LPARAM lParam);
    #endif /* _WIN32_WINNT >= 0x0600 */

    #if(WINVER >= 0x0600)
        virtual VOID        vOnGetTitleBarInfoEx            (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0600 */

    #if(WINVER >= 0x0400)
        virtual VOID        vOnHandHeldFirst                (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnHandHeldFast                 (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnAfxFirst                     (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnAfxLast                      (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */

        virtual VOID        vOnPenWinFirst                  (WPARAM wParam, LPARAM lParam);
        virtual VOID        vOnPenWinLast                   (WPARAM wParam, LPARAM lParam);

    #if(WINVER >= 0x0400)
        virtual VOID        vOnApp                          (WPARAM wParam, LPARAM lParam);
    #endif /* WINVER >= 0x0400 */


        /*
         * NOTE: All Message Numbers below 0x0400 are RESERVED.
         *
         * Private Window Messages Start Here:
         */
        virtual VOID        vOnUser                         (WPARAM wParam, LPARAM lParam);

    private:
        BOOL                _m_bIsDestroyed;        //флаг разрушения окна
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxWindowImplH
