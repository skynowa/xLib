/**
 * \file   CxTest_xDebug.h
 * \brief  test xDebug
 */


#ifndef CxTest_xDebugH
#define CxTest_xDebugH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/xDebug.h>
//---------------------------------------------------------------------------
class CxTest_xDebug :
    public CxTest
{
    public:
                      CxTest_xDebug();
            ///< constructor
        virtual      ~CxTest_xDebug();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullCaseLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_xDebugH
