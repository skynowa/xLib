/****************************************************************************
* Class name:  CxWaitCursor
* Description: wait cursor
* File name:   CxWaitCursor.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.06.2009 19:08:17
*
*****************************************************************************/


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