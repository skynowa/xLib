/**
 * \file  CxImage.cpp
 * \brief GDI+ image
 */


#include <xLib/Gui/Win/GDI+/CxImage.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxImage::CxImage() :
    _m_stRes    (Gdiplus::GenericError),
    _m_pimgImage(NULL)
{
    /*DEBUG*/
}
//---------------------------------------------------------------------------
/*virtual*/
CxImage::~CxImage() {
    /*DEBUG*/

    (void)bDestroy();
}
//---------------------------------------------------------------------------
bool
CxImage::bLoad(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

    xCHECK_DO(true == bIsLoaded(), bDestroy());

#if xUNICODE
    _m_pimgImage = Gdiplus::Image::FromFile(csFilePath.c_str());
#else
    _m_pimgImage = Gdiplus::Image::FromFile(std::wstring(csFilePath.begin(), csFilePath.end()).c_str());
#endif

    /*DEBUG*/xASSERT_RET(NULL        != _m_pimgImage,                  false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bLoad(
    IStream *pisStream
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(NULL != pisStream, false);

    xCHECK_DO(true == bIsLoaded(), bDestroy());

    _m_pimgImage = Gdiplus::Image::FromStream(pisStream);
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage,                         false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bSave(
    const std::tstring_t &csFilePath,
    EEncoderType        etType
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage,        false);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// etType - n/a

    std::tstring_t sEncoderType;
    switch (etType) {
        case etBmp:     { sEncoderType = xT("image/bmp");  }    break;
        case etJpeg:    { sEncoderType = xT("image/jpeg"); }    break;
        case etGif:     { sEncoderType = xT("image/gif");  }    break;
        case etTiff:    { sEncoderType = xT("image/tiff"); }    break;
        case etPng:     { sEncoderType = xT("image/png");  }    break;

        default:        { sEncoderType = xT("image/jpeg"); }     break;
    }

    //Save the altered image.
    CLSID cidClsid = {0};
    _bGetEncoderClsid(sEncoderType, &cidClsid);

#if xUNICODE
    _m_stRes = _m_pimgImage->Save(csFilePath.c_str(), &cidClsid, NULL);
#else
    _m_stRes = _m_pimgImage->Save(std::wstring(csFilePath.begin(), csFilePath.end()).c_str(), &cidClsid, NULL);
#endif
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes,                      false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bSave(
    IStream      *pisStream,
    EEncoderType  etType
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, false);
    /*DEBUG*/xASSERT_RET(NULL != pisStream,    false);
    /*DEBUG*/// etType - n/a

    std::tstring_t sEncoderType;
    switch (etType) {
        case etBmp:     { sEncoderType = xT("image/bmp");  }    break;
        case etJpeg:    { sEncoderType = xT("image/jpeg"); }    break;
        case etGif:     { sEncoderType = xT("image/gif");  }    break;
        case etTiff:    { sEncoderType = xT("image/tiff"); }    break;
        case etPng:     { sEncoderType = xT("image/png");  }    break;

        default:        { sEncoderType = xT("image/jpeg"); }     break;
    }

    //Save the altered image.
    CLSID cidClsid = {0};
    bool bRes = _bGetEncoderClsid(sEncoderType, &cidClsid);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    _m_stRes = _m_pimgImage->Save(pisStream, &cidClsid, NULL);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes,                      false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bDraw(
    HDC         hDC,
    const RECT &crcRect
)
{
    xCHECK_RET(false == bIsLoaded(), true);

    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, false);
    /*DEBUG*/// hDC          - n/a
    /*DEBUG*/// crcRect      - n/a

    Gdiplus::Graphics grGraphics(hDC);
    Gdiplus::Rect     rcRect    (crcRect.left, crcRect.top, crcRect.right, crcRect.bottom);

    _m_stRes = grGraphics.DrawImage(_m_pimgImage, rcRect);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bDraw(
    HDC hDC,
    int iLeft,
    int iTop,
    int iWidth,
    int iHeight
)
{
    xCHECK_RET(false == bIsLoaded(), true);

    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, false);
    /*DEBUG*/// hDC          - n/a
    /*DEBUG*/// crcRect      - n/a

    Gdiplus::Graphics grGraphics(hDC);

    _m_stRes = grGraphics.DrawImage(_m_pimgImage, iLeft, iTop, iWidth, iHeight);
    Gdiplus::Status stCode = _m_pimgImage->GetLastStatus();

    /*DEBUG*/xASSERT_MSG_RET(Gdiplus::Ok == stCode, sGetLastStatus(stCode).c_str(), false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, false);


    return true;
}
//---------------------------------------------------------------------------
#if xTODO
    void
    Example_Clear(
        HDC hdc
    )
    {
        Graphics graphics(hdc);

        // Create a Color object.
        Color blueColor(255, 0, 0, 255);

        // Clear the screen with a blue background.
        graphics.Clear(blueColor);
    }
#endif

bool
CxImage::bClear(
    HDC            hDC,
    Gdiplus::Color clBackGround
)
{
    /*DEBUG*/// _m_pimgImage - n/a

    Gdiplus::Graphics grGraphics(hDC);

    _m_stRes = grGraphics.Clear(clBackGround);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bDestroy() {
    /*DEBUG*/// _m_pimgImage - n/a

    /*CxMacros::*/xPTR_DELETE(_m_pimgImage);
    /*DEBUG*/xASSERT_RET(NULL == _m_pimgImage, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxImage::bIsLoaded() {
    /*DEBUG*/// n/a

    return NULL != _m_pimgImage;
}
//---------------------------------------------------------------------------
uint_t
CxImage::uiGetWidth() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, 0);

    return _m_pimgImage->GetWidth();
}
//---------------------------------------------------------------------------
uint_t
CxImage::uiGetHeight() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, 0);

    return _m_pimgImage->GetHeight();
}
//---------------------------------------------------------------------------
Gdiplus::Status
CxImage::stGetLastStatus() {
    /*DEBUG*/// _m_pimgImage - n/a

    return _m_pimgImage->GetLastStatus();
}
//---------------------------------------------------------------------------
std::tstring_t
CxImage::sGetLastStatus(
    Gdiplus::Status stCode
)
{
    /*DEBUG*/// _m_pimgImage - n/a

    std::tstring_t sRes;

    switch (stCode) {
        case Gdiplus::Ok:                        { sRes = xT("Ok");                         }    break;
        case Gdiplus::GenericError:              { sRes = xT("GenericError");               }    break;
        case Gdiplus::InvalidParameter:          { sRes = xT("InvalidParameter");           }    break;
        case Gdiplus::OutOfMemory:               { sRes = xT("OutOfMemory");                }    break;
        case Gdiplus::ObjectBusy:                { sRes = xT("ObjectBusy");                 }    break;
        case Gdiplus::InsufficientBuffer:        { sRes = xT("InsufficientBuffer");         }    break;
        case Gdiplus::NotImplemented:            { sRes = xT("NotImplemented");             }    break;
        case Gdiplus::Win32Error:                { sRes = xT("Win32Error");                 }    break;
        case Gdiplus::WrongState:                { sRes = xT("WrongState");                 }    break;
        case Gdiplus::Aborted:                   { sRes = xT("Aborted");                    }    break;
        case Gdiplus::FileNotFound:              { sRes = xT("FileNotFound");               }    break;
        case Gdiplus::ValueOverflow:             { sRes = xT("ValueOverflow");              }    break;
        case Gdiplus::AccessDenied:              { sRes = xT("AccessDenied");               }    break;
        case Gdiplus::UnknownImageFormat:        { sRes = xT("UnknownImageFormat");         }    break;
        case Gdiplus::FontFamilyNotFound:        { sRes = xT("FontFamilyNotFound");         }    break;
        case Gdiplus::FontStyleNotFound:         { sRes = xT("FontStyleNotFound");          }    break;
        case Gdiplus::NotTrueTypeFont:           { sRes = xT("NotTrueTypeFont");            }    break;
        case Gdiplus::UnsupportedGdiplusVersion: { sRes = xT("UnsupportedGdiplusVersion");  }    break;
        case Gdiplus::GdiplusNotInitialized:     { sRes = xT("GdiplusNotInitialized");      }    break;
        case Gdiplus::PropertyNotFound:          { sRes = xT("PropertyNotFound");           }    break;
        case Gdiplus::PropertyNotSupported:      { sRes = xT("PropertyNotSupported");       }    break;

        default:                                 { sRes = xUNKNOWN_STRING;                  }    break;
    }

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxImage::_bGetEncoderClsid(
    const std::tstring_t &csFormat,
    CLSID              *pcidClsid
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(false == csFormat.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL != pcidClsid,         false);

    uint_t uiNum  = 0;    //number of image encoders
    uint_t uiSize = 0;    //size of the image encoder array in bytes

    _m_stRes = Gdiplus::GetImageEncodersSize(&uiNum, &uiSize);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, false);
    /*DEBUG*/xASSERT_RET(uiSize      != 0,        false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    Gdiplus::ImageCodecInfo *pImageCodecInfo = (Gdiplus::ImageCodecInfo *)malloc(uiSize);
    /*DEBUG*/xASSERT(NULL != pImageCodecInfo);

    _m_stRes = GetImageEncoders(uiNum, uiSize, pImageCodecInfo);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, false);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), false);

    for (uint_t j = 0; j < uiNum; ++ j) {
    #if xUNICODE
        if (csFormat == pImageCodecInfo[j].MimeType) {
    #else
        if (std::wstring(csFormat.begin(), csFormat.end()) == pImageCodecInfo[j].MimeType) {
    #endif
            *pcidClsid = pImageCodecInfo[j].Clsid;
            xBUFF_FREE(pImageCodecInfo);

            return true /*j*/;
        }
    }

    xBUFF_FREE(pImageCodecInfo);

    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
