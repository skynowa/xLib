/**
 * \file   CxTest_CxFileLog.h
 * \brief
 */


#ifndef CxTest_CxFileLogH
#define CxTest_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Log/CxFileLog.h>
//---------------------------------------------------------------------------
class CxTest_CxFileLog :
    public CxTest
{
    public:
                      CxTest_CxFileLog();
        virtual      ~CxTest_CxFileLog();

        virtual  bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileLogH
