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
/*virtual*/
BOOL
CxTest_CxMsgBoxT::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if xTEST_IGNORE
    //--------------------------------------------------
    //iShow
#if defined(xOS_ENV_WIN)
    xTEST_BLOCK(cullBlockLoops)
    {
        const HWND         chWnd   = NULL;
        const std::tstring csText  = xT("\nmessage box with 3 params...\n");
        const std::tstring csTitle = xT("Simple title");
        const UINT         cuiType = 0;

        CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(chWnd, csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }
#endif

    //--------------------------------------------------
    //iShow (3 params)
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csText  = xT("\nmessage box with 3 params...\n");
        const std::tstring csTitle = xT("Simple title");
        const UINT         cuiType = 0;

        CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(csText, csTitle, cuiType);
        xUNUSED(mrRes);
    }

    //--------------------------------------------------
    //iShow (2 params)
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csText  = xT("\nmessage box with 2 params...\n");
        const std::tstring csTitle = xT("Simple title");

        CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(csText, csTitle);
        xUNUSED(mrRes);
    }

    //--------------------------------------------------
    //iShow (1 param)
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csText  = xT("\nmessage box with 1 param...\n");

        CxMsgBoxT::EModalResult mrRes = CxMsgBoxT::iShow(csText);
        xUNUSED(mrRes);
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
