/**
 * \file   CxTest_CxSocket.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocket.h>

#include <xLib/Patterns/CxSingleton.h>
#include <xLib/Net/CxSocketInit.h>


//------------------------------------------------------------------------------
CxTest_CxSocket::CxTest_CxSocket() {

}
//------------------------------------------------------------------------------
CxTest_CxSocket::~CxTest_CxSocket() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSocket::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxSocketInit::CxSocketInit", a_cullCaseLoops)
    {
        CxSocketInit siInit22(2, 2);
    }
}
//------------------------------------------------------------------------------
