/**
 * \file  DirTemp.cpp
 * \brief Temporary directory
 */


#include "DirTemp.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Crypt/Guid.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DirTemp::DirTemp(
	std::ctstring_t &a_dirPath,
    cbool_t          a_isAutoDelete
) :
    _dirPath     (a_dirPath + xT("_") + Guid(Guid::Type::RandomBased).get()),
    _isAutoDelete(a_isAutoDelete)
{
    xTEST(!a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
DirTemp::~DirTemp()
{
    if (_isAutoDelete) {
        Dir(_dirPath).pathDelete();
    }
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
DirTemp::path() const
{
    return _dirPath;
}
//-------------------------------------------------------------------------------------------------
void_t
DirTemp::create() const
{
    Dir(_dirPath).pathCreate();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
