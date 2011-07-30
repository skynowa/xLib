/****************************************************************************
* Class name:  CxImage
* Description: GDI+ image
* File name:   CxImage.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.05.2010 17:10:16
*
*****************************************************************************/


#include <xLib/Gui/Win/GDI+/CxImage.h>

#include <xLib/Common/CxAutoMallocT.h>

////using namespace Gdiplus;

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxImage
CxImage::CxImage() :
    _m_stRes    (Gdiplus::GenericError),
    _m_pimgImage(NULL)
{
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//TODO: ~CxImage
/*virtual*/
CxImage::~CxImage() {
    /*DEBUG*/

    bDestroy();
}
//---------------------------------------------------------------------------
//TODO: bLoad ()
BOOL 
CxImage::bLoad(
    const tString &csFilePath
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    xCHECK_DO(TRUE == bIsLoaded(), bDestroy());

#if defined(xUNICODE)
    _m_pimgImage = Gdiplus::Image::FromFile(csFilePath.c_str());
#else
    _m_pimgImage = Gdiplus::Image::FromFile(std::wstring(csFilePath.begin(), csFilePath.end()).c_str());
#endif

    /*DEBUG*/xASSERT_RET(NULL        != _m_pimgImage,                  FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bLoad ()
BOOL 
CxImage::bLoad(
    IStream *pisStream
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(NULL != pisStream, FALSE);

    xCHECK_DO(TRUE == bIsLoaded(), bDestroy());

    _m_pimgImage = Gdiplus::Image::FromStream(pisStream);
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage,                         FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSave ()
BOOL 
CxImage::bSave(
    const tString &csFilePath, 
    EEncoderType etType
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage,        FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// etType - n/a

    tString sEncoderType;
    switch (etType) {
        case etBmp:        { sEncoderType = xT("image/bmp");  }    break;
        case etJpeg:    { sEncoderType = xT("image/jpeg"); }    break;
        case etGif:         { sEncoderType = xT("image/gif");  }    break;
        case etTiff:     { sEncoderType = xT("image/tiff"); }    break;
        case etPng:         { sEncoderType = xT("image/png");  }    break;

        default:        { sEncoderType = xT("image/jpeg"); }     break;
    }

    //Save the altered image.
    CLSID cidClsid = {0};
    _bGetEncoderClsid(sEncoderType, &cidClsid);

#if defined(xUNICODE)
    _m_stRes = _m_pimgImage->Save(csFilePath.c_str(), &cidClsid, NULL);
#else
    _m_stRes = _m_pimgImage->Save(std::wstring(csFilePath.begin(), csFilePath.end()).c_str(), &cidClsid, NULL);
#endif
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes,                      FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSave ()
BOOL 
CxImage::bSave(
    IStream *pisStream, 
    EEncoderType etType
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pisStream,    FALSE);
    /*DEBUG*/// etType - n/a

    tString sEncoderType;
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
    BOOL bRes = _bGetEncoderClsid(sEncoderType, &cidClsid);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_stRes = _m_pimgImage->Save(pisStream, &cidClsid, NULL);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes,                      FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDraw ()
BOOL 
CxImage::bDraw(
    HDC         hDC, 
    const RECT &crcRect
)
{
    xCHECK_RET(FALSE == bIsLoaded(), TRUE);

    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, FALSE);
    /*DEBUG*/// hDC          - n/a
    /*DEBUG*/// crcRect      - n/a

    Gdiplus::Graphics grGraphics(hDC);
    Gdiplus::Rect     rcRect    (crcRect.left, crcRect.top, crcRect.right, crcRect.bottom);

    _m_stRes = grGraphics.DrawImage(_m_pimgImage, rcRect);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDraw ()
BOOL 
CxImage::bDraw(
    HDC hDC, 
    INT iLeft, 
    INT iTop, 
    INT iWidth, 
    INT iHeight
)
{
    xCHECK_RET(FALSE == bIsLoaded(), TRUE);

    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, FALSE);
    /*DEBUG*/// hDC          - n/a
    /*DEBUG*/// crcRect      - n/a

    Gdiplus::Graphics grGraphics(hDC);

    _m_stRes = grGraphics.DrawImage(_m_pimgImage, iLeft, iTop, iWidth, iHeight);
    Gdiplus::Status stCode = _m_pimgImage->GetLastStatus();

    /*DEBUG*/xASSERT_MSG_RET(Gdiplus::Ok == stCode, sGetLastStatus(stCode).c_str(), FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, FALSE);


    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bClear ()
/*
VOID 
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
*/
BOOL 
CxImage::bClear(
    HDC            hDC, 
    Gdiplus::Color clBackGround
)
{
    /*DEBUG*/// _m_pimgImage - n/a

    Gdiplus::Graphics grGraphics(hDC);

    _m_stRes = grGraphics.Clear(clBackGround);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDestroy ()
BOOL 
CxImage::bDestroy() {
    /*DEBUG*/// _m_pimgImage - n/a

    /*CxMacros::*/xPTR_DELETE(_m_pimgImage);
    /*DEBUG*/xASSERT_RET(NULL == _m_pimgImage, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bIsLoaded ()
BOOL 
CxImage::bIsLoaded() {
    /*DEBUG*/// n/a

    return NULL != _m_pimgImage;
}
//---------------------------------------------------------------------------
//TODO: uiGetWidth ()
UINT 
CxImage::uiGetWidth() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, 0);

    return _m_pimgImage->GetWidth();
}
//---------------------------------------------------------------------------
//TODO: uiGetHeight ()
UINT 
CxImage::uiGetHeight() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pimgImage, 0);

    return _m_pimgImage->GetHeight();
}
//---------------------------------------------------------------------------
//TODO: stGetLastStatus ()
Gdiplus::Status 
CxImage::stGetLastStatus() {
    /*DEBUG*/// _m_pimgImage - n/a

    return _m_pimgImage->GetLastStatus();
}
//---------------------------------------------------------------------------
//TODO: sGetLastStatus ()
tString 
CxImage::sGetLastStatus(
    Gdiplus::Status stCode
)
{
    /*DEBUG*/// _m_pimgImage - n/a

    tString sRes;

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

        default:                                 { sRes = xT("Unknown");                    }    break;
    }

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: _bGetEncoderClsid ()
BOOL 
CxImage::_bGetEncoderClsid(
    const tString &csFormat, 
    CLSID         *pcidClsid
)
{
    /*DEBUG*/// _m_pimgImage - n/a
    /*DEBUG*/xASSERT_RET(false == csFormat.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pcidClsid,         FALSE);

    UINT uiNum  = 0;    //number of image encoders
    UINT uiSize = 0;    //size of the image encoder array in bytes

    _m_stRes = Gdiplus::GetImageEncodersSize(&uiNum, &uiSize);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, FALSE);
    /*DEBUG*/xASSERT_RET(uiSize      != 0,        FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    CxAutoMallocT<Gdiplus::ImageCodecInfo *> pImageCodecInfo(uiSize);

    _m_stRes = GetImageEncoders(uiNum, uiSize, pImageCodecInfo.pGetPtr());
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_stRes, FALSE);
    /*DEBUG*/xASSERT_RET(Gdiplus::Ok == _m_pimgImage->GetLastStatus(), FALSE);

    for (UINT j = 0; j < uiNum; ++ j) {
#if defined(xUNICODE)
    if (csFormat == pImageCodecInfo.pGetPtr()[j].MimeType) {
#else
    if (std::wstring(csFormat.begin(), csFormat.end()) == pImageCodecInfo.pGetPtr()[j].MimeType) {
#endif
            *pcidClsid = pImageCodecInfo.pGetPtr()[j].Clsid;

            return TRUE /*j*/;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
