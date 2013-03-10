/**
 * \file   CxTest_CxNonCopyable.cpp
 * \brief  test CxNonCopyable
 */


#include <Test/Common/CxTest_CxNonCopyable.h>


//------------------------------------------------------------------------------
class A : 
    public CxNonCopyable 
{

};
//------------------------------------------------------------------------------
CxTest_CxNonCopyable::CxTest_CxNonCopyable() {

}
//------------------------------------------------------------------------------
CxTest_CxNonCopyable::~CxTest_CxNonCopyable() {

}
//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_CxNonCopyable::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxNonCopyable::CxNonCopyable(const CxNonCopyable &)", a_cullCaseLoops)
    {
        #if xNOT_COMPILE
            {
                A a;
                A b(a);
            }
        #endif
    }

    xTEST_CASE("const CxNonCopyable &operator =", a_cullCaseLoops)
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
//------------------------------------------------------------------------------
