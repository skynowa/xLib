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

class CxMsgBoxT
    /// message box
{
public:
    enum ExType
        ///< windows type
    {
        tpOk,
        tpAbortRetryIgnore
    };
    typedef const ExType cExType;

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
    typedef const ExModalResult cExModalResult;

                  CxMsgBoxT() {}
        ///< constructor
    virtual      ~CxMsgBoxT() {}
        ///< destructor

#if xOS_ENV_WIN
    template <class TextT, class TitleT>
    ExModalResult show(const HWND &parentWnd, const TextT &text, const TitleT &title, cuint_t &type)
        const xWARN_UNUSED_RV;
        ///< message box has parent window, with custom text, custom title, custom type
#endif

    template <class TextT, class TitleT>
    ExModalResult show(const TextT &text, const TitleT &title, cExType &type = tpOk)  const
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

    xNO_COPY_ASSIGN(CxMsgBoxT)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxMsgBoxT.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMsgBoxTH
