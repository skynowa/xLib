/**
 * \file   Test_Socket.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Socket)
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
