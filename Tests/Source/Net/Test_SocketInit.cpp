/**
 * \file   Test_SocketInit.cpp
 * \brief
 */


#include <Test/Net/Test_SocketInit.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_SocketInit)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SocketInit::unit()
{
    xTEST_CASE("SocketInit")
    {
        SocketInit siInit10(1, 0);
        SocketInit siInit11(1, 1);
        SocketInit siInit20(2, 0);
        SocketInit siInit21(2, 1);
        SocketInit siInit22(2, 2);
    }
}
//-------------------------------------------------------------------------------------------------
