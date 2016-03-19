/**
 * \file   Test_MsgBox.cpp
 * \brief  test MsgBox
 */


#include <Test/Gui/Test_MsgBox.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MsgBox)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_MsgBox::unit(
    std::csize_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if xTEST_IGNORE || 1
    xTEST_CASE("show", a_caseLoops)
    {
        std::ctstring_t  text  = xT("\n::: Message box :::\n\n\n\nSimple test 1\n\nSimple test 2\n");
        std::ctstring_t  title = xT("Simple title");
        MsgBox::ExType type  = MsgBox::tpOk;

        MsgBox::ExModalResult mrRes = MsgBox().show(text, title, type);
        xUNUSED(mrRes);
    }
#endif
}
//-------------------------------------------------------------------------------------------------
