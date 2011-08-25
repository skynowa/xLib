/**
 * \file  xCommon.h
 * \brief
 */


#ifndef xLib_Gui_CommonH
#define xLib_Gui_CommonH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

///#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <commctrl.h>
#if defined(xCOMPILER_MS)
	#pragma comment(lib, "comctl32.lib")
#endif


//#include <Uxtheme.h>
#if defined(xCOMPILER_MS)
	//#pragma comment(lib, "UxTheme.lib")
#endif

#include <richedit.h>

//#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include <xLib/Log/CxTraceLog.h>
#include <xLib/Gui/Win/CxResources.h>


//---------------------------------------------------------------------------
//имена классов контролов
/*
ANIMATE_CLASS      - Creates animation controls. These controls silently display an audio video interleaved (AVI) clip.
DATETIMEPICK_CLASS - Creates date and time picker controls. These controls provide a simple interface to exchange date and time information with a user.
HOTKEY_CLASS       - Creates hot key controls. These controls make it easy for the user to define hot keys.
LINK_CLASS         - Creates syslink controls. These controls are used with links.
MONTHCAL_CLASS     - Creates month calendar controls. These controls provide a simple way for a user to select a date from a familiar interface.
NATIVEFNTCTL_CLASS - Creates native font controls. These controls are used with native fonts.
PROGRESS_CLASS     - Creates progress bars. These controls indicate the progress of a lengthy operation.
REBARCLASSNAME     - Creates rebar controls. These controls act as a container for child windows.
STANDARD_CLASSES   - Creates intrinsic User32 controls, such as button, edit, and scrollbar.
STATUSCLASSNAME    - Creates status windows. These controls display status information in a horizontal window.
TOOLBARCLASSNAME   - Creates toolbars. These controls contain buttons that carry out menu commands.
TOOLTIPS_CLASS     - Creates tooltip controls. These controls display a small pop-up window containing a line of text that describes the purpose of a tool in an application.
TRACKBAR_CLASS     - Creates trackbars. These controls let the user select from a range of values by moving a slider.
UPDOWN_CLASS       - Creates up-down controls. These controls combine a pair of arrows with an edit control. Clicking the arrows increments or decrements the value in the edit control.
WC_BUTTON          - Creates button controls. These controls enable a user to initiate an action.
WC_COMBOBOX        - Creates combobox controls. These controls contain a drop-down list from which a single item can be selected.
WC_COMBOBOXEX      - Creates ComboBoxEx controls. These controls provide an extension of the combo box control that provides native support for item images.
WC_EDIT            - Creates edit controls. These controls contain editable text.
WC_HEADER           - Creates header controls. These controls display headings at the top of columns of information and let the user sort the information by clicking the headings.
WC_LISTBOX         - Creates listbox controls. These controls contain lists of items.
WC_IPADDRESS       - Creates IP address controls. These controls are similar to an edit control, but they enable you to enter a numeric address in Internet protocol (IP) format.
WC_LINK            - Creates SysLink controls. These controls contain hypertext links.
WC_LISTVIEW        - Creates list-view controls. These controls display a collection of items, each consisting of an icon and a label, and provide several ways to arrange the items.
WC_NATIVEFONTCTL   - Creates native font controls. These are invisible controls that work in the background to enable a dialog box's predefined controls to display the current system language.
WC_PAGESCROLLER    - Creates pager controls. These controls are used to contain and scroll another window.
WC_SCROLLBAR       - Creates scrollbar controls. These controls enable the user to scroll the contents of a window.
WC_STATIC           - Creates static controls. These controls contain noneditable text.
WC_TABCONTROL       - Creates tab controls. These controls define multiple pages for the same area of a window or dialog box. Each page consists of a set of information or a group of controls that an application displays when the user selects the corresponding tab.
WC_TREEVIEW           - Creates tree-view controls. These controls display a hierarchical list of items. Each item consists of a label and an optional bitmap.
*/
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
//дефолтные оконные стили контролов
#define xCXFRAME_DEFAULT_WINDOW_STYLE           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
#define xCXFRAME_DEFAULT_WINDOW_STYLE_EX        0

#define xCXLAYOUT_DEFAULT_WINDOW_STYLE            WS_CHILD | WS_TABSTOP | WS_CAPTION
#define xCXLAYOUT_DEFAULT_WINDOW_STYLE_EX        WS_EX_CONTROLPARENT



#define xCXBUTTON_DEFAULT_WINDOW_STYLE          WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_TEXT /*| BS_NOTIFY*/
#define xCXBUTTON_DEFAULT_WINDOW_STYLE_EX       0

#define xCXPUSHBUTTON_DEFAULT_WINDOW_STYLE      WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX | BS_TEXT | BS_PUSHLIKE /*| BS_NOTIFY*/
#define xCXPUSHBUTTON_DEFAULT_WINDOW_STYLE_EX   0

#define xCXIMAGEBUTTON_DEFAULT_WINDOW_STYLE     WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON /*| BS_NOTIFY*/
#define xCXIMAGEBUTTON_DEFAULT_WINDOW_STYLE_EX  0

#define xCXCHECKBOX_DEFAULT_WINDOW_STYLE        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX /*| BS_NOTIFY*/
#define xCXCHECKBOX_DEFAULT_WINDOW_STYLE_EX     0

#define xCXRADIOBUTTON_DEFAULT_WINDOW_STYLE     WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON /*| BS_NOTIFY*/
#define xCXRADIOBUTTON_DEFAULT_WINDOW_STYLE_EX  0

#define xCXGROUPBOX_DEFAULT_WINDOW_STYLE        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX /*| BS_NOTIFY*/
#define xCXGROUPBOX_DEFAULT_WINDOW_STYLE_EX     0

#define xCXOWNERDRAWBUTTON_DEFAULT_WINDOW_STYLE WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW /*| BS_NOTIFY*/
#define xCXOWNERDRAWBUTTON_DEFAULT_WINDOW_STYLE_EX 0




#define xCXCOMBOBOX_DEFAULT_WINDOW_STYLE        WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWN | CBS_SORT | WS_VSCROLL     /*WS_CHILD | WS_VISIBLE | WS_TABSTOP*/
#define xCXCOMBOBOX_DEFAULT_WINDOW_STYLE_EX     0

#define xCXEDIT_DEFAULT_WINDOW_STYLE            WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL
#define xCXEDIT_DEFAULT_WINDOW_STYLE_EX         WS_EX_CLIENTEDGE

#define xCXMDICLIENT_DEFAULT_WINDOW_STYLE       0    //TODO:
#define xCXMDICLIENT_DEFAULT_WINDOW_STYLE_EX    0

#define xCXSCROLLBAR_DEFAULT_WINDOW_STYLE       0    //TODO:
#define xCXSCROLLBAR_DEFAULT_WINDOW_STYLE_EX    0

#define xCXSTATIC_DEFAULT_WINDOW_STYLE          WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_SIMPLE | SS_NOTIFY
#define xCXSTATIC_DEFAULT_WINDOW_STYLE_EX       0

#define xCXPICTURE_DEFAULT_WINDOW_STYLE         WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_BITMAP | SS_NOTIFY
#define xCXPICTURE_DEFAULT_WINDOW_STYLE_EX      0



#define xCXLISTBOX_DEFAULT_WINDOW_STYLE         WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT
#define xCXLISTBOX_DEFAULT_WINDOW_STYLE_EX      WS_EX_CLIENTEDGE

#define xCXSTATUSBAR_DEFAULT_WINDOW_STYLE       WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | CCS_BOTTOM
#define xCXSTATUSBAR_DEFAULT_WINDOW_STYLE_EX    0

#define xCXPROGRESSBAR_DEFAULT_WINDOW_STYLE     WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER
#define xCXPROGRESSBAR_DEFAULT_WINDOW_STYLE_EX  0

#define xCXLISTVIEW_DEFAULT_WINDOW_STYLE        WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| LVS_REPORT*/
#define xCXLISTVIEW_DEFAULT_WINDOW_STYLE_EX     0

#define xCXRICHEDIT_DEFAULT_WINDOW_STYLE        WS_CHILD | WS_VISIBLE | WS_TABSTOP
#define xCXRICHEDIT_DEFAULT_WINDOW_STYLE_EX     0

#define xCXTAB_DEFAULT_WINDOW_STYLE               WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | TCS_FOCUSNEVER | TCS_SINGLELINE//WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS
#define xCXTAB_DEFAULT_WINDOW_STYLE_EX          0
//---------------------------------------------------------------------------
//дефолтные размеры контролов (ширина, высота)
#define xCXFRAME_DEFAULT_WIDTH                  CW_USEDEFAULT
#define xCXFRAME_DEFAULT_HEIGHT                 CW_USEDEFAULT

#define xCXLAYOUT_DEFAULT_WIDTH                 CW_USEDEFAULT
#define xCXLAYOUT_DEFAULT_HEIGHT                CW_USEDEFAULT


#define xCXBUTTON_DEFAULT_WIDTH                 75
#define xCXBUTTON_DEFAULT_HEIGHT                25

#define xCXPUSHBUTTON_DEFAULT_WIDTH             75
#define xCXPUSHBUTTON_DEFAULT_HEIGHT            25

#define xCXIMAGEBUTTON_DEFAULT_WIDTH            30
#define xCXIMAGEBUTTON_DEFAULT_HEIGHT           25

#define xCXCHECKBOX_DEFAULT_WIDTH               200
#define xCXCHECKBOX_DEFAULT_HEIGHT              17

#define xCXRADIOBUTTON_DEFAULT_WIDTH            120
#define xCXRADIOBUTTON_DEFAULT_HEIGHT           17

#define xCXGROUPBOX_DEFAULT_WIDTH               200
#define xCXGROUPBOX_DEFAULT_HEIGHT              200

#define xCXOWNERDRAWBUTTON_DEFAULT_WIDTH        25
#define xCXOWNERDRAWBUTTON_DEFAULT_HEIGHT       75


#define xCXCOMBOBOX_DEFAULT_WIDTH               120
#define xCXCOMBOBOX_DEFAULT_HEIGHT              21 * 20

#define xCXEDIT_DEFAULT_WIDTH                   120
#define xCXEDIT_DEFAULT_HEIGHT                  21

#define xCXMDICLIENT_DEFAULT_WIDTH              CW_USEDEFAULT
#define xCXMDICLIENT_DEFAULT_HEIGHT             CW_USEDEFAULT

#define xCXSCROLLBAR_DEFAULT_WIDTH              0
#define xCXSCROLLBAR_DEFAULT_HEIGHT             0

#define xCXSTATIC_DEFAULT_WIDTH                 120
#define xCXSTATIC_DEFAULT_HEIGHT                13

#define xCXPICTURE_DEFAULT_WIDTH                120
#define xCXPICTURE_DEFAULT_HEIGHT               120





#define xCXLISTBOX_DEFAULT_WIDTH                100
#define xCXLISTBOX_DEFAULT_HEIGHT               120

#define xCXSTATUSBAR_DEFAULT_WIDTH              0
#define xCXSTATUSBAR_DEFAULT_HEIGHT             0

#define xCXPROGRESSBAR_DEFAULT_WIDTH            120
#define xCXPROGRESSBAR_DEFAULT_HEIGHT           23

#define xCXLISTVIEW_DEFAULT_WIDTH               200
#define xCXLISTVIEW_DEFAULT_HEIGHT              200

#define xCXRICHEDIT_DEFAULT_WIDTH               120
#define xCXRICHEDIT_DEFAULT_HEIGHT              120

#define xCXTAB_DEFAULT_WIDTH                    650
#define xCXTAB_DEFAULT_HEIGHT                   350
//---------------------------------------------------------------------------
#define xSNDMSG(TCastType, uiMsg, wParam, lParam) \
    ((TCastType)( pSendMessage((UINT)(uiMsg), (WPARAM)(wParam), (LPARAM)(lParam)) ));

#define xSNDMSG_API(TCastType, hWnd, uiMsg, wParam, lParam) \
    ((TCastType)( ::SendMessage((HWND)(hWnd), (UINT)(uiMsg), (WPARAM)(wParam), (LPARAM)(lParam)) ));

#define LOG()                                  _m_tlLog.bWrite(xT(__FUNCTION__))
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CommonH






