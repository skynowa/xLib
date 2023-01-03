/**
 * \file   Test_Cpu.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Cpu)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SystemInfo::unit()
{
	Cpu sysInfo;

    xTEST_CASE("cpusNum")
    {
        m_ulRv = sysInfo.cpusNum();
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("currentCpuNum")
    {
        m_ulRv = sysInfo.currentCpuNum();
        xTEST_GR(sysInfo.cpusNum(), m_ulRv);
    }

    xTEST_CASE("cpuVendor")
    {
        Cpu::cCpuVendor cvType = sysInfo.cpuVendor();
        xTEST(cvType == Cpu::CpuVendor::Intel || cvType == Cpu::CpuVendor::Amd);
    }

    xTEST_CASE("cpuModel")
    {
        m_sRv = sysInfo.cpuModel();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("cpuSpeed")
    {
        m_ulRv = sysInfo.cpuSpeed();
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("cpuUsage")
    {
        for (size_t i = 0; i < 5; ++ i) {
            m_ulRv = sysInfo.cpuUsage();
            xTEST_NA(m_ulRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
