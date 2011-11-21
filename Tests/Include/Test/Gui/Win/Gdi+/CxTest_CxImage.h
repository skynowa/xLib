/**
 * \file   CxTest_CxImage.h
 * \brief
 */


#ifndef CxTest_CxImageH
#define CxTest_CxImageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Win/GDI+/CxGdiplus.h>
#include <xLib/Gui/Win/GDI+/CxImage.h>
//---------------------------------------------------------------------------
class CxTest_CxImage :
    public CxTest
{
    public:
                     CxTest_CxImage();
        virtual     ~CxTest_CxImage();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxImageH
