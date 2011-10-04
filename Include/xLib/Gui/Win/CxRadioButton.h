/**
 * \file  CxRadioButton.h
 * \brief radio button
 */


#ifndef XLib_Gui_CxRadioButtonH
#define XLib_Gui_CxRadioButtonH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxRadioButton :
    public CxButtonBase
    /// radio button
{
    public:
        //-------------------------------------
        //���������

        //���������
        enum ECheckState {
            csUknown    = - 1,
            csChecked    = BST_CHECKED,
            csUnchecked    = BST_UNCHECKED,
        };

                    CxRadioButton();
        virtual    ~CxRadioButton();

        BOOL        bCreateRes   (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        ECheckState bstGetState  ();
        BOOL        bSetState    (CxRadioButton::ECheckState csCheckState);

        //-------------------------------------
        //�������
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxRadioButtonH
