/****************************************************************************
* Class name:  CxTest_CxImage
* Description: test CxImage
* File name:   CxTest_CxImage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxImageH
#define CxTest_CxImageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
#include <xLib/Gui/Win/GDI+/CxImage.h>
//---------------------------------------------------------------------------
class CxTest_CxImage : public CxTest {
	public:
		CxTest_CxImage();
		virtual     ~CxTest_CxImage();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxImageH


/****************************************************************************
* Class name:  CxTest_CxImage
* Description: test CxImage
* File name:   CxTest_CxImage.cpp



* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19

*
*****************************************************************************/


//---------------------------------------------------------------------------
//TODO: + CxTest_CxImage (comment)
CxTest_CxImage::CxTest_CxImage() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxImage (comment)
CxTest_CxImage::~CxTest_CxImage() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxImage::bUnit() {
	/*DEBUG*/

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





	return TRUE;
}
//---------------------------------------------------------------------------








//////-------------------------------------
//////[FUNCTION_NAME]
////{
////	tString sTestData[][2] = {
////		{xT("TEST_STRING_1"),		 xT("MUST_BE_1")},
////		{xT("TEST_STRING_2"),		 xT("MUST_BE_2")},
////		{xT("TEST_STRING_3"),		 xT("MUST_BE_3")},
////		{xT("TEST_STRING_4"),		 xT("MUST_BE_4")}
////	};

////	for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
////		////tString sStr1 = [FUNCTION_NAME](sTestData[i][0]);
////		////tString sStr2 = [FUNCTION_NAME](sTestData[i][1]);
////		////XASSERT(sStr1 == sStr2);

////		////tString sStr3 = [FUNCTION_NAME](sTestData[i][0]);
////		////tString sStr4 = sTestData[i][1];
////		////XASSERT(sStr3 == sStr4);
////	}
////}
