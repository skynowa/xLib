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
Test_Cpu::unit()
{
	info::Cpu sysInfo;

    xTEST_CASE("num")
    {
        m_ulRv = sysInfo.num();
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("currentNum")
    {
        m_ulRv = sysInfo.currentNum();
        xTEST_GR(sysInfo.num(), m_ulRv);
    }

    xTEST_CASE("vendor")
    {
    	info::Cpu::cVendor cvType = sysInfo.vendor();
        xTEST(cvType == info::Cpu::Vendor::Intel || cvType == info::Cpu::Vendor::Amd);
    }

    xTEST_CASE("model")
    {
        m_sRv = sysInfo.model();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("speed")
    {
        m_ulRv = sysInfo.speed();
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("usage")
    {
        for (size_t i = 0; i < 5; ++ i) {
            m_ulRv = sysInfo.usage();
            xTEST_NA(m_ulRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
