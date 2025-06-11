/**
 * \file  Path.cpp
 * \brief file system path
 */


#include "Path.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Log/LogStream.h>
#include <xLib/Sync/Process.h>
#include <xLib/System/User.h>

#if   xENV_WIN
    #include "Platform/Win/Path_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Path_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/Path_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/Path_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/Path_apple.inl"
    #endif
#endif


namespace xl::fs
{

/**************************************************************************************************
*    public ctors, dtor
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Path::Path(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
	// TODO: PathDll - test
    /// xTEST(!_filePath.empty());
    xSTD_VERIFY(!a_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
Path::~Path()
{
	/// std::cout << "Path: dtor" << std::endl;
}
//-------------------------------------------------------------------------------------------------
/* static */
Path
Path::exe()
{
	std::ctstring_t &exePath = _exe_impl();
	xTEST(FileInfo(exePath).isExists());

	return Path(exePath);
}
//-------------------------------------------------------------------------------------------------
/* static */
Path
Path::dll()
{
	std::ctstring_t &dllPath = _dll_impl();
#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
	xTEST(FileInfo(dllPath).isExists());
#endif

	return Path(dllPath);
}
//-------------------------------------------------------------------------------------------------
/* static */
Path
Path::shell()
{
    std::ctstring_t &path = _shell_impl();

    return Path(path);
}
//-------------------------------------------------------------------------------------------------
/* static */
Path
Path::homeDir()
{
    std::ctstring_t &path = _homeDir_impl();

    return Path(path);
}
//-------------------------------------------------------------------------------------------------
/**
 * \libs
 *
 * - https://github.com/KDE/kio/blob/master/src/ioslaves/trash/trashimpl.h
 * - https://bugreports.qt.io/browse/QTBUG-47703?page=com.atlassian.jira.plugin.system.issuetabpanels%3Acomment-tabpanel&showAll=true
 * - https://specifications.freedesktop.org/trash-spec/trashspec-1.0.html
 */
/* static */
Path
Path::trashDir()
{
    std::ctstring_t &path = _trashDir_impl();

    return Path(path);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*     public interfaces
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Path::print(
	std::tostream_t &out_stream
) const /* final */
{
	out_stream << str();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Path::str() const /* final */
{
    return _filePath;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Path::isAbsolute() const
{
    xCHECK_RET(_filePath.empty(),                       false);
    xCHECK_RET(_filePath.at(0) == Const::slash().at(0), true);

    return _isAbsolute_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::isRelative() const
{
    return !isAbsolute();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::volume() const
{
    return _volume_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::dir() const
{
    std::csize_t slashPos = _filePath.rfind(Const::slash(), _filePath.size());
    xCHECK_RET(slashPos == std::tstring_t::npos, std::tstring_t());

    return _filePath.substr(0, slashPos);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::dirName() const
{
    std::csize_t slashPos2 = _filePath.rfind(Const::slash());
    xCHECK_RET(slashPos2 == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos1 = _filePath.rfind(Const::slash(), slashPos2 - 1);
    if (slashPos1 == std::tstring_t::npos) {
        return _filePath.substr(0, slashPos2);
    }

    return _filePath.substr(slashPos1 + 1, slashPos2 - slashPos1 - 1);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::fileName() const
{
    std::csize_t slashPos = _filePath.rfind(Const::slash(), _filePath.size());
    xCHECK_RET(slashPos == std::tstring_t::npos, _filePath);

    return _filePath.substr(slashPos + Const::slash().size());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::fileBaseName() const
{
    std::csize_t slashPos = _filePath.rfind(Const::slash(), _filePath.size());
    std::csize_t dotPos   = _filePath.rfind(Const::dot(),   _filePath.size());

    return String::cut(_filePath, slashPos + Const::slash().size(), dotPos);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::ext() const
{
    std::csize_t dotPos = _filePath.rfind(Const::dot(), _filePath.size());
    xCHECK_RET(dotPos == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos = _filePath.rfind(Const::slash(), _filePath.size());
    // if dot after slash - extension not exists
    xCHECK_RET(dotPos < slashPos && slashPos != std::tstring_t::npos, std::tstring_t());

    return _filePath.substr(dotPos + Const::dot().size());
}
//-------------------------------------------------------------------------------------------------
void_t
Path::split(
	std::vec_tstring_t *out_values
) const
{
	xTEST_PTR(out_values);

	String::split(_filePath, Const::slash(), out_values);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::fileExt(
    cFileExt a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
    case FileExt::Config:
        sRv = xT("cfg");
        break;
    case FileExt::Log:
        sRv = xT("log");
        break;
    case FileExt::Db:
        sRv = xT("db");
        break;
    case FileExt::Dat:
        sRv = xT("dat");
        break;
    case FileExt::Backup:
        sRv = xT("bak");
        break;
    case FileExt::Temp:
        sRv = xT("tmp");
        break;
    case FileExt::Text:
        sRv = xT("txt");
        break;
    default:
        sRv = _fileExt_impl(a_fileExt);
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::fileDotExt(
    cFileExt a_fileExt
)
{
	std::ctstring_t &exeExt = fileExt(a_fileExt);
	xCHECK_RET(exeExt.empty(), std::tstring_t());

	return Const::dot() + exeExt;
}
//-------------------------------------------------------------------------------------------------
Path
Path::setVolume(
    std::ctstring_t &a_volumePath
) const
{
    std::tstring_t sRv(_filePath);

    std::tstring_t driveStr = Path(sRv).volume();
    xTEST(!driveStr.empty());

    std::csize_t pos = sRv.find(driveStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return Path( sRv.replace(pos, driveStr.size(), a_volumePath) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::setDir(
    std::ctstring_t &a_dirPath
) const
{
    std::tstring_t sRv(_filePath);

    std::tstring_t dirStr = Path(sRv).dir();
    xTEST(!dirStr.empty());

    std::csize_t pos = sRv.find(dirStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return Path( sRv.replace(pos, dirStr.size(), Path(a_dirPath).slashRemove().str()) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::setFileName(
    std::ctstring_t &a_fullName
) const
{
    std::tstring_t sRv(_filePath);

    std::tstring_t fullName = Path(sRv).fileName();
    xTEST(!fullName.empty());

    std::csize_t pos = sRv.rfind(fullName);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return Path( sRv.replace(pos, fullName.size(), a_fullName) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::setFileBaseName(
    std::ctstring_t &a_name
) const
{
    std::tstring_t sRv(_filePath);

    std::tstring_t name = Path(sRv).fileBaseName();
    xTEST(!name.empty());

    std::csize_t pos = sRv.rfind(name);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return Path( sRv.replace(pos, name.size(), a_name) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::setExt(
    std::ctstring_t &a_ext
) const
{
    xTEST_NA(a_ext);

    return Path(removeExt().str() + Const::dot() + a_ext);
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
Path
Path::removeExt() const
{
    std::csize_t dotPos = _filePath.rfind( Const::dot() );

    return Path( _filePath.substr(0, dotPos) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::removeExtIf(
    std::ctstring_t &a_ext
) const
{
    std::csize_t extPos = _filePath.rfind(Const::dot() + a_ext);
    xCHECK_RET(extPos == std::tstring_t::npos, Path(_filePath));

    std::csize_t dotPos = _filePath.rfind(Const::dot());
    xTEST_DIFF(dotPos, std::tstring_t::npos);

    return Path( _filePath.substr(0, dotPos) );
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::isValid(
    std::ctstring_t &a_filePath,        ///< file, directory path
    std::tstring_t  *a_filePathValid    ///< [out] normalized path
)
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_filePathValid);

    // is empty
    xCHECK_RET(a_filePath.empty(), false);

    // check for size
    xCHECK_RET(a_filePath.size() > maxSize(), false);

    // TODO: [skynowa] Path::isValid() - more checks

    // name
    {
        std::ctstring_t &fileName = Path(a_filePath).fileName();

        xCHECK_RET(!isNameValid(fileName, a_filePathValid), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::isNameValid(
    std::ctstring_t &a_fileName,        ///< file, directory name
    std::tstring_t  *a_fileNameValid    ///< [out] normalized name
)
{
    xTEST_NA(a_fileName);
    xTEST_NA(a_fileNameValid);

    std::tstring_t sRv(a_fileName);

    // check: empty name
    if ( sRv.empty() ) {
        xCHECK_RET(a_fileNameValid == nullptr, false);
        a_fileNameValid->clear();

        return true;
    }

    // check: name size
    std::csize_t _nameMaxSize = nameMaxSize();
    if (sRv.size() > _nameMaxSize) {
        xCHECK_RET(a_fileNameValid == nullptr, false);

        sRv.resize(_nameMaxSize);
    }

    return _isNameValid_impl(sRv, a_fileNameValid);
}
//-------------------------------------------------------------------------------------------------
Path
Path::toWin(
    cbool_t a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

	sRv = a_isSlashAtEnd ? slashAppend().str() : slashRemove().str();
    sRv = String::replaceAll(sRv, Const::unixSlash(), Const::winSlash());

    return Path(sRv);
}
//-------------------------------------------------------------------------------------------------
Path
Path::toUnix(
    cbool_t a_isSlashAtEnd
)  const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    sRv = a_isSlashAtEnd ? slashAppend().str() : slashRemove().str();
    sRv = String::replaceAll(sRv, Const::winSlash(), Const::unixSlash());

    return Path(sRv);
}
//-------------------------------------------------------------------------------------------------
Path
Path::toNative(
    cbool_t a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    sRv = a_isSlashAtEnd ? slashAppend().str() : slashRemove().str();
    _toNative_impl(&sRv);

    return Path(sRv);
}
//-------------------------------------------------------------------------------------------------
Path
Path::absolute() const
{
    std::ctstring_t sRv( _absolute_impl() );
    xTEST(Path(sRv).isAbsolute());

    return Path(sRv);
}
//-------------------------------------------------------------------------------------------------
Path
Path::brief(
    std::csize_t a_maxSize
) const
{
    xTEST_DIFF(a_maxSize, std::size_t(0));

    // util function
    struct _Functor
    {
        static void_t
        slashesMake(
            std::tstring_t *a_str,
            size_t         *a_num
        )
        {
            size_t index {};

            for ( ; ; ) {
                std::csize_t pos = a_str->find_first_of(Const::winSlash() + Const::unixSlash());
                xCHECK_DO(pos == std::tstring_t::npos, break);

                a_str->erase(0, pos + Const::slash().size());

                ++ index;

                xCHECK_DO(*a_num == index && *a_num != 0, break);
            }

            *a_num = index;
        }
    };

    std::tstring_t sRv  = _filePath;
    std::tstring_t path = _filePath;
    size_t         num  {};

    _Functor::slashesMake(&path, &num);

    while (sRv.size() > a_maxSize && num > 2) {
        path = sRv;

        std::size_t numNew = num / 2;

        _Functor::slashesMake(&path, &numNew);

        sRv.erase(sRv.find(path), path.size());

        numNew = 2;
        _Functor::slashesMake(&path, &numNew);

        sRv.append(Const::dot3() + Const::slash() + path);

        -- num;
    }

    return Path(sRv).toNative(false);
}
//-------------------------------------------------------------------------------------------------
Path
Path::brief(
	std::csize_t a_leftDirsNum,	///<
	std::csize_t a_rightDirsNum	///<
) const
{
	std::vec_tstring_t values;
	split(&values);

	std::csize_t showDirsNum  = a_leftDirsNum + a_rightDirsNum;
	if (showDirsNum >= values.size()) {
		// n/a dots - return full path
		return Path(_filePath);
	}

	std::csize_t hideDirsNum = values.size() - showDirsNum;

	// rm hide dirs
	{
		const auto it_cbegin = values.cbegin() + static_cast<ptrdiff_t>(a_leftDirsNum);
		values.erase(it_cbegin, it_cbegin + static_cast<ptrdiff_t>(hideDirsNum - 1 /* dots */));
	}

	// set dot(s) == hide dirs number
	{
		std::ctstring_t dots(hideDirsNum, Const::dot()[0]);
		values.at(a_leftDirsNum) = dots;
	}

	return Path( String::join(values, Const::slash()) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::briefName(
    std::csize_t a_maxSize
) const
{
	xTEST_DIFF(a_maxSize, size_t(0));

	std::tstring_t tildaDotExt;
	{
		std::ctstring_t &_ext = ext();

		if ( _ext.empty() ) {
			tildaDotExt = xT("~");
		} else {
			tildaDotExt = xT("~") + Const::dot() + _ext;
		}
	}

	std::tstring_t sRv;
	{
		std::ctstring_t &_fileName = fileName();

		if (_fileName.size() > a_maxSize) {
			if (a_maxSize < tildaDotExt.size()) {
				sRv = _fileName.substr(0, a_maxSize);
			} else {
				sRv = _fileName.substr(0, a_maxSize - tildaDotExt.size()) + tildaDotExt;
			}
		} else {
			sRv = _fileName;
		}
	}

	return Path(sRv);
}
//-------------------------------------------------------------------------------------------------
Path
Path::homeAsBrief() const
{
	return Path( String::replaceAll(_filePath, homeDir().str(), xT("~")) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::slashAppend() const
{
    return Path( String::trimRightChars(_filePath, Const::slash()).append(Const::slash()) );
}
//-------------------------------------------------------------------------------------------------
Path
Path::slashRemove() const
{
#if xENV_UNIX
	if (_filePath == Const::unixSlash()) {
		return Path(_filePath);
	}
#endif

    return Path( String::trimRightChars(_filePath, Const::slash()) );
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::maxSize()
{
    std::csize_t uiRv = _maxSize_impl();
    xTEST_DIFF(uiRv, std::size_t(0));

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::nameMaxSize()
{
    std::csize_t uiRv = _nameMaxSize_impl();
    xTEST_DIFF(uiRv, std::size_t(0));

    return uiRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
