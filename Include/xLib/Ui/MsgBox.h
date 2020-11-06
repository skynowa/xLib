/**
 * \file   MsgBox.h
 * \brief  message box
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::ui
{

class MsgBox
    /// message box
{
public:
    enum class Type
        ///< windows type
    {
        Unknown,
        Ok,
        OkCancel,
        YesNo,
        RetryCancel,
        YesNoCancel,
        AbortRetryIgnore,
        CancelTryContinue
    };
    xUSING_CONST(Type);

    enum class ModalResult
        /// modal result
    {
        Unknown,
        Ok,
        Yes,
        No,
        Abort,
        Cancel,
        Continue,
        Ignore,
        Retry,
        TryAgain
    };
    xUSING_CONST(ModalResult);

///@name ctors, dtor
///@{
			 MsgBox() = default;
	virtual ~MsgBox() = default;

    xNO_COPY_ASSIGN(MsgBox)
///@}

    ModalResult show(std::ctstring_t &text, std::ctstring_t &title, cType type = Type::Ok) const;
        ///< message box with custom text, custom title, custom type

xPLATFORM_IMPL:
    ModalResult _show_impl(std::ctstring_t &text, std::ctstring_t &title, cType type = Type::Ok) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
