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
std::tstring_t
Os::_distro_impl() const
{
    std::tstring_t sRv;

    enum class _Type
    {
        Unknown = 0,
        Os,
        Arch,
        Fedora,
        Redhat,
        SuSE,
        Gentoo,
        Slackware,
        Frugalware,
        Altlinux,
        Mandriva,
        Meego,
        Angstrom,
        Mageia,
        Debian
    };

    struct _OsRelease
    {
        _Type          type;
        std::tstring_t filePath;
        std::tstring_t name;
    };

    using cos_release_t = const std::vector<_OsRelease>;

    cos_release_t osReleases
    {
        {_Type::Os,         xT("/etc/os-release"),         xT("")},
        {_Type::Arch,       xT("/etc/arch-release"),       xT("Arch Linux")},
        {_Type::Fedora,     xT("/etc/fedora-release"),     xT("")},
        {_Type::Redhat,     xT("/etc/redhat-release"),     xT("")},
        {_Type::SuSE,       xT("/etc/SuSE-release"),       xT("")},
        {_Type::Gentoo,     xT("/etc/gentoo-release"),     xT("")},
        {_Type::Slackware,  xT("/etc/slackware-version"),  xT("")},
        {_Type::Frugalware, xT("/etc/frugalware-release"), xT("")},
        {_Type::Altlinux,   xT("/etc/altlinux-release"),   xT("")},
        {_Type::Mandriva,   xT("/etc/mandriva-release"),   xT("")},
        {_Type::Meego,      xT("/etc/meego-release"),      xT("")},
        {_Type::Angstrom,   xT("/etc/angstrom-version"),   xT("")},
        {_Type::Mageia,     xT("/etc/mageia-release"),     xT("")},
        {_Type::Debian,     xT("/etc/debian_version"),     xT("Debian GNU/Linux")}
    };

    for (const auto &it : osReleases) {
        switch (it.type) {
        case _Type::Os:
            {
                std::unmap_tstring_t values;
                File(it.filePath).textRead(xT("="), &values);

                if ( !values.empty() ) {
                    sRv = values["NAME"];

                    if ( !values["VERSION_ID"].empty() ) {
                        sRv += xT(" ") + values["VERSION_ID"];
                    }

                    sRv += xT(" (") + values["ID_LIKE"];

                    if ( !values["VERSION_CODENAME"].empty() ) {
                        sRv += xT(", ") + values["VERSION_CODENAME"];
                    }

                    sRv += xT(")");

                    sRv = String::removeAll(sRv, Const::dqm());
                }
            }
            break;
        case _Type::Arch:
            sRv = it.name;
            break;
        case _Type::Debian:
            {
                sRv = it.name;

                std::vec_tstring_t values;
                File(it.filePath).textRead(&values);

                if ( !values.empty() ) {
                    sRv += xT(" ") + values[0];
                }
            }
            break;
        default:
            {
                std::vec_tstring_t values;
                File(it.filePath).textRead(&values);

                if ( !values.empty() ) {
                    sRv = values[0];
                }
            }
            break;
        }

        xCHECK_DO(!sRv.empty(), break);
    } // for (osReleases)

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
