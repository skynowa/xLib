/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#if xHAVE_XCB
    #include "XcbMsgBox.h"
#endif


xNAMESPACE_BEGIN2(xlib, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE MsgBox::ExModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    xUNUSED(a_type);

    ExModalResult mrRv = mrUnknown;

#if xHAVE_XCB
    XcbMsgBox msgBox;
    mrRv = static_cast<MsgBox::ExModalResult>( msgBox.show(a_text, a_title, XcbMsgBox::tpOk) );
#else
    Console console;
    console.msgBox(a_text, a_title, 0);

    mrRv = mrOk;
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
