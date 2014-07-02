/**
 * \file   ProcessInfo.h
 * \brief  process information
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Sync/Process.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, system)

class ProcessInfo
    /// process information
{
public:
                    ProcessInfo();
        ///< constructor
    virtual        ~ProcessInfo() {}
        ///< destructor

    void_t          setProcessId(const Process::id_t &a_id);
        ///< set target process ID
    ulong_t         cpuUsage() const xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)
    ulong_t         ramUsage() const xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)
    ulong_t         ioBytes() const xWARN_UNUSED_RV;
        ///< get total read and written bytes
    std::tstring_t  exeName() const xWARN_UNUSED_RV;
        ///< get exe name
    ulong_t         parentId() const xWARN_UNUSED_RV;
        ///< get parent process id
    void_t          commandLine(std::vec_tstring_t *args) const;
        ///< get arguments

    static
    long_t          commandLineArgsMax() xWARN_UNUSED_RV;
        ///< get maximum length of command line arguments (in chars)

private:
    Process::id_t _id;  ///< target process ID

    xNO_COPY_ASSIGN(ProcessInfo)

xPLATFORM:
    ulong_t         _cpuUsage_impl() const xWARN_UNUSED_RV;
    ulong_t         _ramUsage_impl() const xWARN_UNUSED_RV;
    ulong_t         _ioBytes_impl() const xWARN_UNUSED_RV;
    std::tstring_t  _exeName_impl() const xWARN_UNUSED_RV;
    ulong_t         _parentId_impl() const xWARN_UNUSED_RV;
    void_t          _commandLine_impl(std::vec_tstring_t *args) const;

    static
    long_t          _commandLineArgsMax_impl() xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#include "ProcessInfo.inl"
