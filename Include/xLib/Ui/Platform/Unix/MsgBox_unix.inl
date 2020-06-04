/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#if cmXCB_FOUND
    #include "XcbMsgBox.h"
#else
    #include <xLib/System/Console.h>
#endif


xNAMESPACE_BEGIN2(xl, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType            a_type    /* = Ok */
) const
{
    xUNUSED(a_type);

    ModalResult mrRv = ModalResult::Unknown;

#if cmXCB_FOUND
    XcbMsgBox msgBox;
    mrRv = static_cast<MsgBox::ModalResult>( msgBox.show(a_text, a_title, XcbMsgBox::Type::Ok) );
#else
    Console console;
    Console::ModalResult mrConsole = console.msgBox(a_text, a_title, 0);
    xUNUSED(mrConsole);

    mrRv = ModalResult::Ok;
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, ui)
