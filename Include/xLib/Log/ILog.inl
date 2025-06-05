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
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Trace, xT("%s"), msg.c_str());
#else
    std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
    write(Level::Trace, msg);
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::debug(
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Debug, xT("%s"), msg.c_str());
#else
	std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
	write(Level::Debug, msg);
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::info(
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Info, xT("%s"), msg.c_str());
#else
	std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
	write(Level::Info, msg);
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::warning(
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Warning, xT("%s"), msg.c_str());
#else
	std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
	write(Level::Warning, msg);
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::error(
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Error, xT("%s"), msg.c_str());
#else
	std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
	write(Level::Error, msg);
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
ILog::critical(
	cptr_ctchar_t a_format,
	Args&&...     a_args
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);

	write(Level::Critical, xT("%s"), msg.c_str());
#else
	std::ctstring_t msg = FormatC::str(a_format, std::forward<Args>(a_args)...);
	write(Level::Critical, msg);
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace

