/**
 * \file   CxTest_CxRandom.h
 * \brief
 */


#ifndef CxTest_CxRandomH
#define CxTest_CxRandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
class CxTest_CxRandom :
    public CxTest
{
    public:
                     CxTest_CxRandom();
        virtual     ~CxTest_CxRandom();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxRandomH
