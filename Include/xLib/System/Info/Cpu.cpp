/**
 * \file  Cpu.cpp
 * \brief system information
 */


#include "Cpu.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/File.h>
#include <xLib/System/Environment.h>
#include <xLib/System/Info/Os.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/Cpu_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Cpu_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Cpu_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Cpu_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Cpu_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::cpusNum() const
{
    return _cpusNum_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::currentCpuNum() const
{
    return _currentCpuNum_impl();
}
//-------------------------------------------------------------------------------------------------
Cpu::CpuVendor
Cpu::cpuVendor() const
{
    CpuVendor       cvRv  = CpuVendor::Unknown;
    std::ctstring_t value = _cpuVendor_impl();

    if      (value == std::tstring_t(xT("GenuineIntel"))) {
        cvRv = CpuVendor::Intel;
    }
    else if (value == std::tstring_t(xT("AuthenticAMD"))) {
        cvRv = CpuVendor::Amd;
    }
    else {
        cvRv = CpuVendor::Unknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::cpuModel() const
{
    return _cpuModel_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::cpuSpeed() const
{
    return _cpuSpeed_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
