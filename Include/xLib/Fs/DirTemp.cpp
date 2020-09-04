/**
 * \file  DirTemp.cpp
 * \brief DirTemp
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
    _dirPath     (a_dirPath),
    _isAutoDelete(a_isAutoDelete)
{
    xTEST(!a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
DirTemp::~DirTemp()
{
    if (_isAutoDelete && !_dirPath.empty()) {
        Dir(_dirPath).remove();
    }
}
//-------------------------------------------------------------------------------------------------
void_t
DirTemp::create()
{
   /**
    * The last six characters of template must be XXXXXX and
    * these are replaced with a string that makes the filename unique.
    * Since it will be modified, template must not be a string constant,
    * but should be declared as a character array
    */
    std::ctstring_t dirNameTemplate = Guid(Guid::Type::RandomBased).get();

    _dirPath = Path(_dirPath).slashAppend() + dirNameTemplate;

    Dir(_dirPath).pathCreate();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
