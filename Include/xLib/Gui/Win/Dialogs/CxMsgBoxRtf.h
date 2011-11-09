/**
 * \file  CxMsgBoxRtf.h
 * \brief formated message box
 */


#ifndef xLib_Gui_Dialogs_CxMsgBoxRtfH
#define xLib_Gui_Dialogs_CxMsgBoxRtfH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
namespace CxMsgBoxRtf
    /// formated message box
{
    enum EModalResult
        /// modal result
    {
        mrInternalError = - 1,
        mrNone          = 0,
        mrAbort         = 1,
        mrRetry         = 2,
        mrIgnore        = 3,
        mrCopyToClip    = 4,
        mrSendReport    = 5
    };

    BOOL             bCreateContent(HWND hParent);
        ///< create content
    INT_PTR CALLBACK DialogProc    (HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);
        ///< window callback
    EModalResult     iShow         (HWND hwndOwner, const std::string_t &csMessage, const std::string_t &csTiltle);
        ///< show
};
//---------------------------------------------------------------------------
#include <Gui/Win/Dialogs/CxMsgBoxRtf.inl>
//---------------------------------------------------------------------------
#endif //xLib_Gui_Dialogs_CxMsgBoxRtfH
