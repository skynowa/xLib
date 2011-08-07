/****************************************************************************
* Class name:  CxInputBox
* Description: input box
* File name:   CxInputBox.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.10.2010 13:53:30
*
*****************************************************************************/



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
class CxInputBox : 
    public CxNonCopyable 
{
    public:
        enum EModalResult {
            mrOk,
            mrCancel
        };

                                CxInputBox  ();
        virtual                ~CxInputBox  ();

        EModalResult            mrShowModal (const tString &csCaption, const tString &csPrompt, const tString &csText);
        tString                 sGetText    ();

    private:
        BOOL                    _m_bRes;
        tString                 _m_sText;
        HWND                    _m_hWndMain;
        HWND                    _m_hBtnOk;
        HWND                    _m_hBtnCancel;
        HWND                    _m_hStaPrompt;
        HWND                    _m_hEdtText;

        //---------------------------------------------------------------------------
        //TODO: ms_pWndProc
        static LRESULT CALLBACK _ms_pWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
};
//---------------------------------------------------------------------------
#endif //xLib_Gui_CxInputBoxH


/*
void ToggleStyle(HWND hEdit)
{
    if(SendMessage(hEdit,EM_GETPASSWORDCHAR,0,0) == '*')
        SendMessage(hEdit,EM_SETPASSWORDCHAR,0,0);
    else
        SendMessage(hEdit,EM_SETPASSWORDCHAR,(WPARAM)'*',0);
    SetFocus(hEdit);
}
*/
/*
DWORD dwStyle = GetWindowLong(m_hwndEditPassword, GWL_STYLE);

    // �� �������� ���� ��������, ���� ���������� ������ � ����
    if(SendMessage(m_hwndPasswordCheck, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        // ������������� ��������� ����
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle | ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, '*', NULL);
    }
    else
    {
        // ������������� ����������� ����
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle & ~ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, NULL, NULL);
    }

    SetFocus(m_hwndEditPassword);    // ��������� ����� � ���� � ������
    SetFocus(m_hwndPasswordCheck);    // ���������� ����� �� �������
*/
