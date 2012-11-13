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
    const bool &cbIsAutoDelete
) :
    _m_cbIsAutoDelete(cbIsAutoDelete),
    _m_pfFile        (NULL),
    _m_sFilePath     ()
{

}
//---------------------------------------------------------------------------
/* virtual */
CxFileTemp::~CxFileTemp() {
    (*_m_pfFile).vClose();

    if (false != _m_cbIsAutoDelete) {
        CxFile::vDelete(_m_sFilePath);
    }
}
//---------------------------------------------------------------------------
void
CxFileTemp::vCreate(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDirPath,
    CxFile               *pfFile
)
{
    xTEST_EQ(false, csFilePath.empty());
    xTEST_EQ(false, csDirPath.empty());
    xTEST_EQ(false, pfFile->bIsValid());

    const std::tstring_t csFileNameTemplate = xT("XXXXXX");


    FILE *_pfStdFile = NULL;

    CxDir::vCreateForce(csDirPath);

    _m_sFilePath = CxPath::sSlashAppend(csDirPath) + CxPath::sFileName(csFilePath) + csFileNameTemplate;

#if   xOS_ENV_WIN
    #if xCOMPILER_MINGW32 || xCOMPILER_CODEGEAR
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        tchar_t *pszFile = ::xTMKSTEMP(&_m_sFilePath.at(0));
        xTEST_PTR(pszFile);

        _pfStdFile = std::xTFOPEN(pszFile, CxFile::_sOpenMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(_pfStdFile);
    #else
        _m_sFilePath.resize(_m_sFilePath.size() + 1);

        errno_t iError = ::xTMKSTEMP(&_m_sFilePath.at(0), _m_sFilePath.size() + 1);
        xTEST_EQ(0, iError);

        _pfStdFile = ::xTFOPEN(_m_sFilePath.c_str(), CxFile::_sOpenMode(CxFile::omBinCreateReadWrite).c_str());
        xTEST_PTR(_pfStdFile);
    #endif
#elif xOS_ENV_UNIX
    int iFile = ::xTMKSTEMP(&_m_sFilePath.at(0));
    xTEST_DIFF(- 1, iFile);

    _pfStdFile = ::xTFDOPEN(iFile, CxFile::_sOpenMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(_pfStdFile);
#endif

    //out
    (*pfFile).vAttach(_pfStdFile);

    _m_pfFile = pfFile;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
