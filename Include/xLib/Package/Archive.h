/**
 * \file   Archive.h
 * \brief  Compress/Uncompress archives
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

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

///\name ctors, dtor
///\{
	explicit  Archive(const Type type);
			 ~Archive() = default;

	xNO_DEFAULT_CONSTRUCT(Archive);
	xNO_COPY_ASSIGN(Archive);
///\}

	// Compress
	bool_t fileCompress(std::ctstring_t &sourceFilePath, std::ctstring_t &destFilePath,
				cbool_t isRemoveSourceFile);
	bool_t dirCompress(std::ctstring_t &sourceDirPath, std::ctstring_t &destFilePath,
				cbool_t isRemoveSourceDir);

	// Uncompress
	bool_t fileUncompress(std::ctstring_t &sourceFilePath, std::ctstring_t &destDirPath,
				cbool_t isRemoveSourceFile, cbool_t isAutoDetectType);
	bool_t dirUncompress(std::ctstring_t &sourceDirPath, std::ctstring_t &fileShellFilter,
				std::ctstring_t &destDirPath, cbool_t isRemoveSourceFiles, cbool_t isAutoDetectType);

private:
	cType _type {};

xPRIVATE_STATIC:
    static Type _detectType(std::ctstring_t &sourceFilePath);
    	///< auto detect archive type by file extention
};

} // namespace
//-------------------------------------------------------------------------------------------------
