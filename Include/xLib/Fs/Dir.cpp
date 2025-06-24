/**
 * \file  Dir.cpp
 * \brief directory
 */


#include "Dir.h"

#include <xLib/Core/String.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/FileType.h>
#include <xLib/System/Env.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/ThreadCurrent.h>

#if   xENV_WIN
    #include "Platform/Win/Dir_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Dir_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*     public ctors, dtor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Dir::Dir(
    std::ctstring_t &a_dirPath
) :
    _dirPath(a_dirPath)
{
    xTEST(!a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
/* static */
Dir
Dir::current()
{
	std::ctstring_t &currentDir = _current_impl();
	xTEST(Dir(currentDir).isExists());

	return Dir(currentDir);
}
//-------------------------------------------------------------------------------------------------
/* static */
Dir
Dir::temp()
{
	std::ctstring_t &tempDir = _temp_impl();
	xTEST(Dir(tempDir).isExists());

	return Dir(tempDir);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*     public interfaces
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Dir::print(
	std::tostream_t &out_stream
) const /* final */
{
	out_stream << str();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Dir::str() const /* final */
{
    return _dirPath;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Dir::isExists() const
{
    xCHECK_RET(_dirPath.empty(), false);

    FileType type(_dirPath);

    xCHECK_RET(type.get() == static_cast<FileType::types_t>(FileType::Type::Unknown), false);

#if xENV_UNIX
	if (type.get() == static_cast<FileType::types_t>(FileType::Type::SymbolicLink)) {
		std::ctstring_t &symLinkPathTo = Path::readSymLink(_dirPath);

		FileType symLinkType(symLinkPathTo);
		bool_t bRv = symLinkType.isExists(FileType::Type::Directory);
		xCHECK_RET(!bRv, false);

		return true;
	}
#endif

    bool_t bRv = type.isExists(FileType::Type::Directory);
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Dir::isEmpty(
    std::ctstring_t &a_shellFilter /* = Const::maskAll() */
) const
{
    xTEST(!a_shellFilter.empty());

    bool_t bRv {true};

    Finder finder(_dirPath, a_shellFilter);

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
bool_t
Dir::isRoot() const
{
    return _isRoot_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::create() const
{
    bool_t bRv = isExists();
    xCHECK_DO(bRv, return);

    _create_impl();
    xTEST(isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::pathCreate() const
{
    // split dirPath into parts
    std::vec_tstring_t pathParts;
    Path(_dirPath).toNative(false).split(&pathParts);

    // create dirs by steps
    std::tstring_t buildPath;

    for (const auto &it : pathParts) {
        buildPath.append(it).append(Const::slash());

        Dir(buildPath).create();
    }

    xTEST(isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::copy(
    std::ctstring_t &a_dirPathTo,
    cbool_t          a_failIfExists
) const
{
    xTEST(isExists());
    xTEST(!a_dirPathTo.empty());
    xTEST_NA(a_failIfExists);

    // sets attribute "normal"
    bool_t bRv = Dir(a_dirPathTo).isExists();
    if (bRv) {
        FileType(a_dirPathTo).clear();
    }

    FileType(_dirPath).clear();

    // get lists of files
    std::vec_tstring_t filePaths;

    filePaths.clear();
    Finder::files(_dirPath, Const::maskAll(), true, &filePaths);

    // copy
    xFOR_EACH_R_CONST(std::vec_tstring_t, it, filePaths) {
        std::tstring_t filePathTo = *it;

        size_t posBegin = filePathTo.find(_dirPath);
        xTEST_DIFF(posBegin, std::tstring_t::npos);

        filePathTo.replace(posBegin, posBegin + _dirPath.size(), a_dirPathTo);

        Dir( Path(filePathTo).dir() ).pathCreate();

        File(*it).copy(filePathTo, a_failIfExists);
    }

    // TODO: [skynowa] rollback copy
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::move(
    std::ctstring_t &a_dirPathTo,
    cbool_t          a_failIfExists
) const
{
    xTEST(isExists());
    xTEST(!a_dirPathTo.empty());
    xTEST_NA(a_failIfExists);

    Dir dir(_dirPath);

    dir.copy(a_dirPathTo, a_failIfExists);
    dir.pathDelete();
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::createSymlink(
	std::ctstring_t &a_dirPathTo
) const
{
	_createSymlink_impl(a_dirPathTo);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::remove() const
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    FileType(_dirPath).clear();

    _remove_impl();
    xTEST(!isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::tryRemove(
    std::csize_t a_attempts,
    culong_t     a_timeoutMsec
) const
{
    xTEST_DIFF(a_attempts, size_t(0U));

    std::csize_t maxAttempts  = 100;  // MAGIC_NUMBER: maxAttempts
    std::csize_t realAttempts = (maxAttempts < a_attempts) ? maxAttempts : a_attempts;

    for (size_t i = 0; i < realAttempts; ++ i) {
        bool_t bRv = isExists();
        xCHECK_DO(!bRv, break);

        FileType(_dirPath).clear();

        bRv = _tryRemove_impl();
        xCHECK_DO(bRv, break);

        ThreadCurrent::sleep(a_timeoutMsec);
    }

    xTEST(!isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::pathClear() const
{
    xTEST(isExists());

    // checks
    bool_t bRv = isEmpty(Const::maskAll());
    xCHECK_DO(bRv, return);

    // delete files
    {
        std::vec_tstring_t filePaths;

        filePaths.clear();
        Finder::files(_dirPath, Const::maskAll(), true, &filePaths);

        xFOR_EACH_R(std::vec_tstring_t, it, filePaths) {
            File(*it).remove();
        }
    }

    // delete subdirs
    {
        std::vec_tstring_t dirPaths;

        dirPaths.clear();
        Finder::dirs(_dirPath, Const::maskAll(), true, &dirPaths);

        xFOR_EACH_R(std::vec_tstring_t, it, dirPaths) {
            Dir(*it).remove();
        }
    }

    xTEST(isEmpty());
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::pathDelete() const
{
    bool_t bRv = isExists();
    xCHECK_DO(!bRv, return);

    pathClear();
    remove();

    xTEST(!isExists());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
Dir::setCurrent(
    std::ctstring_t &a_dirPath
)
{
    _setCurrent_impl(a_dirPath);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t
Dir::_dirTmp()
{
	std::ctstring_t sRv =
	#if   xENV_WIN
		#if defined(P_tmpdir)
			xT(P_tmpdir)
		#else
			xT("C:\\Temp")  // custom define
		#endif
	#elif xENV_UNIX
		#if defined(P_tmpdir)
			xT(P_tmpdir)
		#else
			xT("/tmp")      // custom define
		#endif
	#endif
	;
	xTEST(!sRv.empty());

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
