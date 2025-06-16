/**
 * \file  SocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::net
{

class SocketInit
    /// initiates use of the Winsock DLL by a process
{
public:
///\name ctors, dtor
///\{
			 SocketInit(cushort_t versionMajor, cushort_t versionMinor);
		///< init winsock DLL
	virtual ~SocketInit();
		///< clean winsock DLL

	xNO_DEFAULT_CONSTRUCT(SocketInit);
	xNO_COPY_ASSIGN(SocketInit);
///\}

xPLATFORM_IMPL:
    void_t   _ctor_impl(cushort_t versionMajor, cushort_t versionMinor) const;
    void_t   _dtor_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
