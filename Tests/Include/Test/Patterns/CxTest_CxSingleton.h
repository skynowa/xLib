/**
 * \file   CxTest_CxSingleton.h
 * \brief
 */


#ifndef CxTest_CxSingletonH
#define CxTest_CxSingletonH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Patterns/CxSingleton.h>
//------------------------------------------------------------------------------
class CxTest_CxSingleton :
    public CxTest
{
public:
                 CxTest_CxSingleton();
    virtual     ~CxTest_CxSingleton();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxSingletonH
