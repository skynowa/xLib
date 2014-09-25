/**
 * \file   MsgBox.h
 * \brief  message box
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, gui)

class MsgBox
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

                  MsgBox() {}
        ///< constructor
    virtual      ~MsgBox() {}
        ///< destructor

    ExModalResult show(std::ctstring_t &text, const std::ctstring_t &title, cExType &type = tpOk)
        const xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

private:
    xNO_COPY_ASSIGN(MsgBox)

xPLATFORM:
    ExModalResult _show_impl(std::ctstring_t &text, const std::ctstring_t &title,
        cExType &type = tpOk) const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, gui)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "MsgBox.cpp"
#endif
