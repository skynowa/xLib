/**
 * \file   Test_Socket.cpp
 * \brief
 */


#include <Test/Net/Test_Socket.h>

#include <xLib/Patterns/Singleton.h>
#include <xLib/Net/SocketInit.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Socket::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("SocketInit::SocketInit", a_caseLoops)
    {
        SocketInit siInit22(2, 2);
    }
}
//-------------------------------------------------------------------------------------------------
