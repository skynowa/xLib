/**
 * \file   Test_Archive.cpp
 * \brief  test Archive
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Archive)
xTEST_UNIT(Test_Archive)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Archive::unit()
{
    Archive::cType type = Archive::Type::Zip;

	std::ctstring_t sourceDirPath = data.tempDirPath;

	// files
	{
		std::ctstring_t destDirPath = data.tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = sourceDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t zipFilePath = destDirPath   + Const::slash() + xT("Archive.zip");

		std::ctstring_t fileContent = xT("12345abcdef");
		File::textWrite(filePath, fileContent, File::OpenMode::omWrite);

	    xTEST_CASE("fileCompress")
		{
			m_bRv = Archive::fileCompress(type, filePath, zipFilePath, false);
			xTEST(m_bRv);
			xTEST(File::isExists(zipFilePath));
		}

		xTEST_CASE("fileUncompress")
		{
			std::ctstring_t txtfilePath = destDirPath + Const::slash() + xT("Archive.txt");

			m_bRv = Archive::fileUncompress(type, zipFilePath, destDirPath, true);
			xTEST(m_bRv);
			xTEST(File::isExists(filePath));

			std::tstring_t _fileContent;
			File::textRead(filePath, &_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}

		File::remove(filePath);
	}

	// dirs
	{
		std::ctstring_t destDirPath = data.tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = destDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t fileContent = xT("12345abcdef");
		File::textWrite(filePath, fileContent, File::OpenMode::omWrite);

	    xTEST_CASE("dirCompress")
		{
			std::ctstring_t zipFilePath = data.tempDirPath + Const::slash() + xT("ArchiveNew.zip");

			m_bRv = Archive::dirCompress(type, destDirPath, zipFilePath, true);
			xTEST(m_bRv);
		}

		xTEST_CASE("dirUncompress")
		{
			std::ctstring_t destDirPath = data.tempDirPath + Const::slash() + "ArchiveNew";

			m_bRv = Archive::dirUncompress(type, sourceDirPath, "*.zip", destDirPath, false);
			xTEST(m_bRv);

			std::ctstring_t txtfilePath = destDirPath + Const::slash() + xT("Archive.txt");

			std::tstring_t _fileContent;
			File::textRead(txtfilePath, &_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
