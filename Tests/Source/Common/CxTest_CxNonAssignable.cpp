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
CxTest_CxNonAssignable::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxNonAssignable::CxNonAssignable, cullCaseLoops)
    {
        A a;
    }

    xTEST_CASE(CxNonAssignable::CxNonAssignable, cullCaseLoops)
    {
        #if xNOT_COMPILE
            A a;
            A b;

            a = b;
        #endif
    }
}
//---------------------------------------------------------------------------
