/**
 * \file  PathExe.h
 * \brief file system path
 *
 * http://www.cplusplus.com/forum/general/11104/
 * http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
 * http://libsylph.sourceforge.net/wiki/Full_path_to_binary
 * http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?
 *     ciid=88086d6e1de021106d6e1de02110275d6e10RCRD
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
