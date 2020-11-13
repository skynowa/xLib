/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


#include "FileTemp.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>

#if   xENV_WIN
    #include "Platform/Win/FileTemp_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/FileTemp_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * The last six characters of template must be XXXXXX and
 * these are replaced with a string that makes the filename unique.
 * Since it will be modified, template must not be a string constant,
 * but should be declared as a character array
 */
FileTemp::FileTemp(
	std::ctstring_t &a_filePathPrefix,
	std::ctstring_t &a_dirPath,
    cbool_t          a_isAutoDelete
) :
    _filePath    (Path(a_dirPath).slashAppend() + Path(a_filePathPrefix).fileName() + xT("XXXXXX")),
    _isAutoDelete(a_isAutoDelete)
{
    xTEST(!a_filePathPrefix.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
FileTemp::~FileTemp()
{
    if (_file != nullptr) {
        _file->close();
    }

    if (_isAutoDelete) {
        File(_filePath).remove();
    }
}
//-------------------------------------------------------------------------------------------------
void_t
FileTemp::create(
    FileIO *a_file
)
{
    xTEST_PTR(a_file);
    xTEST(!a_file->get().isValid());

    Dir( Path(_filePath).dir() ).pathCreate();

    HandleStdFile stdFile;
    _create_impl(stdFile);
    xTEST(stdFile.isValid());

    // out
    a_file->attach(stdFile, _filePath);

    _file = a_file;
}
//-------------------------------------------------------------------------------------------------

} // namespace
