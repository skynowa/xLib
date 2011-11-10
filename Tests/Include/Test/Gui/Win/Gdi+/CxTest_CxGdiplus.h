/**
 * \file   CxTest_CxGdiplus.h
 * \brief
 */


#ifndef CxTest_CxGdiplusH
#define CxTest_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)

#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
//---------------------------------------------------------------------------
class CxTest_CxGdiplus :
    public CxTest
{
    public:
                     CxTest_CxGdiplus();
        virtual     ~CxTest_CxGdiplus();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};

#endif
//---------------------------------------------------------------------------
#endif //CxTest_CxGdiplusH
