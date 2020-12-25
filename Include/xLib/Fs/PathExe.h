/**
 * \file  PathExe.h
 * \brief file system path
 */


#pragma once

#include <xLib/Fs/Path.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class PathExe :
	public Path
    /// file system path
{
public:
///@name ctors, dtor
///@{
	explicit  PathExe();
	virtual  ~PathExe() = default;

	xNO_COPY_ASSIGN(PathExe)
///@}

xPLATFORM_IMPL:
	static
	std::tstring_t _exe_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
