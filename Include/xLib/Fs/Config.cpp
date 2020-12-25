/**
 * \file  Config.inl
 * \brief config file
 */


#include "Config.h"

#include <xLib/Core/String.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/PathExe.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>

namespace xl::fs
{

/**************************************************************************************************
*    public: creation
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Config::Config() :
	Config( PathExe().str() )
{
}
//-------------------------------------------------------------------------------------------------
Config::Config(
    std::ctstring_t &a_filePath
) :
    _separator{ Const::equal() },
    _fileExt  { Path::fileExt(Path::FileExt::Config) }
{
    xTEST(!_separator.empty());
    xTEST(!_fileExt.empty());
    xTEST(_filePath.empty());
    xTEST(!a_filePath.empty());

    setPath( Path(a_filePath).setExt(_fileExt) );
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Config::~Config()
{
    save();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Config::path() const
{
    xTEST(!_filePath.empty());

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::setPath(
    std::ctstring_t &a_filePath
)
{
    xTEST(!a_filePath.empty());

    Dir( Path(a_filePath).dir() ).pathCreate();

    _filePath = a_filePath;
}
//-------------------------------------------------------------------------------------------------
std::map_tstring_t &
Config::get()
{
    return _config;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::read()
{
    if ( !FileInfo(path()).isExists() ) {
		return;
    }

    File(path()).textRead(_separator, &_config);
    _config.erase(Const::strEmpty());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::save() const
{
	xCHECK_DO(_config.empty(), return);

    File(path()).textWrite(_separator, _config, FileIO::OpenMode::Write);
}
//-------------------------------------------------------------------------------------------------
void_t
Config::saveDefault(
    std::cmap_tstring_t &a_content
)
{
    xTEST_NA(a_content);

    _config = a_content;
    save();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::clear()
{
	_config.clear();

    FileIO file(path());
    file.open(FileIO::OpenMode::Write);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::remove()
{
    // file
    File(path()).remove();

    // std::map_tstring_t
    _config.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: key
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Config::keyIsExists(
    std::ctstring_t &a_key
) const
{
    return (_config.find(a_key) != _config.cend());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyClear(
    std::ctstring_t &a_key
)
{
    xTEST(!a_key.empty());

    setValue(a_key, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::keyDelete(
   std::ctstring_t &a_key
)
{
    xTEST(!a_key.empty());

    _config.erase(a_key);
}
//-------------------------------------------------------------------------------------------------

} // namespace
