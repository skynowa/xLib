/**
 * \file  CxMsgBoxRtf.h
 * \brief formated message box
 */


#ifndef xLib_Gui_Dialogs_CxMsgBoxRtfH
#define xLib_Gui_Dialogs_CxMsgBoxRtfH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

xNAMESPACE_BEGIN(CxMsgBoxRtf)
    /// formated message box

    enum ExModalResult
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

    void             vCreateContent(const HWND &hParent);
        ///< create content
    INT_PTR CALLBACK DialogProc    (HWND hDlg, uint_t uiMsg, WPARAM wParam, LPARAM lParam);
        ///< window callback
    ExModalResult    iShow         (const HWND &hwndOwner, const std::tstring_t &csMessage, const std::tstring_t &csTiltle);
        ///< show

xNAMESPACE_END(CxMsgBoxRtf)

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxMsgBoxRtf.inl"
//---------------------------------------------------------------------------
#endif //xLib_Gui_Dialogs_CxMsgBoxRtfH
