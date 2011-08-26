/**
 * \file  CxGroupBox.h
 * \brief group box
 */


#ifndef XLib_Gui_CxGroupBoxH
#define XLib_Gui_CxGroupBoxH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxGroupBox : 
    public CxButtonBase 
    /// group box   
{
    public:
        //-------------------------------------
        //���������

                 CxGroupBox();
        virtual ~CxGroupBox();

        BOOL     bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������


        //-------------------------------------
        //�������
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxGroupBoxH
