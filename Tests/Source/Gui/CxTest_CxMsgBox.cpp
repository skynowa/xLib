/**
 * \file   CxTest_CxMsgBox.cpp
 * \brief  test CxMsgBox
 */


#include <Test/Gui/CxTest_CxMsgBox.h>


//---------------------------------------1---------------------------------------
/* virtual */
void_t
CxTest_CxMsgBox::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if xTEST_IGNORE

#if xOS_ENV_WIN
    xTEST_CASE("CxMsgBox::show", a_caseLoops)
    {
        const HWND        wnd   = NULL;
        std::ctstring_t   text  = xT("\nmessage box...\n");
        std::ctstring_t   title = xT("Simple title");
        CxMsgBox::ExType type  = CxMsgBox::tpOk;

        CxMsgBox::ExModalResult mrRes = CxMsgBox().show(wnd, text, title, type);
        xUNUSED(mrRes);
    }
#endif

    xTEST_CASE("CxMsgBox::show", a_caseLoops)
    {
        std::ctstring_t   text  = xT("\nmessage box...\n");
        std::ctstring_t   title = xT("Simple title");
        CxMsgBox::ExType type = CxMsgBox::tpOk;

        CxMsgBox::ExModalResult mrRes = CxMsgBox().show(text, title, type);
        xUNUSED(mrRes);
    }
#endif
}
//------------------------------------------------------------------------------
