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
class CxPushButton: public CxButtonBase {
    public:
        //-------------------------------------
        //константы

        //состояния
        enum ECheckState {
            csUknown     = - 1,
            csChecked     = BST_CHECKED,
            csUnchecked     = BST_UNCHECKED,
        };

        //стиль (изображение/текст)
        enum EViewStyle {
            vsText   = BS_TEXT,
            vsBitmap = BS_BITMAP,
            vsIcon   = BS_ICON
        };

        //тип изображения
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
        //сообщения
        BOOL        bSetViewStyle(EViewStyle vsViewStyle);
        BOOL        bSetImage    (EImageType itImageType, HANDLE hImage);

        ECheckState csGetState   ();
        BOOL        bSetState    (CxPushButton::ECheckState csCheckState);

        //-------------------------------------
        //события

    private:
        EViewStyle _m_vsViewStyle;
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxPushButtonH
