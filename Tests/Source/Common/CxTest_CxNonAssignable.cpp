/**
 * \file   CxTest_CxNonAssignable.cpp
 * \brief  test CxNonAssignable
 */


#include <Test/Common/CxTest_CxNonAssignable.h>


//---------------------------------------------------------------------------
class A : 
    public CxNonAssignable 
{

};
//---------------------------------------------------------------------------
CxTest_CxNonAssignable::CxTest_CxNonAssignable() {

}
//---------------------------------------------------------------------------
CxTest_CxNonAssignable::~CxTest_CxNonAssignable() {

}
//---------------------------------------------------------------------------
/*virtual*/
void
CxTest_CxNonAssignable::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxNonAssignable::CxNonAssignable(const CxNonAssignable &)", cullCaseLoops)
    {
        A a;
        A b(a);
    }

    xTEST_CASE("CxNonAssignable &operator = ", cullCaseLoops)
    {
        #if xNOT_COMPILE
            A a;
            A b;

            a = b;
        #endif
    }
}
//---------------------------------------------------------------------------
