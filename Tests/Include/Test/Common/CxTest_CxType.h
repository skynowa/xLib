/**
 * \file   CxTest_CxType.h
 * \brief
 */


#ifndef CxTest_CxTypeH
#define CxTest_CxTypeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxType.h>
//---------------------------------------------------------------------------
class CxTest_CxType :
    public CxTest
{
    public:
                      CxTest_CxType();
        virtual      ~CxTest_CxType();

        virtual bool  bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTypeH
