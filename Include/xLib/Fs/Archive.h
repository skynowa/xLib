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

	bool_t   fileArchive(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceFile);
		///< archive file
	bool_t   dirArchive(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceDir);
		///< archive dir

	bool_t   fileUnarchive(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destDirPath, cbool_t isRemoveSourceFile);
		///< unarchive file
	bool_t   dirUnarchive(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &fileShellFilter, std::ctstring_t &destDirPath,
				cbool_t isRemoveSourceFiles);
		///< unarchive dir

private:
    xNO_COPY_ASSIGN(Archive)
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
