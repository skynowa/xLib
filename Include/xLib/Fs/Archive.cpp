/**
 * \file   Archive.cpp
 * \brief  Pack/unpack archives
 */


#include "Archive.h"

#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Sync/Process.h>


xNAMESPACE_ANONYM_BEGIN

// TODO: use CMake
std::ctstring_t zipPath    = xT("/usr/bin/zip");
std::ctstring_t tarPath    = xT("/usr/bin/tar");

std::ctstring_t unzipPath  = xT("/usr/bin/unzip");
std::ctstring_t unrarPath  = xT("/usr/local/bin/unrar");
std::ctstring_t gunzipPath = xT("/usr/bin/gunzip");

std::ctstring_t chmodPath  = xT("chmod");

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Archive::fileArchive(
	const Type       a_archive_type,		///< archive type
	std::ctstring_t &a_source_path,			///< source path
	std::ctstring_t &a_dest_archive_path,	///< destination archive path
	cbool_t          a_is_remove_source		///< is remove source dir
)
{
	xTEST_DIFF((int_t)a_archive_type, (int_t)Type::Unknown);
	xTEST(!a_source_path.empty());
	xTEST(!a_dest_archive_path.empty());
	xTEST_NA(a_is_remove_source);

	std::ctstring_t dest_dir = Path(a_dest_archive_path).dir();
	Dir(dest_dir).pathCreate();

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (a_archive_type) {
		case Type::Zip:
			binPath = zipPath;
			params  = {"-9", "-Dj", a_dest_archive_path, a_source_path};
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

	Process::create(binPath, xTIMEOUT_INFINITE, params, {});

	// remove source dir
	if (a_is_remove_source) {
		Dir(a_source_path).pathDelete();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Archive::dirArchive(
	const Type       a_archive_type,		///< archive type
	std::ctstring_t &a_source_path,			///< source path
	std::ctstring_t &a_dest_archive_path,	///< destination archive path
	cbool_t          a_is_remove_source		///< is remove source dir
)
{
	xTEST_DIFF((int_t)a_archive_type, (int_t)Type::Unknown);
	xTEST(!a_source_path.empty());
	xTEST(!a_dest_archive_path.empty());
	xTEST_NA(a_is_remove_source);

	std::ctstring_t dest_dir = Path(a_dest_archive_path).dir();
	Dir(dest_dir).pathCreate();

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (a_archive_type) {
		case Type::Zip:
			binPath = zipPath;
			params  = {"-9", "-r", "-Dj", a_dest_archive_path, a_source_path};
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

	Process::create(binPath, xTIMEOUT_INFINITE, params, {});

	// remove source dir
	if (a_is_remove_source) {
		Dir(a_source_path).pathDelete();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Archive::fileUnarchive(
	const Type       a_archive_type,       ///< archive type
	std::ctstring_t &a_archive_path,       ///< file path
	std::ctstring_t &a_dest_dir,           ///< destination dir
	cbool_t          a_is_remove_archive   ///< is remove source archive file
)
{
	xTEST_DIFF((int_t)a_archive_type, (int_t)Type::Unknown);
	xTEST(!a_archive_path.empty());
	xTEST(!a_dest_dir.empty());
	xTEST_NA(a_is_remove_archive);

	Dir(a_dest_dir).pathCreate();

	std::tstring_t     binPath;
	std::vec_tstring_t params;
	{
		switch (a_archive_type) {
		case Type::Zip:
			binPath = unzipPath;
			params  = {a_archive_path, "-d", a_dest_dir};
			break;
		case Type::Rar:
			binPath = unrarPath;
			params  = {"x", "-r", a_archive_path, a_dest_dir};
			break;
		case Type::Gz:
			xUNUSED(a_dest_dir);

			binPath = gunzipPath;
			params  = {a_archive_path};
			break;
		case Type::TarBz2:
			binPath = tarPath;
			params  = {"xvjf", a_archive_path, "-C", a_dest_dir};
			break;
		case Type::Unknown:
		default:
			xTEST(false);
			return false;
			break;
		}
	}

	Process::create(binPath, xTIMEOUT_INFINITE, params, {});

	// remove zip file
	if (a_is_remove_archive) {
		if (a_archive_type == Type::Gz) {
			// n/a
		} else {
			File::remove(a_archive_path);
		}
	}

	// fix unzip bug - chmod for dest dir
	if (a_archive_type == Type::Zip &&
		!Dir(a_dest_dir).isExists())
	{
		std::ctstring_t     binPath = chmodPath;
		std::cvec_tstring_t params  = {xT("-R 0777"), a_dest_dir};

		Process::create(binPath, xTIMEOUT_INFINITE, params, {});
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Archive::dirUnarchive(
	const Type       a_archive_type,         ///< archive type
	std::ctstring_t &a_archive_dir_path,     ///< dir path
	std::ctstring_t &a_archive_shell_filter, ///< shell wildcard pattern
	std::ctstring_t &a_dest_dir,             ///< destination dir
	cbool_t          a_is_remove_archives    ///< is remove source archive files
)
{
	bool_t bRv {};

	std::vec_tstring_t archive_files;
	Finder::files(a_archive_dir_path, a_archive_shell_filter, true, &archive_files);
	if ( archive_files.empty() ) {
		xTEST(false);
		return false;
	}

	for (auto &it_archive_file : archive_files) {
		bRv = fileUnarchive(a_archive_type, it_archive_file, a_dest_dir, a_is_remove_archives);
		if (!bRv) {
			xTEST(false);
			return false;
		}
	}

	return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
