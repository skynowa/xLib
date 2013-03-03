/**
 * \file   CxTest_CxDll.h
 * \brief
 */


#ifndef CxTest_CxDllH
#define CxTest_CxDllH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxDll.h>
//------------------------------------------------------------------------------
class CxTest_CxDll :
    public CxTest
{
public:
                 CxTest_CxDll();
    virtual     ~CxTest_CxDll();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxDllH
