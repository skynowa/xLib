/**
 * \file   CxTest_CxSocket.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocket.h>

#include <xLib/Patterns/CxSingleton.h>
#include <xLib/Net/CxSocketInit.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSocket::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSocketInit::CxSocketInit", a_caseLoops)
    {
        CxSocketInit siInit22(2, 2);
    }
}
//-------------------------------------------------------------------------------------------------
