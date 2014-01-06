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
        mrUnknown,
        mrAbort,
        mrIgnore,
        mrRetry
    };
    typedef const ExModalResult cExModalResult;

                  CxMsgBox() {}
        ///< constructor
    virtual      ~CxMsgBox() {}
        ///< destructor

    ExModalResult show(std::ctstring_t &text, const std::ctstring_t &title, cExType &type = tpOk)  const
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

private:
    ExModalResult show_impl(std::ctstring_t &text, const std::ctstring_t &title, cExType &type = tpOk)  const
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

    xNO_COPY_ASSIGN(CxMsgBox)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxMsgBox.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMsgBoxH
