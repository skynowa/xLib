/**
 * \file  CxMsgBoxRtf.inl
 * \brief RTF message box
 */


#include <commctrl.h>
#if xCOMPILER_MS
    #pragma comment(lib, "comctl32.lib")
#endif
#include <richedit.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(CxMsgBoxRtf)

#define xCXWINDOW_CONTROL_CLASS                 xT("WC_XWINDOW")
#define xCXLAYOUT_CONTROL_CLASS                 xT("WC_XLAYOUT")

#define xCXBUTTON_CONTROL_CLASS                 WC_BUTTON
#define xCXPUSHBUTTON_CONTROL_CLASS             WC_BUTTON
#define xCXIMAGEBUTTON_CONTROL_CLASS            WC_BUTTON
#define xCXCHECKBOX_CONTROL_CLASS               WC_BUTTON
#define xCXRADIOBUTTON_CONTROL_CLASS            WC_BUTTON
#define xCXGROUPBOX_CONTROL_CLASS               WC_BUTTON
#define xCXOWNERDRAWBUTTON_CONTROL_CLASS        WC_BUTTON

#define xCXCOMBOBOX_CONTROL_CLASS               WC_COMBOBOX
#define xCXEDIT_CONTROL_CLASS                   WC_EDIT
#define xCXMDICLIENT_CONTROL_CLASS              xT("MDICLIENT")
#define xCXSCROLLBAR_CONTROL_CLASS              xT("SCROLLBAR")
#define xCXSTATIC_CONTROL_CLASS                 WC_STATIC
#define xCXPICTURE_CONTROL_CLASS                WC_STATIC
#define xCXLISTBOX_CONTROL_CLASS                WC_LISTBOX
#define xCXSTATUSBAR_CONTROL_CLASS              STATUSCLASSNAME
#define xCXPROGRESSBAR_CONTROL_CLASS            PROGRESS_CLASS
#define xCXLISTVIEW_CONTROL_CLASS               WC_LISTVIEW
#define xCXRICHEDIT10_CONTROL_CLASS             xT("RichEdit")
#define xCXRICHEDIT20_CONTROL_CLASS             RICHEDIT_CLASS
#define xCXTAB_CONTROL_CLASS                    WC_TABCONTROL
//---------------------------------------------------------------------------
ExModalResult g_mrRes          = mrNone;
std::tstring_t g_sTitle;
std::tstring_t g_sMessage;

const int    ID_staImg        = 200;
const int    ID_redtText      = 201;
const int    ID_btnAbort      = 202;
const int    ID_btnRetry      = 203;
const int    ID_btnIgnore     = 204;
const int    ID_btnCopyToClip = 205;
const int    ID_btnSendReport = 206;

HWND         g_hMainWnd       = NULL;
HINSTANCE    g_hInst          = ::GetModuleHandle(NULL);
HFONT        g_hFont          = NULL;
HWND         g_hStaImg        = NULL;
HWND         g_hRedtText      = NULL;
HWND         g_hBtnAbort      = NULL;
HWND         g_hBtnBreak      = NULL;
HWND         g_hBtnIgnore     = NULL;
HWND         g_hBtnCopyToClip = NULL;
HWND         g_hBtnSendReport = NULL;

const int    ciLeft           = 350;
const int    ciTop            = 200;
const int    ciWidth          = 270;
const int    ciHeight         = 230;

const int    ciBtnWidth       = 75;
const int    ciBtnHeight      = 25;
const int    ciBtnShift       = 100;
const int    ciRichEdtShift   = 68;

const int    ciBtnLeftMargin  = 90;
const int    ciBtnSpace       = 8;
//---------------------------------------------------------------------------
bool
bCreateContent(
    HWND a_hParent
)
{
    g_hFont = (HFONT)::SendMessage(g_hMainWnd, WM_GETFONT, 0, 0);

    //-------------------------------------
    //image
    g_hStaImg = ::CreateWindowEx(
                        0x00000000,
                        xT("Static"),
                        xT("ID_staImg"),
                        WS_CHILD | WS_VISIBLE | SS_ICON,
                        16, 16, 56, 40,
                        a_hParent,
                        (HMENU)ID_staImg,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hStaImg, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);
    ::SendMessage(g_hStaImg, STM_SETICON, (WPARAM)::LoadIcon(NULL, IDI_ERROR), (LPARAM)0);

    //-------------------------------------
    //text field (RICHEDIT)
    g_hRedtText = ::CreateWindowEx(
                        0x00000000,
                        xCXRICHEDIT10_CONTROL_CLASS /*xT("RICHEDIT")*/,
                        xT(""),
                        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_READONLY,
                        90, 8, 420, 400,
                        a_hParent,
                        (HMENU)ID_redtText,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hRedtText, EM_SETBKGNDCOLOR, (WPARAM)0, (LPARAM)::GetSysColor(COLOR_3DFACE));
    ::SendMessage(g_hRedtText, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);
    ::ShowScrollBar(g_hRedtText, SB_VERT/*SB_BOTH*/, true);

    CHARRANGE crRange = {0};
    crRange.cpMin = ::GetWindowTextLength(g_hRedtText);
    crRange.cpMax = ::GetWindowTextLength(g_hRedtText);

    ::SendMessage(g_hRedtText, EM_EXSETSEL, (WPARAM)0, (LPARAM)&crRange);
    ::SendMessage(g_hRedtText, EM_REPLACESEL, (WPARAM)/*bCanUndo*/false, (LPARAM)g_sMessage.c_str());

    //-------------------------------------
    //button "Abort"
    g_hBtnAbort = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Abort"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin, 420, ciBtnWidth, ciBtnHeight,
                        a_hParent,
                        (HMENU)ID_btnAbort,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnAbort, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);

    //-------------------------------------
    //button "Retry"
    g_hBtnBreak = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Break"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 1, 420, ciBtnWidth, ciBtnHeight,
                        a_hParent,
                        (HMENU)ID_btnRetry,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnBreak, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);

    //-------------------------------------
    //button "Ignore"
    g_hBtnIgnore = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Ignore"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 2, 420, ciBtnWidth, ciBtnHeight,
                        a_hParent,
                        (HMENU)ID_btnIgnore,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnIgnore, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);

    //-------------------------------------
    //button "Copy to clip"
    g_hBtnIgnore = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Copy"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 3, 420, ciBtnWidth, ciBtnHeight,
                        a_hParent,
                        (HMENU)ID_btnCopyToClip,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnIgnore, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);

    //-------------------------------------
    //button "Send report"
    g_hBtnSendReport = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Report"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 4, 420, ciBtnWidth, ciBtnHeight,
                        a_hParent,
                        (HMENU)ID_btnSendReport,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnSendReport, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)true);

    return true;
}
//---------------------------------------------------------------------------
INT_PTR CALLBACK
DialogProc(
    HWND   a_hDlg,
    uint_t a_uiMsg,
    WPARAM a_wParam,
    LPARAM a_lParam
)
{
    switch(a_uiMsg) {
        case WM_INITDIALOG:    {
                bCreateContent(a_hDlg);
            }
            return true;

        case WM_CLOSE: {
                ::EndDialog(a_hDlg, 0);
            }
            return true;

        case WM_COMMAND:
            {
                switch (LOWORD(a_wParam))    {
                    case ID_btnAbort: {
                            g_mrRes = CxMsgBoxRtf::mrAbort;
                            ::SendMessage(a_hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return true;

                    case ID_btnRetry: {
                            g_mrRes = CxMsgBoxRtf::mrRetry;
                            ::SendMessage(a_hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return true;

                    case ID_btnIgnore: {
                            g_mrRes = CxMsgBoxRtf::mrIgnore;
                            ::SendMessage(a_hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return true;

                    case ID_btnCopyToClip: {
                            g_mrRes = CxMsgBoxRtf::mrCopyToClip;
                            ::SendMessage(g_hRedtText, WM_COPY, (WPARAM)0, (LPARAM)0);
                        }
                        return true;

                    case ID_btnSendReport: {
                            g_mrRes = CxMsgBoxRtf::mrSendReport;
                            ::MessageBox(0, xT("ID_btnSendReport"), xT(""), MB_OK);
                        }
                        return true;

                    default: {

                        }
                        return false;
                }
            }
            return true;
    }

    return false;
}
//---------------------------------------------------------------------------
ExModalResult
iShow(
    HWND                  a_hwndOwner,
    const std::tstring_t &a_csMessage,
    const std::tstring_t &a_csTiltle
)
{
    HMODULE           hmRichEdtDll = NULL;
    HGLOBAL           hgbl         = INVALID_HANDLE_VALUE;
    LPDLGTEMPLATE     lpdt         = NULL;
    ////LPDLGITEMTEMPLATE lpdit        = NULL;
    LPWORD            lpw          = NULL;
    LPWSTR            lpwsz        = NULL;
    LRESULT           lpRes        = (LRESULT)NULL;
    int               nchar        = - 1;

    //-------------------------------------
    //loading DLL
    hmRichEdtDll = ::LoadLibrary(xT("RICHED32.DLL"));
    if (NULL == hmRichEdtDll) {
        return mrInternalError;
    }

    hgbl = ::GlobalAlloc(GMEM_ZEROINIT, 1024);
    if (NULL == hgbl) {
        return mrInternalError;
    }

    lpdt = (LPDLGTEMPLATE)::GlobalLock(hgbl);
    if (NULL == lpdt) {
        return mrInternalError;
    }

    //-------------------------------------
    //dialog box
    lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION;
    lpdt->cdit = 0;         // Number of controls
    lpdt->x    = ciLeft;
    lpdt->y    = ciTop;
    lpdt->cx   = ciWidth;
    lpdt->cy   = ciHeight;

    lpw = (LPWORD)(lpdt + 1);
    *lpw ++ = 0;             // No menu
    *lpw ++ = 0;             // Predefined dialog box class (by default)

    lpwsz = (LPWSTR)lpw;
    ////TODO: nchar = 1 + ::MultiByteToWideChar(CP_ACP, 0, csTiltle.c_str(), -1, lpwsz, 50);
    nchar = 1 + a_csTiltle.size();
    lpw += nchar;

    g_sTitle   = a_csTiltle;
    g_sMessage = a_csMessage;

    ::GlobalUnlock(hgbl);
    lpRes = ::DialogBoxIndirect(g_hInst, (LPDLGTEMPLATE)hgbl, a_hwndOwner, reinterpret_cast<DLGPROC>(DialogProc));
    ::GlobalFree(hgbl);

    //-------------------------------------
    //unloading DLL
    if (NULL != hmRichEdtDll) {
        ::FreeLibrary(hmRichEdtDll);    hmRichEdtDll = NULL;
    }

    return /*lpRes*/g_mrRes;
}
//---------------------------------------------------------------------------
xNAMESPACE_END(CxMsgBoxRtf)
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
