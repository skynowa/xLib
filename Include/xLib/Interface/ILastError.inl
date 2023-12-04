/**
 * \file  ILastError.inl
 * \brief Last error
 */


#include <xLib/Core/Format.h>

namespace xl::interface_
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename CodeT>
ILastError<CodeT>::ILastError(
	const CodeT      a_code,
	std::ctstring_t &a_what
) :
    _code{a_code},
    _what{a_what}
{
}
//-------------------------------------------------------------------------------------------------
template<typename CodeT>
bool_t
ILastError<CodeT>::isError() const
{
    return !isOk();
}
//-------------------------------------------------------------------------------------------------
template<typename CodeT>
std::tstring_t
ILastError<CodeT>::str() const
{
    const auto &code_  = code();
    const auto &okStr_ = isOk() ? xT("Success") : xT("Failure");
    const auto &what_  = what();

    return Format::str(xT("{} ({}) - {}"), code_, okStr_, what_);
}
//-------------------------------------------------------------------------------------------------

} // namespace
