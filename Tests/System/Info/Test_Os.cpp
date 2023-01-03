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
        Os::cOsType otType = sysInfo.os();
        xTEST_DIFF((int)otType, (int)Os::OsType::Unknown);

        #if   xENV_WIN
            m_bRv =
                otType == Os::OsType::Windows3 ||
                otType == Os::OsType::Windows95 ||
                otType == Os::OsType::Windows98 ||
                otType == Os::OsType::WindowsNT ||
                otType == Os::OsType::Windows2000 ||
                otType == Os::OsType::WindowsXP ||
                otType == Os::OsType::WindowsXPProx64Edition ||
                otType == Os::OsType::WindowsServer2003 ||
                otType == Os::OsType::WindowsHomeServer ||
                otType == Os::OsType::WindowsServer2003R2 ||
                otType == Os::OsType::WindowsVista ||
                otType == Os::OsType::WindowsServer2008 ||
                otType == Os::OsType::WindowsServer2008R2 ||
                otType == Os::OsType::Windows7;

            xTEST(m_bRv);
        #elif xENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ((int)otType, (int)Os::OsType::FreeBSD);
            #else
                xTEST_EQ((int)otType, (int)Os::OsType::Linux);
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
        Os::cOsArch oaRes = sysInfo.osArch();
        xTEST_DIFF((int)oaRes, (int)Os::OsArch::Unknown);
    }

    xTEST_CASE("formatOsArch")
    {
        m_sRv = sysInfo.formatOsArch();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
