/**
 * \file   MsgBox.h
 * \brief  message box
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, ui)

class MsgBox
    /// message box
{
public:
    enum Type
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
    xTYPEDEF_CONST(Type);

    enum ModalResult
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
    xTYPEDEF_CONST(ModalResult);

                  MsgBox() {}
        ///< constructor
    virtual      ~MsgBox() {}
        ///< destructor

    ModalResult show(std::ctstring_t &text, std::ctstring_t &title, cType &type = tpOk) const
        xWARN_UNUSED_RV;
        ///< message box with custom text, custom title, custom type

private:
    xNO_COPY_ASSIGN(MsgBox)

xPLATFORM_IMPL:
    ModalResult _show_impl(std::ctstring_t &text, std::ctstring_t &title,
        cType &type = tpOk) const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xl, ui)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "MsgBox.cpp"
#endif
