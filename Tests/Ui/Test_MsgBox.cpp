/**
 * \file   Test_MsgBox.cpp
 * \brief  test MsgBox
 */


#include "Test_MsgBox.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MsgBox)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MsgBox::unit()
{
#if xTEST_IGNORE || 1
    xTEST_CASE("show")
    {
        std::ctstring_t title = xT("Title-Test");
        std::ctstring_t text  = xT("Line_aaaaa\nLine_bbbbbbb\nLine_cccccc\ndddddd fffffffffffff hhhhhhhhhhhhhhhhh jjjjjjjjjjjjjjjjjjjjj kkkkkkkkkkkkkk");
        MsgBox::ExType  type  = MsgBox::tpOk;

		MsgBox msgBox;
        MsgBox::ExModalResult mrRes = msgBox.show(text, title, type);
        xUNUSED(mrRes);
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
