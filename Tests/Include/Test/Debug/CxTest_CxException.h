/**
 * \file   CxTest_CxException.h
 * \brief
 */


#ifndef CxTest_CxExceptionH
#define CxTest_CxExceptionH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxException.h>
//------------------------------------------------------------------------------
class CxTest_CxException :
    public CxTest
{
public:
                 CxTest_CxException();
    virtual     ~CxTest_CxException();

    virtual void unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxExceptionH
