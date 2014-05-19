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

#if   xENV_WIN
    #if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
        _filePath.resize(_filePath.size() + 1);

        tchar_t *file = xTMKSTEMP(&_filePath.at(0));
        xTEST_PTR(file);

        stdFile = std::xTFOPEN(file, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(stdFile);
    #else
        _filePath.resize(_filePath.size() + 1);

        errno_t error = xTMKSTEMP(&_filePath.at(0), _filePath.size() + 1);
        xTEST_EQ(0, error);

        stdFile = std::xTFOPEN(_filePath.c_str(), CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(stdFile);
    #endif
#elif xENV_UNIX
    int_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_DIFF(file, - 1);

    stdFile = ::xTFDOPEN(file, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(stdFile);
#endif

    //out
    a_file->attach(stdFile);

    _file = a_file;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
