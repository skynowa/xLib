/**
 * \file   CxTest_CxShell.h
 * \brief
 */


#ifndef CxTest_CxShellH
#define CxTest_CxShellH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxShell.h>
//------------------------------------------------------------------------------
class CxTest_CxShell :
    public CxTest
{
public:
                 CxTest_CxShell();
    virtual     ~CxTest_CxShell();

    virtual void unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxShellH
