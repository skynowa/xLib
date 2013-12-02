/**
 * \file   CxTest_CxMsgBoxT.cpp
 * \brief  test CxMsgBoxT
 */


#include <Test/Gui/CxTest_CxMsgBoxT.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMsgBoxT::unit(
    culonglong_t &a_caseLoops
)
{
#if 1

#if xOS_ENV_WIN
    xTEST_CASE("CxMsgBoxT::show", a_caseLoops)
    {
        const HWND        wnd   = NULL;
        std::ctstring_t   text  = xT("\nmessage box...\n");
        std::ctstring_t   title = xT("Simple title");
        CxMsgBoxT::ExType type  = CxMsgBoxT::tpOk;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT().show(wnd, text, title, type);
        xUNUSED(mrRes);
    }
#endif

    xTEST_CASE("CxMsgBoxT::show", a_caseLoops)
    {
        std::ctstring_t   text  = xT("\nmessage box...\n");
        std::ctstring_t   title = xT("Simple title");
        CxMsgBoxT::ExType type = CxMsgBoxT::tpOk;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT().show(text, title, type);
        xUNUSED(mrRes);
    }
#endif
}
//------------------------------------------------------------------------------
