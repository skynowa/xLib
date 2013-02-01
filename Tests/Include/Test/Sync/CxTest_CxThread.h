/**
 * \file   CxTest_CxThread.h
 * \brief
 */


#ifndef CxTest_CxThreadH
#define CxTest_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxCurrentThread.h>
//---------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
public:
                 CxTest_CxThread();
    virtual     ~CxTest_CxThread();

    virtual void unit          (const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadH
