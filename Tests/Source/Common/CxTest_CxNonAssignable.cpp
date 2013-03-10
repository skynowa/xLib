/**
 * \file   CxTest_CxNonAssignable.cpp
 * \brief  test CxNonAssignable
 */


#include <Test/Common/CxTest_CxNonAssignable.h>


//------------------------------------------------------------------------------
class A : 
    public CxNonAssignable 
{

};
//------------------------------------------------------------------------------
CxTest_CxNonAssignable::CxTest_CxNonAssignable() {

}
//------------------------------------------------------------------------------
CxTest_CxNonAssignable::~CxTest_CxNonAssignable() {

}
//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_CxNonAssignable::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxNonAssignable::CxNonAssignable(const CxNonAssignable &)", a_cullCaseLoops)
    {
        A a;
        A b(a);
    }

    xTEST_CASE("CxNonAssignable &operator = ", a_cullCaseLoops)
    {
        #if xNOT_COMPILE
            A a;
            A b;

            a = b;
        #endif
    }
}
//------------------------------------------------------------------------------
