/**
 * \file   CxTest_CxNonCopyable.h
 * \brief  test CxNonCopyable
 */


#ifndef CxTest_CxNonCopyableH
#define CxTest_CxNonCopyableH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxTest_CxNonCopyable :
    public CxTest
{
public:
                  CxTest_CxNonCopyable();
        ///< constructor
    virtual      ~CxTest_CxNonCopyable();
        ///< destructor

    virtual void  vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
#endif //CxTest_CxNonCopyableH
