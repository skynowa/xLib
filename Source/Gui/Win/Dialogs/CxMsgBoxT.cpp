/****************************************************************************
* Class name:  CxMsgBoxT
* Description: message box
* File name:   CxMsgBoxT.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.04.2009 10:24:49
*
*****************************************************************************/


#include <xLib/Gui/Win/Dialogs/CxMsgBoxT.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxMsgBoxT
CxMsgBoxT::CxMsgBoxT() {

}
//---------------------------------------------------------------------------
//DONE: ~CxMsgBoxT
/*virtual*/
CxMsgBoxT::~CxMsgBoxT() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: mrMessageBox
#if defined(xOS_WIN)
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::mrMessageBox(
    const tString &csText, 
    const tString &csTitle,  
    const UINT     cuiType
) 
{
    EModalResult mrRes;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };
    
    tcout << xT("\n####################################################################################################\n");
    tcout << xT("#    ") << csTitle << xT("\n");
    tcout << xT("#\n");
    tcout << xT("#    ") << csText  << xT("\n");
    tcout << xT("\n####################################################################################################\n");
    tcout << xT("\n");
    tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    switch (cmRes) {
        case cmAbort:  { mrRes = mrAbort;  } break;
        case cmIgnore: { mrRes = mrIgnore; } break;
        case cmRetry:  { mrRes = mrRetry;  } break;

        default:       { mrRes = mrRetry;  } break;
    }

    return mrRes; 
}
#endif
//---------------------------------------------------------------------------
