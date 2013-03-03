/**
 * \file   CxTest_CxBackuper.h
 * \brief  test CxBackuper
 */


#ifndef CxTest_CxBackuperH
#define CxTest_CxBackuperH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxBackuper.h>
//------------------------------------------------------------------------------
class CxTest_CxBackuper :
    public CxTest
{
public:
                  CxTest_CxBackuper();
        ///< constructor
    virtual      ~CxTest_CxBackuper();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
#endif //CxTest_CxBackuperH
