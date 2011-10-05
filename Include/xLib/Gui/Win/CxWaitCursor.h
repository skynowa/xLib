/**
 * \file  CxWaitCursor.h
 * \brief wait cursor
 */


#ifndef xLib_Gui_CxWaitCursorH
#define xLib_Gui_CxWaitCursorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxWaitCursor :
    public CxNonCopyable
    /// wait cursor
{
    public:
                CxWaitCursor();
               ~CxWaitCursor();

        BOOL    bRestore    ();

    private:
        HCURSOR _m_hCursor;
};
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxWaitCursorH
