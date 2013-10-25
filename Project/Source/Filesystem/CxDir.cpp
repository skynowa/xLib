/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/System/CxEnvironment.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxDir::CxDir(
    std::ctstring_t &a_dirPath
) :
    _dirPath(a_dirPath)
{
    xTEST_EQ(false, a_dirPath.empty());
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxDir::dirPath() const
{
    xTEST_EQ(false, _dirPath.empty());

    return _dirPath;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isExists()
{
    xCHECK_RET(dirPath().empty(), false);

    CxFileType ftType(dirPath());

    xCHECK_RET(CxFileType::faInvalid == ftType.get(), false);

    bool_t bRv = ftType.isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isEmpty(
    std::ctstring_t &a_shellFilter /* = CxConst::xMASK_ALL() */
)
{
    xTEST_EQ(false, a_shellFilter.empty());

    bool_t bRv = true;

    CxFinder fnFinder(dirPath(), a_shellFilter);

    xFOREVER {
        xCHECK_DO(!fnFinder.moveNext(), break);

        xCHECK_DO(CxConst::xDOT()  == fnFinder.entryName(), continue);
        xCHECK_DO(CxConst::x2DOT() == fnFinder.entryName(), continue);

        bRv = false;
        break;
    }

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isRoot()
{
#if xOS_ENV_WIN
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRes1 = CxChar::isAlpha(dirPath().at(0));
    bool_t bRes2 = (dirPath().at(1) == CxConst::xCOLON().at(0));
    bool_t bRes3 = (dirPath().at(2) == CxConst::xWIN_SLASH().at(0) ||
                    dirPath().at(2) == CxConst::xUNIX_SLASH().at(0));

    xCHECK_RET(!bRes1 || !bRes2 || !bRes3, false);
#else
    xCHECK_RET(CxConst::xSLASH() != dirPath(), false);
#endif

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isDir()
{
    bool_t bRv = CxFileType(dirPath()).isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//--------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::create()
{
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

#if xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(dirPath().c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::mkdir(dirPath().c_str(), 0755);
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(true, isExists());
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathCreate()
{
    std::vec_tstring_t vsPathParts;
    std::tstring_t     sBuildPath;

    //-------------------------------------
    // split dirPath into parts
     CxString::split( CxPath(dirPath()).toNative(false), CxConst::xSLASH(), &vsPathParts );

    //-------------------------------------
    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH());

        CxDir(sBuildPath).create();
    }

    xTEST_EQ(true, isExists());
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::copy(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
)
{
    xTEST_EQ(true,  isExists());
    xTEST_EQ(false, a_dirPathTo.empty());
    xTEST_NA(a_failIfExists);

    //-------------------------------------
    // sets attribute "normal"
    bool_t bRv = CxDir(a_dirPathTo).isExists();
    if (bRv) {
        CxFileType(a_dirPathTo).clear();
    }

    CxFileType(dirPath()).clear();

    //--------------------------------------------------
    // get lists of files
    std::vec_tstring_t vsFilePaths;

    vsFilePaths.clear();
    CxFinder::files(dirPath(), CxConst::xMASK_ALL(), true, &vsFilePaths);

    //--------------------------------------------------
    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, vsFilePaths) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(dirPath());
        xTEST_DIFF(std::tstring_t::npos, uiPosBegin);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + dirPath().size(), a_dirPathTo);

        CxDir( CxPath(sFilePathTo).dir() ).pathCreate();

        CxFile::copy(*it, sFilePathTo, a_failIfExists);
    }

    //--------------------------------------------------
    // TODO: rollback copy
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::move(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
)
{
    xTEST_EQ(true,  isExists());
    xTEST_EQ(false, a_dirPathTo.empty());
    xTEST_NA(a_failIfExists);

    CxDir drDir(dirPath());

    drDir.copy(a_dirPathTo, a_failIfExists);
    drDir.pathDelete();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::remove()
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    CxFileType(dirPath()).clear();

#if xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::rmdir(dirPath().c_str());
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(false, isExists());
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::tryRemove(
    std::csize_t &a_attempts,
    culong_t     &a_timeoutMsec
)
{
    xTEST_LESS(size_t(0U), a_attempts);

    std::csize_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    std::csize_t cuiRealAttempts = (cuiMaxAttempts < a_attempts) ?
                                    cuiMaxAttempts : a_attempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bool_t bRv = isExists();
        xCHECK_DO(!bRv, break);

        CxFileType(dirPath()).clear();

    #if xOS_ENV_WIN
        BOOL blRes = ::RemoveDirectory(dirPath().c_str());
        xCHECK_DO(FALSE != blRes, break);
    #else
        int_t iRv = ::rmdir(dirPath().c_str());
        xCHECK_DO(- 1 != iRv, break);
    #endif

        CxCurrentThread::sleep(a_timeoutMsec);
    }

    xTEST_EQ(false, isExists());
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathClear()
{
    xTEST_EQ(true, isExists());

    //-------------------------------------
    // checks
    bool_t bRv = isEmpty(CxConst::xMASK_ALL());
    xCHECK_DO(bRv, return);

    //-------------------------------------
    // delete files
    {
        std::vec_tstring_t vsFilePaths;

        vsFilePaths.clear();
        CxFinder::files(dirPath(), CxConst::xMASK_ALL(), true, &vsFilePaths);

        xFOREACH_R(std::vec_tstring_t, it, vsFilePaths) {
            CxFile::remove(*it);
        }
    }

    //-------------------------------------
    // delete subdirs
    {
        std::vec_tstring_t vsDirPaths;

        vsDirPaths.clear();
        CxFinder::dirs(dirPath(), CxConst::xMASK_ALL(), true, &vsDirPaths);

        xFOREACH_R(std::vec_tstring_t, it, vsDirPaths) {
            CxDir(*it).remove();
        }
    }

    xTEST_EQ(true, isEmpty());
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathDelete()
{
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
xINLINE_HO std::tstring_t
CxDir::current()
{
    std::tstring_t sRv;
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

#if xOS_ENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#else
    tchar_t *pszRes = ::getcwd(&sBuff[0], xPATH_MAX);
    xTEST_PTR(pszRes);
    xTEST_EQ(sBuff.c_str(), const_cast<ctchar_t *>( pszRes ));

    sRv.assign(pszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = CxPath(a_dirPath).slashAppend();

#if xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::chdir(a_dirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxDir::temp()
{
    std::tstring_t sRv;

#if xOS_ENV_WIN
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#else
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
