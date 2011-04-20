/****************************************************************************
* Class name:  -
* Description: Карта сообщений 
* File name:   xMessageMap.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     31.08.2009 16:44:56
*
*****************************************************************************/


#ifndef xLib_Gui_xMessageMapH
#define xLib_Gui_xMessageMapH
//---------------------------------------------------------------------------
#include <xLib/Gui/xCommon.h>
//---------------------------------------------------------------------------
#define xDECLARE_MSG_MAP()                virtual LRESULT lpProcessMsg(UINT uiMsg, WPARAM wParam, LPARAM lParam) 

#define xBEGIN_MSG_MAP_NO_DECLARE()     virtual LRESULT lpProcessMsg(UINT uiMsg, WPARAM wParam, LPARAM lParam) {    

#define xBEGIN_MSG_MAP(_CXClass)         LRESULT _CXClass::lpProcessMsg(UINT uiMsg, WPARAM wParam, LPARAM lParam) {    

#define xMSG(_msg, _func)                if ((_msg) == uiMsg) {                                                \
                                            /*LOG*/_m_tlLog.bWrite(_T("xMSG:  %i, %i"), wParam, lParam);    \
                                                                                                            \
                                            (_func)(wParam, lParam);                                        \
                                                                                                            \
                                            return NULL;                                                    \
                                        }

#define xCMD(_id, _func)                if ((WM_COMMAND == uiMsg) && (LOWORD(wParam) == (_id))) {            \
                                            /*LOG*/_m_tlLog.bWrite(_T("xCMD:  %i, %i"), wParam, lParam);    \
                                                                                                            \
                                            (_func)(LOWORD(wParam), lParam);                                \
                                                                                                            \
                                            return NULL;                                                    \
                                        }

#define xEND_MSG_MAP(_CXParentClass)        return _CXParentClass::lpProcessMsg(uiMsg, wParam, lParam);        \
                                        };

#define xEND_MSG_MAP_NOPARENT                return NULL;                                                    \
                                        };
//---------------------------------------------------------------------------
#endif //xLib_Gui_xMessageMapH


/*
#define HANDLE_MSG(hwnd, message, fn)    \
        case (message): return HANDLE_##message((hwnd), (wParam), (lParam), (fn))
*/