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

#if   xENV_WIN
    #include "Platform/Win/CxDir_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxDir_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxDir_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxDir_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

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
    return _isRoot_impl();
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

    _create_impl();
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

    _remove_impl();
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

        bRv = _tryRemove_impl();
        xCHECK_DO(bRv, break);

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
    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    _setCurrent_impl(a_dirPath);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDir::temp()
{
    std::tstring_t sRv;

    sRv = _temp_impl();
    xTEST_EQ(CxDir(sRv).isExists(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
