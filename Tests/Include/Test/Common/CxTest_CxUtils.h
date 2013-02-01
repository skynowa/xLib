/**
 * \file   CxTest_CxUtils.h
 * \brief
 */


#ifndef CxTest_CxUtilsH
#define CxTest_CxUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxUtils.h>
//---------------------------------------------------------------------------
class CxTest_CxUtils :
    public CxTest
{
public:
                   CxTest_CxUtils();
    virtual       ~CxTest_CxUtils();

    virtual  void  unit          (const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxUtilsH
