/****************************************************************************
* Class name:  
* Description: файл ресурсов (синтаксис С++)
* File name:   Resource.xrc
* String type: Ansi
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.09.2009 9:44:20
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
_bInitControl(IDD_DIALOG1,          _T("wndMain"),          0,   0,    600, 500, 0, 0);

_bInitControl(IDC_btnButton1,       _T("btnButton1"),       10,  11,   100,  75,  0, 0);
_bInitControl(IDC_btnPushButton1,   _T("btnPushButton1"),   240, 11,   100,  75,  0, 0);
_bInitControl(IDC_chkCheckBox1,     _T("chkCheckBox1"),     10,  202,  100,  16,  0, 0);
_bInitControl(IDC_rbtnRadioButton1, _T("rbtnRadioButton1"), 10,  400,  100,  16,  0, 0);
_bInitControl(IDC_grpbGroupBox1,    _T("grpbGroupBox1"),    10,  128,  100,  65,  0, 0);


_bInitControl(IDC_edtEdit1,         _T("edtEdit1"),         10,  100,  100,  23,  0, 0);
_bInitControl(IDC_cboComboBox1,     _T("cboComboBox1"),     10,  234,  100,  49,  0, 0);
_bInitControl(IDC_staStatic1,       _T("staStatic1"),       10,  270,  100,  13,  0, 0);
_bInitControl(IDC_picPicture1,      _T("picPicture1"),      10,  364,  100,  13,  0, 0);
_bInitControl(IDC_lstListBox1,      _T("lstListBox1"),      10,  294,  100,  55,  LBS_SORT | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, 0);
_bInitControl(IDC_lvListView1,      _T("lvListView1"),      120,  11,  100,  81,  LVS_LIST | LVS_ALIGNLEFT | WS_BORDER, 0);
_bInitControl(IDC_prgProgressBar1,  _T("prgProgressBar1"),  120,  98,  100,  23,  WS_BORDER, 0);
_bInitControl(IDC_redtRichEdit1,    _T("redtRichEdit1"),    120,  124, 220,  100, ES_AUTOHSCROLL | WS_BORDER, 0);
_bInitControl(IDC_stabStatusBar1,   _T("stabStatusBar1"),   0,    0,   0,   0,   0, 0);
_bInitControl(IDC_tabTab1,          _T("tabTab1"),          120,  240, 300, 200, 0, 0);


_bInitControl(IDC_btnExit,          _T("Exit"),             500, 400,  75,  23,  0, 0);
//---------------------------------------------------------------------------


/****************************************************************************
*   IDD_WND_DIALOG
*
*****************************************************************************/

//---------------------------------------------------------------------------
_bInitControl(IDD_WND_DIALOG,      _T("About Dialog"),    100,   200,   300, 200, 0, 0);
//---------------------------------------------------------------------------

/****************************************************************************
*   IDD_WND_SHEET
*
*****************************************************************************/

//---------------------------------------------------------------------------
_bInitControl(IDD_WND_SHEET1,      _T("Layout1"),    100,   200,   300, 200, 0, 0);
_bInitControl(IDD_WND_SHEET2,      _T("Layout2"),    100,   200,   300, 200, 0, 0);
//---------------------------------------------------------------------------
#endif //XLib_Gui_ResourceXrcH