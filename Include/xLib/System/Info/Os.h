/**
 * \file  Os.h
 * \brief OS information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Os
    /// OS information
{
public:
///\name ctors, dtor
///\{
			 Os() = default;
	virtual ~Os() = default;

	xNO_COPY_ASSIGN(Os);
///\}

    enum class Type
        /// OS type
    {
        Unknown,
        // windows family
        Windows3,
        Windows95,
        Windows98,
        WindowsNT,
        Windows2000,
        WindowsXP,
        WindowsXPProx64Edition,
        WindowsServer2003,
        WindowsHomeServer,
        WindowsServer2003R2,
        WindowsVista,
        WindowsServer2008,
        WindowsServer2008R2,
        Windows7,
        // Linux  family
        Linux,
        // BSD family
        FreeBSD,
        // Apple family
        Mac
    };
    xUSING_CONST(Type);

    enum class Arch
        /// OS architecture
    {
        Unknown,
        Bit32,
        Bit64
    };
    xUSING_CONST(Arch);

	Type           os() const;
		///< get information about the current OS
	std::tstring_t formatOs() const;
		///< format OS type
	std::tstring_t distro() const;
		///< distributive info

	Arch           arch() const;
		///< get OS architecture
	std::tstring_t formatArch() const;
		///< format get OS architecture

	std::tstring_t desktopName() const;
		///< desktop environments

xPLATFORM_IMPL:
    Type           _os_impl() const;
    std::tstring_t _formatOs_impl() const;
    std::tstring_t _distro_impl() const;
    Arch           _arch_impl() const;
    std::tstring_t _desktopName_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
