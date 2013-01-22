/**
 * \file   CxTest_CxNonArrayHeap.h
 * \brief  test CxNonArrayHeap
 */


#ifndef CxTest_CxNonArrayHeapH
#define CxTest_CxNonArrayHeapH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxNonArrayHeap.h>
//---------------------------------------------------------------------------
class CxTest_CxNonArrayHeap :
    public CxTest
{
public:
                  CxTest_CxNonArrayHeap();
        ///< constructor
    virtual      ~CxTest_CxNonArrayHeap();
        ///< destructor

    virtual void  vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
#endif //CxTest_CxNonArrayHeapH
