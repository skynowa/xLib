/**
 * \file  Config.inl
 * \brief config file
 */


#include "Config.h"

#include <xLib/Core/String.h>
#include <xLib/Fs/Path.h>
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
	Config( Path::exe().str() )
{
}
//-------------------------------------------------------------------------------------------------
Config::Config(
    std::ctstring_t &a_filePath
) :
	_filePath {a_filePath},
    _separator{ Const::equal() }
{
    xTEST(!_filePath.empty());
    xTEST(!_separator.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Config::~Config()
{
    save();
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
    if ( !FileInfo(_filePath).isExists() ) {
		return;
    }

    File(_filePath).textRead(_separator, &_config);
    _config.erase(Const::strEmpty());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::save() const
{
	xCHECK_DO(_config.empty(), return);

    File(_filePath).textWrite(_separator, _config, FileIO::OpenMode::Write);
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

    FileIO file(_filePath);
    file.open(FileIO::OpenMode::Write);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::remove()
{
    // file
    File(_filePath).remove();

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
