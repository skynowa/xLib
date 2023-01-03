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
	Os sysInfo;

    xTEST_CASE("os")
    {
        SystemInfo::cOsType otType = sysInfo.os();
        xTEST_DIFF((int)otType, (int)SystemInfo::OsType::Unknown);

        #if   xENV_WIN
            m_bRv =
                otType == SystemInfo::OsType::Windows3 ||
                otType == SystemInfo::OsType::Windows95 ||
                otType == SystemInfo::OsType::Windows98 ||
                otType == SystemInfo::OsType::WindowsNT ||
                otType == SystemInfo::OsType::Windows2000 ||
                otType == SystemInfo::OsType::WindowsXP ||
                otType == SystemInfo::OsType::WindowsXPProx64Edition ||
                otType == SystemInfo::OsType::WindowsServer2003 ||
                otType == SystemInfo::OsType::WindowsHomeServer ||
                otType == SystemInfo::OsType::WindowsServer2003R2 ||
                otType == SystemInfo::OsType::WindowsVista ||
                otType == SystemInfo::OsType::WindowsServer2008 ||
                otType == SystemInfo::OsType::WindowsServer2008R2 ||
                otType == SystemInfo::OsType::Windows7;

            xTEST(m_bRv);
        #elif xENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ((int)otType, (int)SystemInfo::OsType::FreeBSD);
            #else
                xTEST_EQ((int)otType, (int)SystemInfo::OsType::Linux);
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

    xTEST_CASE("osArch")
    {
        SystemInfo::cOsArch oaRes = sysInfo.osArch();
        xTEST_DIFF((int)oaRes, (int)SystemInfo::OsArch::Unknown);
    }

    xTEST_CASE("formatOsArch")
    {
        m_sRv = sysInfo.formatOsArch();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
