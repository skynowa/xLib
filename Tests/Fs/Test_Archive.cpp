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
    std::ctstring_t sourceDirPath = data.tempDirPath;
    std::ctstring_t destDirPath   = data.tempDirPath + Const::slash() + "Archive";

    std::ctstring_t filePath      = sourceDirPath + Const::slash() + xT("Archive.txt");
    std::ctstring_t zipFilePath   = destDirPath   + Const::slash() + xT("Archive.zip");

    std::ctstring_t fileContent = xT("12345abcdef");
    File::textWrite(filePath, fileContent, File::OpenMode::omWrite);

    Archive archive;
    Archive::cType type = Archive::Type::Zip;

    xTEST_CASE("fileArchive")
    {
        m_bRv = archive.fileArchive(type, filePath, zipFilePath, false);
        xTEST(m_bRv);
        xTEST(File::isExists(zipFilePath));
    }

    xTEST_CASE("fileUnarchive")
    {
		std::ctstring_t txtfilePath = destDirPath + Const::slash() + xT("Archive.txt");
		File::remove(txtfilePath);

		m_bRv = archive.fileUnarchive(type, zipFilePath, destDirPath, false);
		xTEST(m_bRv);
		xTEST(File::isExists(filePath));

		std::tstring_t _fileContent;
		File::textRead(filePath, &_fileContent);
		xTEST_EQ(_fileContent, fileContent);
    }

    xTEST_CASE("dirArchive")
    {
        m_bRv = archive.dirArchive(type, destDirPath, sourceDirPath, true);
		xTEST(m_bRv);
    }

    xTEST_CASE("dirUnarchive")
    {
         m_bRv = archive.dirUnarchive(type, sourceDirPath, "*.zip", destDirPath, false);
    }

    /// File::remove(filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------
