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
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");

    /*******************************************************************************
    *    prepare
    *
    *******************************************************************************/

    xTEST_CASE("remove")
    {
        File(filePath).remove();
    }

	/*******************************************************************************
	*   static
	*
	*******************************************************************************/

	xTEST_CASE("rename")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		File(filePath).textWrite(xT("Simple text"), FileIO::OpenMode::Write);

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
		std::ctstring_t sFilePathFrom = getData().tempDirPath + Const::slash() + xT("test_copy.txt");
		std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name.txt");

		{
			FileIO file(sFilePathFrom);
			file.open(FileIO::OpenMode::BinReadWrite, false);
			file.setSize(1024 * 5);
		}

		{
			File(sFilePathFrom).copy(sFilePathTo, false);
		}

		m_bRv = FileInfo(sFilePathTo).isExists();
		xTEST(m_bRv);

		{
			File(sFilePathTo).remove();
		}

		{
			File(sFilePathFrom).copy(sFilePathTo, true);
		}
	}

	xTEST_CASE("move")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		File(newFilePath).textWrite(xT("Simple text"), FileIO::OpenMode::Write);

		{
			File(getData().tempDirPath + Const::slash() + newFilePath).remove();
		}

		{
			File(newFilePath).move(getData().tempDirPath);
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
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		File(newFilePath).remove();
		File(newFilePath).remove();
	}

	xTEST_CASE("tryRemove")
	{
		std::ctstring_t tryfilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

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

			File(filePath).binWrite(bytes, FileIO::OpenMode::BinReadWrite);
		}

		for (size_t i = 0; i < 3; ++ i) {
			File(filePath).wipe(10);
		}
	}


	/*******************************************************************************
	*   static: utils
	*
	*******************************************************************************/

	xTEST_CASE("textRead, textWrite")
	{
		std::tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);

			for (size_t i = 0; i < 7; ++ i) {
				file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
			}
		}

		File(filePath).textRead( &content);
		File(filePath).textWrite(content, FileIO::OpenMode::Write);

		std::tstring_t str;
		File(filePath).textRead( &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// empty content
		std::tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		File(filePath).textRead( &content);
		File(filePath).textWrite(content, FileIO::OpenMode::Write);

		std::tstring_t str;
		File(filePath).textRead( &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// std::vector
		std::vec_tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);

			for (size_t i = 0; i < 10; ++ i) {
				file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
			}
		}

		File(filePath).textRead( &content);
		File(filePath).textWrite(content, FileIO::OpenMode::Write);

		std::vec_tstring_t vec;
		File(filePath).textRead( &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST(content == vec);
	}

	xTEST_CASE("textRead, textWrite")
	{
		//  empty content
		std::vec_tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		File(filePath).textRead( &content);
		File(filePath).textWrite(content, FileIO::OpenMode::Write);

		std::vec_tstring_t vec;
		File(filePath).textRead( &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST(content == vec);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// std::vector
		std::map_tstring_t content;
		std::ctstring_t    separator = Const::equal();

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);

			for (size_t i = 0; i < 10; ++ i) {
				file.writeLine(xT("asducfgnoawifg") + separator + xT("umoaeriuatgmoi"));
			}
		}

		File(filePath).textRead( separator, &content);
		File(filePath).textWrite(separator, content, FileIO::OpenMode::Write);

		std::map_tstring_t msStr;
		File(filePath).textRead( separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST(content == msStr);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// empty content
		std::map_tstring_t content;
		std::ctstring_t    separator = Const::equal();

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		File(filePath).textRead( separator, &content);
		File(filePath).textWrite(separator, content, FileIO::OpenMode::Write);

		std::map_tstring_t msStr;
		File(filePath).textRead( separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST(content == msStr);
	}

	xTEST_CASE("binRead, binWrite")
	{
		// binary
		std::ustring_t content;   content.resize(1024 * 5);

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::BinReadWrite);

			m_iRv = file.write(xT("0123456789"));
			xTEST_LESS(0, m_iRv);

			file.setSize(1024 * 5);

			m_iRv = file.write(xT("0123456789"));
			xTEST_LESS(0, m_iRv);
		}

		File(filePath).binWrite(content, FileIO::OpenMode::BinWrite);

		std::ustring_t str;
		File(filePath).binRead( &str);

		xTEST(content == str);
	}

	xTEST_CASE("binRead, binWrite")
	{
		// empty content
		std::ustring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::BinReadWrite);
		}

		File(filePath).binWrite(content, FileIO::OpenMode::BinWrite);

		std::ustring_t str;
		File(filePath).binRead( &str);

		xTEST(content == str);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
