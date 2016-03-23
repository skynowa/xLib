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
bool_t
Test_Socket::unit()
{
    xTEST_CASE("SocketInit")
    {
        SocketInit socketInit(2, 2);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
