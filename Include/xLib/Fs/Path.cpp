/**
 * \file  Path.inl
 * \brief file system path
 */


#include "Path.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Sync/Process.h>
#include <xLib/Log/Trace.h>
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


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Path::Path(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(_filePath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Path::filePath() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/**
* FAQ:
*
* http://www.cplusplus.com/forum/general/11104/
* http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
* http://libsylph.sourceforge.net/wiki/Full_path_to_binary
* http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?
*     ciid=88086d6e1de021106d6e1de02110275d6e10RCRD
*/

/* static */
std::tstring_t
Path::exe()
{
    std::ctstring_t sRv( _exe_impl() );
    xTEST_EQ(File::isExists(sRv), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::dll()
{
    return _dll_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::exeDir()
{
    return Path(exe()).dir();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::dir() const
{
    std::csize_t slashPos = filePath().rfind(Const::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, std::tstring_t());

    return filePath().substr(0, slashPos);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::dirName() const
{
    std::csize_t slashPos2 = filePath().rfind(Const::slash());
    xCHECK_RET(slashPos2 == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos1 = filePath().rfind(Const::slash(), slashPos2 - 1);
    if (slashPos1 == std::tstring_t::npos) {
        return filePath().substr(0, slashPos2);
    } else {
        return filePath().substr(slashPos1 + 1, slashPos2 - slashPos1 - 1);
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::fileName() const
{
    std::csize_t slashPos = filePath().rfind(Const::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, filePath());

    return filePath().substr(slashPos + Const::slash().size());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::fileBaseName() const
{
    std::csize_t slashPos = filePath().rfind(Const::slash(), filePath().size());
    std::csize_t dotPos   = filePath().rfind(Const::dot(),   filePath().size());

    return String::cut(filePath(), slashPos + Const::slash().size(), dotPos);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::ext() const
{
    std::csize_t dotPos   = filePath().rfind(Const::dot(),   filePath().size());
    xCHECK_RET(dotPos == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos = filePath().rfind(Const::slash(), filePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(dotPos < slashPos && slashPos != std::tstring_t::npos, std::tstring_t());

    return filePath().substr(dotPos + Const::dot().size());
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
    case FileExt::seConfig:
        sRv = xT("cfg");
        break;
    case FileExt::seLog:
        sRv = xT("log");
        break;
    case FileExt::seDb:
        sRv = xT("db");
        break;
    case FileExt::seDat:
        sRv = xT("dat");
        break;
    case FileExt::seBackup:
        sRv = xT("bak");
        break;
    case FileExt::seTemp:
        sRv = xT("tmp");
        break;
    case FileExt::seText:
        sRv = xT("txt");
        break;
    default:
        sRv = _fileExt_impl(a_fileExt);
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::setDir(
    std::ctstring_t &a_dirPath
)
{
    // dirPath

    std::tstring_t sRv(filePath());

    std::tstring_t dirStr = Path(sRv).dir();
    xTEST_EQ(dirStr.empty(), false);

    std::csize_t pos = sRv.find(dirStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, dirStr.size(), Path(a_dirPath).slashRemove());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::setFileName(
    std::ctstring_t &a_fullName
)
{
    // fullName

    std::tstring_t sRv(filePath());

    std::tstring_t fullName = Path(sRv).fileName();
    xTEST_EQ(fullName.empty(), false);

    std::csize_t pos = sRv.rfind(fullName);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, fullName.size(), a_fullName);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::setFileBaseName(
    std::ctstring_t &a_name
)
{
    // name

    std::tstring_t sRv(filePath());

    std::tstring_t name = Path(sRv).fileBaseName();
    xTEST_EQ(name.empty(), false);

    std::csize_t pos = sRv.rfind(name);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, name.size(), a_name);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::setExt(
    std::ctstring_t &a_ext
)
{
    xTEST_NA(a_ext);

    return removeExt() + Const::dot() + a_ext;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::removeExt()
{
    std::csize_t dotPos = filePath().rfind(Const::dot());

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::removeExtIf(
    std::ctstring_t &a_ext
)
{
    std::csize_t extPos = filePath().rfind(Const::dot() + a_ext);
    xCHECK_RET(extPos == std::tstring_t::npos, filePath());

    std::csize_t dotPos = filePath().rfind(Const::dot());
    xTEST_DIFF(dotPos, std::tstring_t::npos);

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::isValid(
    std::ctstring_t &a_filePath,                    ///< file, directory path
    std::tstring_t  *a_filePathValid /* = nullptr */   ///< [out] normalized path
)
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_filePathValid);

    // is empty
    xCHECK_RET(a_filePath.empty(), false);

    // check for size
    xCHECK_RET(a_filePath.size() > xPATH_MAX, false);

    // TODO: [skynowa] Path::isValid() - more checks

    // name
    {
        std::ctstring_t fileName = Path(a_filePath).fileName();

        xCHECK_RET(!isNameValid(fileName, a_filePathValid), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Path::isNameValid(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = nullptr */   ///< [out] normalized name
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
    if (sRv.size() > xNAME_MAX) {
        xCHECK_RET(a_fileNameValid == nullptr, false);

        sRv.resize(xNAME_MAX);
    }

    return _isNameValid_impl(sRv, a_fileNameValid);
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::isCaseSensitive() const
{
    xCHECK_RET(filePath().empty(), false);

    return _isCaseSensitive_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::isAbsolute() const
{
    xCHECK_RET(filePath().empty(),                         false);
    xCHECK_RET(filePath().at(0) == Const::slash().at(0), true);

    return _isAbsolute_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::toWin(
    cbool_t &a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = String::replaceAll(sRv, Const::unixSlash(), Const::winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::toUnix(
    cbool_t &a_isSlashAtEnd
)  const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    sRv = String::replaceAll(sRv, Const::winSlash(), Const::unixSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::toNative(
    cbool_t &a_isSlashAtEnd
) const
{
    xTEST_NA(a_isSlashAtEnd);

    std::tstring_t sRv;

    if (a_isSlashAtEnd) {
        sRv = slashAppend();
    } else {
        sRv = slashRemove();
    }

    _toNative_impl(&sRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::absolute() const
{
    std::ctstring_t sRv( _absolute_impl() );
    xTEST_EQ(Path(sRv).isAbsolute(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::shortName(
    std::ctstring_t &a_fileName,
    std::csize_t    &a_maxSize
)
{
    xTEST_EQ(a_fileName.empty(), false);
    xTEST_LESS(size_t(0), a_maxSize);

    std::tstring_t sRv;

    std::tstring_t tildaDotExt;

    if ( Path(a_fileName).ext().empty() ) {
        tildaDotExt = xT("~");
    } else {
        tildaDotExt = xT("~") + Const::dot() + Path(a_fileName).ext();
    }

    if (a_fileName.size() > a_maxSize) {
        if (a_maxSize < tildaDotExt.size()) {
            sRv = a_fileName.substr(0, a_maxSize);
        } else {
            sRv = a_fileName.substr(0, a_maxSize - tildaDotExt.size()) + tildaDotExt;
        }
    } else {
        sRv = a_fileName;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::brief(
    std::csize_t &a_maxSize
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
            size_t index = 0;

            for ( ; ; ) {
                std::csize_t pos = a_str->find_first_of(Const::winSlash() + Const::unixSlash());
                xCHECK_DO(pos == std::tstring_t::npos,    break);

                a_str->erase(0, pos + Const::slash().size());

                ++ index;

                xCHECK_DO(*a_num == index && *a_num != 0, break);
            }

            *a_num = index;
        }
    };


    std::tstring_t sRv  = filePath();
    std::tstring_t path = filePath();
    size_t         num  = 0;

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

    sRv = Path(sRv).toNative(false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::brief(
	std::csize_t a_leftDirsNum,			///<
	std::csize_t a_rightDirsNum,		///<
	cbool_t      a_isShowHiddenDirsNum	/// ("/dir1/..{3}../dirN")
) const
{
	std::tstring_t sRv;

	std::ctstring_t &fullPath = filePath();

	std::vec_tstring_t values;
	String::split(fullPath, Const::slash(), &values);

	std::csize_t allDirsNum  = a_leftDirsNum + a_rightDirsNum;
	if (values.size() <= allDirsNum) {
		return fullPath;
	}

	std::csize_t hideDirsNum = values.size() - allDirsNum;

	std::ctstring_t &dots = a_isShowHiddenDirsNum ?
		Format::str(xT("..{}.."), hideDirsNum) : xT("...");

	values.erase(values.cbegin() + a_leftDirsNum,
                 values.cbegin() + a_leftDirsNum + hideDirsNum - 1 /* dots */);
	values.at(a_leftDirsNum) = dots;

	sRv = String::join(values, Const::slash());

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::homeAsBrief() const
{
	return String::replaceAll(filePath(), User().homeDir(), xT("~"));
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::slashAppend() const
{
    return String::trimRightChars(filePath(), Const::slash()).append(Const::slash());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Path::slashRemove() const
{
    return String::trimRightChars(filePath(), Const::slash());
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::maxSize()
{
    return _maxSize_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
Path::nameMaxSize()
{
    return _nameMaxSize_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
