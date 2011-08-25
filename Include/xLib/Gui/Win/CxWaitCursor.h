/**
 * \file  CxWaitCursor.h
 * \brief wait cursor
 */


#ifndef xLib_Gui_CxWaitCursorH
#define xLib_Gui_CxWaitCursorH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------
class CxWaitCursor : public CxNonCopyable {
    public:
                CxWaitCursor();
               ~CxWaitCursor();

        BOOL    bRestore    ();

    private:
        HCURSOR _m_hCursor;
};
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxWaitCursorH
