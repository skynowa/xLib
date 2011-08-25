/**
 * \file  CxToolBar.cpp
 * \brief tool bar
 */


#include <xLib/Gui/CxToolBar.h>

//---------------------------------------------------------------------------
CxToolBar::CxToolBar() :
    CxWindow()
{
    _m_bIsControl     = TRUE;

    m_hInstance=GetModuleHandle(NULL);
    m_nBitmaps=0;
    m_nButtons=0;
    HANDLE hHeap=GetProcessHeap();
    m_InfoButtons=(ULTB_INFO_BUTTONS*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,sizeof(ULTB_INFO_BUTTONS));
}
//---------------------------------------------------------------------------
CxToolBar::~CxToolBar() {

}
//---------------------------------------------------------------------------
HWND CxToolBar::Create(HWND hParentWnd,
                DWORD tbStyle,
                DWORD tbExStyle,
                UINT tbID,//ID тулбара
                INT nBitmaps,//колличество битмапов в тулбаре(ресурс/ширина)
                UINT_PTR wBMID,//ID ресурса битмапа для тулбара
                INT dxButton,//ширина кнопки
                INT dyButton,//высота кнопки
                INT dxBitmap,//ширина картинки для кнопки
                INT dyBitmap)//высота картинки для кнопки
{
    _m_hParentWnd=hParentWnd;
    m_nBitmaps=nBitmaps;
    _m_hWnd= CreateToolbarEx(hParentWnd,
                            tbStyle,
                            tbID, nBitmaps, m_hInstance, wBMID,
                            0,0, dxButton, dyButton, dxBitmap, dyBitmap, sizeof (TBBUTTON));
    if(_m_hWnd!=NULL)
        SendMessage(_m_hWnd, TB_SETEXTENDEDSTYLE , 0, tbExStyle );
    return _m_hWnd;
}
//---------------------------------------------------------------------------
INT CxToolBar::AddButton(INT nBitmap,//номер картинки для тулбара (ресурс/ширина, счёт слева направо)
                INT idCommand,//ID контрола(кнопки)
                BYTE btnState,//состояние кнопки
                BYTE btnStyle,//стиль кнопки
                DWORD_PTR dwData,
                INT_PTR iString,//подпись для кнопки
                TCHAR* szTTip,//тултип для кнопки
                INT idMenu)//ID контекстного меню для кнопки(если btnStyle==BTNS_DROPDOWN)
{
//========================добавление в массив m_InfoButtons===============
    HANDLE hHeap=GetProcessHeap();
    ULTB_INFO_BUTTONS* tmpInfoButtons=(ULTB_INFO_BUTTONS*)HeapAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    memcpy(tmpInfoButtons,m_InfoButtons,(m_nButtons)*sizeof(ULTB_INFO_BUTTONS));
    m_nButtons++;
    m_InfoButtons=(ULTB_INFO_BUTTONS*)HeapReAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_InfoButtons,
        m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    memcpy(m_InfoButtons,tmpInfoButtons,(m_nButtons-1)*sizeof(ULTB_INFO_BUTTONS));
    HeapFree(hHeap,0,tmpInfoButtons);
    if((btnStyle&BTNS_SEP)==0)
    {
        if((btnStyle&BTNS_DROPDOWN)!=0)
            m_InfoButtons[m_nButtons-1].idMenu=idMenu;
        else
            m_InfoButtons[m_nButtons-1].idMenu=0;
        m_InfoButtons[m_nButtons-1].szToolTip=(TCHAR*)HeapAlloc(hHeap,
            HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, ::lstrlen(szTTip)*sizeof(TCHAR*));
        ::lstrcpy(m_InfoButtons[m_nButtons-1].szToolTip,szTTip);
        m_InfoButtons[m_nButtons-1].idCommand=idCommand;
        m_InfoButtons[m_nButtons-1].nBitmap=nBitmap;
    }
    else
    {
        m_InfoButtons[m_nButtons-1].idMenu=0;
        m_InfoButtons[m_nButtons-1].szToolTip=NULL;
        m_InfoButtons[m_nButtons-1].idCommand=0;
        m_InfoButtons[m_nButtons-1].nBitmap=0;
    }
//=========================================================================
    TBBUTTON tbButtonsAdd[]={nBitmap-m_nBitmaps, idCommand, btnState, btnStyle,
#if defined(_WIN32) | defined(_WIN64)
        {0},
#endif
        dwData, iString};
    TBADDBITMAP tb;
    INT  stdidx;
    tb.hInst = GetModuleHandle(NULL);
    tb.nID = 100;
    stdidx = (INT)SendMessage (_m_hWnd, TB_ADDBITMAP, 0, (LPARAM)&tb);
    for (INT i = 0; i < xARRAY_SIZE(tbButtonsAdd); i++)
        tbButtonsAdd[i].iBitmap += stdidx;
    SendMessage (_m_hWnd,
        TB_ADDBUTTONS,
        xARRAY_SIZE(tbButtonsAdd),
        (LPARAM) &tbButtonsAdd[0]);
    return TRUE;
}
//---------------------------------------------------------------------------
void CxToolBar::DoNotify(LPARAM lParam) {//вставить в обработчик WM_NOTIFY окна родителя
    #define lpnm   ((LPNMHDR)lParam)
    #define lpnmTB ((LPNMTOOLBAR)lParam)
    #define lpttt ((LPTOOLTIPTEXT)lParam)
    switch(lpnm->code)
    {
    case TTN_GETDISPINFO:
        {
            lpttt->hinst = m_hInstance;
            UINT_PTR idButton = lpttt->hdr.idFrom;
            for(INT i=0;i<m_nButtons;i++)
                if(idButton==m_InfoButtons[i].idCommand)
                {
                    lpttt->lpszText = m_InfoButtons[i].szToolTip;
                    break;
                }
            break;
        };
    case TBN_DROPDOWN:
        {
           RECT rc;
           TPMPARAMS tpm;
           HMENU hPopupMenu = NULL;
           HMENU hMenuLoaded;
           BOOL bRet = FALSE;
           SendMessage(lpnmTB->hdr.hwndFrom, TB_GETRECT,
               (WPARAM)lpnmTB->iItem, (LPARAM)&rc);
              MapWindowPoints(lpnmTB->hdr.hwndFrom,
               HWND_DESKTOP, (LPPOINT)&rc, 2);
           tpm.cbSize = sizeof(TPMPARAMS);
           tpm.rcExclude = rc;
           for(INT i=0;i<m_nButtons;i++)
                if(lpnmTB->iItem==m_InfoButtons[i].idCommand)
                {
                    hMenuLoaded = LoadMenu(m_hInstance, MAKEINTRESOURCE(m_InfoButtons[i].idMenu));
                    hPopupMenu = GetSubMenu(LoadMenu(m_hInstance,
                        MAKEINTRESOURCE(m_InfoButtons[i].idMenu)),0);
                    TrackPopupMenuEx(hPopupMenu,
                        TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
                        rc.left, rc.bottom, _m_hParentWnd, &tpm);
                    DestroyMenu(hMenuLoaded);
                }
                break;
        }
    }
}
//---------------------------------------------------------------------------
void CxToolBar::AutoSize() {//вставить в обработчик WM_SIZE окна родителя
    SendMessage(_m_hWnd, TB_AUTOSIZE, 0, 0);
}
//---------------------------------------------------------------------------
INT CxToolBar::DeleteButton(INT nButton) {
//========================удаление из массива m_InfoButtons===============
    HANDLE hHeap=GetProcessHeap();
    ULTB_INFO_BUTTONS* tmpInfoButtons=(ULTB_INFO_BUTTONS*)HeapAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    memcpy(tmpInfoButtons,m_InfoButtons,(m_nButtons)*sizeof(ULTB_INFO_BUTTONS));
    m_nButtons--;
    m_InfoButtons=(ULTB_INFO_BUTTONS*)HeapReAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_InfoButtons,
        m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    INT counter=0;
    for (INT i=0;i<(m_nButtons+1);i++)
        if (i!=nButton) {
            memcpy(m_InfoButtons+counter,tmpInfoButtons+i,sizeof(ULTB_INFO_BUTTONS));
            counter++;
        };
    HeapFree(hHeap,HEAP_NO_SERIALIZE,tmpInfoButtons);
    SendMessage(_m_hWnd,TB_DELETEBUTTON,nButton,0);

    return 0;
}
//---------------------------------------------------------------------------
INT CxToolBar::InsertButton(INT nInto,//куда вставить
                             INT nBitmap,
                             INT idCommand,
                             BYTE btnState,
                             BYTE btnStyle,
                             DWORD_PTR dwData,
                             INT_PTR iString,
                             TCHAR* szTTip,
                             INT idMenu)
{
//========================вставка в массив m_InfoButtons===============
    HANDLE hHeap=GetProcessHeap();
    ULTB_INFO_BUTTONS* tmpInfoButtons=(ULTB_INFO_BUTTONS*)HeapAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    memcpy(tmpInfoButtons,m_InfoButtons,(m_nButtons)*sizeof(ULTB_INFO_BUTTONS));
    m_nButtons++;
    m_InfoButtons=(ULTB_INFO_BUTTONS*)HeapReAlloc(hHeap,
        HEAP_ZERO_MEMORY,m_InfoButtons,
        m_nButtons*sizeof(ULTB_INFO_BUTTONS));
    memcpy(m_InfoButtons,tmpInfoButtons,(nInto)*sizeof(ULTB_INFO_BUTTONS));
    if((btnStyle&BTNS_SEP)==0)
    {
        if((btnStyle&BTNS_DROPDOWN)!=0)
            m_InfoButtons[nInto].idMenu=idMenu;
        m_InfoButtons[nInto].szToolTip=(TCHAR*)HeapAlloc(hHeap,
            HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY, ::lstrlen(szTTip)*sizeof(TCHAR*));
        ::lstrcpy(m_InfoButtons[nInto].szToolTip,szTTip);
        m_InfoButtons[nInto].idCommand=idCommand;
        m_InfoButtons[nInto].nBitmap=nBitmap;
    }
    else
    {
        m_InfoButtons[m_nButtons-1].idMenu=0;
        m_InfoButtons[m_nButtons-1].szToolTip=NULL;
        m_InfoButtons[m_nButtons-1].idCommand=0;
        m_InfoButtons[m_nButtons-1].nBitmap=0;
    }

    memcpy(m_InfoButtons+nInto+1,tmpInfoButtons+nInto,(m_nButtons-nInto-1)*sizeof(ULTB_INFO_BUTTONS));
    HeapFree(hHeap,HEAP_NO_SERIALIZE,tmpInfoButtons);

//===========================================================
    TBBUTTON tbButtonsAdd={nBitmap, idCommand, btnState, btnStyle,
#if defined(_WIN32) | defined(_WIN64)
        {0},
#endif
        dwData, iString};
    SendMessage(_m_hWnd,TB_INSERTBUTTON,nInto,LPARAM(&tbButtonsAdd));
    return 0;
}
//---------------------------------------------------------------------------
