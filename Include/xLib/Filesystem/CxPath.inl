/**
 * \file  CxPath.inl
 * \brief file system path
 */


#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxString.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxPath_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxPath_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxPath_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxPath_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxPath::CxPath(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(_filePath.empty(), false);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxPath::filePath() const
{
    xTEST_EQ(_filePath.empty(), false);

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/**
* FAQ:
*   http://www.cplusplus.com/forum/general/11104/
*   http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
*   http://libsylph.sourceforge.net/wiki/Full_path_to_binary
*   http://h21007.www2.hp.com/portal/site/dspp/menuitem.863c3e4cbcdc3f3515b49c108973a801?
*       ciid=88086d6e1de021106d6e1de02110275d6e10RCRD
*/

/* static */
inline std::tstring_t
CxPath::exe()
{
    std::ctstring_t sRv( _exe_impl() );
    xTEST_EQ(CxFile::isExists(sRv), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::dll()
{
    return _dll_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::exeDir()
{
    return CxPath(exe()).dir();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::dir() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, std::tstring_t());

    return filePath().substr(0, slashPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::dirName() const
{
    std::csize_t slashPos2 = filePath().rfind(CxConst::slash());
    xCHECK_RET(slashPos2 == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos1 = filePath().rfind(CxConst::slash(), slashPos2 - 1);
    if (slashPos1 == std::tstring_t::npos) {
        return filePath().substr(0, slashPos2);
    } else {
        return filePath().substr(slashPos1 + 1, slashPos2 - slashPos1 - 1);
    }
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::fileName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    xCHECK_RET(slashPos == std::tstring_t::npos, filePath());

    return filePath().substr(slashPos + CxConst::slash().size());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::fileBaseName() const
{
    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    std::csize_t dotPos   = filePath().rfind(CxConst::dot(),   filePath().size());

    return CxString::cut(filePath(), slashPos + CxConst::slash().size(), dotPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::ext() const
{
    std::csize_t dotPos   = filePath().rfind(CxConst::dot(),   filePath().size());
    xCHECK_RET(dotPos == std::tstring_t::npos, std::tstring_t());

    std::csize_t slashPos = filePath().rfind(CxConst::slash(), filePath().size());
    // if dot after slash - extension not exists
    xCHECK_RET(dotPos < slashPos && slashPos != std::tstring_t::npos, std::tstring_t());

    return filePath().substr(dotPos + CxConst::dot().size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::standartExt(
    const ExStandartExt &a_fileExt
)
{
    return _standartExt_impl(a_fileExt);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setDir(
    std::ctstring_t &a_dirPath
)
{
    // dirPath

    std::tstring_t sRv(filePath());

    std::tstring_t dirStr = CxPath(sRv).dir();
    xTEST_EQ(dirStr.empty(), false);

    std::csize_t pos = sRv.find(dirStr);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, dirStr.size(), CxPath(a_dirPath).slashRemove());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setFileName(
    std::ctstring_t &a_fullName
)
{
    // fullName

    std::tstring_t sRv(filePath());

    std::tstring_t fullName = CxPath(sRv).fileName();
    xTEST_EQ(fullName.empty(), false);

    std::csize_t pos = sRv.rfind(fullName);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, fullName.size(), a_fullName);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setFileBaseName(
    std::ctstring_t &a_name
)
{
    // name

    std::tstring_t sRv(filePath());

    std::tstring_t name = CxPath(sRv).fileBaseName();
    xTEST_EQ(name.empty(), false);

    std::csize_t pos = sRv.rfind(name);
    xTEST_DIFF(pos, std::tstring_t::npos);

    return sRv.replace(pos, name.size(), a_name);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::setExt(
    std::ctstring_t &a_ext
)
{
    xTEST_NA(a_ext);

    return removeExt() + CxConst::dot() + a_ext;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::removeExt()
{
    std::csize_t dotPos = filePath().rfind(CxConst::dot());

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::removeExtIf(
    std::ctstring_t &a_ext
)
{
    std::csize_t extPos = filePath().rfind(CxConst::dot() + a_ext);
    xCHECK_RET(extPos == std::tstring_t::npos, filePath());

    std::csize_t dotPos = filePath().rfind(CxConst::dot());
    xTEST_DIFF(dotPos, std::tstring_t::npos);

    return filePath().substr(0, dotPos);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxPath::isValid(
    std::ctstring_t &a_filePath,                    ///< file, directory path
    std::tstring_t  *a_filePathValid /* = xPTR_NULL */   ///< [out] normalized path
)
{
    xTEST_NA(a_filePath);
    xTEST_NA(a_filePathValid);

    // is empty
    xCHECK_RET(a_filePath.empty(), false);

    // check for size
    xCHECK_RET(a_filePath.size() > xPATH_MAX, false);

    // TODO: CxPath::isValid() - more checks

    // name
    {
        std::ctstring_t fileName = CxPath(a_filePath).fileName();

        xCHECK_RET(!isNameValid(fileName, a_filePathValid), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxPath::isNameValid(
    std::ctstring_t &a_fileName,                    ///< file, directory name
    std::tstring_t  *a_fileNameValid /* = xPTR_NULL */   ///< [out] normalized name
)
{
    xTEST_NA(a_fileName);
    xTEST_NA(a_isNormalize);
    xTEST_NA(a_fileNameValid);

    std::tstring_t sRv(a_fileName);

    // check: empty name
    if ( sRv.empty() ) {
        xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

        a_fileNameValid->clear();
        return true;
    }

    // check: name size
    if (sRv.size() > xNAME_MAX) {
        xCHECK_RET(a_fileNameValid == xPTR_NULL, false);

        sRv.resize(xNAME_MAX);
    }

    return _isNameValid_impl(sRv, a_fileNameValid);;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxPath::isAbsolute() const
{
    xCHECK_RET(filePath().empty(),                         false);
    xCHECK_RET(filePath().at(0) == CxConst::slash().at(0), true);

    return _isAbsolute_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::toWin(
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

    sRv = CxString::replaceAll(sRv, CxConst::unixSlash(), CxConst::winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::toUnix(
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

    sRv = CxString::replaceAll(sRv, CxConst::winSlash(), CxConst::unixSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::toNative(
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
inline std::tstring_t
CxPath::absolute() const
{
    std::ctstring_t sRv( _absolute_impl() );
    xTEST_EQ(CxPath(sRv).isAbsolute(), true);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::shortName(
    std::ctstring_t &a_fileName,
    std::csize_t    &a_maxSize
)
{
    xTEST_EQ(a_fileName.empty(), false);
    xTEST_LESS(size_t(0), a_maxSize);

    std::tstring_t sRv;

    std::tstring_t tildaDotExt;

    if ( CxPath(a_fileName).ext().empty() ) {
        tildaDotExt = xT("~");
    } else {
        tildaDotExt = xT("~") + CxConst::dot() + CxPath(a_fileName).ext();
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
inline std::tstring_t
CxPath::brief(
    std::csize_t &a_maxSize
) const
{
    xTEST_LESS(size_t(0), a_maxSize);

    // util function
    struct _Functor
    {
        static void_t
        slashesMake(
            std::tstring_t &a_str,
            size_t         *a_num
        )
        {
            size_t index = 0;

            for ( ; ; ) {
                std::csize_t pos = a_str.find_first_of(CxConst::winSlash() + CxConst::unixSlash());

                a_str.erase(0, pos + CxConst::slash().size());

                xCHECK_DO(pos != std::tstring_t::npos,    ++ index);
                xCHECK_DO(*a_num == index && *a_num != 0, break);
                xCHECK_DO(pos == std::tstring_t::npos,    break);
            }

            *a_num = index;
        }
    };


    std::tstring_t sRv  = filePath();
    std::tstring_t path = filePath();
    size_t         num  = 0;

    _Functor::slashesMake(path, &num);

    while (sRv.size() > a_maxSize && num > 2) {
        path = sRv;

        std::size_t numNew = num / 2;

        _Functor::slashesMake(path, &numNew);

        sRv.erase(sRv.find(path), path.size());

        numNew = 2;
        _Functor::slashesMake(path, &numNew);

        sRv.append(CxConst::dot3() + CxConst::slash() + path);

        -- num;
    }

    sRv = CxPath(sRv).toNative(false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::slashAppend() const
{
    return CxString::trimRightChars(filePath(), CxConst::slash()).append(CxConst::slash());
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxPath::slashRemove() const
{
    return CxString::trimRightChars(filePath(), CxConst::slash());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::maxSize()
{
    return _maxSize_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline size_t
CxPath::nameMaxSize()
{
    return _nameMaxSize_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
