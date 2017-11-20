/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "FileTemp.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
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
xINLINE
FileTemp::FileTemp(
    cbool_t &a_isAutoDelete
) :
    _isAutoDelete(a_isAutoDelete),
    _file        (xPTR_NULL),
    _filePath    ()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
FileTemp::~FileTemp()
{
    if (_file != xPTR_NULL) {
        _file->close();
    }

    if (_isAutoDelete && !_filePath.empty()) {
        File::remove(_filePath);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileTemp::create(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath,
    File            *a_file
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_dirPath.empty(),  false);
    xTEST_PTR(a_file);
    xTEST_EQ(a_file->get().isValid(),  false);

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
