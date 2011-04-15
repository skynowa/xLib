/****************************************************************************
* Class name:
* Description: файл ресурсов (синтаксис С++)
* File name:   Resource.xrc
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     07.09.2009 9:44:20
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_ResourceXrcH
#define XLib_Gui_ResourceXrcH

#include <xLib/GUI/Resource.xrc.h>
#include <tchar.h>

/****************************************************************************
*   IDD_DIALOG1
*
*****************************************************************************/


//---------------------------------------------------------------------------
//_bInitControl(INT iID, const tstring &csText, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx);
//---------------------------------------------------------------------------
_bInitControl(IDD_DIALOG1,          xT("wndMain"),          0,   0,    600, 500, 0, 0);

_bInitControl(IDC_btnButton1,       xT("btnButton1"),       10,  11,   100,  75,  0, 0);
_bInitControl(IDC_btnPushButton1,   xT("btnPushButton1"),   240, 11,   100,  75,  0, 0);
_bInitControl(IDC_chkCheckBox1,     xT("chkCheckBox1"),     10,  202,  100,  16,  0, 0);
_bInitControl(IDC_rbtnRadioButton1, xT("rbtnRadioButton1"), 10,  400,  100,  16,  0, 0);
_bInitControl(IDC_grpbGroupBox1,    xT("grpbGroupBox1"),    10,  128,  100,  65,  0, 0);


_bInitControl(IDC_edtEdit1,         xT("edtEdit1"),         10,  100,  100,  23,  0, 0);
_bInitControl(IDC_cboComboBox1,     xT("cboComboBox1"),     10,  234,  100,  49,  0, 0);
_bInitControl(IDC_staStatic1,       xT("staStatic1"),       10,  270,  100,  13,  0, 0);
_bInitControl(IDC_picPicture1,      xT("picPicture1"),      10,  364,  100,  13,  0, 0);
_bInitControl(IDC_lstListBox1,      xT("lstListBox1"),      10,  294,  100,  55,  LBS_SORT | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, 0);
_bInitControl(IDC_lvListView1,      xT("lvListView1"),      120,  11,  100,  81,  LVS_LIST | LVS_ALIGNLEFT | WS_BORDER, 0);
_bInitControl(IDC_prgProgressBar1,  xT("prgProgressBar1"),  120,  98,  100,  23,  WS_BORDER, 0);
_bInitControl(IDC_redtRichEdit1,    xT("redtRichEdit1"),    120,  124, 220,  100, ES_AUTOHSCROLL | WS_BORDER, 0);
_bInitControl(IDC_stabStatusBar1,   xT("stabStatusBar1"),   0,    0,   0,   0,   0, 0);
_bInitControl(IDC_tabTab1,          xT("tabTab1"),          120,  240, 300, 200, 0, 0);


_bInitControl(IDC_btnExit,          xT("Exit"),             500, 400,  75,  23,  0, 0);
//---------------------------------------------------------------------------


/****************************************************************************
*   IDD_WND_DIALOG
*
*****************************************************************************/

//---------------------------------------------------------------------------
_bInitControl(IDD_WND_DIALOG,      xT("About Dialog"),    100,   200,   300, 200, 0, 0);
//---------------------------------------------------------------------------

/****************************************************************************
*   IDD_WND_SHEET
*
*****************************************************************************/

//---------------------------------------------------------------------------
_bInitControl(IDD_WND_SHEET1,      xT("Layout1"),    100,   200,   300, 200, 0, 0);
_bInitControl(IDD_WND_SHEET2,      xT("Layout2"),    100,   200,   300, 200, 0, 0);
//---------------------------------------------------------------------------
#endif //XLib_Gui_ResourceXrcH
