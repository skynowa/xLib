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
    ExModalResult mrRv = mrUnknown;

#if xHAVE_XCB
    xUNUSED(a_type);

    XcbMsgBox msgBox;
    mrRv = static_cast<MsgBox::ExModalResult>( msgBox.show(a_text, a_title, XcbMsgBox::tpOk) );
#else
    xUNUSED(a_text);
    xUNUSED(a_title);
    xUNUSED(a_type);

    xUNUSED(internal::enums::types);
    xUNUSED(internal::enums::modalResults);

    // TODO: MsgBox::_show_impl() - Unix
    #pragma message("xLib: MsgBox::_show_impl() - n/a")
#endif

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, ui)
