/**
 * \file   CxTest_CxNonHeap.h
 * \brief  test CxNonHeap
 */


#ifndef CxTest_CxNonHeapH
#define CxTest_CxNonHeapH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxNonHeap.h>
//------------------------------------------------------------------------------
class CxTest_CxNonHeap :
    public CxTest
{
public:
                  CxTest_CxNonHeap();
        ///< constructor
    virtual      ~CxTest_CxNonHeap();
        ///< destructor

    virtual void  unit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
#endif //CxTest_CxNonHeapH
