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
