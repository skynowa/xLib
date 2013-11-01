/**
 * \file   CxFileTemp.cpp
 * \brief  temporary file
 */


#include <xLib/Filesystem/CxFileTemp.h>

#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxFileTemp::CxFileTemp(
    cbool_t &a_isAutoDelete
) :
    _isAutoDelete(a_isAutoDelete),
    _file        (NULL),
    _filePath    ()
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxFileTemp::~CxFileTemp()
{
    _file->close();

    if (_isAutoDelete) {
        CxFile::remove(_filePath);
    }
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxFileTemp::create(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_dirPath,
    CxFile          *a_file
)
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_dirPath.empty());
    xTEST_EQ(false, a_file->isValid());

    std::ctstring_t csFileNameTemplate = xT("XXXXXX");


    FILE *stdFile = NULL;

    CxDir(a_dirPath).pathCreate();

    _filePath = CxPath(a_dirPath).slashAppend() + CxPath(a_filePath).fileName() + csFileNameTemplate;

#if xOS_ENV_WIN
    #if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
        _filePath.resize(_filePath.size() + 1);

        tchar_t *pszFile = ::xTMKSTEMP(&_filePath.at(0));
        xTEST_PTR(pszFile);

        stdFile = std::xTFOPEN(pszFile, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(stdFile);
    #else
        _filePath.resize(_filePath.size() + 1);

        errno_t iError = ::xTMKSTEMP(&_filePath.at(0), _filePath.size() + 1);
        xTEST_EQ(0, iError);

        stdFile = ::xTFOPEN(_filePath.c_str(), CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(stdFile);
    #endif
#else
    int_t iFile = ::xTMKSTEMP(&_filePath.at(0));
    xTEST_DIFF(- 1, iFile);

    stdFile = ::xTFDOPEN(iFile, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(stdFile);
#endif

    //out
    a_file->attach(stdFile);

    _file = a_file;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
