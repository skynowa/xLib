/**
 * \file   CxTest_CxEnvironment.h
 * \brief
 */


#ifndef CxTest_CxEnvironmentH
#define CxTest_CxEnvironmentH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxEnvironment.h>
//------------------------------------------------------------------------------
class CxTest_CxEnvironment :
    public CxTest
{
public:
                 CxTest_CxEnvironment();
    virtual     ~CxTest_CxEnvironment();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxEnvironmentH
