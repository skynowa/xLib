/**
 * \file  ILog.h
 * \brief logging interface
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, log)

template<class T>
class AutoLog
    /// Auto log
{
public:
    AutoLog(std::ctstring_t &a_str, cbool_t a_isEnable = true) :
        _str(a_str)
    {
        _log.setEnabled(a_isEnable);

        _log << xT("\n\n::: Start ") << _str << xT(" :::\n");
    }
   ~AutoLog()
    {
        _log << xT("\n::: Finish ") << _str << xT(" :::\n");
    }

private:
    std::ctstring_t _str;
    T               _log;

    xNO_COPY_ASSIGN(AutoLog)
};

typedef AutoLog<Trace>     AutoTrace;
typedef AutoLog<FileLog>   AutoFileLog;
typedef AutoLog<SystemLog> AutoSystemLog;

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
