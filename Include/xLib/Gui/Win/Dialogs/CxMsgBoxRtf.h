/****************************************************************************
* Class name:  CxMsgBoxRtf
* Description: RTF message box
* File name:   CxMsgBoxRtf.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     08.05.2009 12:38:09
*
*****************************************************************************/


#ifndef xLib_Gui_Dialogs_CxMsgBoxRtfH
#define xLib_Gui_Dialogs_CxMsgBoxRtfH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/xCommon.h>
//---------------------------------------------------------------------------
namespace CxMsgBoxRtf {

    enum EModalResult {
        mrInternalError = - 1,
        mrNone          = 0,
        mrAbort         = 1,
        mrRetry         = 2,
        mrIgnore        = 3,
        mrCopyToClip    = 4,
        mrSendReport    = 5
    };

    BOOL             bCreateContent(HWND hParent);
    INT_PTR CALLBACK DialogProc    (HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    EModalResult     iShow         (HWND hwndOwner, const tString &csMessage, const tString &csTiltle);
};
//---------------------------------------------------------------------------
#include <Gui/Win/Dialogs/CxMsgBoxRtf.inl>
//---------------------------------------------------------------------------
#endif //xLib_Gui_Dialogs_CxMsgBoxRtfH
