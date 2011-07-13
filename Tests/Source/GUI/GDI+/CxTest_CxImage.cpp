/****************************************************************************
* Class name:  CxTest_CxImage
* Description: test CxImage
* File name:   CxTest_CxImage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <GUI/GDI+/CxTest_CxImage.h>

#include <xLib/Gui/Win/GDI+/CxGdiplus.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxImage (comment)
CxTest_CxImage::CxTest_CxImage() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxImage (comment)
CxTest_CxImage::~CxTest_CxImage() {
	//code
}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxImage::bUnit() {
	/*DEBUG*/

#if defined(xOS_WIN)
    CxGdiplus  m_gdiGdi;
    CxImage    m_imgImage;
    tString    sTempDirPath = xT("Test");

    //-------------------------------------
    //bLoad
    {
        m_bRes = m_imgImage.bLoad(sTempDirPath + CxConst::xSLASH + xT("Test1.bmp"));
    }

    //-------------------------------------
    //bLoad
    {
        //m_bRes = m_imgImage.bLoad(IStream *pstStream);
    }

    //-------------------------------------
    //bSave
    {
        m_bRes = m_imgImage.bSave(sTempDirPath + CxConst::xSLASH + xT("Test1.Saved.bmp"), CxImage::etBmp);
        xASSERT(FALSE != m_bRes);

        m_bRes = m_imgImage.bSave(sTempDirPath + CxConst::xSLASH + xT("Test1.Saved.jpeg"), CxImage::etJpeg);
        xASSERT(FALSE != m_bRes)
            ;
        m_bRes = m_imgImage.bSave(sTempDirPath + CxConst::xSLASH + xT("Test1.Saved.gif"), CxImage::etGif);
        xASSERT(FALSE != m_bRes);

        m_bRes = m_imgImage.bSave(sTempDirPath + CxConst::xSLASH + xT("Test1.Saved.tiff"), CxImage::etTiff);
        xASSERT(FALSE != m_bRes);

        m_bRes = m_imgImage.bSave(sTempDirPath + CxConst::xSLASH + xT("Test1.Saved.png"), CxImage::etPng);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSave
    {
        //m_bRes = m_imgImage.bSave(IStream *pstStream);
    }

    //-------------------------------------
    //bDraw
    {
        //m_bRes = m_imgImage.bDraw(HDC hDC, const RECT &crcRect);
    }

    //-------------------------------------
    //bDraw
    {
        //m_bRes = m_imgImage.bDraw(HDC hDC, INT iLeft, INT iTop, INT iWidth, INT iHeight);
    }

    //-------------------------------------
    //bClear
    {
        //m_bRes = m_imgImage.bClear(HDC hDC, const RECT &crcRect, Gdiplus::Color clBackGround);
    }

    //-------------------------------------
    //bDestroy
    {
        //m_bRes = m_imgImage.bDestroy(HDC hDC, Gdiplus::Color clBackGround);
    }
#elif defined(xOS_LINUX)

#endif

	return TRUE;
}
//---------------------------------------------------------------------------
