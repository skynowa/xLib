/**
 * \file   Test_Socket.cpp
 * \brief
 */


#include <Test/Net/Test_Socket.h>

#include <xLib/Patterns/Singleton.h>
#include <xLib/Net/SocketInit.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Socket)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Socket::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("SocketInit", a_caseLoops)
    {
        SocketInit socketInit(2, 2);
    }
}
//-------------------------------------------------------------------------------------------------
