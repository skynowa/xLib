/**
 * \file  CxImage.h
 * \brief GDI+ image
 */


#ifndef xLib_GdiPlus_CxImageH
#define xLib_GdiPlus_CxImageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

#include <GDIPlus.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

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

        bool            bLoad            (const std::tstring &csFilePath);
            ///< load
        bool            bLoad            (IStream *pisStream);
            ///< load
        bool            bSave            (const std::tstring &csFilePath, EEncoderType etType);
            ///< save
        bool            bSave            (IStream *pisStream, EEncoderType etType);
            ///< save
        bool            bDraw            (HDC hDC, const RECT &crcRect);
            ///< draw
        bool            bDraw            (HDC hDC, int iLeft, int iTop, int iWidth, int iHeight);
            ///< draw
        bool            bClear           (HDC hDC, Gdiplus::Color clBackGround);
            ///< clear
        bool            bDestroy         ();
            ///< sestroy
        bool            bIsLoaded        ();
            ///< is loaded

        UINT            uiGetWidth       ();
            ///< get width
        UINT            uiGetHeight      ();
            ///< get height

        Gdiplus::Status stGetLastStatus  ();
            ///< get last status
        std::tstring    sGetLastStatus   (Gdiplus::Status stCode);
            ///< get last status

    private:
        Gdiplus::Status _m_stRes;        ///< for private use
        Gdiplus::Image *_m_pimgImage;    ///< pointer to GDI+ image

        bool            _bGetEncoderClsid(const std::tstring &csFormat, CLSID *pcidClsid);
            ///< get encoder clsid
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxImageH
