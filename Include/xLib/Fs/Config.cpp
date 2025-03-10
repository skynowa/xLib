/**
 * \file  Config.cpp
 * \brief config file
 */


#include "Config.h"

#include <xLib/Core/String.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
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
	_fileInfo (a_filePath),
	_file     (a_filePath),
	_separator(Const::equal())
{
    xTEST(!a_filePath.empty());
    xTEST(!_separator.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Config::~Config()
{
    write();
}
//-------------------------------------------------------------------------------------------------
std::map_tstring_t &
Config::get() /*  final */
{
    return _config;
}
//-------------------------------------------------------------------------------------------------
void_t
Config::read()
{
    xCHECK_DO(!_fileInfo.isExists(), return);

    _file.read(_separator, &_config);
    _config.erase(Const::strEmpty());
}
//-------------------------------------------------------------------------------------------------
void_t
Config::write() const
{
	xCHECK_DO(_config.empty(), return);

    _file.write(_separator, _config, FileIO::OpenMode::Write);
}
//-------------------------------------------------------------------------------------------------
void_t
Config::writeDefault(
    std::cmap_tstring_t &a_content
)
{
    xTEST_NA(a_content);

    _config = a_content;
    write();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::clear()
{
    _config.clear();

    File file(_fileInfo);
    file.clear();
}
//-------------------------------------------------------------------------------------------------
void_t
Config::remove()
{
    _config.clear();

    File file(_fileInfo);
    file.remove();
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
    return _config.contains(a_key);
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
