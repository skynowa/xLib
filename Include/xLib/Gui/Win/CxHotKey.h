/**
 * \file  CxHotkey.h
 * \brief hotkey
 */


#ifndef XLib_Gui_CXHotKeyH
#define XLib_Gui_CXHotKeyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CXHotKey :
    public CxNonCopyable
    /// hotkey
{
    public:
        CXHotKey();
       ~CXHotKey();
};
#endif
//---------------------------------------------------------------------------
#endif //XLib_Gui_CXHotKeyH
