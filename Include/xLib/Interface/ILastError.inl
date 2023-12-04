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
    const auto &code_     = code();
    const auto &okStr_    = isOk() ? xT("Success") : xT("Failure");
    const auto &category_ = category();
    const auto &message_  = message();

    return Format::str(xT("[{}] {} ({}) - {}"),  category_, code_, okStr_, message_);
}
//-------------------------------------------------------------------------------------------------

} // namespace
