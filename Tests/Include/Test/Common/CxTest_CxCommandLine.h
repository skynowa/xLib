/**
 * \file   CxTest_CxCommandLine.h
 * \brief
 */


#ifndef CxTest_CxCommandLineH
#define CxTest_CxCommandLineH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxCommandLine.h>
//------------------------------------------------------------------------------
class CxTest_CxCommandLine :
    public CxTest
{
public:
                 CxTest_CxCommandLine();
    virtual     ~CxTest_CxCommandLine();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxCommandLineH
