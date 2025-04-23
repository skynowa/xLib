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
Os::Type
Os::_os_impl() const
{
    Type otRv = Type::Unknown;

    OSVERSIONINFO info {};
    info.dwOSVersionInfoSize = sizeof(info);

    BOOL blRv = ::GetVersionEx(&info);
    xTEST_DIFF(blRv, FALSE);

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        otRv = Type::Windows3;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        xCHECK_DO(info.dwMinorVersion == 0UL,  otRv = Type::Windows95; break);
        xCHECK_DO(info.dwMinorVersion == 10UL, otRv = Type::Windows98; break);
        xCHECK_DO(info.dwMinorVersion == 90UL, otRv = Type::Windows98; break);
        break;
    case VER_PLATFORM_WIN32_NT:
        xCHECK_DO(info.dwMajorVersion <= 4UL,                               otRv = Type::WindowsNT;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 0UL, otRv = Type::Windows2000;            break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 1UL, otRv = Type::WindowsXP;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = Type::WindowsXPProx64Edition; break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = Type::WindowsServer2003;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = Type::WindowsHomeServer;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = Type::WindowsServer2003R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = Type::WindowsVista;           break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = Type::WindowsServer2008;      break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = Type::WindowsServer2008R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = Type::Windows7;               break);

        // for unknown windows/newest windows version
        otRv = Type::Unknown;
        break;
    default:
        otRv = Type::Unknown;
        break;
    }

    return otRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_formatOs_impl() const
{
    std::tstring_t sRv;

    cType type = os();
    switch (type) {
    case Type::Windows3:
        sRv = xT("Windows 3.1");
        break;
    case Type::Windows95:
        sRv = xT("Windows 95");
        break;
    case Type::Windows98:
        sRv = xT("Windows 98");
        break;
    case Type::WindowsNT:
        sRv = xT("Windows NT 4.0");
        break;
    case Type::Windows2000:
        sRv = xT("Windows 2000");
        break;
    case Type::WindowsXP:
        sRv = xT("Windows XP");
        break;
    case Type::WindowsXPProx64Edition:
        sRv = xT("Windows XP Pro x64 Edition");
        break;
    case Type::WindowsServer2003:
        sRv = xT("Windows Server 2003");
        break;
    case Type::WindowsHomeServer:
        sRv = xT("Windows Home Server");
        break;
    case Type::WindowsServer2003R2:
        sRv = xT("Windows Server 2003 R2");
        break;
    case Type::WindowsVista:
        sRv = xT("Windows Vista");
        break;
    case Type::WindowsServer2008:
        sRv = xT("Windows Server 2008");
        break;
    case Type::WindowsServer2008R2:
        sRv = xT("Windows Server 2008 R2");
        break;
    case Type::Windows7:
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
Os::Arch
Os::_arch_impl() const
{
    Arch oaRv = Arch::Unknown;

#if   xARCH_BITS_32
	using func_t = BOOL (WINAPI *)(HANDLE hProcess, PBOOL Wow64Process);

	Dll dll(xT("kernel32.dll"));
	dll.load();

	auto func = dll.symbol<func_t>(xT("IsWow64Process"));
	if (func != nullptr) {
		BOOL is64BitOs = FALSE;
		BOOL blRv = func(::GetCurrentProcess(), &is64BitOs);

		oaRv = (blRv && is64BitOs) ? Arch::Bit64 : Arch::Bit32;
	} else {
		oaRv = Arch::Bit32;
	}
#elif xARCH_BITS_64
    oaRv = Arch::Bit64;
#else
    // 64-bit Windows does not support Win16
    oaRv = Arch::Unknown;
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

    xTEST(!sRv.empty());
#else
    sRv = nativeDesktop;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
