/**
 * \file   CxTest_CxNonCopyable.cpp
 * \brief  test CxNonCopyable
 */


#include <Test/Common/CxTest_CxNonCopyable.h>


//---------------------------------------------------------------------------
class A : 
    public CxNonCopyable 
{

};
//---------------------------------------------------------------------------
CxTest_CxNonCopyable::CxTest_CxNonCopyable() {

}
//---------------------------------------------------------------------------
CxTest_CxNonCopyable::~CxTest_CxNonCopyable() {

}
//---------------------------------------------------------------------------
/*virtual*/
void
CxTest_CxNonCopyable::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxNonCopyable::CxNonCopyable(const CxNonCopyable &), cullCaseLoops)
    {
        #if xNOT_COMPILE
            {
                A a;
                A b(a);
            }
        #endif
    }

    xTEST_CASE(const CxNonCopyable &operator =, cullCaseLoops)
    {
        #if xNOT_COMPILE                
            {
                A a;
                A b;

                a = b;
            }
        #endif
    }
}
//---------------------------------------------------------------------------
