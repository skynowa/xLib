/**
 * \file   CxFileTemp.inl
 * \brief  temporary file
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if   xENV_WIN
    #include "Platform/Win/CxFileTemp_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxFileTemp_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxFileTemp_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxFileTemp_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFileTemp::CxFileTemp(
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
CxFileTemp::~CxFileTemp()
{
    _file->close();

    if (_isAutoDelete) {
        CxFile::remove(_filePath);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileTemp::create(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath,
    CxFile          *a_file
)
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_dirPath.empty(), false);
    xTEST_EQ(a_file->isValid(), false);

    std::ctstring_t fileNameTemplate = xT("XXXXXX");


    FILE *stdFile = xPTR_NULL;

    CxDir(a_dirPath).pathCreate();

    _filePath = CxPath(a_dirPath).slashAppend() + CxPath(a_filePath).fileName() + fileNameTemplate;

    _create_impl(stdFile);

    // out
    a_file->attach(stdFile);

    _file = a_file;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
