/****************************************************************************
* Class name:  CxOwnerDrawButton
* Description: 
* File name:   CxOwnerDrawButton.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:38:38
*
*****************************************************************************/


#ifndef XLib_Gui_CxOwnerDrawButtonH
#define XLib_Gui_CxOwnerDrawButtonH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxOwnerDrawButton: public CxButtonBase {
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