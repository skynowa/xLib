/****************************************************************************
* Class name:  CxTest_CxGdiplus
* Description: test CxGdiplus
* File name:   CxTest_CxGdiplus.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxGdiplusH
#define CxTest_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
//---------------------------------------------------------------------------
class CxTest_CxGdiplus : public CxTest {
	public:
		CxTest_CxGdiplus();
		virtual     ~CxTest_CxGdiplus();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxGdiplusH
