/**
 * \file   CxFileTemp.cpp
 * \brief
 */


#include <xLib/Filesystem/CxFileTemp.h>

#include <xLib/Filesystem/CxFile.h>
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
    const bool cbIsAutoDelete
) :
    _m_cbIsAutoDelete(cbIsAutoDelete),
    _m_pfFile        (NULL),
    _m_sFilePath     ()
{

}
//---------------------------------------------------------------------------
/* virtual */
CxFileTemp::~CxFileTemp() {
    (void)(*_m_pfFile).bClose();

    if (false != _m_cbIsAutoDelete) {
        (void)CxFile::bDelete(_m_sFilePath);
    }
}
//---------------------------------------------------------------------------
bool
CxFileTemp::bCreate(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath,
    CxFile               *pfFile
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/xTEST_EQ(false, pfFile->bIsValid());

    const std::tstring_t csFileNameTemplate = xT("XXXXXX");


    FILE *_pfStdFile = NULL;

    bool bRv = CxDir::bCreateForce(csDirPath);
    /*DEBUG*/xTEST_EQ(true, bRv);

    _m_sFilePath = CxPath::sSlashAppend(csDirPath) + CxPath::sGetFileName(csFilePath) + csFileNameTemplate;

#if   xOS_ENV_WIN
    #if xCOMPILER_MINGW32 || xCOMPILER_CODEGEAR
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        tchar_t *pszFile = ::xTMKSTEMP(&_m_sFilePath.at(0));
        /*DEBUG*/xTEST_PTR(pszFile, false);

        _pfStdFile = std::xTFOPEN(pszFile, CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
        /*DEBUG*/xTEST_PTR(_pfStdFile, false);
    #else
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        errno_t iError = ::xTMKSTEMP(&_m_sFilePath.at(0), _m_sFilePath.size() + 1);
        /*DEBUG*/xTEST_EQ(0, iError);

        _pfStdFile = ::xTFOPEN(_m_sFilePath.c_str(), CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
        /*DEBUG*/xTEST_PTR(_pfStdFile);
    #endif
#elif xOS_ENV_UNIX
    int iFile = ::xTMKSTEMP(&_m_sFilePath.at(0));
    /*DEBUG*/xTEST_DIFF(- 1, iFile);

    _pfStdFile = ::xTFDOPEN(iFile, CxFile::_sGetOpenMode(CxFile::omBinCreateReadWrite).c_str());
    /*DEBUG*/xTEST_PTR(_pfStdFile);
#endif

    //out
    bRv = (*pfFile).bAttach(_pfStdFile);
    /*DEBUG*/xTEST_EQ(true, bRv);

    _m_pfFile = pfFile;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
