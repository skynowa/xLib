/**
 * \file   CxTest_CxMsgBoxT.cpp
 * \brief  test CxMsgBoxT
 */


#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>


//------------------------------------------------------------------------------
CxTest_CxMsgBoxT::CxTest_CxMsgBoxT() {

}
//------------------------------------------------------------------------------
CxTest_CxMsgBoxT::~CxTest_CxMsgBoxT() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMsgBoxT::unit(
    culonglong_t &cullCaseLoops
)
{
#if xTEST_IGNORE

#if   xOS_ENV_WIN
    xTEST_CASE("CxMsgBoxT::show", cullCaseLoops)
    {
        const HWND           chWnd   = NULL;
        std::ctstring_t csText  = xT("\nmessage box with 3 params...\n");
        std::ctstring_t csTitle = xT("Simple title");
        cuint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(chWnd, csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }
#endif

    xTEST_CASE("CxMsgBoxT::show (3 params)", cullCaseLoops)
    {
        std::ctstring_t csText  = xT("\nmessage box with 3 params...\n");
        std::ctstring_t csTitle = xT("Simple title");
        cuint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }

    xTEST_CASE("CxMsgBoxT::show (2 params)", cullCaseLoops)
    {
        std::ctstring_t csText  = xT("\nmessage box with 2 params...\n");
        std::ctstring_t csTitle = xT("Simple title");

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(csText, csTitle);
        xUNUSED(mrRes);
    }

    xTEST_CASE("CxMsgBoxT::show (1 param)", cullCaseLoops)
    {
        std::ctstring_t csText  = xT("\nmessage box with 1 param...\n");

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::show(csText);
        xUNUSED(mrRes);
    }
#endif
}
//------------------------------------------------------------------------------
