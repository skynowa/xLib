/****************************************************************************
* Class name:  CxStatic
* Description: ������ � ����������� �����
* File name:   CxStatic.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 11:20:41
*
*****************************************************************************/


#ifndef XLib_Gui_CxStaticH
#define XLib_Gui_CxStaticH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxStatic: public CxWindow {
    public:
                 CxStatic  ();
        virtual ~CxStatic  ();

        BOOL     bCreateRes(INT iID, CxWindow *pwndParent);
        
        //-------------------------------------
        //���������


        //-------------------------------------
        //�������
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxStaticH
