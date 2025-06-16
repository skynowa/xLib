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
	virtual  ~SystemLog();
///\}

///\name Overrides
///\{
	void_t write(cLevel level, std::ctstring_t &msg) const final;
///\}

private:
#if xENV_WIN
    HANDLE _handle {xNATIVE_HANDLE_NULL}; ///< event log handle
#endif

xPLATFORM_IMPL:
    void_t _ctor_impl(std::ctstring_t &logName);
    void_t _dtor_impl();
    void_t _write_impl(cLevel level, std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
