/****************************************************************************
* Class name:  CxGroupBox
* Description: 
* File name:   CxGroupBox.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:10:19
*
*****************************************************************************/


#ifndef XLib_Gui_CxGroupBoxH
#define XLib_Gui_CxGroupBoxH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxGroupBox: public CxButtonBase {
    public:
        //-------------------------------------
        //константы

                 CxGroupBox();
        virtual ~CxGroupBox();

        BOOL     bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //сообщения
                    

        //-------------------------------------
        //события
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxGroupBoxH