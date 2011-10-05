/**
 * \file  CxRebar.h
 * \brief rebar
 */


#ifndef XLib_Gui_CxRebarH
#define XLib_Gui_CxRebarH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/CxWindow.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxRebar :
    public CxWindow
    /// rebar
{
    public:
        enum AlignFlags    {
            AlignTop    = CCS_TOP,
            AlignBottom = CCS_BOTTOM,
            AlignLeft   = CCS_LEFT,
            AlignRight  = CCS_RIGHT,
        };

             CxRebar ();
            ~CxRebar();

        HWND Create(HWND hwndOwner,AlignFlags afFlag);
        VOID InsertBand(HWND hClientWnd,TCHAR* szName);
        BOOL DeleteBand(int numBand);
        VOID AutoSize();
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxRebarH
