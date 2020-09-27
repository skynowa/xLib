/**
 * \file   Archive.cpp
 * \brief  Compress/Uncompress archives
 */


#include "Archive.h"

#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/Process.h>

//-------------------------------------------------------------------------------------------------
namespace
{

// TODO: use CMake
std::ctstring_t zipPath    = xT("/usr/bin/zip");
std::ctstring_t zip7Path   = xT("/usr/bin/7z");
std::ctstring_t tarPath    = xT("/usr/bin/tar");

std::ctstring_t unzipPath  = xT("/usr/bin/unzip");
std::ctstring_t unrarPath  = xT("/usr/bin/unrar");
std::ctstring_t gunzipPath = xT("/usr/bin/gunzip");

std::ctstring_t chmodPath  = xT("chmod");
}
//-------------------------------------------------------------------------------------------------

namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Archive::fileCompress(
	const Type       a_type,              ///< archive type
	std::ctstring_t &a_sourceFilePath,    ///< source path
	std::ctstring_t &a_destFilePath,      ///< destination archive path
	cbool_t          a_isRemoveSourceFile ///< is remove source dir
)
{
	xTEST_DIFF((int_t)a_type, (int_t)Type::Unknown);
	xTEST(!a_sourceFilePath.empty());
	xTEST(!a_destFilePath.empty());
	xTEST_NA(a_isRemoveSourceFile);

	std::ctstring_t dest_dir = Path(a_destFilePath).dir();
	Dir(dest_dir).pathCreate();

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (a_type) {
		case Type::Zip:
			binPath = zipPath;
			params  = {"-9", "-Dj", a_destFilePath, a_sourceFilePath};
			break;
		case Type::zip7:
			// TODO: Type::zip7
			return false;
			break;
		case Type::Rar:
			// TODO: Type::Rar
			return false;
			break;
		case Type::Gz:
			// TODO: Type::Gz
			return false;
			break;
		case Type::TarBz2:
			// TODO: Type::TarBz2
			return false;
			break;
		case Type::Unknown:
		default:
			xTEST(false);
			return false;
			break;
		}
	}

	Process::execute(binPath, params, {}, xTIMEOUT_INFINITE, nullptr, nullptr);

	// remove source dir
	if (a_isRemoveSourceFile) {
		Dir(a_sourceFilePath).pathDelete();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Archive::dirCompress(
	const Type       a_type,             ///< archive type
	std::ctstring_t &a_sourceDirPath,	 ///< source path
	std::ctstring_t &a_destFilePath,	 ///< destination archive path
	cbool_t          a_isRemoveSourceDir ///< is remove source dir
)
{
	xTEST_DIFF((int_t)a_type, (int_t)Type::Unknown);
	xTEST(Dir(a_sourceDirPath).isExists());
	xTEST(!a_destFilePath.empty());
	xTEST_NA(a_isRemoveSourceDir);

	std::ctstring_t dest_dir = Path(a_destFilePath).dir();
	Dir(dest_dir).pathCreate();

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (a_type) {
		case Type::Zip:
			binPath = zipPath;
			params  = {"-9", "-r", "-Dj", a_destFilePath, a_sourceDirPath};
			break;
		case Type::zip7:
			// TODO: Type::zip7
			return false;
			break;
		case Type::Rar:
			// TODO: Type::Rar
			return false;
			break;
		case Type::Gz:
			// TODO: Type::Gz
			return false;
			break;
		case Type::TarBz2:
			// TODO: Type::TarBz2
			return false;
			break;
		case Type::Unknown:
		default:
			xTEST(false);
			return false;
			break;
		}
	}

	Process::execute(binPath, params, {}, xTIMEOUT_INFINITE, nullptr, nullptr);

	// remove source dir
	if (a_isRemoveSourceDir) {
		Dir(a_sourceDirPath).pathDelete();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Archive::fileUncompress(
	const Type       a_type,              	///< archive type
	std::ctstring_t &a_sourceFilePath,    	///< file path
	std::ctstring_t &a_destDirPath,       	///< destination dir
	cbool_t          a_isRemoveSourceFile,	///< is remove source archive file
	cbool_t          a_isAutoDetectType 	///< is auto detect archive type by file extention
)
{
	if ( !a_isAutoDetectType ) {
		xTEST_DIFF((int_t)a_type, (int_t)Type::Unknown);
	}
	xTEST(!a_sourceFilePath.empty());
	xTEST(!a_destDirPath.empty());
	xTEST_NA(a_isRemoveSourceFile);

	Dir(a_destDirPath).pathCreate();

	const auto type = a_isAutoDetectType ? _detectType(a_sourceFilePath) : a_type;

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (type) {
		case Type::Zip:
			binPath = unzipPath;
			params  = {a_sourceFilePath, "-d", a_destDirPath};
			break;
		case Type::zip7:
			binPath = zip7Path;
			params  = {"x", a_sourceFilePath, "-o", a_destDirPath};
			break;
		case Type::Rar:
			binPath = unrarPath;
			params  = {"x", a_sourceFilePath, a_destDirPath};
			break;
		case Type::Gz:
			xUNUSED(a_isRemoveSourceFile);

			binPath = gunzipPath;
			params  = {a_sourceFilePath};
			break;
		case Type::TarBz2:
			binPath = tarPath;
			params  = {"xvjf", a_sourceFilePath, "-C", a_destDirPath};
			break;
		case Type::Unknown:
		default:
			xTEST(false);
			return false;
			break;
		}
	}

	Process::execute(binPath, params, {}, xTIMEOUT_INFINITE, nullptr, nullptr);

	// remove zip file
	if (a_isRemoveSourceFile) {
		if (type == Type::Gz) {
			// n/a
		} else {
			File(a_sourceFilePath).remove();
		}
	}

	// fix unzip bug - chmod for dest dir
	if (type == Type::Zip &&
		!Dir(a_destDirPath).isExists())
	{
		std::ctstring_t     binPath = chmodPath;
		std::cvec_tstring_t params  = {xT("-R"), xT("0777"), a_destDirPath};

		Process::execute(binPath, params, {}, xTIMEOUT_INFINITE, nullptr, nullptr);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Archive::dirUncompress(
	const Type       a_type,                ///< archive type
	std::ctstring_t &a_sourceDirPath,      	///< dir path
	std::ctstring_t &a_fileShellFilter,    	///< shell wildcard pattern
	std::ctstring_t &a_destDirPath,        	///< destination dir
	cbool_t          a_isRemoveSourceFiles,	///< is remove source archive files
	cbool_t          a_isAutoDetectType 	///< is auto detect archive type by file extention
)
{
	bool_t bRv {};

	std::vec_tstring_t archive_files;
	Finder::files(a_sourceDirPath, a_fileShellFilter, true, &archive_files);
	if ( archive_files.empty() ) {
		xTEST(false);
		return false;
	}

	for (const auto &it_archive_file : archive_files) {
		bRv = fileUncompress(a_type, it_archive_file, a_destDirPath, a_isRemoveSourceFiles,
					a_isAutoDetectType);
		if (!bRv) {
			xTEST(false);
			return false;
		}
	}

	return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Archive::Type
Archive::_detectType(
	std::ctstring_t &sourceFilePath
)
{
	static const std::map<std::tstring_t, Type> types
	{
		{xT(""),       Type::Unknown},
		{xT("zip"),    Type::Zip},
		{xT("7z"),     Type::zip7},
		{xT("rar"),    Type::Rar},
		{xT("gz"),     Type::Gz},
		{xT("tarbz2"), Type::TarBz2}
	};

	std::ctstring_t fileExt = Path(sourceFilePath).ext();

	auto it = types.find(fileExt);
	xCHECK_RET(it == types.end(), Type::Unknown);

	return it->second;
}
//-------------------------------------------------------------------------------------------------

} // namespace
