/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#if cmXCB_FOUND
    #include "XcbMsgBox.h"
#endif


xNAMESPACE_BEGIN2(xl, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE MsgBox::ModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType           &a_type    /* = tpOk */
) const
{
    xUNUSED(a_type);

    ModalResult mrRv = mrUnknown;

#if cmXCB_FOUND
    XcbMsgBox msgBox;
    mrRv = static_cast<MsgBox::ModalResult>( msgBox.show(a_text, a_title, XcbMsgBox::tpOk) );
#else
    Console console;
    console.msgBox(a_text, a_title, 0);

    mrRv = mrOk;
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, ui)
