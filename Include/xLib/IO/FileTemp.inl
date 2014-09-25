/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


#if !xOPTION_HEADER_ONLY
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
#include <xLib/IO/File.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>

#if   xENV_WIN
    #include "Platform/Win/FileTemp_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/FileTemp_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/FileTemp_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/FileTemp_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
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
inline
FileTemp::~FileTemp()
{
    _file->close();

    if (_isAutoDelete) {
        File::remove(_filePath);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
FileTemp::create(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath,
    File          *a_file
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_dirPath.empty(), false);
    xTEST_EQ(a_file->isValid(), false);

    std::ctstring_t fileNameTemplate = xT("XXXXXX");


    FILE *stdFile = xPTR_NULL;

    Dir(a_dirPath).pathCreate();

    _filePath = Path(a_dirPath).slashAppend() + Path(a_filePath).fileName() + fileNameTemplate;

    _create_impl(stdFile);

    // out
    a_file->attach(stdFile);

    _file = a_file;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
