/**
 * \file  CxRichEdit.cpp
 * \brief rich edit
 */


#include <xLib/Gui/Win/CxRichEdit.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxRichEdit
CxRichEdit::CxRichEdit() {
    LOG();

    _m_bRes = _m_dlDll.bLoad(xT("RICHED32.DLL"));        //FIX: + Msftedit.dll
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName     = xCXRICHEDIT20_CONTROL_CLASS;
    _m_ulStyle        = xCXRICHEDIT_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXRICHEDIT_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXRICHEDIT_DEFAULT_WIDTH;
    _m_iHeight        = xCXRICHEDIT_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//TODO: - ~CxRichEdit
CxRichEdit::~CxRichEdit() {
    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxRichEdit::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText(iID),
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID),
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID),
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Selection
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetSel (The EM_EXGETSEL message retrieves the starting and ending character positions of the selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetSel(LONG *pliMin, LONG *pliMax)  {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    CHARRANGE chrRange = {0};

    xSNDMSG(VOID, EM_EXGETSEL, 0, &chrRange);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pliMin, *pliMin = chrRange.cpMin);
    xCHECK_DO(NULL != pliMax, *pliMax = chrRange.cpMax);

    //The range includes everything if cpMin is 0 and cpMax is �1.

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetSel (The EM_EXSETSEL message selects a range of characters or COM objects in a Rich Edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetSel(LONG liMin, LONG liMax) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    LONG liRes = 0;

    CHARRANGE chrRange = {liMin, liMax};

    liRes = xSNDMSG(LONG, EM_EXSETSEL, 0, &chrRange);
    /*DEBUG*/xASSERT_RET(liMax - liMin == liRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bHideSelection (The EM_HIDESELECTION message hides or shows the selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bHideSelection(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_HIDESELECTION, bFlag, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - stGetSelectionType (The EM_SELECTIONTYPE message determines the selection type for a rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::ESelectionType CxRichEdit::stGetSelectionType() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, stEmpty);

    return xSNDMSG(ESelectionType, EM_SELECTIONTYPE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Clip operations
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - METHOD_NAME (The EM_CANPASTE message determines whether a rich edit control can paste a specified clipboard format)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bCanPaste(INT iClipboardFormat /*0 - any format*/)  {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(BOOL, EM_CANPASTE, iClipboardFormat, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bCanRedo (The EM_CANREDO message determines whether there are any actions in the control redo queue)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bCanRedo()  {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return     xSNDMSG(BOOL, EM_CANREDO, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - METHOD_NAME (The EM_PASTESPECIAL message pastes a specific clipboard format in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bPasteSpecial(INT iClipboardFormat, ULONG ulAspect, ULONG ulParam) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    REPASTESPECIAL rpsRepasteSpecial = {ulAspect, ulParam};

    _m_bRes = xSNDMSG(BOOL, EM_PASTESPECIAL, iClipboardFormat, &rpsRepasteSpecial);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bRedo (Send an EM_REDO message to a rich edit control to redo the next action in the control's redo queue)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bRedo() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_REDO, 0, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetUndoLimit (An application sends an EM_SETUNDOLIMIT message to a rich edit control to set the maximum number of actions that can stored in the undo queue )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetUndoLimit(INT iNum) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = 0;

    iRes = xSNDMSG(INT, EM_SETUNDOLIMIT, iNum, 0);
    /*DEBUG*/xASSERT_RET(iNum == iRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - uidGetRedoName (An application sends an EM_GETREDONAME message to a rich edit control to retrieve the type of the next action, if any, in the control's redo queue)
#if (xWINVER >= xWIN32_2K)
UNDONAMEID CxRichEdit::uidGetRedoName() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, UID_UNKNOWN);

    UNDONAMEID uidEnumeration = UID_UNKNOWN;

    uidEnumeration = xSNDMSG(UNDONAMEID, EM_GETREDONAME, 0, 0);
    /*DEBUG*/xASSERT_RET(UID_UNKNOWN != uidEnumeration, UID_UNKNOWN);

    return uidEnumeration;
}
#endif //xWIN32_2K

//---------------------------------------------------------------------------
//TODO: - uidGetUndoName (Microsoft Rich Edit 20 and later: An application sends an EM_GETUNDONAME message to a rich edit control to retrieve the type of the next undo action, if any; Microsoft Rich Edit 10: This message is not supported)
#if (xWINVER >= xWIN32_2K)
UNDONAMEID CxRichEdit::uidGetUndoName() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, UID_UNKNOWN);

    UNDONAMEID uidEnumeration = UID_UNKNOWN;

    uidEnumeration = xSNDMSG(UNDONAMEID, EM_GETUNDONAME, 0, 0);
    /*DEBUG*/xASSERT_RET(UID_UNKNOWN != uidEnumeration, UID_UNKNOWN);

    return uidEnumeration;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Options
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - ovGetOptions (The EM_GETOPTIONS message retrieves rich edit control options)
//FIX: Return Value: This message returns a combination of the current option flag values described in the EM_SETOPTIONS message.
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EOptionValue CxRichEdit::ovGetOptions() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EOptionValue>(0));

    return xSNDMSG(EOptionValue, EM_GETOPTIONS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetOptions (The EM_SETOPTIONS message sets the options for a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetOptions(EOptionOperation ooOperation, EOptionValue ovValue) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(EOptionValue, EM_SETOPTIONS, ooOperation, ovValue);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetBidiOptions (The EM_GETBIDIOPTIONS message indicates the current state of the bidirectional options in the rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetBidiOptions(UINT *puiSize, USHORT *pusMask, USHORT *pusEffects) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    BIDIOPTIONS boOptions = {0};

    xSNDMSG(VOID, EM_GETBIDIOPTIONS, 0, &boOptions);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != puiSize,    *puiSize    = boOptions.cbSize);
    xCHECK_DO(NULL != pusMask,    *pusMask    = boOptions.wMask);
    xCHECK_DO(NULL != pusEffects, *pusEffects = boOptions.wEffects);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetBidiOptions (The EM_SETBIDIOPTIONS message sets the current state of the bidirectional options in the rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetBidiOptions(UINT uiSize, USHORT usMask, USHORT usEffects) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    BIDIOPTIONS boOptions = {uiSize, usMask, usEffects};

    xSNDMSG(VOID, EM_SETBIDIOPTIONS, 0, &boOptions);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - loGetLangOptions (An application sends an EM_GETLANGOPTIONS message to get a rich edit control's option settings for IME and Asian language support)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::ELangOption CxRichEdit::loGetLangOptions() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<ELangOption>(0));

    return xSNDMSG(ELangOption, EM_GETLANGOPTIONS, 0, 0);
    /*DEBUG*/// n/a ;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetLangOptions (An application sends an EM_SETLANGOPTIONS message to set options for IME and Asian language support in a rich edit control )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetLangOptions(ELangOption loOption) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    iRes = xSNDMSG(INT, EM_SETLANGOPTIONS, 0, loOption);
    /*DEBUG*/xASSERT_RET(1 == iRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - toGetTypographyOptions (The EM_GETTYPOGRAPHYOPTIONS message returns the current state of the typography options of a rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::ETypographyOption CxRichEdit::toGetTypographyOptions() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<ETypographyOption>(0));

    return xSNDMSG(ETypographyOption, EM_GETTYPOGRAPHYOPTIONS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetTypographyOptions (The EM_SETTYPOGRAPHYOPTIONS message sets the current state of the typography options of a rich edit control )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetTypographyOptions(ETypographyOption toOptions, ULONG ulMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETTYPOGRAPHYOPTIONS, toOptions, ulMask);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Scroll
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetScrollPos (An application sends an EM_GETSCROLLPOS message to obtain the current scroll position of the edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetScrollPos(LONG *pliX, LONG *pliY) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    POINT ptPos = {0, 0};

    iRes = xSNDMSG(INT, EM_GETSCROLLPOS, 0, &ptPos);
    /*DEBUG*/xASSERT_RET(1 == iRes, FALSE);

    xCHECK_DO(NULL != pliX, *pliX = ptPos.x);
    xCHECK_DO(NULL != pliY, *pliY = ptPos.y);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetScrollPos (An application sends an EM_SETSCROLLPOS message to tell the rich edit control to scroll to a particular point)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetScrollPos(LONG liX, LONG liY) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    POINT ptPos = {liX, liY};

    iRes = xSNDMSG(INT, EM_SETSCROLLPOS, 0, &ptPos);
    /*DEBUG*/xASSERT_RET(1 == iRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bShowScrollbar (The EM_SHOWSCROLLBAR message shows or hides one of the scroll bars in the Text Host window)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bShowScrollbar(BOOL bFlagVert, BOOL bFlagHorz) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_SHOWSCROLLBAR, SB_VERT, bFlagVert);
    /*DEBUG*/// n/a

    xSNDMSG(VOID, EM_SHOWSCROLLBAR, SB_HORZ, bFlagVert);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Style
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - stGetEditStyle (The EM_GETEDITSTYLE message retrieves the current edit style flags)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EEditStyle CxRichEdit::stGetEditStyle() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EEditStyle>(- 1));

    return xSNDMSG(EEditStyle, EM_GETEDITSTYLE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetEditStyle (The EM_SETEDITSTYLE message sets the current edit style flags)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetEditStyle(EEditStyle stStyle, EEditStyle stMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(EEditStyle, EM_SETEDITSTYLE, stStyle, stMask);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Text
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - sGetTextEx (The EM_GETTEXTEX message allows you to get all of the text from the rich edit control in any particular code base you want )
#if (xWINVER >= xWIN32_2K)
tString CxRichEdit::sGetTextEx(ULONG ulFlags, UINT uiCodePage, LPCSTR pcszDefaultChar, BOOL *pbUsedDefChar) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, tString());

    tString sRes;
    sRes.resize(ulGetTextLengthEx(ulFlags, uiCodePage));

    GETTEXTEX gtText = {sRes.size(), ulFlags, uiCodePage, pcszDefaultChar, pbUsedDefChar};

    ULONG ulRes = xSNDMSG(ULONG, EM_GETTEXTEX, &ulRes, &sRes.at(0));
    /*DEBUG*/xASSERT_RET(sRes.size() == ulRes, tString());

    return sRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - sGetSelText (The EM_GETSELTEXT message retrieves the currently selected text in a rich edit control)
#if (xWINVER >= xWIN32_2K)
tString CxRichEdit::sGetSelText() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, tString());

    tString sRes;
    sRes.resize(256/*ulGetTextLengthEx(ulFlags, uiCodePage)*/);        //FIX: string size

    ULONG ulRes = xSNDMSG(ULONG, EM_GETSELTEXT, 0, &sRes.at(0));
    /*DEBUG*/xASSERT_RET(sRes.size() == ulRes, tString());

    sRes.resize(ulRes);

    return sRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetTextEx (The EM_SETTEXTEX message combines the functionality of WM_SETTEXT and EM_REPLACESEL and adds the ability to set text using a code page and to use either rich text or plain text)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetTextEx(const tString &csStr, ULONG ulFlags, UINT uiCodePage) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    SETTEXTEX stText = {ulFlags, uiCodePage};

    iRes = xSNDMSG(INT, EM_SETTEXTEX, &stText, csStr.c_str());
    /*DEBUG*/xASSERT_RET( iRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - ulGetTextLengthEx (The EM_GETTEXTLENGTHEX message calculates text length in various ways)
#if (xWINVER >= xWIN32_2K)
ULONG CxRichEdit::ulGetTextLengthEx(ULONG ulFlags, UINT uiCodePage) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    ULONG ulRes = 0;

    GETTEXTLENGTHEX tlLength = {ulFlags, uiCodePage};

    ulRes = xSNDMSG(ULONG, EM_GETTEXTLENGTHEX, &tlLength, 0);
    /*DEBUG*/xASSERT_RET(E_INVALIDARG != ulRes, 0);

    return ulRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - METHOD_NAME (The EM_GETTEXTRANGE message retrieves a specified range of characters from a rich edit control)
#if (xWINVER >= xWIN32_2K)
tString CxRichEdit::sGetTextRange(LONG liMin, LONG liMax) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, tString());

    tString sRes;
    sRes.resize(liMax - liMin + 1);        //+ terminating null character

    CHARRANGE crRange = {liMin, liMax};
    TEXTRANGE trRange = {crRange, &sRes.at(0)};

    ULONG ulRes = xSNDMSG(ULONG, EM_GETTEXTRANGE, 0, &trRange);
    /*DEBUG*/xASSERT_RET(sRes.size() - 1 == ulRes, tString());

    sRes.resize(ulRes);

    return sRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - tmGetTextMode (An application sends an EM_GETTEXTMODE message to get the current text mode and undo level of a rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::ETextMode CxRichEdit::tmGetTextMode() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<ETextMode>(0));

    return xSNDMSG(ETextMode, EM_GETTEXTMODE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetTextMode (An application sends an EM_SETTEXTMODE message to set the text mode or undo level of a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetTextMode(ETextMode tmMode) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETTEXTMODE, tmMode, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bLimitText (The EM_EXLIMITTEXT message sets an upper limit to the amount of text the user can type or paste into a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bLimitText(LONG iChars) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_EXLIMITTEXT, 0, iChars);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Find
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - iFindText (The EM_FINDTEXT message finds text within a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bFindText(const tString &csText, LONG liMin, LONG liMax, EFindParams fpParams, LONG *pliFoundMin) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    CHARRANGE crRange = {liMin, liMax};
    FINDTEXT  ftText  = {crRange, csText.c_str()};

#if defined(UNICODE) || defined(_UNICODE)
    iRes = xSNDMSG(INT, EM_FINDTEXTW, fpParams, &ftText);
#else
    iRes = xSNDMSG(INT, EM_FINDTEXT,  fpParams, &ftText);
#endif // UNICODE

    /*DEBUG*/// n/a
    xCHECK_RET(- 1 == iRes, FALSE);

    //-------------------------------------
    //����� ������
    xCHECK_DO(NULL != pliFoundMin, *pliFoundMin = iRes);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bFindTextEx (The EM_FINDTEXTEX message finds text within a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bFindTextEx(const tString &csText, LONG liMin, LONG liMax, EFindParams fpParams, LONG *pliFoundMin, LONG *pliFoundMax) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

    INT iRes = - 1;

    CHARRANGE  crRange    = {liMin, liMax};
    CHARRANGE  crRangeOut = {0};
    FINDTEXTEX ftTextEx   = {crRange, csText.c_str(), crRangeOut};

#if defined(UNICODE) || defined(_UNICODE)
    iRes = xSNDMSG(INT, EM_FINDTEXTEXW, fpParams, &ftTextEx);
#else
    iRes = xSNDMSG(INT, EM_FINDTEXTEX,  fpParams, &ftTextEx);
#endif // UNICODE

    /*DEBUG*/// n/a
    xCHECK_RET(- 1 == iRes,             FALSE);
    xCHECK_RET(- 1 == crRangeOut.cpMin, FALSE);
    xCHECK_RET(- 1 == crRangeOut.cpMax, FALSE);
    /*DEBUG*/xASSERT_RET(crRangeOut.cpMin == iRes, FALSE);

    //-------------------------------------
    //����� ������
    xCHECK_DO(NULL != pliFoundMin, *pliFoundMin = crRangeOut.cpMin);
    xCHECK_DO(NULL != pliFoundMax, *pliFoundMax = crRangeOut.cpMax);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//EM_FINDTEXTW        The EM_FINDTEXTW message finds Unicode text within a rich edit control
//EM_FINDTEXTEXW    The EM_FINDTEXTEXW message finds Unicode text within a rich edit control
//---------------------------------------------------------------------------
//TODO: - liFindWordBreak (The EM_FINDWORDBREAK message finds the next word break before or after the specified character position or retrieves information about the character at that position)
#if (xWINVER >= xWIN32_2K)
LONG CxRichEdit::liFindWordBreak(EFindOperation foOperation, LONG liPos) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

    return xSNDMSG(LONG, EM_FINDWORDBREAK, foOperation, liPos);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, IME
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bIsIme (An application sends a EM_ISIME message to determine if current input locale is an East Asian locale )
#if (xWINVER >= xWIN32_S03)
BOOL CxRichEdit::bIsIme() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(BOOL, EM_ISIME, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_S03
//---------------------------------------------------------------------------
//TODO: - ivGetImeOptions (The EM_GETIMEOPTIONS message retrieves the current IME options This message is available only in Asian-language versions of the operating system)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EImeOptionValue CxRichEdit::ivGetImeOptions() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EImeOptionValue>(0));

    return xSNDMSG(EImeOptionValue, EM_GETIMEOPTIONS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetImeOptions (The EM_SETIMEOPTIONS message sets the IME options)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetImeOptions(EOptionOperation ooOperation, EImeOptionValue ioValue) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETIMEOPTIONS, ooOperation, ioValue);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - ibmGetImeModeBias (An application sends an EM_GETIMEMODEBIAS message to get the IME mode bias for a Rich Edit control)
#if (xWINVER >= xWIN32_SO3)
CxRichEdit::EImeBiasMode CxRichEdit::ibmGetImeModeBias() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EImeBiasMode>(0));

    return xSNDMSG(EImeBiasMode, EM_GETIMEMODEBIAS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bSetImeModeBias (An application sends an EM_SETIMEMODEBIAS message to set the IME mode bias for a Rich Edit control )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bSetImeModeBias(EImeBiasMode ibmMode) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    EImeBiasMode ibmRes;

    ibmRes = xSNDMSG(EImeBiasMode, EM_SETIMEMODEBIAS, ibmMode, ibmMode);
    /*DEBUG*/xASSERT_RET(ibmMode == ibmRes, FALSE);

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - cbmGetCtfModeBias (An application sends a EM_GETCTFMODEBIAS message to get the Text Services Framework mode bias values for a Rich Edit control)
#if (xWINVER >= xWIN32_SO3)
CxRichEdit::ECtfBiasMode CxRichEdit::cbmGetCtfModeBias() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, cbmDefault);

    return xSNDMSG(ECtfBiasMode, EM_GETCTFMODEBIAS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bSetCtfModeBias (An application sends an EM_SETCTFMODEBIAS message to set the Text Services Framework (TSF) mode bias for a Rich Edit control )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bSetCtfModeBias(ECtfBiasMode cbmMode) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ECtfBiasMode cbmRes = cbmDefault;

    cbmRes = xSNDMSG(ECtfBiasMode, EM_SETCTFMODEBIAS, cbmMode, 0);
    /*DEBUG*/xASSERT_RET(cbmMode == cbmRes, FALSE);

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bGetCtfOpenStatus (An application sends an EM_GETCTFOPENSTATUS message to determine if the Text Services Framework (TSF) keyboard is open or closed )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bGetCtfOpenStatus() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(BOOL, EM_GETCTFOPENSTATUS, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: bSetCtfOpenStatus (An application sends an EM_SETCTFOPENSTATUS message to open or close the Text Services Framework (TSF) keyboard )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bSetCtfOpenStatus(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETCTFOPENSTATUS, bFlag, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bGetImeColor (The EM_GETIMECOLOR message retrieves the Input Method Editor (IME) composition color)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetImeColor(COMPCOLOR *pccColor[4]) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_GETIMECOLOR, 0, pccColor);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetImeColor (The EM_SETIMECOLOR message sets the IME composition color)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetImeColor(COLORREF crText, COLORREF crBackground, ULONG ulEffects) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    COMPCOLOR ccColor = {crText, crBackground, ulEffects};

    _m_bRes = xSNDMSG(BOOL, EM_SETIMECOLOR, 0, &ccColor);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - icmGetImeCompMode (An application sends an EM_GETIMECOMPMODE message to get the current IME mode for a rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EImeCompMode CxRichEdit::icmGetImeCompMode() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EImeCompMode>(- 1));

    return xSNDMSG(EImeCompMode, EM_GETIMECOMPMODE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - sGetImeCompText (EM_GETIMECOMPTEXT    An application sends an EM_GETIMECOMPTEXT message to get the IME composition text )
#if (xWINVER >= xWIN32_SO3)
tString CxRichEdit::sGetImeCompText(ULONG ulFlags) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, tString());

    tString sRes;

    sRes.resize(256);    //FIX: str size

    IMECOMPTEXT ictText = {sRes.size(), ulFlags};

    LONG liRes = xSNDMSG(LONG, EM_GETIMECOMPTEXT, &ictText, &sRes.at(0));
    /*DEBUG*///FIX: xASSERT_RET(sRes.size() == liRes, tString());

    sRes.resize(liRes);

    return sRes;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - iGetImeProperty (An application sends a EM_GETIMEPROPERTY message to get the property and capabilities of the IME associated with the current input locale )
#if (xWINVER >= xWIN32_SO3)
INT CxRichEdit::iGetImeProperty(EImePropertyType iptType) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

    return xSNDMSG(INT, EM_GETIMEPROPERTY, iptType, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bGetReconversion (The EM_RECONVERSION message invokes the IME reconversion dialog box )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetReconversion() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(INT, EM_RECONVERSION, 0, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, WORD
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - wbmGetWordWrapMode (The EM_GETWORDWRAPMODE message gets the current word wrap and word-break options for the rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EWordWrapMode CxRichEdit::wbmGetWordWrapMode() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, static_cast<EWordWrapMode>(0));

    return xSNDMSG(EWordWrapMode, EM_GETWORDWRAPMODE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetWordWrapMode (The EM_SETWORDWRAPMODE message sets the word-wrapping and word-breaking options for the rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetWordWrapMode(EWordWrapMode wbmMode) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(EWordWrapMode, EM_SETWORDWRAPMODE, wbmMode, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - iGetWordBreakProcEx (The EM_GETWORDBREAKPROCEX message retrieves the address of the currently registered extended word-break procedure)
#if (xWINVER >= xWIN32_2K)
INT CxRichEdit::iGetWordBreakProcEx() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    INT iRes = NULL;

    iRes = xSNDMSG(INT, EM_GETWORDBREAKPROCEX, 0, 0);
    /*DEBUG*/xASSERT_RET(NULL != iRes, NULL);

    return iRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - iSetWordBreakProcEx (The EM_SETWORDBREAKPROCEX message sets the extended word-break procedure)
#if (xWINVER >= xWIN32_2K)
INT CxRichEdit::iSetWordBreakProcEx(INT *piProcEx /*NULL - default procedure*/) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return xSNDMSG(INT, EM_SETWORDBREAKPROCEX, 0, piProcEx);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Format
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetParaFormat (The EM_GETPARAFORMAT message retrieves the paragraph formatting of the current selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetParaFormat(PARAFORMAT *ppfFormat, ULONG *pulMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ULONG ulMask = 0;

    ulMask = xSNDMSG(ULONG, EM_GETPARAFORMAT, 0, ppfFormat);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pulMask, *pulMask = ulMask);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetParaFormat_20 (The EM_GETPARAFORMAT message retrieves the paragraph formatting of the current selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetParaFormat_20(PARAFORMAT2 *ppfFormat20, ULONG *pulMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ULONG ulMask = 0;

    ulMask = xSNDMSG(ULONG, EM_GETPARAFORMAT, 0, ppfFormat20);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pulMask, *pulMask = ulMask);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetParaFormat (The EM_SETPARAFORMAT message sets the paragraph formatting for the current selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetParaFormat(const PARAFORMAT *pcpfFormat) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ////(*pcpfFormat).cbSize = sizeof(PARAFORMAT);

    _m_bRes = xSNDMSG(BOOL, EM_SETPARAFORMAT, 0, pcpfFormat);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetParaFormat_20 (The EM_SETPARAFORMAT message sets the paragraph formatting for the current selection in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetParaFormat_20(const PARAFORMAT2 *pcpfFormat20) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ////(*pcpfFormat).cbSize = sizeof(PARAFORMAT2);

    _m_bRes = xSNDMSG(BOOL, EM_SETPARAFORMAT, 0, pcpfFormat20);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetCharFormat (The EM_GETCHARFORMAT message determines the character formatting in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetCharFormat(BOOL bFromSel, CHARFORMAT *pcfFormat, ULONG *pulMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ULONG ulMask = 0;

    ulMask = xSNDMSG(ULONG, EM_GETCHARFORMAT, (FALSE == bFromSel) ? SCF_DEFAULT : SCF_SELECTION, pcfFormat);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pulMask, *pulMask = ulMask);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetCharFormat_20 (The EM_GETCHARFORMAT message determines the character formatting in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetCharFormat_20(BOOL bFromSel, CHARFORMAT2 *pcfFormat20, ULONG *pulMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ULONG ulMask = 0;

    ulMask = xSNDMSG(ULONG, EM_GETCHARFORMAT, (FALSE == bFromSel) ? SCF_DEFAULT : SCF_SELECTION, pcfFormat20);
    /*DEBUG*/// n/a

    xCHECK_DO(NULL != pulMask, *pulMask = ulMask);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetCharFormat (The EM_SETCHARFORMAT message sets character formatting in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetCharFormat(ECharFormat cfFormat, CHARFORMAT *pcfFormat) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    (*pcfFormat).cbSize = sizeof(CHARFORMAT);

    _m_bRes = xSNDMSG(BOOL, EM_SETCHARFORMAT, cfFormat, pcfFormat);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetCharFormat_20 (The EM_SETCHARFORMAT message sets character formatting in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetCharFormat_20(ECharFormat cfFormat, CHARFORMAT2 *pcfFormat20) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ////(*pcfFormat).cbSize = sizeof(CHARFORMAT2);

    _m_bRes = xSNDMSG(BOOL, EM_SETCHARFORMAT, cfFormat, pcfFormat20);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bFormatRange (The EM_FORMATRANGE message formats a range of text in a rich edit control for a specific device)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bFormatRange(BOOL bDisplay, HDC hDC, HDC hDCTarget, RECT rcRect, RECT rcPage, LONG liMin, LONG liMax) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    CHARRANGE   crRange = {liMin, liMax};
    FORMATRANGE frRange = {hDC, hDCTarget, rcRect, rcPage, crRange};

    xSNDMSG(INT, EM_FORMATRANGE, bDisplay, &frRange);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Stream
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - liStreamIn (The EM_STREAMIN message replaces the contents of a rich edit control with a stream of data provided by an application defined�EditStreamCallback callback function)
#if (xWINVER >= xWIN32_2K)
LONG CxRichEdit::liStreamIn(EStreamFormat sfFormat, EStreamFormatFlag sffFlags, EDITSTREAM *pesStream) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    return xSNDMSG(LONG, EM_STREAMIN, sfFormat | sffFlags, pesStream);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - liStreamOut (The EM_STREAMOUT message causes a rich edit control to pass its contents to an application�defined EditStreamCallback callback function)
#if (xWINVER >= xWIN32_2K)
LONG CxRichEdit::liStreamOut(EStreamFormat sfFormat, EStreamFormatFlag sffFlags, EDITSTREAM *pesStream) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    return xSNDMSG(LONG, EM_STREAMOUT, sfFormat | sffFlags, pesStream);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Punctuation
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetPunctuation (The EM_GETPUNCTUATION message gets the current punctuation characters for the rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetPunctuation(EPunctuationType ptType, tString *psStr) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    PUNCTUATION pntPunct = {0, 0};

    _m_bRes = xSNDMSG(BOOL, EM_GETPUNCTUATION, ptType, &pntPunct);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    xCHECK_DO(NULL != psStr, (*psStr).assign(pntPunct.szPunctuation, pntPunct.iSize));

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetPunctuation (The EM_SETPUNCTUATION message sets the punctuation characters for a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetPunctuation(EPunctuationType ptType, const tString &csStr) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    PUNCTUATION pntPunct = {csStr.size(), const_cast<LPSTR>( &csStr.at(0) )};    //FIX: const_cast

    _m_bRes = xSNDMSG(BOOL, EM_SETPUNCTUATION, ptType, &pntPunct);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Url
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetAutoUrlDetect (The EM_GETAUTOURLDETECT message indicates whether the auto URL detection is turned on in the rich edit control )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetAutoUrlDetect() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    iRes = xSNDMSG(INT, EM_GETAUTOURLDETECT, 0, 0);
    /*DEBUG*/// n/a

    _m_bRes = (0 == iRes) ? FALSE : TRUE;

    return _m_bRes;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetAutoUrlDetect (An EM_AUTOURLDETECT message enables or disables automatic detection of URLs by a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetAutoUrlDetect(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    iRes = xSNDMSG(INT, EM_AUTOURLDETECT, bFlag, 0);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Zoom
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetZoom (The EM_GETZOOM message gets the current zoom ratio, which is always between 1/64 and 64)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetZoom(INT *piNumerator, INT *piDenominator) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xCHECK_RET(NULL == piNumerator || NULL == piDenominator, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_GETZOOM, piNumerator, piDenominator);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetZoom (The EM_SETZOOM message sets the zoom ratio anywhere between 1/64 and 64)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetZoom(INT iNumerator, INT iDenominator) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETZOOM, iNumerator, iDenominator);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Event
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - emGetEventMask (The EM_GETEVENTMASK message retrieves the event mask for a rich edit control)
#if (xWINVER >= xWIN32_2K)
CxRichEdit::EEventMask CxRichEdit::emGetEventMask() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, emNone);

    return xSNDMSG(EEventMask, EM_GETEVENTMASK, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetEventMask (The EM_SETEVENTMASK message sets the event mask for a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetEventMask(EEventMask emMask) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(EEventMask, EM_SETEVENTMASK, 0, emMask);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Hyphenate info
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetHyphenateInfo (An application sends an EM_GETHYPHENATEINFO message to get information about hyphenation for a Rich Edit control )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bGetHyphenateInfo(HYPHENATEINFO *phiInfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_GETHYPHENATEINFO, phiInfo, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - bSetHyphenateInfo (An application sends an EM_SETHYPHENATEINFO message to set the way a Rich Edit control does hyphenation )
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bSetHyphenateInfo(const HYPHENATEINFO *cphiInfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_SETHYPHENATEINFO, cphiInfo, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Page rotate
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bSetPageRotate (Deprecated, An application sends an EM_SETPAGEROTATE message to set the text layout for a Rich Edit control)
#if (xWINVER >= xWIN32_SO3)
BOOL CxRichEdit::bSetPageRotate(ETextLayout tlLayout) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ETextLayout tlRes = tlEpr_0;

    tlRes = xSNDMSG(ETextLayout, EM_SETPAGEROTATE, tlLayout, 0);
    /*DEBUG*/xASSERT_RET(tlLayout == tlRes, FALSE);

    return TRUE;
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------
//TODO: - tlGetPageRotate (Deprecated An application sends an EM_GETPAGEROTATE message to get the text layout for a Rich Edit control )
#if (xWINVER >= xWIN32_SO3)
CxRichEdit::ETextLayout CxRichEdit::tlGetPageRotate() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, tlEpr_0);

    return xSNDMSG(ETextLayout, EM_GETPAGEROTATE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_SO3
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������, Other
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bRequestResize (The EM_REQUESTRESIZE message forces a rich edit control to send an EN_REQUESTRESIZE notification code to its parent window)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bRequestResize() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_REQUESTRESIZE, 0, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetBkgndColor (The EM_SETBKGNDCOLOR message sets the background color for a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetBkgndColor(BOOL bUseDefault, COLORREF crColor) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(COLORREF, EM_SETBKGNDCOLOR, bUseDefault, crColor);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetFontSize (The EM_SETFONTSIZE message sets the font size for the selected text)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetFontSize(INT iSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// iSize - n/a

    xCHECK_DO(iSize < - 1637, iSize = - 1637);
    xCHECK_DO(iSize > 1638,   iSize = 1638);

    INT iRes = - 1;

    _m_bRes = xSNDMSG(BOOL, EM_SETFONTSIZE, iSize, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetOleCallback (The EM_SETOLECALLBACK message gives a rich edit control an IRichEditOleCallback object that the control uses to get OLE-related resources and information from the client)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetOleCallback(IUnknown *pIRichEditOleCallback) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETOLECALLBACK, 0, pIRichEditOleCallback);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetPalette (An application sends an EM_SETPALETTE message to change the palette that rich edit uses for its display window )
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetPalette(HANDLE hPalette) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(VOID, EM_SETPALETTE, hPalette, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetTargetDevice (The EM_SETTARGETDEVICE message sets the target device and line width used for "what you see is what you get" (WYSIWYG) formatting in a rich edit control)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bSetTargetDevice(HDC hDevice, LONG liLineWidth) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_SETTARGETDEVICE, hDevice, liLineWidth);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bStopGroupTyping (An application sends an EM_STOPGROUPTYPING message to a rich edit control to stop the control from collecting additional typing actions into the current undo action)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bStopGroupTyping() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_STOPGROUPTYPING, 0, 0);
    /*DEBUG*/xASSERT_RET(0 == _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetOleInterface (The EM_GETOLEINTERFACE message retrieves an IRichEditOle object that a client can use to access a rich edit control's COM functionality)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bGetOleInterface(IUnknown *pIRichEditOle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_GETOLEINTERFACE, 0, pIRichEditOle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bDisplayBand (The EM_DISPLAYBAND message displays a portion of the contents of a rich edit control, as previously formatted for a device using the EM_FORMATRANGE message)
#if (xWINVER >= xWIN32_2K)
BOOL CxRichEdit::bDisplayBand(RECT rcDevice) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, EM_DISPLAYBAND, 0, &rcDevice);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - liGetLineFromChar (The EM_EXLINEFROMCHAR message determines which line contains the specified character in a rich edit control)
#if (xWINVER >= xWIN32_2K)
LONG CxRichEdit::liGetLineFromChar(LONG liCharIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    LONG liRes = - 1;

    liRes = xSNDMSG(LONG, EM_EXLINEFROMCHAR, 0, liCharIndex);
    /*DEBUG*/xASSERT_RET(- 1 < liRes, FALSE);

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------










////---------------------------------------------------------------------------
////BOOL CxRichEdit::CanUndo() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (BOOL)::SendMessage(_m_hWnd, EM_CANUNDO, 0, 0L);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::GetLineCount() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (INT)::SendMessage(_m_hWnd, EM_GETLINECOUNT, 0, 0L);
////}
//////---------------------------------------------------------------------------
////BOOL CxRichEdit::GetModify() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (BOOL)::SendMessage(_m_hWnd, EM_GETMODIFY, 0, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::SetModify(BOOL bModified) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_SETMODIFY, bModified, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::GetRect(LPRECT lpRect) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_GETRECT, 0, (LPARAM)lpRect);
////}
//////---------------------------------------------------------------------------
////POINT CxRichEdit::GetCharPos(LONG lChar) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    POINT pt;
////    ::SendMessage(_m_hWnd, EM_POSFROMCHAR, (WPARAM) &pt, (LPARAM)lChar);
////
////    return pt;
////}
//////---------------------------------------------------------------------------
////// NOTE: first word in lpszBuffer must contain the size of the buffer!
////INT CxRichEdit::GetLine(INT nIndex, LPTSTR lpszBuffer) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (INT)::SendMessage(_m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::GetLine(INT nIndex, LPTSTR lpszBuffer, INT nMaxLength) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    *(LPINT)lpszBuffer = nMaxLength;
////
////    return (INT)::SendMessage(_m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::GetSel(LONG &nStartChar, LONG &nEndChar) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    CHARRANGE cr = {0};
////    ::SendMessage(_m_hWnd, EM_EXGETSEL, 0, (LPARAM) &cr);
////    nStartChar = cr.cpMin;
////    nEndChar = cr.cpMax;
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::GetSel(CHARRANGE &cr) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_EXGETSEL, 0, (LPARAM) &cr);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::LimitText(LONG nChars) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_EXLIMITTEXT, 0, nChars);
////}
//////---------------------------------------------------------------------------
////LONG CxRichEdit::LineFromChar(LONG nIndex) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (LONG)::SendMessage(_m_hWnd, EM_EXLINEFROMCHAR, 0, nIndex);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::SetSel(LONG nStartChar, LONG nEndChar) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    CHARRANGE cr = {0};
////    cr.cpMin = nStartChar;
////    cr.cpMax = nEndChar;
////
////    return (INT)::SendMessage(_m_hWnd, EM_EXSETSEL, 0, (LPARAM) &cr);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::SetSel(CHARRANGE &cr) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////    return (INT)::SendMessage(_m_hWnd, EM_EXSETSEL, 0, (LPARAM) &cr);
////}
//////---------------------------------------------------------------------------
////DWORD CxRichEdit::GetDefaultCharFormat(CHARFORMAT &cf) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    cf.cbSize = sizeof(CHARFORMAT);
////
////    return (DWORD)::SendMessage(_m_hWnd, EM_GETCHARFORMAT, 0, (LPARAM) &cf);
////}
//////---------------------------------------------------------------------------
////DWORD CxRichEdit::GetSelectionCharFormat(CHARFORMAT &cf) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    cf.cbSize = sizeof(CHARFORMAT);
////
////    return (DWORD)::SendMessage(_m_hWnd, EM_GETCHARFORMAT, 1, (LPARAM) &cf);
////}
//////---------------------------------------------------------------------------
////LONG CxRichEdit::GetEventMask() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (LONG)::SendMessage(_m_hWnd, EM_GETEVENTMASK, 0, 0L);
////}
//////---------------------------------------------------------------------------
////LONG CxRichEdit::GetLimitText() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (LONG)::SendMessage(_m_hWnd, EM_GETLIMITTEXT, 0, 0L);
////}
//////---------------------------------------------------------------------------
////DWORD CxRichEdit::GetParaFormat(PARAFORMAT &pf) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    pf.cbSize = sizeof(PARAFORMAT);
////
////    return (DWORD)::SendMessage(_m_hWnd, EM_GETPARAFORMAT, 0, (LPARAM) &pf);
////}
//////---------------------------------------------------------------------------
//////richedit EM_GETSELTEXT is ANSI
////LONG CxRichEdit::GetSelText(LPSTR lpBuf) const {
////
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (LONG)::SendMessage(_m_hWnd, EM_GETSELTEXT, 0, (LPARAM)lpBuf);
////}
//////---------------------------------------------------------------------------
////LONG CxRichEdit::GetTextLength() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (LONG)::SendMessage(_m_hWnd, WM_GETTEXTLENGTH, 0, 0L);
////}
//////---------------------------------------------------------------------------
////BOOL CxRichEdit::SetReadOnly(BOOL bReadOnly) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (BOOL)::SendMessage(_m_hWnd, EM_SETREADONLY, bReadOnly, 0L);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::GetFirstVisibleLine() const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (INT)::SendMessage(_m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0L);
////}
//////---------------------------------------------------------------------------
////// Operations
////VOID CxRichEdit::EmptyUndoBuffer() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_EMPTYUNDOBUFFER, 0, 0L);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::LineIndex(INT nLine) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (INT)::SendMessage(_m_hWnd, EM_LINEINDEX, nLine, 0L);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::LineLength(INT nLine) const {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (INT)::SendMessage(_m_hWnd, EM_LINELENGTH, nLine, 0L);
////}
//////---------------------------------------------------------------------------
////BOOL CxRichEdit::LineScroll(INT nLines, INT nChars) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (BOOL)::SendMessage(_m_hWnd, EM_LINESCROLL, nChars, nLines);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::SetRect(LPCRECT lpRect) {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_SETRECT, 0, (LPARAM)lpRect);
////}
//////---------------------------------------------------------------------------
////// Additional operations
////VOID CxRichEdit::ScrollCaret() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, EM_SCROLLCARET, 0, 0L);
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::InsertText(LONG nInsertAfterChar, LPCTSTR lpstrText, BOOL bCanUndo) {
////    INT nRet = SetSel(nInsertAfterChar, nInsertAfterChar);
////    ReplaceSel(lpstrText, bCanUndo);
////
////    return nRet;
////}
//////---------------------------------------------------------------------------
////INT CxRichEdit::AppendText(LPCTSTR lpstrText, BOOL bCanUndo) {
////    return InsertText(::GetWindowTextLength(_m_hWnd), lpstrText, bCanUndo);
////}
//////---------------------------------------------------------------------------
////// Clipboard operations
////BOOL CxRichEdit::Undo() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    return (BOOL)::SendMessage(_m_hWnd, EM_UNDO, 0, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::Clear() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, WM_CLEAR, 0, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::Copy() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, WM_COPY, 0, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::Cut() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, WM_CUT, 0, 0L);
////}
//////---------------------------------------------------------------------------
////VOID CxRichEdit::Paste() {
////    /*DEBUG*/xASSERT(::IsWindow(_m_hWnd));
////
////    ::SendMessage(_m_hWnd, WM_PASTE, 0, 0L);
////}
//////---------------------------------------------------------------------------
#endif
