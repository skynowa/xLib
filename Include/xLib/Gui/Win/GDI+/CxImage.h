/****************************************************************************
* Class name:  CxImage
* Description: GDI+ image
* File name:   CxImage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.05.2010 17:10:16
*
*****************************************************************************/


#ifndef xLib_GdiPlus_CxImageH
#define xLib_GdiPlus_CxImageH
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
#include <xLib/Common/xCommon.h>
#include <GDIPlus.h>
//---------------------------------------------------------------------------
class CxImage : public CxNonCopyable {
    public:
        enum EEncoderType {
            etBmp  = 0,
            etJpeg = 1,
            etGif  = 2,
            etTiff = 3,
            etPng  = 4
        };

                        CxImage   ();
                       ~CxImage   ();

        BOOL            bLoad     (const tString &csFilePath);
        BOOL            bLoad     (IStream *pisStream);
        BOOL            bSave     (const tString &csFilePath, EEncoderType etType);
        BOOL            bSave     (IStream *pisStream, EEncoderType etType);
        BOOL            bDraw     (HDC hDC, const RECT &crcRect);
        BOOL            bDraw     (HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight);
        BOOL            bClear    (HDC hDC, Gdiplus::Color clBackGround);
        BOOL            bDestroy  ();
        BOOL            bIsLoaded ();

        UINT            uiGetWidth ();
        UINT            uiGetHeight();

        Gdiplus::Status stGetLastStatus();
        tString         sGetLastStatus (Gdiplus::Status stCode);

    private:
        Gdiplus::Status _m_stRes;
        Gdiplus::Image *_m_pimgImage;

        BOOL            _bGetEncoderClsid(const tString &csFormat, CLSID *pcidClsid);
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxImageH
