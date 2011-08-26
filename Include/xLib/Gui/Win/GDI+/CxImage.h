/**
 * \file  CxImage.h
 * \brief GDI+ image
 */


#ifndef xLib_GdiPlus_CxImageH
#define xLib_GdiPlus_CxImageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <GDIPlus.h>
    //---------------------------------------------------------------------------
    class CxImage :
        public CxNonCopyable
        /// GDI+ image
    {
        public:
            enum EEncoderType {
                etBmp  = 0,
                etJpeg = 1,
                etGif  = 2,
                etTiff = 3,
                etPng  = 4
            };

                            CxImage   ();
            virtual        ~CxImage   ();

            BOOL            bLoad     (const std::tstring &csFilePath);
            BOOL            bLoad     (IStream *pisStream);
            BOOL            bSave     (const std::tstring &csFilePath, EEncoderType etType);
            BOOL            bSave     (IStream *pisStream, EEncoderType etType);
            BOOL            bDraw     (HDC hDC, const RECT &crcRect);
            BOOL            bDraw     (HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight);
            BOOL            bClear    (HDC hDC, Gdiplus::Color clBackGround);
            BOOL            bDestroy  ();
            BOOL            bIsLoaded ();

            UINT            uiGetWidth ();
            UINT            uiGetHeight();

            Gdiplus::Status stGetLastStatus();
            std::tstring         sGetLastStatus (Gdiplus::Status stCode);

        private:
            Gdiplus::Status _m_stRes;
            Gdiplus::Image *_m_pimgImage;

            BOOL            _bGetEncoderClsid(const std::tstring &csFormat, CLSID *pcidClsid);
    };
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxImageH
