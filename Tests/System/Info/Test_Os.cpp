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
    	info::Os::cOsType otType = sysInfo.os();
        xTEST_DIFF((int)otType, (int)info::Os::OsType::Unknown);

        #if   xENV_WIN
            m_bRv =
                otType == info::Os::OsType::Windows3 ||
                otType == info::Os::OsType::Windows95 ||
                otType == info::Os::OsType::Windows98 ||
                otType == info::Os::OsType::WindowsNT ||
                otType == info::Os::OsType::Windows2000 ||
                otType == info::Os::OsType::WindowsXP ||
                otType == info::Os::OsType::WindowsXPProx64Edition ||
                otType == info::Os::OsType::WindowsServer2003 ||
                otType == info::Os::OsType::WindowsHomeServer ||
                otType == info::Os::OsType::WindowsServer2003R2 ||
                otType == info::Os::OsType::WindowsVista ||
                otType == info::Os::OsType::WindowsServer2008 ||
                otType == info::Os::OsType::WindowsServer2008R2 ||
                otType == info::Os::OsType::Windows7;

            xTEST(m_bRv);
        #elif xENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ((int)otType, (int)info::Os::OsType::FreeBSD);
            #else
                xTEST_EQ((int)otType, (int)info::Os::OsType::Linux);
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
    	info::Os::cOsArch oaRes = sysInfo.osArch();
        xTEST_DIFF((int)oaRes, (int)info::Os::OsArch::Unknown);
    }

    xTEST_CASE("formatOsArch")
    {
        m_sRv = sysInfo.formatOsArch();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
