/**
 * \file  CxCheckBox.h
 * \brief checkbox
 */


#ifndef XLib_Gui_CxCheckBoxH
#define XLib_Gui_CxCheckBoxH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxCheckBox: public CxButtonBase {
    public:
        //-------------------------------------
        //���������

        //���������
        enum ECheckState {
            csUknown    = - 1,
            csChecked    = BST_CHECKED,
            csGrayed    = BST_INDETERMINATE,
            csUnchecked = BST_UNCHECKED,
        };

                    CxCheckBox     ();
        virtual    ~CxCheckBox     ();

        BOOL        bCreateRes     (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        ECheckState csGetState     ();
        BOOL        bSetState      (CxCheckBox::ECheckState csCheckState);
        BOOL        bSetAllowGrayed(BOOL bFlag);

        //-------------------------------------
        //�������

};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxCheckBoxH
