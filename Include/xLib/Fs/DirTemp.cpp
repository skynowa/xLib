/**
 * \file  DirTemp.cpp
 * \brief Temporary directory
 */


#include "DirTemp.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Path.h>
#include <xLib/Crypt/OpenSsl/Guid.h>


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DirTemp::DirTemp(
	std::ctstring_t &a_dirPath,
	cbool_t          a_isRandomPostfix,
	cbool_t          a_isAutoDelete
) :
	_dir         (a_dirPath + (a_isRandomPostfix ? (xT("_") + Guid().str()) : xT(""))),
	_isAutoDelete(a_isAutoDelete)
{
	xTEST(!a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
DirTemp::~DirTemp()
{
	if (_isAutoDelete) {
		_dir.pathDelete();
	}
}
//-------------------------------------------------------------------------------------------------
const Dir &
DirTemp::dir() const
{
	return _dir;
}
//-------------------------------------------------------------------------------------------------
void_t
DirTemp::create() const
{
	_dir.pathCreate();
}
//-------------------------------------------------------------------------------------------------

} // namespace
