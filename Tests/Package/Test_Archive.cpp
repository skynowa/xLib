/**
 * \file   Test_Archive.cpp
 * \brief  test Archive
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Archive)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Archive::unit()
{
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	Archive archive(Archive::Type::Zip);

	std::ctstring_t sourceDirPath = option().tempDirPath;

	// files
	{
		std::ctstring_t destDirPath = option().tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = sourceDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t zipFilePath = destDirPath   + Const::slash() + xT("Archive.zip");

		std::ctstring_t fileContent = xT("12345abcdef");
		FileText(filePath).write( fileContent, FileIO::OpenMode::Write);

		xTEST_CASE("fileCompress")
		{
			m_bRv = archive.fileCompress(filePath, zipFilePath, false);
			xTEST(m_bRv);
			xTEST(FileInfo(zipFilePath).isExists());
		}

		xTEST_CASE("fileUncompress")
		{
			std::ctstring_t txtfilePath = destDirPath + Const::slash() + xT("Archive.txt");

			m_bRv = archive.fileUncompress(zipFilePath, destDirPath, true, false);
			xTEST(m_bRv);
			xTEST(FileInfo(filePath).isExists());

			std::tstring_t _fileContent;
			FileText(filePath).read(&_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}

		File(filePath).remove();
	}

	// dirs
	{
		std::ctstring_t destDirPath = option().tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = destDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t fileContent = xT("12345abcdef");
		FileText(filePath).write( fileContent, FileIO::OpenMode::Write);

		xTEST_CASE("dirCompress")
		{
			std::ctstring_t zipFilePath = option().tempDirPath + Const::slash() + xT("ArchiveNew.zip");

			m_bRv = archive.dirCompress(destDirPath, zipFilePath, true);
			xTEST(m_bRv);
		}

		xTEST_CASE("dirUncompress")
		{
			std::ctstring_t destDirPathNew = option().tempDirPath + Const::slash() + "ArchiveNew";

			m_bRv = archive.dirUncompress(sourceDirPath, "*.zip", destDirPathNew, false, false);
			xTEST(m_bRv);

			std::ctstring_t txtfilePath = destDirPathNew + Const::slash() + xT("Archive.txt");

			std::tstring_t _fileContent;
			FileText(txtfilePath).read(&_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}
	}

	xTEST_CASE("fileUncompress")
	{
		// TEST: fileUncompress
		if (0) {
			std::ctstring_t filePathRar = xT("/media/skynowa/Disk/Foto/SriLanka.rar");
			std::ctstring_t destDirPath = xT("/media/skynowa/Disk/Foto/SriLanka");

			Archive archiveRar(Archive::Type::Rar);

			cbool_t isRemoveSourceFile {false};
			cbool_t isAutoDetectType   {true};
			m_bRv = archiveRar.fileUncompress(filePathRar, destDirPath, isRemoveSourceFile,
				isAutoDetectType);
			xTEST(m_bRv);
		} else {
			LogCout() << "[TODO]";
		}
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
