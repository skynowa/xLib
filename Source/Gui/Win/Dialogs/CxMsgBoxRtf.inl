/**
 * \file  CxMsgBoxRtf.inl
 * \brief RTF message box
 */


#include <commctrl.h>
#if defined(xCOMPILER_MS)
    #pragma comment(lib, "comctl32.lib")
#endif
#include <richedit.h>


//---------------------------------------------------------------------------
namespace CxMsgBoxRtf {

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
EModalResult g_mrRes          = mrNone;
std::tstring g_sTitle;
std::tstring g_sMessage;

const INT    ID_staImg        = 200;
const INT    ID_redtText      = 201;
const INT    ID_btnAbort      = 202;
const INT    ID_btnRetry      = 203;
const INT    ID_btnIgnore     = 204;
const INT    ID_btnCopyToClip = 205;
const INT    ID_btnSendReport = 206;

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

const INT    ciLeft           = 350;
const INT    ciTop            = 200;
const INT    ciWidth          = 270;
const INT    ciHeight         = 190;

const INT    ciBtnWidth       = 75;
const INT    ciBtnHeight      = 25;
const INT    ciBtnShift       = 100;
const INT    ciRichEdtShift   = 68;

const INT    ciBtnLeftMargin  = 90;
const INT    ciBtnSpace       = 8;
//---------------------------------------------------------------------------
BOOL
bCreateContent(
    HWND hParent
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
                        hParent,
                        (HMENU)ID_staImg,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hStaImg, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);
    ::SendMessage(g_hStaImg, STM_SETICON, (WPARAM)::LoadIcon(NULL, IDI_ERROR), (LPARAM)0);

    //-------------------------------------
    //text field (RICHEDIT)
    g_hRedtText = ::CreateWindowEx(
                        0x00000000,
                        xCXRICHEDIT10_CONTROL_CLASS /*xT("RICHEDIT")*/,
                        xT(""),
                        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_READONLY,
                        90, 8, 420, 320,
                        hParent,
                        (HMENU)ID_redtText,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hRedtText, EM_SETBKGNDCOLOR, (WPARAM)0, (LPARAM)::GetSysColor(COLOR_3DFACE));
    ::SendMessage(g_hRedtText, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);
    ::ShowScrollBar(g_hRedtText, SB_VERT/*SB_BOTH*/, TRUE);

    CHARRANGE crRange = {0};
    crRange.cpMin = ::GetWindowTextLength(g_hRedtText);
    crRange.cpMax = ::GetWindowTextLength(g_hRedtText);

    ::SendMessage(g_hRedtText, EM_EXSETSEL, (WPARAM)0, (LPARAM)&crRange);
    ::SendMessage(g_hRedtText, EM_REPLACESEL, (WPARAM)/*bCanUndo*/FALSE, (LPARAM)g_sMessage.c_str());

    //-------------------------------------
    //button "Abort"
    g_hBtnAbort = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Abort"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin, 340, ciBtnWidth, ciBtnHeight,
                        hParent,
                        (HMENU)ID_btnAbort,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnAbort, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);

    //-------------------------------------
    //button "Retry"
    g_hBtnBreak = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Break"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 1, 340, ciBtnWidth, ciBtnHeight,
                        hParent,
                        (HMENU)ID_btnRetry,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnBreak, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);

    //-------------------------------------
    //button "Ignore"
    g_hBtnIgnore = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Ignore"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 2, 340, ciBtnWidth, ciBtnHeight,
                        hParent,
                        (HMENU)ID_btnIgnore,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnIgnore, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);

    //-------------------------------------
    //button "Copy to clip"
    g_hBtnIgnore = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Copy"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 3, 340, ciBtnWidth, ciBtnHeight,
                        hParent,
                        (HMENU)ID_btnCopyToClip,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnIgnore, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);

    //-------------------------------------
    //button "Send report"
    g_hBtnSendReport = ::CreateWindowEx(
                        0x00000000,
                        xCXBUTTON_CONTROL_CLASS,
                        xT("Report"),
                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
                        ciBtnLeftMargin + (ciBtnWidth + ciBtnSpace) * 4, 340, ciBtnWidth, ciBtnHeight,
                        hParent,
                        (HMENU)ID_btnSendReport,
                        g_hInst,
                        NULL);
    ::SendMessage(g_hBtnSendReport, WM_SETFONT, (WPARAM)g_hFont, (LPARAM)TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
INT_PTR CALLBACK
DialogProc(
    HWND   hDlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch(uiMsg) {
        case WM_INITDIALOG:    {
                bCreateContent(hDlg);
            }
            return TRUE;

        case WM_CLOSE: {
                ::EndDialog(hDlg, 0);
            }
            return TRUE;

        case WM_COMMAND:
            {
                switch (LOWORD(wParam))    {
                    case ID_btnAbort: {
                            g_mrRes = CxMsgBoxRtf::mrAbort;
                            ::SendMessage(hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return TRUE;

                    case ID_btnRetry: {
                            g_mrRes = CxMsgBoxRtf::mrRetry;
                            ::SendMessage(hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return TRUE;

                    case ID_btnIgnore: {
                            g_mrRes = CxMsgBoxRtf::mrIgnore;
                            ::SendMessage(hDlg, WM_CLOSE, (WPARAM)0, (LPARAM)0);
                        }
                        return TRUE;

                    case ID_btnCopyToClip: {
                            g_mrRes = CxMsgBoxRtf::mrCopyToClip;
                            ::SendMessage(g_hRedtText, WM_COPY, (WPARAM)0, (LPARAM)0);
                        }
                        return TRUE;

                    case ID_btnSendReport: {
                            g_mrRes = CxMsgBoxRtf::mrSendReport;
                            ::MessageBox(0, xT("ID_btnSendReport"), xT(""), MB_OK);
                        }
                        return TRUE;

                    default: {

                        }
                        return FALSE;
                }
            }
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
EModalResult
iShow(
    HWND                hwndOwner,
    const std::tstring &csMessage,
    const std::tstring &csTiltle
)
{
    HMODULE           hmRichEdtDll = NULL;
    HGLOBAL           hgbl         = INVALID_HANDLE_VALUE;
    LPDLGTEMPLATE     lpdt         = NULL;
    ////LPDLGITEMTEMPLATE lpdit        = NULL;
    LPWORD            lpw          = NULL;
    LPWSTR            lpwsz        = NULL;
    LRESULT           lpRes        = (LRESULT)NULL;
    INT               nchar        = - 1;

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
    nchar = 1 + csTiltle.size();
    lpw += nchar;

    g_sTitle   = csTiltle;
    g_sMessage = csMessage;

    ::GlobalUnlock(hgbl);
    lpRes = ::DialogBoxIndirect(g_hInst, (LPDLGTEMPLATE)hgbl, hwndOwner, reinterpret_cast<DLGPROC>(DialogProc));
    ::GlobalFree(hgbl);

    //-------------------------------------
    //unloading DLL
    if (NULL != hmRichEdtDll) {
        ::FreeLibrary(hmRichEdtDll);    hmRichEdtDll = NULL;
    }

    return /*lpRes*/g_mrRes;
}
//---------------------------------------------------------------------------
}; //namespace CxMsgBoxRtf
//---------------------------------------------------------------------------
