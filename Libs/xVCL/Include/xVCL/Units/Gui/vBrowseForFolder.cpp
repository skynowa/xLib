/**********************************************************************
*	vBrowseForFolder.cpp	
*
***********************************************************************/


#include "uDicMaker.h"


//---------------------------------------------------------------------------
tString __fastcall asBrowseForFolder() {
    char FileName[MAX_PATH + 1];
    BROWSEINFO bi;
    memcpy(FileName, "C:", 3);
    bi.hwndOwner      = /*hWnd*/0;
    bi.pidlRoot       = NULL;
    bi.pszDisplayName = FileName;
    bi.lpszTitle      = "Заголовок";
    bi.ulFlags        = BIF_STATUSTEXT
                          |BIF_BROWSEFORCOMPUTER
                          |BIF_EDITBOX
                          |BIF_NEWDIALOGSTYLE
                          /*|BIF_NONEWFOLDERBUTTON*/
                          |BIF_USENEWUI;
                          //|BIF_BROWSEINCLUDEFILES;
    bi.lpfn           = /*BrowseCallbackProc*/NULL;

    SHGetPathFromIDList(SHBrowseForFolder(&bi), FileName);

    return tString(FileName);
}
//---------------------------------------------------------------------------
