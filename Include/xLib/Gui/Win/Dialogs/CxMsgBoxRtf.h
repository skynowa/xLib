/**
 * \file  CxMsgBoxRtf.h
 * \brief RTF message box
 */


#ifndef xLib_Gui_Dialogs_CxMsgBoxRtfH
#define xLib_Gui_Dialogs_CxMsgBoxRtfH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/xCommon.h>
//---------------------------------------------------------------------------
namespace CxMsgBoxRtf 
    /// RTF message box
{

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
    EModalResult     iShow         (HWND hwndOwner, const std::tstring &csMessage, const std::tstring &csTiltle);
};
//---------------------------------------------------------------------------
#include <Gui/Win/Dialogs/CxMsgBoxRtf.inl>
//---------------------------------------------------------------------------
#endif //xLib_Gui_Dialogs_CxMsgBoxRtfH
