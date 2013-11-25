/**
 * \file  CxMsgBoxT.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

template <class TextT, class TitleT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const HWND   &a_parentWnd,
    const TextT  &a_text,
    const TitleT &a_title,
    cuint_t      &a_type
)
{
    ExModalResult mrRes = mrAbort;

    mrRes = static_cast<ExModalResult>( ::MessageBox(
        a_parentWnd,
        CxString::cast(a_text).c_str(),
        CxString::cast(a_title).c_str(),
        a_type) );

    return mrRes;
}

#endif
//-------------------------------------------------------------------------------------------------
template <class TextT, class TitleT>
/* static */
CxMsgBoxT::ExModalResult
CxMsgBoxT::show(
    const TextT  &a_text,
    const TitleT &a_title,
    cExType      &a_type    /* = 0U */
)
{
    ExModalResult mrRes = mrAbort;
    std::string   title = CxString::cast(a_title);

    if ( title.empty() ) {
        title = CxPath(CxPath::exe()).fileName();
    }

#if 0
    // TODO: from CxDebugger::_msgboxPlain()
    #if xOS_ENV_WIN
        uint_t type = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
    #else
        uint_t type = 1U;
    #endif
#endif

#if   xOS_ENV_WIN
    mrRes = static_cast<ExModalResult>( ::MessageBox(
        NULL,
        CxString::cast(a_text).c_str(),
        title.c_str(),
        a_type) );
#elif xOS_ENV_UNIX
    std::ctstring_t msg = CxString::format(
        xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
        CxString::cast(a_text).c_str(),
        title.c_str(),
        xT("Abort, Ignore, Retry"));    /* xT("Ok") */

    mrRes = static_cast<ExModalResult>( std::xTSYSTEM(msg.c_str()) );
#endif

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
