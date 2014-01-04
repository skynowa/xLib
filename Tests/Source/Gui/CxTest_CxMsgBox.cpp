/**
 * \file   CxTest_CxMsgBox.cpp
 * \brief  test CxMsgBox
 */


#include <Test/Gui/CxTest_CxMsgBox.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMsgBox::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if xTEST_IGNORE || 1
    xTEST_CASE("CxMsgBox::show", a_caseLoops)
    {
        std::ctstring_t  text  = xT("\n::: Message box\n\n\n\nSimple test 1\n\nSimple test 2:::\n");
        std::ctstring_t  title = xT("Simple title");
        CxMsgBox::ExType type = CxMsgBox::tpOk;

        CxMsgBox::ExModalResult mrRes = CxMsgBox().show(text, title, type);
        xUNUSED(mrRes);
    }
#endif
}
//-------------------------------------------------------------------------------------------------
