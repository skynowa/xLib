/**
 * \file  ILog.h
 * \brief logging interface
 */


#pragma once

#include "Trace.h"
#include "FileLog.h"
#include "SystemLog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, log)

template<class T>
class AutoLog
    /// Auto log
{
public:
    AutoLog(std::ctstring_t &a_str, cbool_t a_isEnable = true) :
        _str     (a_str),
        _isEnable(a_isEnable)
    {
        _log.setEnabled(_isEnable);
        _log.write(xT("\n\n::: Start %s :::\n"), _str.c_str());
    }

   ~AutoLog()
    {
        _log.write(xT("\n\n::: Finish %s :::\n"), _str.c_str());
    }

private:
    std::ctstring_t _str;
    cbool_t         _isEnable;
    T               _log;

    xNO_COPY_ASSIGN(AutoLog)
};

typedef AutoLog<Trace>     AutoTrace;
typedef AutoLog<FileLog>   AutoFileLog;
typedef AutoLog<SystemLog> AutoSystemLog;

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
