/**
 * \file  CxMsgBoxT.inl
 * \brief message box
 */


#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const HWND    chWnd,
    const TextT  &cText,
    const TitleT &cTitle,
    const UINT    cuiType
)
{
    EModalResult mrRes = mrAbort;

    mrRes = static_cast<EModalResult>( ::MessageBox(
                            chWnd,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            cuiType) );

    return mrRes;
}

#endif
//---------------------------------------------------------------------------
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle,
    const UINT    cuiType
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_ENV_WIN)
    mrRes = static_cast<EModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            cuiType) );
#elif defined(xOS_ENV_UNIX)
    std::tstring sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            xT("Abort, Ignore, Retry"));

    mrRes = static_cast<EModalResult>( xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
template <class TextT, class TitleT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT  &cText,
    const TitleT &cTitle
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_ENV_WIN)
    mrRes = static_cast<EModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            MB_OK) );
#elif defined(xOS_ENV_UNIX)
    std::tstring sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            CxString::lexical_cast(cTitle).c_str(),
                            xT("Ok"));

    mrRes = static_cast<EModalResult>( xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
template <class TextT>
/*static*/
CxMsgBoxT::EModalResult
CxMsgBoxT::iShow(
    const TextT &cText
)
{
    EModalResult mrRes = mrAbort;

#if defined(xOS_ENV_WIN)
    mrRes = static_cast<EModalResult>( ::MessageBox(
                            NULL,
                            CxString::lexical_cast(cText).c_str(),
                            CxPath::sGetFullName( CxPath::sGetExe() ).c_str(),
                            MB_OK) );
#elif defined(xOS_ENV_UNIX)
    std::tstring sMsg = CxString::sFormat(
                            xT("xmessage -center \"%s\" -title \"%s\" -buttons \"%s\""),
                            CxString::lexical_cast(cText).c_str(),
                            xT("Message box"),
                            xT("Ok"));

    mrRes = static_cast<EModalResult>( xTSYSTEM(sMsg.c_str()) );
#endif

    return mrRes;
}
//---------------------------------------------------------------------------
