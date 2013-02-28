/**
 * \file   CxTest_CxConsole.h
 * \brief
 */


#ifndef CxTest_CxConsoleH
#define CxTest_CxConsoleH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxConsole.h>
//------------------------------------------------------------------------------
class CxTest_CxConsole :
    public CxTest
{
public:
                 CxTest_CxConsole();
    virtual     ~CxTest_CxConsole();

    virtual void unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxConsoleH
