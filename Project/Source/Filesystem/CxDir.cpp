/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxString.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxDir::CxDir(
    std::ctstring_t &a_csDirPath
) :
    _m_csDirPath(a_csDirPath)
{
    xTEST_EQ(false, a_csDirPath.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxDir::~CxDir() {

}
//------------------------------------------------------------------------------
std::ctstring_t &
CxDir::dirPath() const {
    xTEST_EQ(false, _m_csDirPath.empty());

    return _m_csDirPath;
}
//------------------------------------------------------------------------------
bool_t
CxDir::isExists() {
    xCHECK_RET(dirPath().empty(), false);

    CxFileAttribute faAttr(dirPath());

    xCHECK_RET(CxFileAttribute::faInvalid == faAttr.get(), false);

    bool_t bRv = faAttr.isExists(CxFileAttribute::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//------------------------------------------------------------------------------
bool_t
CxDir::isEmpty(
    std::ctstring_t &a_csShellFilter /* = CxConst::xMASK_ALL */
)
{
    xTEST_EQ(false, a_csShellFilter.empty());

    bool_t bRv = true;

    CxFinder fnFinder(dirPath(), a_csShellFilter);

    xFOREVER {
        xCHECK_DO(!fnFinder.moveNext(), break);

        xCHECK_DO(CxConst::xDOT  == fnFinder.entryName(), continue);
        xCHECK_DO(CxConst::x2DOT == fnFinder.entryName(), continue);

        bRv = false;
        break;
    }

    return bRv;
}
//------------------------------------------------------------------------------
bool_t
CxDir::isRoot() {
#if   xOS_ENV_WIN
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRes1 = CxChar::isAlpha(dirPath().at(0));
    bool_t bRes2 = (dirPath().at(1) == CxConst::xCOLON.at(0));
    bool_t bRes3 = (dirPath().at(2) == CxConst::xWIN_SLASH.at(0) ||
                    dirPath().at(2) == CxConst::xUNIX_SLASH.at(0));

    xCHECK_RET(!bRes1 || !bRes2 || !bRes3, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(CxConst::xSLASH != dirPath(), false);
#endif

    return true;
}
//------------------------------------------------------------------------------
bool_t
CxDir::isDir() {
    bool_t bRv = CxFileAttribute(dirPath()).isExists(CxFileAttribute::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//--------------------------------------------------------------------------
void_t
CxDir::create() {
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(dirPath().c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::mkdir(dirPath().c_str(), 0755);
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(true, isExists());
}
//------------------------------------------------------------------------------
void_t
CxDir::pathCreate() {
    std::vec_tstring_t vsPathParts;
    std::tstring_t     sBuildPath;

    //-------------------------------------
    // split csDirPath into parts
     CxString::split( CxPath(dirPath()).toNative(false), CxConst::xSLASH, &vsPathParts );

    //-------------------------------------
    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH);

        CxDir(sBuildPath).create();
    }

    xTEST_EQ(true, isExists());
}
//------------------------------------------------------------------------------
void_t
CxDir::copy(
    std::ctstring_t &a_csDirPathTo,
    cbool_t         &a_cbFailIfExists
)
{
    xTEST_EQ(true,  isExists());
    xTEST_EQ(false, a_csDirPathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    //-------------------------------------
    // sets attribute "normal"
    bool_t bRv = CxDir(a_csDirPathTo).isExists();
    if (bRv) {
        CxFileAttribute(a_csDirPathTo).set(CxFileAttribute::faNormal);
    }

    CxFileAttribute(dirPath()).set(CxFileAttribute::faNormal);

    //--------------------------------------------------
    // get lists of files
    std::vec_tstring_t vsFilePaths;

    vsFilePaths.clear();
    CxFinder::files(dirPath(), CxConst::xMASK_ALL, true, &vsFilePaths);

    //--------------------------------------------------
    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, vsFilePaths) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(dirPath());
        xTEST_DIFF(std::tstring_t::npos, uiPosBegin);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + dirPath().size(), a_csDirPathTo);

        CxDir( CxPath(sFilePathTo).dir() ).pathCreate();

        CxFile::copy(*it, sFilePathTo, a_cbFailIfExists);
    }

    //--------------------------------------------------
    // TODO: rollback copy
}
//------------------------------------------------------------------------------
void_t
CxDir::move(
    std::ctstring_t &a_csDirPathTo,
    cbool_t         &a_cbFailIfExists
)
{
    xTEST_EQ(true,  isExists());
    xTEST_EQ(false, a_csDirPathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    CxDir drDir(dirPath());

    drDir.copy(a_csDirPathTo, a_cbFailIfExists);
    drDir.pathDelete();
}
//------------------------------------------------------------------------------
void_t
CxDir::remove() {
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    CxFileAttribute(dirPath()).set(CxFileAttribute::faNormal);

#if   xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::rmdir(dirPath().c_str());
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(false, isExists());
}
//------------------------------------------------------------------------------
void_t
CxDir::tryRemove(
    std::csize_t &a_cuiAttempts,
    culong_t     &a_culTimeoutMsec
)
{
    xTEST_LESS(size_t(0U), a_cuiAttempts);

    std::csize_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    std::csize_t cuiRealAttempts = (cuiMaxAttempts < a_cuiAttempts) ?
                                    cuiMaxAttempts : a_cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bool_t bRv = isExists();
        xCHECK_DO(!bRv, break);

        CxFileAttribute(dirPath()).set(CxFileAttribute::faNormal);

    #if   xOS_ENV_WIN
        BOOL blRes = ::RemoveDirectory(dirPath().c_str());
        xCHECK_DO(FALSE != blRes, break);
    #elif xOS_ENV_UNIX
        int_t iRv = ::rmdir(dirPath().c_str());
        xCHECK_DO(- 1 != iRv, break);
    #endif

        CxCurrentThread::sleep(a_culTimeoutMsec);
    }

    xTEST_EQ(false, isExists());
}
//------------------------------------------------------------------------------
void_t
CxDir::pathClear() {
    xTEST_EQ(true, isExists());

    //-------------------------------------
    // checks
    bool_t bRv = isEmpty(CxConst::xMASK_ALL);
    xCHECK_DO(bRv, return);

    //-------------------------------------
    // delete files
    {
        std::vec_tstring_t vsFilePaths;

        vsFilePaths.clear();
        CxFinder::files(dirPath(), CxConst::xMASK_ALL, true, &vsFilePaths);

        xFOREACH_R(std::vec_tstring_t, it, vsFilePaths) {
            CxFile::remove(*it);
        }
    }

    //-------------------------------------
    // delete subdirs
    {
        std::vec_tstring_t vsDirPaths;

        vsDirPaths.clear();
        CxFinder::dirs(dirPath(), CxConst::xMASK_ALL, true, &vsDirPaths);

        xFOREACH_R(std::vec_tstring_t, it, vsDirPaths) {
            CxDir(*it).remove();
        }
    }

    xTEST_EQ(true, isEmpty());
}
//------------------------------------------------------------------------------
void_t
CxDir::pathDelete() {
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    pathClear();
    remove();

    xTEST_EQ(false, isExists());
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
std::tstring_t
CxDir::current() {
    std::tstring_t sRv;
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

#if   xOS_ENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    tchar_t *pszRes = ::getcwd(&sBuff[0], xPATH_MAX);
    xTEST_PTR(pszRes);
    xTEST_EQ(sBuff.c_str(), const_cast<ctchar_t *>( pszRes ));

    sRv.assign(pszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
void_t
CxDir::setCurrent(
    std::ctstring_t &a_csDirPath
)
{
    std::tstring_t dirPath = CxPath(a_csDirPath).slashAppend();

#if   xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::chdir(a_csDirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::temp() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    std::ctstring_t csEnvDirTemp = xT("TMPDIR");

    bool_t bRv = CxEnvironment::isExists(csEnvDirTemp);
    if (bRv) {
        sRv = CxEnvironment::var(csEnvDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }
#endif

    xTEST_EQ(true, CxDir(sRv).isExists());

    return sRv;
}
//--------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
