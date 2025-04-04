/**
 * \file  Os.inl
 * \brief system information
 *
 * \see   https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
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

    utsname info {};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if      (StringCI::compare(xA2T(info.sysname), xT("Linux"))) {
        otRv = Type::Linux;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("FreeBSD"))) {
        otRv = Type::FreeBSD;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("Darwin"))) {
        otRv = Type::Mac;
    }
    else {
        otRv = Type::Unknown;
    }

    return otRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_formatOs_impl() const
{
    std::tstring_t sRv;

    utsname info {};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = Format::str(xT("{} {} ({}) {}"), info.sysname, info.release, info.version,
        info.machine);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
Os::Arch
Os::_arch_impl() const
{
    Arch oaRv = Arch::Unknown;

    std::tstring_t infoMachine;
    {
        utsname info {};

        int_t iRv = ::uname(&info);
        xTEST_DIFF(iRv, - 1);

        infoMachine = xA2T(info.machine);
    }

    // 32-bit checks
    if      (StringCI::compare(infoMachine, xT("i386"))) {
        oaRv = Arch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i486"))) {
        oaRv = Arch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i586"))) {
        oaRv = Arch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i686"))) {
        oaRv = Arch::Bit32;
    }

    // 64-bit checks
    else if (StringCI::compare(infoMachine, xT("x86_64"))) {
        oaRv = Arch::Bit64;
    }
    else if (StringCI::compare(infoMachine, xT("ia64"))) {
        oaRv = Arch::Bit64;
    }
    else if (StringCI::compare(infoMachine, xT("amd64"))) {
        oaRv = Arch::Bit64;
    }

    // unknown
    else {
        oaRv = Arch::Unknown;
    }

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_desktopName_impl() const
{
    std::tstring_t sRv;

    sRv = Env(xT("DESKTOP_SESSION")).value();
    xCHECK_RET(sRv.empty(), Const::strUnknown());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
