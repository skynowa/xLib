/**
 * \file   SystemLog.h
 * \brief  logging to system log
 */


#pragma once

#include <xLib/Core/Core.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, log)

class SystemLog :
    public ILog
    /// logging to system event log
{
public:
                   SystemLog();
        ///< constructor
    explicit       SystemLog(std::ctstring_t &logName);
        ///< constructor
    virtual       ~SystemLog();
        ///< destructor

    template<typename T>
    SystemLog &    operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< write to log
    virtual void_t write(cExLevel &level, cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< write to log

private:
#if xENV_WIN
    HANDLE         _handle;     ///< event log handle
#endif

xPLATFORM_IMPL:
    void_t         _construct_impl(std::ctstring_t &logName);
    void_t         _destruct_impl();
    void_t         _write_impl(cExLevel &level, std::ctstring_t &msg) const;
};

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
#include "SystemLog.inl"

#if cmOPTION_PROJECT_HEADER_ONLY
    #include "SystemLog.cpp"
#endif
