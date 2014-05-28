/**
 * \file   CxSystemLog.h
 * \brief  logging to system log
 */


#pragma once

#include <xLib/Core/xCore.h>
#include "IxLog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, log)

class CxSystemLog :
    public IxLog
    /// logging to system event log
{
public:
                   CxSystemLog();
        ///< constructor
    explicit       CxSystemLog(std::ctstring_t &logName);
        ///< constructor
    virtual       ~CxSystemLog();
        ///< destructor

    template<class T>
    CxSystemLog &  operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(ctchar_t *format, ...) const xOVERRIDE;
        ///< write to log
    virtual void_t write(cExLevel &level, ctchar_t *format, ...) const xOVERRIDE;
        ///< write to log

private:
#if xENV_WIN
    HANDLE         _handle;     ///< event log handle
#endif

xPLATFORM:
    void_t         _construct_impl(std::ctstring_t &logName);
    void_t         _destruct_impl();
    void_t         _write_impl(cExLevel &level, std::ctstring_t &msg) const;
};

xNAMESPACE_END2(xlib, log)
//-------------------------------------------------------------------------------------------------
#include "CxSystemLog.inl"
