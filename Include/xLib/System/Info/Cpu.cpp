/**
 * \file  Cpu.cpp
 * \brief CPU information
 */


#include "Cpu.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Dll.h>

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
Cpu::num() const
{
    return _num_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::currentNum() const
{
    return _currentNum_impl();
}
//-------------------------------------------------------------------------------------------------
Cpu::Vendor
Cpu::vendor() const
{
    Vendor          cvRv  = Vendor::Unknown;
    std::ctstring_t value = _vendor_impl();

    if      (value == std::tstring_t(xT("GenuineIntel"))) {
        cvRv = Vendor::Intel;
    }
    else if (value == std::tstring_t(xT("AuthenticAMD"))) {
        cvRv = Vendor::Amd;
    }
    else {
        cvRv = Vendor::Unknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::model() const
{
    return _model_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::speed() const
{
    return _speed_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::usage() const
{
    return _usage_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
