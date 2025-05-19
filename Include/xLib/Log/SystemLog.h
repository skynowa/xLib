/**
 * \file   SystemLog.h
 * \brief  logging to system log
 */


#pragma once

#include <xLib/Core/Core.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class SystemLog final :
    public ILog
    /// logging to system event log
{
public:
///\name ctors, dtor
///\{
			  SystemLog();
	explicit  SystemLog(std::ctstring_t &logName);
			 ~SystemLog() final;
///\}

///\name operators
///\{
	template<typename T>
	SystemLog & operator << (const T &valueT);
///\}

///\name Overrides
///\{
	void_t write(cLevel level, cptr_ctchar_t format, ...) const final;
///\}

private:
#if xENV_WIN
    HANDLE _handle {xNATIVE_HANDLE_NULL}; ///< event log handle
#endif

xPLATFORM_IMPL:
    void_t _construct_impl(std::ctstring_t &logName);
    void_t _destruct_impl();
    void_t _write_impl(cLevel level, std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "SystemLog.inl"
