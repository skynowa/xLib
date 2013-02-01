/**
 * \file   CxTest_CxFileLog.h
 * \brief
 */


#ifndef CxTest_CxFileLogH
#define CxTest_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxFileLog.h>
//---------------------------------------------------------------------------
class CxTest_CxFileLog :
    public CxTest
{
public:
                  CxTest_CxFileLog();
    virtual      ~CxTest_CxFileLog();

    virtual  void unit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileLogH
