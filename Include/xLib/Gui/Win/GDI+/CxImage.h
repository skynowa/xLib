/**
 * \file  CxImage.h
 * \brief GDI+ image
 */


#ifndef xLib_GdiPlus_CxImageH
#define xLib_GdiPlus_CxImageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
#include <GDIPlus.h>
//---------------------------------------------------------------------------
class CxImage :
    public CxNonCopyable
    /// GDI+ image
{
    public:
        enum EEncoderType
            /// encoder type
        {
            etBmp  = 0,
            etJpeg = 1,
            etGif  = 2,
            etTiff = 3,
            etPng  = 4
        };

                        CxImage          ();
            ///< constructor
        virtual        ~CxImage          ();
            ///< destructor

        BOOL            bLoad            (const std::string_t &csFilePath);
            ///< load
        BOOL            bLoad            (IStream *pisStream);
            ///< load
        BOOL            bSave            (const std::string_t &csFilePath, EEncoderType etType);
            ///< save
        BOOL            bSave            (IStream *pisStream, EEncoderType etType);
            ///< save
        BOOL            bDraw            (HDC hDC, const RECT &crcRect);
            ///< draw
        BOOL            bDraw            (HDC hDC, int iLeft, int iTop, int iWidth, int iHeight);
            ///< draw
        BOOL            bClear           (HDC hDC, Gdiplus::Color clBackGround);
            ///< clear
        BOOL            bDestroy         ();
            ///< sestroy
        BOOL            bIsLoaded        ();
            ///< is loaded

        UINT            uiGetWidth       ();
            ///< get width
        UINT            uiGetHeight      ();
            ///< get height

        Gdiplus::Status stGetLastStatus  ();
            ///< get last status
        std::string_t    sGetLastStatus   (Gdiplus::Status stCode);
            ///< get last status

    private:
        Gdiplus::Status _m_stRes;        ///< for private use
        Gdiplus::Image *_m_pimgImage;    ///< pointer to GDI+ image

        BOOL            _bGetEncoderClsid(const std::string_t &csFormat, CLSID *pcidClsid);
            ///< get encoder clsid
};
#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxImageH
