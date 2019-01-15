/**
 * \file   Archive.h
 * \brief  Pack/unpack archives
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class Archive
    ///< Pack/unpack archives
{
public:
	enum class Type
		/// archive type
	{
		Unknown = 0,
		Zip     = 1,
		zip7    = 2,
		Rar     = 3,
		Gz      = 4,
		TarBz2  = 5
	};
	xUSING_CONST(Type);

	static
	bool_t   fileCompress(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceFile);
		///< archive file
	static
	bool_t   dirCompress(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceDir);
		///< archive dir

	static
	bool_t   fileUncompress(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destDirPath, cbool_t isRemoveSourceFile);
		///< unarchive file
	static
	bool_t   dirUncompress(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &fileShellFilter, std::ctstring_t &destDirPath,
				cbool_t isRemoveSourceFiles);
		///< unarchive dir

private:
    xNO_DEFAULT_CONSTRUCT(Archive)
    xNO_COPY_ASSIGN(Archive)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
