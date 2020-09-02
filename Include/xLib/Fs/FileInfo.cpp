/**
 * \file  FileInfo.cpp
 * \brief File information
 */


#include "FileInfo.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/FileType.h>
#include <xLib/Fs/Path.h>

#if   xENV_WIN
    #include "Platform/Win/FileInfo_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/FileInfo_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FileInfo::FileInfo(
	std::ctstring_t &a_filePath
) :
	_filePath(a_filePath)
{
    xTEST(!_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
FileInfo::FileInfo(
	const Path &a_path
) :
	FileInfo( a_path.filePath() )
{
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] review / rm
FileInfo::FileInfo(
	const FileIO &a_file
) :
	FileInfo( a_file.path() )
{
}
//-------------------------------------------------------------------------------------------------
FileInfo::~FileInfo()
{
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] FileInfo::size() - maybe rm ?
longlong_t
FileInfo::size() const
{
    FileIO file(_filePath);
    file.create(FileIO::OpenMode::ReadOnly);

    clonglong_t llRv = file.size();
    xTEST_GR_EQ(llRv, 0LL);

    return llRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
FileInfo::isEmpty() const
{
    return (size() == 0LL);
}
//-------------------------------------------------------------------------------------------------
// TODO: [skynowa] FileInfo::lines() - maybe rm ?
ulonglong_t
FileInfo::lines() const
{
    xTEST(isExists());

    std::locale::global( std::locale() );

    ulonglong_t ullRv {};

    std::tifstream_t ifs(xT2A(_filePath), std::ios::in);
    xCHECK_RET(!ifs || ifs.fail() || !ifs.good() || !ifs.is_open() || ifs.eof(), 0LL);

    tchar_t chChar {};
    for (ullRv = 0LL; ifs.get(chChar); ) {
        xCHECK_DO(chChar == xT('\n'), ++ ullRv);
    }

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
void_t
FileInfo::time(
    time_t *a_create,	///< [out]
    time_t *a_access,	///< [out]
    time_t *a_modified	///< [out]
) const
{
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

    _time_impl(a_create, a_access, a_modified);
}
//-------------------------------------------------------------------------------------------------
void_t
FileInfo::setTime(
    const time_t a_create,
    const time_t a_access,
    const time_t a_modified
) const
{
    xTEST_NA(a_create);
    xTEST_NA(a_access);
    xTEST_NA(a_modified);

    _setTime_impl(a_create, a_access, a_modified);
}
//-------------------------------------------------------------------------------------------------
void_t
FileInfo::resetTime() const
{
	setTime({}, {}, {});
}
//-------------------------------------------------------------------------------------------------
bool_t
FileInfo::isExists() const
{
    xCHECK_RET(!FileType(_filePath).isFile(), false);

    int_t iRv = xTACCESS(_filePath.c_str(), static_cast<int_t>(AccessMode::Existence));
    xCHECK_RET(iRv == - 1 && StdError::get() == ENOENT, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
FileInfo::isExistsEx() const
{
    std::tstring_t sRv;

    Path path(_filePath);

    std::ctstring_t &fileDir  = path.dir();
    std::ctstring_t &fileName = path.fileBaseName();
    std::tstring_t   fileExt  = path.ext();

    xCHECK_DO(!fileExt.empty(), fileExt.insert(0, Const::dot()));

    for (ulong_t existsIndex = 1; ; ++ existsIndex) {
        sRv = Format::str(xT("{}{}{} ({}){}"), fileDir, Const::slash(), fileName, existsIndex,
            fileExt);
        xCHECK_DO(!FileInfo(sRv).isExists(), break);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
FileInfo::checkAccess(
    cAccessMode a_mode
) const
{
    xTEST_NA(a_mode);

    int_t iRv = xTACCESS(_filePath.c_str(), static_cast<int_t>(a_mode));
    xCHECK_RET(iRv == - 1, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
FileInfo::chmod(
    cPermissionMode a_mode
) const
{
    xTEST_NA(a_mode);

#if   xENV_WIN
    using _mode_t = cint_t;
#elif xENV_UNIX
    using _mode_t = const mode_t;
#endif

    int_t iRv = xTCHMOD(_filePath.c_str(), static_cast<_mode_t>(a_mode));
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
