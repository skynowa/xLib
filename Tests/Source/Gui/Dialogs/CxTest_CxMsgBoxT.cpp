/**
 * \file   CxTest_CxMsgBoxT.cpp
 * \brief  test CxMsgBoxT
 */


#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMsgBoxT::unit(
    culonglong_t &a_cullCaseLoops
)
{
#if 1

#if xOS_ENV_WIN
    xTEST_CASE("CxMsgBoxT::show", a_cullCaseLoops)
    {
        const HWND      chWnd   = NULL;
        std::ctstring_t csText  = xT("\nmessage box with 3 params...\n");
        std::ctstring_t csTitle = xT("Simple title");
        cuint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT().show(chWnd, csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }
#endif

    xTEST_CASE("CxMsgBoxT::show (3 params)", a_cullCaseLoops)
    {
        std::ctstring_t csText  = xT("\nmessage box with 3 params...\n");
        std::ctstring_t csTitle = xT("Simple title");
        cuint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT().show(csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }
#endif
}
//------------------------------------------------------------------------------
