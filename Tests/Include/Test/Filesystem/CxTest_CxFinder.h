/**
 * \file   CxTest_CxFinder.h
 * \brief  test CxFinder
 */


#ifndef CxTest_CxFinderH
#define CxTest_CxFinderH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFinder.h>
//------------------------------------------------------------------------------
class CxTest_CxFinder :
    public CxTest
    ///< tests for CxFinder
{
public:
                  CxTest_CxFinder();
        ///< constructor
    virtual      ~CxTest_CxFinder();
        ///< destructor

    virtual void  unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
#endif // CxTest_CxFinderH
