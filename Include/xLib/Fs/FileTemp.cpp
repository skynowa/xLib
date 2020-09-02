/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


#include "FileTemp.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
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


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileTemp::FileTemp(
    cbool_t a_isAutoDelete
) :
    _isAutoDelete(a_isAutoDelete)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
FileTemp::~FileTemp()
{
    if (_file != nullptr) {
        _file->close();
    }

    if (_isAutoDelete && !_filePath.empty()) {
        File(_filePath).remove();
    }
}
//-------------------------------------------------------------------------------------------------
void_t
FileTemp::create(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath,
    FileIO          *a_file
)
{
    xTEST(!a_filePath.empty());
    xTEST(!a_dirPath.empty());
    xTEST_PTR(a_file);
    xTEST(!a_file->get().isValid());

    std::ctstring_t fileNameTemplate = xT("XXXXXX");

    Dir(a_dirPath).pathCreate();
    _filePath = Path(a_dirPath).slashAppend() + Path(a_filePath).fileName() + fileNameTemplate;

    HandleStdFile stdFile;
    _create_impl(stdFile);
    xTEST_EQ(stdFile.isValid(), true);

    // out
    a_file->attach(stdFile, _filePath);

    _file = a_file;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
