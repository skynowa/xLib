/**
 * \file  ILog.inl
 * \brief logging
 */


#include <xLib/Core/FormatC.h>
#include <xLib/Debug/Debug.h>

namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::trace(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

    std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
    write(Level::Trace, msg);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::debug(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

	std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
	write(Level::Debug, msg);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::info(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

	std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
	write(Level::Info, msg);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::warning(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

	std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
	write(Level::Warning, msg);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::error(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

	std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
	write(Level::Error, msg);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::critical(
	cptr_ctchar_t      a_fmt,
	Args          &&...a_args
) const
{
    xCHECK_DO(!_isEnable, return);

	std::ctstring_t msg = FormatC::str(a_fmt, std::forward<Args>(a_args)...);
	write(Level::Critical, msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace

