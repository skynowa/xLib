/**
 * \file  Test_File.cpp
 * \brief test File
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_File)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_File::unit()
{
    std::ctstring_t filePath = option().tempDirPath + Const::slash() + xT("Test.txt");

    /*******************************************************************************
    *    prepare
    *
    *******************************************************************************/

    xTEST_CASE("clear")
    {
        FileText(filePath).write(xT("xxx"), FileIO::OpenMode::Write);

        File(filePath).clear();
        xTEST(FileInfo(filePath).isExists());
        xTEST(FileInfo(filePath).isEmpty());
    }

    xTEST_CASE("remove")
    {
        FileText(filePath).write(xT("yyy"), FileIO::OpenMode::Write);

        File(filePath).remove();
        xTEST(!FileInfo(filePath).isExists());
    }

	/*******************************************************************************
	*   static
	*
	*******************************************************************************/

	xTEST_CASE("rename")
	{
		std::ctstring_t newFilePath = option().tempDirPath + Const::slash() + xT("New.Test.txt");

		FileText(filePath).write(xT("Simple text"), FileIO::OpenMode::Write);

		{
			File(newFilePath).remove();
		}

		{
			File(filePath).rename(newFilePath);
		}

		{
			File(newFilePath).remove();
		}
	}

	xTEST_CASE("copy")
	{
		std::ctstring_t sFilePathFrom = option().tempDirPath + Const::slash() + xT("test_copy.txt");
		std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name.txt");

		{
			FileIO file(sFilePathFrom);
			file.open(FileIO::OpenMode::BinReadWrite, false);
			file.setSize(1024 * 5);
		}

		{
			cbool_t isFailIfExists{false};
			const auto errorCode = File(sFilePathFrom).copy(sFilePathTo, isFailIfExists);
			xTEST_EQ((int)errorCode, (int)Backup::Error::Ok);
		}

		m_bRv = FileInfo(sFilePathTo).isExists();
		xTEST(m_bRv);

		{
			File(sFilePathTo).remove();
		}

		{
			cbool_t isFailIfExists{true};
			const auto errorCode = File(sFilePathFrom).copy(sFilePathTo, isFailIfExists);
			xTEST_EQ((int)errorCode, (int)Backup::Error::Ok);
		}
	}

	xTEST_CASE("move")
	{
		std::ctstring_t newFilePath = option().tempDirPath + Const::slash() + xT("New.Test.txt");

		FileText(newFilePath).write(xT("Simple text"), FileIO::OpenMode::Write);

		{
			File(option().tempDirPath + Const::slash() + newFilePath).remove();
		}

		{
			File(newFilePath).move(option().tempDirPath);
		}
	}

	xTEST_CASE("createSymlink")
	{
		// TEST: createSymlink
	}

	xTEST_CASE("unlink")
	{
	#if xTEMP_DISABLED
		File(newFilePath).unlink();
	#endif
	}

	xTEST_CASE("remove")
	{
		std::ctstring_t newFilePath = option().tempDirPath + Const::slash() + xT("New.Test.txt");

		File(newFilePath).remove();
		File(newFilePath).remove();
	}

	xTEST_CASE("tryRemove")
	{
		std::ctstring_t tryfilePath = option().tempDirPath + Const::slash() + xT("New.Test.txt");

		for (size_t i = 0; i < 20; ++ i) {
			if (i < 10) {
				FileIO file(tryfilePath);
				file.open(FileIO::OpenMode::ReadWrite);
				file.setSize(1024);
				file.locking(FileIO::LockingMode::Lock, 10);

				{
					File lockedFile(tryfilePath);
					lockedFile.tryRemove(10, 2000);
				}

				file.locking(FileIO::LockingMode::Unlock, 10);
			} else {
				File file(tryfilePath);
				file.tryRemove(10, 33);
			}
		}
	}

	xTEST_CASE("wipe")
	{
		{
			std::ctstring_t buff = "0123456789";
			std::custring_t bytes(buff.cbegin(), buff.cend());

			FileBin(filePath).write(bytes, FileIO::OpenMode::BinReadWrite);
		}

		for (size_t i = 0; i < 3; ++ i) {
			File(filePath).wipe(10);
		}
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
