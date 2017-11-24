/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#include "MsgBox.h"

#include "Platform/MsgBox_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/MsgBox_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/MsgBox_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ModalResult
MsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType           &a_type    /* = tpOk */
) const
{
    // TODO: MsgBox - fix unused warnings
    xUNUSED(internal::enums::modalResults);
    xUNUSED(internal::enums::types);

    return _show_impl(a_text, a_title, a_type);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, ui)
