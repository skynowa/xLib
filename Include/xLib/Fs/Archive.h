/**
 * \file   Archive.h
 * \brief  Pack/unpack archives
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Archive
    ///< Pack/unpack archives
{
public:
	enum class Type
		/// archive type
	{
		Unknown = 0,
		Zip     = 1,
		Rar     = 2,
		Gz      = 3,
		TarBz2  = 4
	};
	xUSING_CONST(Type);

             Archive() = default;
        ///< constructor
    virtual ~Archive() = default;
        ///< destructor

	bool_t   fileArchive(const Type archive_type, std::ctstring_t &source_path,
				std::ctstring_t &dest_archive_path, cbool_t is_remove_source);
		///< archive file
	bool_t   dirArchive(const Type archive_type, std::ctstring_t &source_path,
				std::ctstring_t &dest_archive_path, cbool_t is_remove_source);
		///< archive dir

	bool_t   fileUnarchive(const Type archive_type, std::ctstring_t &archive_path,
				std::ctstring_t &dest_dir, cbool_t is_remove_archive);
		///< unarchive file
	bool_t   dirUnarchive(const Type archive_type, std::ctstring_t &archive_dir_path,
				std::ctstring_t &archive_shell_filter, std::ctstring_t &dest_dir,
				cbool_t is_remove_archives);
		///< unarchive dir

private:
    xNO_COPY_ASSIGN(Archive)

	// static
	static
	std::tstring_t quoted(std::ctstring_t &value, std::ctstring_t &delimiter = Const::dqm());
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
