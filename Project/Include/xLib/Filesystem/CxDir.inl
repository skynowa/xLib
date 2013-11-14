/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/System/CxEnvironment.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxDir::CxDir(
    std::ctstring_t &a_dirPath
) :
    _dirPath(a_dirPath)
{
    xTEST_EQ(false, a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxDir::dirPath() const
{
    xTEST_EQ(false, _dirPath.empty());

    return _dirPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isExists()
{
    xCHECK_RET(dirPath().empty(), false);

    CxFileType type(dirPath());

    xCHECK_RET(CxFileType::faInvalid == type.get(), false);

    bool_t bRv = type.isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isEmpty(
    std::ctstring_t &a_shellFilter /* = CxConst::maskAll() */
)
{
    xTEST_EQ(false, a_shellFilter.empty());

    bool_t bRv = true;

    CxFinder finder(dirPath(), a_shellFilter);

    xFOREVER {
        xCHECK_DO(!finder.moveNext(), break);

        xCHECK_DO(CxConst::dot()  == finder.entryName(), continue);
        xCHECK_DO(CxConst::dot2() == finder.entryName(), continue);

        bRv = false;
        break;
    }

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isRoot()
{
#if xOS_ENV_WIN
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRv1 = CxChar::isAlpha(dirPath().at(0));
    bool_t bRv2 = (dirPath().at(1) == CxConst::colon().at(0));
    bool_t bRv3 = (dirPath().at(2) == CxConst::winSlash().at(0) ||
                    dirPath().at(2) == CxConst::unixSlash().at(0));

    xCHECK_RET(!bRv1 || !bRv2 || !bRv3, false);
#else
    xCHECK_RET(CxConst::slash() != dirPath(), false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO bool_t
CxDir::isDir()
{
    bool_t bRv = CxFileType(dirPath()).isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::create()
{
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

#if xOS_ENV_WIN
    BOOL blRv = ::CreateDirectory(dirPath().c_str(), NULL);
    xTEST_DIFF(FALSE, blRv);
#else
    int_t iRv = ::mkdir(dirPath().c_str(), 0755);
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(true, isExists());
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathCreate()
{
    std::vec_tstring_t pathParts;
    std::tstring_t     buildPath;

    //-------------------------------------
    // split dirPath into parts
     CxString::split( CxPath(dirPath()).toNative(false), CxConst::slash(), &pathParts );

    //-------------------------------------
    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, pathParts) {
        buildPath.append(*it).append(CxConst::slash());

        CxDir(buildPath).create();
    }

    xTEST_EQ(true, isExists());
}
//-------------------------------------------------------------------------------------------------
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
    std::vec_tstring_t filePaths;

    filePaths.clear();
    CxFinder::files(dirPath(), CxConst::maskAll(), true, &filePaths);

    //--------------------------------------------------
    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, filePaths) {
        std::tstring_t filePathTo = *it;

        size_t posBegin = filePathTo.find(dirPath());
        xTEST_DIFF(std::tstring_t::npos, posBegin);

        filePathTo.replace(posBegin, posBegin + dirPath().size(), a_dirPathTo);

        CxDir( CxPath(filePathTo).dir() ).pathCreate();

        CxFile::copy(*it, filePathTo, a_failIfExists);
    }

    //--------------------------------------------------
    // TODO: rollback copy
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::move(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
)
{
    xTEST_EQ(true,  isExists());
    xTEST_EQ(false, a_dirPathTo.empty());
    xTEST_NA(a_failIfExists);

    CxDir dir(dirPath());

    dir.copy(a_dirPathTo, a_failIfExists);
    dir.pathDelete();
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::remove()
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    CxFileType(dirPath()).clear();

#if xOS_ENV_WIN
    BOOL blRv = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(FALSE, blRv);
#else
    int_t iRv = ::rmdir(dirPath().c_str());
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(false, isExists());
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::tryRemove(
    std::csize_t &a_attempts,
    culong_t     &a_timeoutMsec
)
{
    xTEST_LESS(size_t(0U), a_attempts);

    std::csize_t maxAttempts  = 100;  // MAGIC_NUMBER: maxAttempts
    std::csize_t realAttempts = (maxAttempts < a_attempts) ? maxAttempts : a_attempts;

    for (size_t i = 0; i < realAttempts; ++ i) {
        bool_t bRv = isExists();
        xCHECK_DO(!bRv, break);

        CxFileType(dirPath()).clear();

    #if xOS_ENV_WIN
        BOOL blRv = ::RemoveDirectory(dirPath().c_str());
        xCHECK_DO(FALSE != blRv, break);
    #else
        int_t iRv = ::rmdir(dirPath().c_str());
        xCHECK_DO(- 1 != iRv, break);
    #endif

        CxThread::currentSleep(a_timeoutMsec);
    }

    xTEST_EQ(false, isExists());
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathClear()
{
    xTEST_EQ(true, isExists());

    //-------------------------------------
    // checks
    bool_t bRv = isEmpty(CxConst::maskAll());
    xCHECK_DO(bRv, return);

    //-------------------------------------
    // delete files
    {
        std::vec_tstring_t filePaths;

        filePaths.clear();
        CxFinder::files(dirPath(), CxConst::maskAll(), true, &filePaths);

        xFOREACH_R(std::vec_tstring_t, it, filePaths) {
            CxFile::remove(*it);
        }
    }

    //-------------------------------------
    // delete subdirs
    {
        std::vec_tstring_t dirPaths;

        dirPaths.clear();
        CxFinder::dirs(dirPath(), CxConst::maskAll(), true, &dirPaths);

        xFOREACH_R(std::vec_tstring_t, it, dirPaths) {
            CxDir(*it).remove();
        }
    }

    xTEST_EQ(true, isEmpty());
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::pathDelete()
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    pathClear();
    remove();

    xTEST_EQ(false, isExists());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxDir::current()
{
    std::tstring_t sRv;
    std::tstring_t buff(xPATH_MAX + 1, 0);

#if xOS_ENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);
#else
    tchar_t *pszRv = ::getcwd(&buff[0], xPATH_MAX);
    xTEST_PTR(pszRv);
    xTEST_EQ(buff.c_str(), const_cast<ctchar_t *>( pszRv ));

    sRv.assign(pszRv);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxDir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = CxPath(a_dirPath).slashAppend();

#if xOS_ENV_WIN
    BOOL blRv = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(FALSE, blRv);
#else
    int_t iRv = ::chdir(a_dirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxDir::temp()
{
    std::tstring_t sRv;

#if xOS_ENV_WIN
    std::tstring_t buff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);
#else
    std::ctstring_t envDirTemp = xT("TMPDIR");

    bool_t bRv = CxEnvironment::isExists(envDirTemp);
    if (bRv) {
        sRv = CxEnvironment::var(envDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }
#endif

    xTEST_EQ(true, CxDir(sRv).isExists());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
