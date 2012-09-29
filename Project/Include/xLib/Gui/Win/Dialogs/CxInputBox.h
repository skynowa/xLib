/**
 * \file  CxInputBox.h
 * \brief input box
 */


#ifndef xLib_Gui_CxInputBoxH
#define xLib_Gui_CxInputBoxH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#define ID_staPrompt    101
#define ID_edtText      102
#define ID_btnOK        IDOK
#define ID_btnCancel    IDCANCEL
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxInputBox :
    private CxNonCopyable
    /// input box
{
    public:
        enum ExModalResult
            /// modal result
        {
            mrOk,
            mrCancel
        };

                                CxInputBox  ();
            ///< constructor
        virtual                ~CxInputBox  ();
            ///< destructor

        ExModalResult           mrShowModal (const std::tstring_t &csCaption, const std::tstring_t &csPrompt, const std::tstring_t &csText);
            ///< show modal
        std::tstring_t          sGetText    ();
            ///< get text

    private:
        std::tstring_t          _m_sText;        ///< text
        HWND                    _m_hWndMain;    ///< handle to main window
        HWND                    _m_hBtnOk;        ///< handle to button "Ok"
        HWND                    _m_hBtnCancel;    ///< handle to button "Cancel"
        HWND                    _m_hStaPrompt;    ///< handle to button "Prompt"
        HWND                    _m_hEdtText;    ///< handle to edit text field

        static LRESULT CALLBACK _ms_pWndProc(HWND hWnd, uint_t uiMsg, WPARAM wParam, LPARAM lParam);
            ///< window callback
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Gui_CxInputBoxH


#if xTODO
    void ToggleStyle(HWND hEdit)
    {
        if(SendMessage(hEdit,EM_GETPASSWORDCHAR,0,0) == '*')
            SendMessage(hEdit,EM_SETPASSWORDCHAR,0,0);
        else
            SendMessage(hEdit,EM_SETPASSWORDCHAR,(WPARAM)'*',0);
        SetFocus(hEdit);
    }
#endif

#if xTODO
    DWORD dwStyle = GetWindowLong(m_hwndEditPassword, GWL_STYLE);

    if(SendMessage(m_hwndPasswordCheck, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle | ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, '*', NULL);
    }
    else
    {
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle & ~ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, NULL, NULL);
    }

    SetFocus(m_hwndEditPassword);
    SetFocus(m_hwndPasswordCheck);
#endif
