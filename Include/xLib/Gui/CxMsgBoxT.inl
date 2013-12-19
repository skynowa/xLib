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
) const
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
    cExType      &a_type    /* = tpOk */
) const
{
    ExModalResult mrRes = mrAbort;
    std::string   title = CxString::cast(a_title);

    // title
    if ( title.empty() ) {
        title = CxPath(CxPath::exe()).fileName();
    }

#if   xOS_ENV_WIN
    UINT type = MB_OK;
    {
        switch (a_type) {
        case tpOk:
        default:
            type = MB_OK;
            break;
        case tpAbortRetryIgnore:
            type = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
            break;
        }
    }

    mrRes = static_cast<ExModalResult>( ::MessageBox(
        NULL,
        CxString::cast(a_text).c_str(),
        title.c_str(),
        a_type) );
#elif xOS_ENV_UNIX
    #if xHAVE_XMESSAGE
        std::tstring_t type = xT("Ok");
        {
            switch (a_type) {
            case tpOk:
            default:
                type = xT("Ok");
                break;
            case tpAbortRetryIgnore:
                type = xT("Abort, Ignore, Retry");
                break;
            }
        }

        std::ctstring_t msg = CxString::format(
            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
            CxString::cast(a_text).c_str(),
            title.c_str(),
            type.c_str());

        mrRes = static_cast<ExModalResult>( std::xTSYSTEM(msg.c_str()) );
    #else
        #pragma message("xLib: CxMsgBoxT::show() - n/a")
        mrRes = mrUnknown;
    #endif
#endif

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
