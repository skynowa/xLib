/**
 * \file   MsgBox.inl
 * \brief  message box
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "MsgBox.h"
#endif

#include "Platform/MsgBox_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/MsgBox_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/MsgBox_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/MsgBox_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/MsgBox_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, gui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE MsgBox::ExModalResult
MsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    return _show_impl(a_text, a_title, a_type);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, gui)
