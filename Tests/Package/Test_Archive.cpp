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

	std::ctstring_t sourceDirPath = getData().tempDirPath;

	// files
	{
		std::ctstring_t destDirPath = getData().tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = sourceDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t zipFilePath = destDirPath   + Const::slash() + xT("Archive.zip");

		std::ctstring_t fileContent = xT("12345abcdef");
		File(filePath).textWrite( fileContent, FileIO::OpenMode::Write);

		xTEST_CASE("fileCompress")
		{
			m_bRv = Archive::fileCompress(type, filePath, zipFilePath, false);
			xTEST(m_bRv);
			xTEST(FileInfo(zipFilePath).isExists());
		}

		xTEST_CASE("fileUncompress")
		{
			std::ctstring_t txtfilePath = destDirPath + Const::slash() + xT("Archive.txt");

			m_bRv = Archive::fileUncompress(type, zipFilePath, destDirPath, true, false);
			xTEST(m_bRv);
			xTEST(FileInfo(filePath).isExists());

			std::tstring_t _fileContent;
			File(filePath).textRead(&_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}

		File(filePath).remove();
	}

	// dirs
	{
		std::ctstring_t destDirPath = getData().tempDirPath + Const::slash() + "Archive";

		std::ctstring_t filePath    = destDirPath + Const::slash() + xT("Archive.txt");
		std::ctstring_t fileContent = xT("12345abcdef");
		File(filePath).textWrite( fileContent, FileIO::OpenMode::Write);

		xTEST_CASE("dirCompress")
		{
			std::ctstring_t zipFilePath = getData().tempDirPath + Const::slash() + xT("ArchiveNew.zip");

			m_bRv = Archive::dirCompress(type, destDirPath, zipFilePath, true);
			xTEST(m_bRv);
		}

		xTEST_CASE("dirUncompress")
		{
			std::ctstring_t destDirPathNew = getData().tempDirPath + Const::slash() + "ArchiveNew";

			m_bRv = Archive::dirUncompress(type, sourceDirPath, "*.zip", destDirPathNew, false, false);
			xTEST(m_bRv);

			std::ctstring_t txtfilePath = destDirPathNew + Const::slash() + xT("Archive.txt");

			std::tstring_t _fileContent;
			File(txtfilePath).textRead(&_fileContent);
			xTEST_EQ(_fileContent, fileContent);
		}
	}

	{
	#if 0
		xTEST_CASE("fileUncompress")
		{
			std::ctstring_t filePathRar = xT("/media/skynowa/Disk/Foto/SriLanka.rar");
			std::ctstring_t destDirPath = xT("/media/skynowa/Disk/Foto/SriLanka");

			m_bRv = Archive::fileUncompress(Archive::Type::Rar, filePathRar, destDirPath, false);
			xTEST(m_bRv);
		}
	#endif
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
