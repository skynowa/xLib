/**
 * \file   CxTest_CxFileTemp.h
 * \brief  test CxFileTemp
 */


#ifndef CxTest_CxFileTempH
#define CxTest_CxFileTempH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxFileTemp.h>
//---------------------------------------------------------------------------
class CxTest_CxFileTemp :
    public CxTest
{
    public:
                      CxTest_CxFileTemp();
            ///< constructor
        virtual      ~CxTest_CxFileTemp();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullBlockLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileTempH
