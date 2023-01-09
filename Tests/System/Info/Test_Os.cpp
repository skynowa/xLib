/**
 * \file   Test_Os.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Os)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Os::unit()
{
	info::Os sysInfo;

    xTEST_CASE("os")
    {
    	info::Os::cType otType = sysInfo.os();
        xTEST_DIFF((int)otType, (int)info::Os::Type::Unknown);

        #if   xENV_WIN
            m_bRv =
                otType == info::Os::Type::Windows3 ||
                otType == info::Os::Type::Windows95 ||
                otType == info::Os::Type::Windows98 ||
                otType == info::Os::Type::WindowsNT ||
                otType == info::Os::Type::Windows2000 ||
                otType == info::Os::Type::WindowsXP ||
                otType == info::Os::Type::WindowsXPProx64Edition ||
                otType == info::Os::Type::WindowsServer2003 ||
                otType == info::Os::Type::WindowsHomeServer ||
                otType == info::Os::Type::WindowsServer2003R2 ||
                otType == info::Os::Type::WindowsVista ||
                otType == info::Os::Type::WindowsServer2008 ||
                otType == info::Os::Type::WindowsServer2008R2 ||
                otType == info::Os::Type::Windows7;

            xTEST(m_bRv);
        #elif xENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ((int)otType, (int)info::Os::Type::FreeBSD);
            #else
                xTEST_EQ((int)otType, (int)info::Os::Type::Linux);
            #endif
        #endif
    }

    xTEST_CASE("formatOs")
    {
        m_sRv = sysInfo.formatOs();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("distro")
    {
        m_sRv = sysInfo.distro();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("arch")
    {
    	info::Os::cArch oaRes = sysInfo.arch();
        xTEST_DIFF((int)oaRes, (int)info::Os::Arch::Unknown);
    }

    xTEST_CASE("formatArch")
    {
        m_sRv = sysInfo.formatArch();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
