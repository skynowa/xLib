/**
 * \file  CxDir.inl
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


xNAMESPACE2_BEGIN(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxDir::CxDir(
    std::ctstring_t &a_dirPath
) :
    _dirPath(a_dirPath)
{
    xTEST_EQ(a_dirPath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxDir::dirPath() const
{
    xTEST_EQ(_dirPath.empty(), false);

    return _dirPath;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::isExists() const
{
    xCHECK_RET(dirPath().empty(), false);

    CxFileType type(dirPath());

    xCHECK_RET(type.get() == CxFileType::faInvalid, false);

    bool_t bRv = type.isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::isEmpty(
    std::ctstring_t &a_shellFilter /* = CxConst::maskAll() */
) const
{
    xTEST_EQ(a_shellFilter.empty(), false);

    bool_t bRv = true;

    CxFinder finder(dirPath(), a_shellFilter);

    for ( ; ; ) {
        xCHECK_DO(!finder.moveNext(), break);

        xCHECK_DO(finder.entryName() == CxConst::dot(),  continue);
        xCHECK_DO(finder.entryName() == CxConst::dot2(), continue);

        bRv = false;
        break;
    }

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::isRoot() const
{
#if   xENV_WIN
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRv1 = CxChar::isAlpha(dirPath().at(0));
    bool_t bRv2 = (dirPath().at(1) == CxConst::colon().at(0));
    bool_t bRv3 = (dirPath().at(2) == CxConst::winSlash().at(0) ||
                   dirPath().at(2) == CxConst::unixSlash().at(0));

    xCHECK_RET(!bRv1 || !bRv2 || !bRv3, false);
#elif xENV_UNIX
    xCHECK_RET(dirPath() != CxConst::slash(), false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::isDir() const
{
    bool_t bRv = CxFileType( dirPath() ).isExists(CxFileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::create() const
{
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

#if   xENV_WIN
    BOOL blRv = ::CreateDirectory(dirPath().c_str(), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
#elif xENV_UNIX
    int_t iRv = ::mkdir(dirPath().c_str(), S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH);
    xTEST_DIFF(iRv, - 1);
#endif

    xTEST_EQ(isExists(), true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::pathCreate() const
{
    std::vec_tstring_t pathParts;
    std::tstring_t     buildPath;

    // split dirPath into parts
     CxString::split( CxPath(dirPath()).toNative(false), CxConst::slash(), &pathParts );

    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, pathParts) {
        buildPath.append(*it).append(CxConst::slash());

        CxDir(buildPath).create();
    }

    xTEST_EQ(isExists(), true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::copy(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
) const
{
    xTEST_EQ(isExists(), true);
    xTEST_EQ(a_dirPathTo.empty(), false);
    xTEST_NA(a_failIfExists);

    // sets attribute "normal"
    bool_t bRv = CxDir(a_dirPathTo).isExists();
    if (bRv) {
        CxFileType(a_dirPathTo).clear();
    }

    CxFileType(dirPath()).clear();

    // get lists of files
    std::vec_tstring_t filePaths;

    filePaths.clear();
    CxFinder::files(dirPath(), CxConst::maskAll(), true, &filePaths);

    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, filePaths) {
        std::tstring_t filePathTo = *it;

        size_t posBegin = filePathTo.find(dirPath());
        xTEST_DIFF(posBegin, std::tstring_t::npos);

        filePathTo.replace(posBegin, posBegin + dirPath().size(), a_dirPathTo);

        CxDir( CxPath(filePathTo).dir() ).pathCreate();

        CxFile::copy(*it, filePathTo, a_failIfExists);
    }

    // TODO: rollback copy
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::move(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
) const
{
    xTEST_EQ(isExists(), true);
    xTEST_EQ(a_dirPathTo.empty(), false);
    xTEST_NA(a_failIfExists);

    CxDir dir(dirPath());

    dir.copy(a_dirPathTo, a_failIfExists);
    dir.pathDelete();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::remove() const
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    CxFileType(dirPath()).clear();

#if   xENV_WIN
    BOOL blRv = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(blRv, FALSE);
#elif xENV_UNIX
    int_t iRv = ::rmdir(dirPath().c_str());
    xTEST_DIFF(iRv, - 1);
#endif

    xTEST_EQ(isExists(), false);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::tryRemove(
    std::csize_t &a_attempts,
    culong_t     &a_timeoutMsec
) const
{
    xTEST_LESS(size_t(0U), a_attempts);

    std::csize_t maxAttempts  = 100;  // MAGIC_NUMBER: maxAttempts
    std::csize_t realAttempts = (maxAttempts < a_attempts) ? maxAttempts : a_attempts;

    for (size_t i = 0; i < realAttempts; ++ i) {
        bool_t bRv = isExists();
        xCHECK_DO(!bRv, break);

        CxFileType(dirPath()).clear();

    #if   xENV_WIN
        BOOL blRv = ::RemoveDirectory(dirPath().c_str());
        xCHECK_DO(blRv != FALSE, break);
    #elif xENV_UNIX
        int_t iRv = ::rmdir(dirPath().c_str());
        xCHECK_DO(iRv != - 1, break);
    #endif

        CxThread::currentSleep(a_timeoutMsec);
    }

    xTEST_EQ(isExists(), false);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::pathClear() const
{
    xTEST_EQ(isExists(), true);

    // checks
    bool_t bRv = isEmpty(CxConst::maskAll());
    xCHECK_DO(bRv, return);

    // delete files
    {
        std::vec_tstring_t filePaths;

        filePaths.clear();
        CxFinder::files(dirPath(), CxConst::maskAll(), true, &filePaths);

        xFOREACH_R(std::vec_tstring_t, it, filePaths) {
            CxFile::remove(*it);
        }
    }

    // delete subdirs
    {
        std::vec_tstring_t dirPaths;

        dirPaths.clear();
        CxFinder::dirs(dirPath(), CxConst::maskAll(), true, &dirPaths);

        xFOREACH_R(std::vec_tstring_t, it, dirPaths) {
            CxDir(*it).remove();
        }
    }

    xTEST_EQ(isEmpty(), true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::pathDelete() const
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    pathClear();
    remove();

    xTEST_EQ(isExists(), false);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxDir::current()
{
    std::tstring_t sRv;
    std::tstring_t buff(xPATH_MAX + 1, 0);

#if   xENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);
#elif xENV_UNIX
    tchar_t *pszRv = ::getcwd(&buff[0], xPATH_MAX);
    xTEST_PTR(pszRv);
    xTEST_EQ(buff.c_str(), const_cast<ctchar_t *>( pszRv ));

    sRv.assign(pszRv);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = CxPath(a_dirPath).slashAppend();

#if   xENV_WIN
    BOOL blRv = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(blRv, FALSE);
#elif xENV_UNIX
    int_t iRv = ::chdir(a_dirPath.c_str());
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDir::temp()
{
    std::tstring_t sRv;

#if   xENV_WIN
    std::tstring_t buff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);
#elif xENV_UNIX
    std::ctstring_t envDirTemp = xT("TMPDIR");

    bool_t bRv = CxEnvironment::isExists(envDirTemp);
    if (bRv) {
        sRv = CxEnvironment::var(envDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }
#endif

    xTEST_EQ(CxDir(sRv).isExists(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, filesystem)
