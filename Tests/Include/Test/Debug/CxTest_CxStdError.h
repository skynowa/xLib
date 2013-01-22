/**
 * \file   CxTest_CxStdError.h
 * \brief  test CxStdError
 */


#ifndef CxTest_CxStdErrorH
#define CxTest_CxStdErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxStdError.h>
//---------------------------------------------------------------------------
class CxTest_CxStdError :
    public CxTest
{
public:
                  CxTest_CxStdError();
        ///< constructor
    virtual      ~CxTest_CxStdError();
        ///< destructor

    virtual void  vUnit            (const ulonglong_t &cullCaseLoops);
        ///< unit test
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStdErrorH
