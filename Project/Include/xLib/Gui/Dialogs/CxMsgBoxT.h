/**
 * \file  CxMsgBoxT.h
 * \brief message box
 */


#pragma once

#ifndef xLib_CxMsgBoxTH
#define xLib_CxMsgBoxTH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMsgBoxT :
    public CxNonCopyable
    /// message box
{
public:
    enum ExModalResult
        /// modal result
    {
        #if xOS_ENV_WIN
            mrAbort  = IDABORT,
            mrIgnore = IDIGNORE,
            mrRetry  = IDRETRY
        #else
            mrAbort  = 25856,
            mrIgnore = 26112,
            mrRetry  = 26368
        #endif
    };

#if xOS_ENV_WIN
    template <class TextT, class TitleT>
    static ExModalResult show(const HWND &handle, const TextT &text, const TitleT &title,
        cuint_t &type) xWARN_UNUSED_RV;
        ///< message box has parent window, with custom text, custom title, custom type
#endif

    template <class TextT, class TitleT>
    static ExModalResult show(const TextT &text, const TitleT &title, cuint_t &type)
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

    template <class TextT, class TitleT>
    static ExModalResult show(const TextT &text, const TitleT &title) xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, default type

    template <class TextT>
    static ExModalResult show(const TextT &text) xWARN_UNUSED_RV;
        ///< message box with custom text, default title, default type

private:
                         CxMsgBoxT();
        ///< constructor
    virtual             ~CxMsgBoxT();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxMsgBoxT.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMsgBoxTH
