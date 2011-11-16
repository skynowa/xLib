/**
 * \file   CxFileTemp.cpp
 * \brief
 */


#include <xLib/Filesystem/CxFileTemp.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*explicit*/
CxFileTemp::CxFileTemp(
    const BOOL cbIsAutoDelete
) :
    _m_cbIsAutoDelete(cbIsAutoDelete),
    _m_sFilePath     ()
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxFileTemp::~CxFileTemp() {
    (void)(*_m_pfFile).bClose();

    if (FALSE != _m_cbIsAutoDelete) {
        (void)CxFile::bDelete(_m_sFilePath);
    }
}
//---------------------------------------------------------------------------
BOOL
CxFileTemp::bCreate(
    const std::string_t  &csFilePath,
    const std::string_t  &csDirPath,
    CxFile              *pfFile
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE == pfFile->bIsValid(), FALSE);

    const std::string_t csFileNameTemplate = xT("XXXXXX");


    FILE *_pfStdFile = NULL;

    BOOL bRes = CxDir::bCreateForce(csDirPath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_sFilePath = CxPath::sSlashAppend(csDirPath) + CxPath::sGetFullName(csFilePath) + csFileNameTemplate;

#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_CODEGEAR)
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        char_t *pszFile = std::xTMKSTEMP(&_m_sFilePath.at(0));
        /*DEBUG*/xASSERT_RET(NULL != pszFile, FALSE);

        _pfStdFile = std::xTFOPEN(pszFile, CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
        /*DEBUG*/xASSERT_RET(NULL != _pfStdFile, FALSE);
    #else
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        errno_t iError = ::xTMKSTEMP(&_m_sFilePath.at(0), _m_sFilePath.size() + 1);
        /*DEBUG*/xASSERT_RET(0 == iError, FALSE);

        _pfStdFile = std::xTFOPEN(_m_sFilePath.c_str(), CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
        /*DEBUG*/xASSERT_RET(NULL != _pfStdFile, FALSE);
    #endif
#elif defined(xOS_ENV_UNIX)
    int iFile = ::xTMKSTEMP(&_m_sFilePath.at(0));
    /*DEBUG*/xASSERT_RET(- 1 != iFile, FALSE);

    _pfStdFile = ::xTFDOPEN(iFile, CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
    /*DEBUG*/xASSERT_RET(NULL != _pfStdFile, FALSE);
#endif

    //out
    bRes = (*pfFile).bAttach(_pfStdFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_pfFile = pfFile;

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
