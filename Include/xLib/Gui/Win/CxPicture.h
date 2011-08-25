/**
 * \file  CxPicture.h
 * \brief picture
 */


#ifndef XLib_Gui_CxPictureH
#define XLib_Gui_CxPictureH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxPicture : public CxWindow {
    public:
        //-------------------------------------
        //���������

        //����� �����������
        enum EViewStyle {
            vsUknown       = 0,
            vsBitmap       = SS_BITMAP,
            vsIcon         = SS_ICON,
            vsCursor       = SS_ICON,
            vsEnhMetaFile  = SS_ENHMETAFILE,
            vsOwnerDraw    = SS_OWNERDRAW
        };

        //��� �����������
        enum EImageType {
            itUknown      = - 1,
            itBitmap      = IMAGE_BITMAP,
            itIcon          = IMAGE_ICON,
            itCursor      = IMAGE_CURSOR,
            itEnhMetaFile = IMAGE_ENHMETAFILE
        };

                   CxPicture    ();
        virtual   ~CxPicture    ();

        BOOL       bCreateRes   (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        BOOL       bSetViewStyle(EViewStyle vsViewStyle);
        BOOL       bSetImage    (EImageType itImageType, HANDLE hImage);

        //-------------------------------------
        //�������

    private:
        EViewStyle _m_vsViewStyle;
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxPictureH
