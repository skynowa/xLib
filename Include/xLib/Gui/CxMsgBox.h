/**
 * \file   CxMsgBox.h
 * \brief  message box
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, gui)

class CxMsgBox
    /// message box
{
public:
    enum ExType
        ///< windows type
    {
        tpUnknown,
        tpOk,
        tpOkCancel,
        tpYesNo,
        tpRetryCancel,
        tpYesNoCancel,
        tpAbortRetryIgnore,
        tpCancelTryContinue
    };
    typedef const ExType cExType;

    enum ExModalResult
        /// modal result
    {
        mrUnknown,
        mrOk,
        mrYes,
        mrNo,
        mrAbort,
        mrCancel,
        mrContinue,
        mrIgnore,
        mrRetry,
        mrTryAgain
    };
    typedef const ExModalResult cExModalResult;

                  CxMsgBox() {}
        ///< constructor
    virtual      ~CxMsgBox() {}
        ///< destructor

    ExModalResult show(std::ctstring_t &text, const std::ctstring_t &title, cExType &type = tpOk)
        const xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

private:
    xNO_COPY_ASSIGN(CxMsgBox)

xPLATFORM_IMPL:
    ExModalResult _show_impl(std::ctstring_t &text, const std::ctstring_t &title,
        cExType &type = tpOk) const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, gui)
//-------------------------------------------------------------------------------------------------
#include "CxMsgBox.inl"
