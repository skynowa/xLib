/**
 * \file   CxTest_CxGdiplus.h
 * \brief
 */


#ifndef CxTest_CxGdiplusH
#define CxTest_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN

#include <xLib/Test/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
//---------------------------------------------------------------------------
class CxTest_CxGdiplus :
    public CxTest
{
    public:
                     CxTest_CxGdiplus();
        virtual     ~CxTest_CxGdiplus();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};

#endif
//---------------------------------------------------------------------------
#endif //CxTest_CxGdiplusH
