/**
 * \file   Archive.h
 * \brief  Compress/Uncompress archives
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class Archive
    /// Compress/unpack archives
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
	bool_t fileCompress(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceFile);
		///< compress file
	static
	bool_t dirCompress(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &destFilePath, cbool_t isRemoveSourceDir);
		///< compress dir

	static
	bool_t fileUncompress(const Type type, std::ctstring_t &sourceFilePath,
				std::ctstring_t &destDirPath, cbool_t isRemoveSourceFile, cbool_t isAutoDetectType);
		///< uncompress file
	static
	bool_t dirUncompress(const Type type, std::ctstring_t &sourceDirPath,
				std::ctstring_t &fileShellFilter, std::ctstring_t &destDirPath,
				cbool_t isRemoveSourceFiles, cbool_t isAutoDetectType);
		///< uncompress dir

private:
    xNO_DEFAULT_CONSTRUCT(Archive)
    xNO_COPY_ASSIGN(Archive)

    static
    Type  	_detectType(std::ctstring_t &sourceFilePath);
    	///< auto detect archive type by file extention
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
