/**
 * \file   CxMsgBox.inl
 * \brief  message box
 */


#include <xLib/Filesystem/CxPath.h>

#include "Platform/CxMsgBox_internal.inl"

#if   xOS_ENV_WIN
    #include "Platform/Win/CxMsgBox_win.inl"
#elif xOS_ENV_UNIX
    #if   xOS_ENV_LINUX
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xOS_ENV_BSD
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xOS_ENV_APPLE
        #include "Platform/Apple/CxMsgBox.inl"
    #endif
#endif

xNAMESPACE2_BEGIN(xlib, gui)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    return _show_impl(a_text, a_title, a_type);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, gui)
