/**
 * \file  Dir.inl
 * \brief directory
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Dir.h"
#endif

#include <xLib/Core/Char.h>
#include <xLib/Core/String.h>
#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/IO/FileType.h>
#include <xLib/System/Environment.h>
#include <xLib/IO/Finder.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/Dir_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/Dir_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/Dir_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/Dir_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Dir::Dir(
    std::ctstring_t &a_dirPath
) :
    _dirPath(a_dirPath)
{
    xTEST_EQ(a_dirPath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Dir::dirPath() const
{
    xTEST_EQ(_dirPath.empty(), false);

    return _dirPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dir::isExists() const
{
    xCHECK_RET(dirPath().empty(), false);

    FileType type(dirPath());

    xCHECK_RET(type.get() == FileType::faInvalid, false);

    bool_t bRv = type.isExists(FileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dir::isEmpty(
    std::ctstring_t &a_shellFilter /* = Const::maskAll() */
) const
{
    xTEST_EQ(a_shellFilter.empty(), false);

    bool_t bRv = true;

    Finder finder(dirPath(), a_shellFilter);

    for ( ; ; ) {
        xCHECK_DO(!finder.moveNext(), break);

        xCHECK_DO(finder.entryName() == Const::dot(),  continue);
        xCHECK_DO(finder.entryName() == Const::dot2(), continue);

        bRv = false;
        break;
    }

    return bRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dir::isRoot() const
{
    return _isRoot_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dir::isDir() const
{
    bool_t bRv = FileType( dirPath() ).isExists(FileType::faDirectory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::create() const
{
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

    _create_impl();
    xTEST_EQ(isExists(), true);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::pathCreate() const
{
    std::vec_tstring_t pathParts;
    std::tstring_t     buildPath;

    // split dirPath into parts
     String::split( Path(dirPath()).toNative(false), Const::slash(), &pathParts );

    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, pathParts) {
        buildPath.append(*it).append(Const::slash());

        Dir(buildPath).create();
    }

    xTEST_EQ(isExists(), true);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::copy(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
) const
{
    xTEST_EQ(isExists(), true);
    xTEST_EQ(a_dirPathTo.empty(), false);
    xTEST_NA(a_failIfExists);

    // sets attribute "normal"
    bool_t bRv = Dir(a_dirPathTo).isExists();
    if (bRv) {
        FileType(a_dirPathTo).clear();
    }

    FileType(dirPath()).clear();

    // get lists of files
    std::vec_tstring_t filePaths;

    filePaths.clear();
    Finder::files(dirPath(), Const::maskAll(), true, &filePaths);

    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, filePaths) {
        std::tstring_t filePathTo = *it;

        size_t posBegin = filePathTo.find(dirPath());
        xTEST_DIFF(posBegin, std::tstring_t::npos);

        filePathTo.replace(posBegin, posBegin + dirPath().size(), a_dirPathTo);

        Dir( Path(filePathTo).dir() ).pathCreate();

        File::copy(*it, filePathTo, a_failIfExists);
    }

    // TODO: rollback copy
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::move(
    std::ctstring_t &a_dirPathTo,
    cbool_t         &a_failIfExists
) const
{
    xTEST_EQ(isExists(), true);
    xTEST_EQ(a_dirPathTo.empty(), false);
    xTEST_NA(a_failIfExists);

    Dir dir(dirPath());

    dir.copy(a_dirPathTo, a_failIfExists);
    dir.pathDelete();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::remove() const
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    FileType(dirPath()).clear();

    _remove_impl();
    xTEST_EQ(isExists(), false);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::tryRemove(
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

        FileType(dirPath()).clear();

        bRv = _tryRemove_impl();
        xCHECK_DO(bRv, break);

        Thread::currentSleep(a_timeoutMsec);
    }

    xTEST_EQ(isExists(), false);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::pathClear() const
{
    xTEST_EQ(isExists(), true);

    // checks
    bool_t bRv = isEmpty(Const::maskAll());
    xCHECK_DO(bRv, return);

    // delete files
    {
        std::vec_tstring_t filePaths;

        filePaths.clear();
        Finder::files(dirPath(), Const::maskAll(), true, &filePaths);

        xFOREACH_R(std::vec_tstring_t, it, filePaths) {
            File::remove(*it);
        }
    }

    // delete subdirs
    {
        std::vec_tstring_t dirPaths;

        dirPaths.clear();
        Finder::dirs(dirPath(), Const::maskAll(), true, &dirPaths);

        xFOREACH_R(std::vec_tstring_t, it, dirPaths) {
            Dir(*it).remove();
        }
    }

    xTEST_EQ(isEmpty(), true);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::pathDelete() const
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
xINLINE std::tstring_t
Dir::current()
{
    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    _setCurrent_impl(a_dirPath);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Dir::temp()
{
    std::tstring_t sRv;

    sRv = _temp_impl();
    xTEST_EQ(Dir(sRv).isExists(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
