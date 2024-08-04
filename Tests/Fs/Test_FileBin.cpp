/**
 * \file  Test_FileBin.cpp
 * \brief test FileBin
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileBin)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileBin::unit()
{
    std::ctstring_t filePath = data().tempDirPath + Const::slash() + xT("Test.txt");

	xTEST_CASE("read, write")
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

		FileBin file(filePath);
		file.write(content, FileIO::OpenMode::BinWrite);

		std::ustring_t str;
		file.read(&str);

		xTEST(content == str);
	}

	xTEST_CASE("read, write")
	{
		// empty content
		std::ustring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::BinReadWrite);
		}

		FileBin file(filePath);
		file.write(content, FileIO::OpenMode::BinWrite);

		std::ustring_t str;
		file.read(&str);

		xTEST(content == str);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
