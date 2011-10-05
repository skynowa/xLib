/**
 * \file  CxOwnerDrawButton.h
 * \brief owner draw button
 */


#ifndef XLib_Gui_CxOwnerDrawButtonH
#define XLib_Gui_CxOwnerDrawButtonH
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

#include <xLib/Gui/Win/CxWindow.h>
#include <xLib/Gui/Win/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxOwnerDrawButton :
    public CxButtonBase
    /// owner draw button
{
    public:
        //-------------------------------------
        //���������

                 CxOwnerDrawButton();
        virtual ~CxOwnerDrawButton();

        BOOL     bCreateRes       (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������


        //-------------------------------------
        //�������

};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxOwnerDrawButtonH
