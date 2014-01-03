/**
 * \file  CxMsgBox.h
 * \brief message box
 */


#pragma once

#ifndef xLib_CxMsgBoxH
#define xLib_CxMsgBoxH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMsgBox
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
        #if   xOS_ENV_WIN
            mrUnknown = - 1,
            mrAbort   = IDABORT,
            mrIgnore  = IDIGNORE,
            mrRetry   = IDRETRY
        #elif xOS_ENV_UNIX
            mrUnknown = - 1,
            mrAbort   = 25856,
            mrIgnore  = 26112,
            mrRetry   = 26368
        #endif
    };
    typedef const ExModalResult cExModalResult;

                  CxMsgBox() {}
        ///< constructor
    virtual      ~CxMsgBox() {}
        ///< destructor

    ExModalResult show(std::ctstring_t &text, const std::ctstring_t &title, cExType &type = tpOk)  const
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

    xNO_COPY_ASSIGN(CxMsgBox)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxMsgBox.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMsgBoxH
