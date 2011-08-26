/**
 * \file  CxOwnerDrawButton.h
 * \brief owner draw button
 */


#ifndef XLib_Gui_CxOwnerDrawButtonH
#define XLib_Gui_CxOwnerDrawButtonH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxOwnerDrawButton : 
    public CxButtonBase 
    /// owner draw button    
{
    public:
        //-------------------------------------
        //константы

                 CxOwnerDrawButton();
        virtual ~CxOwnerDrawButton();

        BOOL     bCreateRes       (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //сообщения


        //-------------------------------------
        //события

};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxOwnerDrawButtonH
