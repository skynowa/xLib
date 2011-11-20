/**
 * \file   CxTest_CxType.h
 * \brief
 */


#ifndef CxTest_CxTypeH
#define CxTest_CxTypeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxType.h>
//---------------------------------------------------------------------------
class CxTest_CxType :
    public CxTest
{
    public:
                      CxTest_CxType();
        virtual      ~CxTest_CxType();

        virtual bool  bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTypeH
