/**
 * \file  Libs.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Libs
    /// system information
{
public:
///\name ctors, dtor
///\{
			 Libs() = default;
	virtual ~Libs() = default;

	xNO_COPY_ASSIGN(Libs)
///\}

#if xENV_UNIX
	std::tstring_t glibcVersion() const;
		///< get glibc version available on the system
	std::tstring_t libPthreadVersion() const;
		///< get POSIX implementation supplied by C library ("NPTL 2.3.4" or "linuxthreads-0.10")
#endif

xPLATFORM_IMPL:

};

} // namespace
//-------------------------------------------------------------------------------------------------
