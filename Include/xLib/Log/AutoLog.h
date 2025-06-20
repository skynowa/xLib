/**
 * \file  AutoLog.h
 * \brief logging
 */


#pragma once

#include "Cout.h"
#include "FileLog.h"
#include "SystemLog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

template<class T>
class AutoLog
    /// Auto log
{
public:
///\name ctors, dtor
///\{
	AutoLog(std::ctstring_t &a_str, cbool_t a_isEnable = true) :
		_str     (a_str),
		_isEnable(a_isEnable)
	{
		_log.setEnabled(_isEnable);
		_log.trace(xT("\n\n::: Start %s :::\n"), _str.c_str());
	}

   ~AutoLog()
	{
		_log.trace(xT("\n\n::: Finish %s :::\n"), _str.c_str());
	}

    xNO_COPY_ASSIGN(AutoLog);
///\}

private:
    std::ctstring_t _str;
    cbool_t         _isEnable {};
    T               _log;
};

using AutoTrace     = AutoLog<Cout>;
using AutoFileLog   = AutoLog<FileLog>;
using AutoSystemLog = AutoLog<SystemLog>;

} // namespace
//-------------------------------------------------------------------------------------------------
