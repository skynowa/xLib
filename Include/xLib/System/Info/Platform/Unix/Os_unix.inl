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
Os::OsType
Os::_os_impl() const
{
    OsType otRv = OsType::Unknown;

    utsname info {};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if      (StringCI::compare(xA2T(info.sysname), xT("Linux"))) {
        otRv = OsType::Linux;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("FreeBSD"))) {
        otRv = OsType::FreeBSD;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("Darwin"))) {
        otRv = OsType::Mac;
    }
    else {
        otRv = OsType::Unknown;
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
Os::OsArch
Os::_osArch_impl() const
{
    OsArch oaRv = OsArch::Unknown;

    std::tstring_t infoMachine;
    {
        utsname info {};

        int_t iRv = ::uname(&info);
        xTEST_DIFF(iRv, - 1);

        infoMachine = xA2T(info.machine);
    }

    // 32-bit checks
    if      (StringCI::compare(infoMachine, xT("i386"))) {
        oaRv = OsArch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i486"))) {
        oaRv = OsArch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i586"))) {
        oaRv = OsArch::Bit32;
    }
    else if (StringCI::compare(infoMachine, xT("i686"))) {
        oaRv = OsArch::Bit32;
    }

    // 64-bit checks
    else if (StringCI::compare(infoMachine, xT("x86_64"))) {
        oaRv = OsArch::Bit64;
    }
    else if (StringCI::compare(infoMachine, xT("ia64"))) {
        oaRv = OsArch::Bit64;
    }
    else if (StringCI::compare(infoMachine, xT("amd64"))) {
        oaRv = OsArch::Bit64;
    }

    // unknown
    else {
        oaRv = OsArch::Unknown;
    }

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Os::_desktopName_impl() const
{
    std::tstring_t sRv;

    sRv = Environment(xT("DESKTOP_SESSION")).var();
    xCHECK_RET(sRv.empty(), Const::strUnknown());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
