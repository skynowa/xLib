/**
 * \file  CxPushButton.h
 * \brief push button
 */


#ifndef XLib_Gui_CxPushButtonH
#define XLib_Gui_CxPushButtonH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxPushButton :
    public CxButtonBase
    /// push button
{
    public:
        //-------------------------------------
        //���������

        //���������
        enum ECheckState {
            csUknown     = - 1,
            csChecked     = BST_CHECKED,
            csUnchecked     = BST_UNCHECKED,
        };

        //����� (�����������/�����)
        enum EViewStyle {
            vsText   = BS_TEXT,
            vsBitmap = BS_BITMAP,
            vsIcon   = BS_ICON
        };

        //��� �����������
        enum EImageType {
            itBitmap   = IMAGE_BITMAP,
            itIcon       = IMAGE_ICON,
            itCursor   = IMAGE_CURSOR,
            itMetaFile = IMAGE_ENHMETAFILE
        };

                    CxPushButton (BOOL bRadioButtonLike);
        virtual    ~CxPushButton ();

        BOOL        bCreateRes   (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        BOOL        bSetViewStyle(EViewStyle vsViewStyle);
        BOOL        bSetImage    (EImageType itImageType, HANDLE hImage);

        ECheckState csGetState   ();
        BOOL        bSetState    (CxPushButton::ECheckState csCheckState);

        //-------------------------------------
        //�������

    private:
        EViewStyle _m_vsViewStyle;
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxPushButtonH
