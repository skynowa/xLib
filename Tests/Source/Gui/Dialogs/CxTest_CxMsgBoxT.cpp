/**
 * \file   CxTest_CxMsgBoxT.cpp
 * \brief  test CxMsgBoxT
 */


#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>


//---------------------------------------------------------------------------
CxTest_CxMsgBoxT::CxTest_CxMsgBoxT() {

}
//---------------------------------------------------------------------------
CxTest_CxMsgBoxT::~CxTest_CxMsgBoxT() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxMsgBoxT::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
#if xTEST_IGNORE

#if   xOS_ENV_WIN
    xTEST_CASE(CxMsgBoxT::iShow, cullCaseLoops)
    {
        const HWND           chWnd   = NULL;
        const std::tstring_t csText  = xT("\nmessage box with 3 params...\n");
        const std::tstring_t csTitle = xT("Simple title");
        const uint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::iShow(chWnd, csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }
#endif

    xTEST_CASE(CxMsgBoxT::iShow (3 params), cullCaseLoops)
    {
        const std::tstring_t csText  = xT("\nmessage box with 3 params...\n");
        const std::tstring_t csTitle = xT("Simple title");
        const uint_t         cuiType = 0;

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::iShow(csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }

    xTEST_CASE(CxMsgBoxT::iShow (2 params), cullCaseLoops)
    {
        const std::tstring_t csText  = xT("\nmessage box with 2 params...\n");
        const std::tstring_t csTitle = xT("Simple title");

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::iShow(csText, csTitle);
        xUNUSED(mrRes);
    }

    xTEST_CASE(CxMsgBoxT::iShow (1 param), cullCaseLoops)
    {
        const std::tstring_t csText  = xT("\nmessage box with 1 param...\n");

        CxMsgBoxT::ExModalResult mrRes = CxMsgBoxT::iShow(csText);
        xUNUSED(mrRes);
    }
#endif
}
//---------------------------------------------------------------------------
