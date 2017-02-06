/**
 * \file   Test_SocketInit.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_SocketInit)
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

    return true;
}
//-------------------------------------------------------------------------------------------------
