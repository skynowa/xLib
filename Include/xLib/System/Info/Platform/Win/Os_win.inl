/**
 * \file  Os.inl
 * \brief system information
 */


namespace xl::system::info
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Os::OsType
Os::_os_impl() const
{
    OsType otRv = OsType::Unknown;

    OSVERSIONINFO info {};
    info.dwOSVersionInfoSize = sizeof(info);

    BOOL blRv = ::GetVersionEx(&info);
    xTEST_DIFF(blRv, FALSE);

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        otRv = OsType::Windows3;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        xCHECK_DO(info.dwMinorVersion == 0UL,  otRv = OsType::Windows95; break);
        xCHECK_DO(info.dwMinorVersion == 10UL, otRv = OsType::Windows98; break);
        xCHECK_DO(info.dwMinorVersion == 90UL, otRv = OsType::Windows98; break);
        break;
    case VER_PLATFORM_WIN32_NT:
        xCHECK_DO(info.dwMajorVersion <= 4UL,                               otRv = OsType::WindowsNT;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 0UL, otRv = OsType::Windows2000;            break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 1UL, otRv = OsType::WindowsXP;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = OsType::WindowsXPProx64Edition; break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = OsType::WindowsServer2003;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = OsType::WindowsHomeServer;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = OsType::WindowsServer2003R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = OsType::WindowsVista;           break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = OsType::WindowsServer2008;      break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = OsType::WindowsServer2008R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = OsType::Windows7;               break);

        // for unknown windows/newest windows version
        otRv = OsType::Unknown;
        break;
    default:
        otRv = OsType::Unknown;
        break;
    }

    return otRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_formatOs_impl() const
{
    std::tstring_t sRv;

    cOsType type = os();
    switch (type) {
    case OsType::Windows3:
        sRv = xT("Windows 3.1");
        break;
    case OsType::Windows95:
        sRv = xT("Windows 95");
        break;
    case OsType::Windows98:
        sRv = xT("Windows 98");
        break;
    case OsType::WindowsNT:
        sRv = xT("Windows NT 4.0");
        break;
    case OsType::Windows2000:
        sRv = xT("Windows 2000");
        break;
    case OsType::WindowsXP:
        sRv = xT("Windows XP");
        break;
    case OsType::WindowsXPProx64Edition:
        sRv = xT("Windows XP Pro x64 Edition");
        break;
    case OsType::WindowsServer2003:
        sRv = xT("Windows Server 2003");
        break;
    case OsType::WindowsHomeServer:
        sRv = xT("Windows Home Server");
        break;
    case OsType::WindowsServer2003R2:
        sRv = xT("Windows Server 2003 R2");
        break;
    case OsType::WindowsVista:
        sRv = xT("Windows Vista");
        break;
    case OsType::WindowsServer2008:
        sRv = xT("Windows Server 2008");
        break;
    case OsType::WindowsServer2008R2:
        sRv = xT("Windows Server 2008 R2");
        break;
    case OsType::Windows7:
        sRv = xT("Windows 7");
        break;
    default:
        sRv = Const::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_distro_impl() const
{
    return formatOs();
}
//-------------------------------------------------------------------------------------------------
Os::OsArch
Os::_osArch_impl() const
{
    OsArch oaRv = OsArch::Unknown;

#if   xARCH_BITS_32
    BOOL isFuncExist = FALSE;
    {
        Dll dll;
        dll.load(xT("kernel32.dll"));
        isFuncExist = dll.isProcExists(xT("IsWow64Process"));
    }

    BOOL is64BitOs      = FALSE;
    BOOL isWow64Process = ::IsWow64Process(::GetCurrentProcess(), &is64BitOs);

    oaRv = (isFuncExist && isWow64Process && is64BitOs) ? OsArch::Bit64 : OsArch::Bit32;
#elif xARCH_BITS_64
    oaRv = OsArch::Bit64;
#else
    // 64-bit Windows does not support Win16
    oaRv = OsArch::Unknown;
#endif

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_desktopName_impl() const
{
    std::tstring_t  sRv;
    std::ctstring_t nativeDesktop = xT("explorer.exe");

#if 0
    // TODO: [skynowa] Os::desktopName()
    const Process::id_t pid = Process::idByName(nativeDesktop);

    bool_t bRv = Process::isRunning(pid);
    if (bRv) {
        sRv = nativeDesktop;
    } else {
        // TODO: [skynowa] Os::desktopName() - checks for detecting Windows shell
    }

    xTEST_EQ(sRv.empty(), false);
#else
    sRv = nativeDesktop;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
