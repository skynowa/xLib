/**
 * \file  CxStatic.h
 * \brief static field
 */


#ifndef XLib_Gui_CxStaticH
#define XLib_Gui_CxStaticH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/CxWindow.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxStatic :
    public CxWindow
    /// static field
{
    public:
                 CxStatic  ();
        virtual ~CxStatic  ();

        BOOL     bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������


        //-------------------------------------
        //�������
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxStaticH
