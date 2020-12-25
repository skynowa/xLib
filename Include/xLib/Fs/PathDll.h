/**
 * \file  Path.h
 * \brief file system path
 */


#pragma once

#include <xLib/Fs/Path.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class PathDll :
	public Path
    /// file system path
{
public:
///@name ctors, dtor
///@{
	explicit  PathDll();
	virtual  ~PathDll() = default;

	xNO_COPY_ASSIGN(PathDll)
///@}

xPLATFORM_IMPL:
    static
    std::tstring_t _dll_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
