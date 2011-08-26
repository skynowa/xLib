/**
 * \file  CxStatic.h
 * \brief static field
 */


#ifndef XLib_Gui_CxStaticH
#define XLib_Gui_CxStaticH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxStatic : 
    public CxWindow 
    /// static field
{
    public:
                 CxStatic  ();
        virtual ~CxStatic  ();

        BOOL     bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //сообщения


        //-------------------------------------
        //события
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxStaticH
