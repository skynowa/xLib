/**
 * \file  Test_FileText.cpp
 * \brief test FileText
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileText)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileText::unit()
{
    std::ctstring_t filePath = data().tempDirPath + Const::slash() + xT("Test.txt");

	xTEST_CASE("read, write")
	{
		std::tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);

			for (size_t i = 0; i < 7; ++ i) {
				file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
			}
		}

		FileText(filePath).read( &content);
		FileText(filePath).write(content, FileIO::OpenMode::Write);

		std::tstring_t str;
		FileText(filePath).read( &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("read, write")
	{
		// empty content
		std::tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		FileText(filePath).read( &content);
		FileText(filePath).write(content, FileIO::OpenMode::Write);

		std::tstring_t str;
		FileText(filePath).read( &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("read, write")
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

		FileText(filePath).read( &content);
		FileText(filePath).write(content, FileIO::OpenMode::Write);

		std::vec_tstring_t vec;
		FileText(filePath).read( &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST(content == vec);
	}

	xTEST_CASE("read, write")
	{
		//  empty content
		std::vec_tstring_t content;

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		FileText(filePath).read( &content);
		FileText(filePath).write(content, FileIO::OpenMode::Write);

		std::vec_tstring_t vec;
		FileText(filePath).read( &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST(content == vec);
	}

	xTEST_CASE("read, write")
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

		FileText(filePath).read( separator, &content);
		FileText(filePath).write(separator, content, FileIO::OpenMode::Write);

		std::map_tstring_t msStr;
		FileText(filePath).read( separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST(content == msStr);
	}

	xTEST_CASE("read, write")
	{
		// empty content
		std::map_tstring_t content;
		std::ctstring_t    separator = Const::equal();

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::ReadWrite);
		}

		FileText(filePath).read( separator, &content);
		FileText(filePath).write(separator, content, FileIO::OpenMode::Write);

		std::map_tstring_t msStr;
		FileText(filePath).read( separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST(content == msStr);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
