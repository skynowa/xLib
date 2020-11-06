/**
 * \file   ProcessInfo.h
 * \brief  process information
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Sync/Process.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class ProcessInfo
    /// process information
{
public:
///@name ctors, dtor
///@{
			 ProcessInfo() = default;
	virtual ~ProcessInfo() = default;

	xNO_COPY_ASSIGN(ProcessInfo)
///@}

    void_t         setProcessId(const Process::id_t &a_id);
        ///< set target process ID
    ulong_t        cpuUsage() const;
        ///< get CPU usage (percentage)
    ulong_t        ramUsage() const;
        ///< get RAM usage (percentage)
    ulong_t        ioBytes() const;
        ///< get total read and written bytes
    std::tstring_t exeName() const;
        ///< get exe name
    ulong_t        parentId() const;
        ///< get parent process id
    void_t         commandLine(std::vec_tstring_t *args) const;
        ///< get arguments

    static
    long_t         commandLineArgsMax();
        ///< get maximum length of command line arguments (in chars)
    static
    void_t         commandLine(cint_t &argsNum, cptr_ctchar_t argv[], std::vec_tstring_t *args);
        ///< get arguments

private:
    Process::id_t _id {};  ///< target process ID

xPLATFORM_IMPL:
    ulong_t        _cpuUsage_impl() const;
    ulong_t        _ramUsage_impl() const;
    ulong_t        _ioBytes_impl() const;
    std::tstring_t _exeName_impl() const;
    ulong_t        _parentId_impl() const;
    void_t         _commandLine_impl(std::vec_tstring_t *args) const;

    static
    long_t _commandLineArgsMax_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
