/**
 * \file   Test_File.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

class Test_File :
    public Unit
{
public:
           Test_File() {}

    bool_t unit() override;

private:
    bool_t unit1();
    bool_t unitPrivate();
};
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
        File file;
        file.create(filePath, File::OpenMode::Write);
        file.remove();
    }

    /*******************************************************************************
    *    open, get
    *
    *******************************************************************************/

    xTEST_CASE("operator =")
    {
        for (size_t i = 0; i < 10; ++ i) {
            HandleStdFile _handle;
            xTEST_EQ(_handle.isValid(), false);

            {
                std::FILE *file = xTFOPEN(filePath.c_str(), "w+");
                xTEST_PTR(file);

                _handle = file;
                xTEST_EQ(file, _handle.get());
                xTEST_EQ(_handle.isValid(), true);

                twint_t iRv = std::fclose(_handle.get()); _handle = nullptr;
                xTEST_DIFF(iRv, xTEOF);
                xTEST_EQ(_handle.isValid(), false);
            }

            {
                std::FILE *file = xTFOPEN(filePath.c_str(), "w+");
                xTEST_PTR(file);

                _handle = file;
                xTEST_EQ(file, _handle.get());
                xTEST_EQ(_handle.isValid(), true);

                twint_t iRv = std::fclose(_handle.get()); _handle = nullptr;
                xTEST_DIFF(iRv, xTEOF);
                xTEST_EQ(_handle.isValid(), false);
            }
        }

        for (size_t i = 0; i < 10; ++ i) {
            File file;
            file.create(filePath, File::OpenMode::CreateReadWrite);
            file.close();
            file.create(filePath, File::OpenMode::CreateReadWrite);
            file.close();
        }
    }

    xTEST_CASE("create")
    {
        File file;

        for (size_t i = 0; i < 1; ++ i) {
            file.create(filePath, File::OpenMode::CreateReadWrite);
        }
    }

    xTEST_CASE("reopen")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        for (size_t i = 0; i < 7; ++ i) {
            file.reopen(filePath, File::OpenMode::OpenReadWrite);
        }
    }

    // TDOO: test
    xTEST_CASE("attach")
    {
    #if xTEMP_DISABLED
        HandleStdFile handle(stdout);

        std::ctstring_t filePath;

        File file;
        file.attach(handle, filePath);

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);

        HandleStdFile stdFile;
        stdFile = file.detach();
        xTEST_EQ(stdFile.isValid(), true);
        xTEST_EQ(stdout, stdFile.get());
    #endif
    }

    xTEST_CASE("get")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        FILE *stdFile = file.get().get();
        xTEST_PTR(stdFile);
    }

    xTEST_CASE("path")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        xTEST_EQ(file.path(), filePath);
    }


    /*******************************************************************************
    *    read, write
    *
    *******************************************************************************/

    xTEST_CASE("write, read")
    {
        std::tstring_t buffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring_t buffRead  = xT("");       buffRead.resize(buffWrite.size());

        // write
        {
            File file;
            file.create(filePath, File::OpenMode::BinCreateReadWrite);
            m_stRv = file.write((cptr_cvoid_t)&buffWrite.at(0), buffWrite.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        // read
        {
            File file;
            file.create(filePath, File::OpenMode::BinRead);
            m_stRv = file.read(&buffRead.at(0), buffRead.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        xTEST_EQ(buffWrite, buffRead);
    }

    xTEST_CASE("write, read")
    {
        std::custring_t content(10, 5);

        std::ustring_t  text1;
        std::ustring_t  text2;

        // write
        {
            File file;
            file.create(filePath, File::OpenMode::BinWrite);
            file.write(content);
        }

        // read
        {
            File file;
            file.create(filePath, File::OpenMode::BinRead);
            file.read(&text1);
        }

        // write
        {
            std::ctstring_t dataNewPath = getData().tempDirPath + Const::slash() + xT("DataNew.dat");

            File file;
            file.create(dataNewPath, File::OpenMode::BinWrite);
            file.write(text1);

            file.remove();
        }

        // read
        {
            File file;
            file.create(filePath, File::OpenMode::BinRead);
            file.read(&text2);

            xTEST_EQ(text1.size(), text2.size());
            xTEST_EQ(true, text1 == text2);
        }
    }

    xTEST_CASE("readLine, writeLine")
    {
        std::tstring_t buffWrite = xT("<test1><test2><test3><...>");
        std::tstring_t buffRead  = xT("");

        // writeLine
        {
            File file;
            file.create(filePath, File::OpenMode::Write);
            file.writeLine(buffWrite);
        }

        // readLine
        {
            File file;
            file.create(filePath, File::OpenMode::Read);
            file.readLine(&buffRead, 1024);
        }

        xTEST_EQ(buffWrite.size(), buffRead.size());
        xTEST_EQ(buffWrite,        buffRead);
    }

    xTEST_CASE("writeChar, readChar, ungetChar")
    {
        ctchar_t ch = xT('W');

        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.writeChar(ch);
        file.setPosition(0, File::PointerPosition::Begin);

        m_chRv = file.readChar();
        xTEST_EQ(ch, m_chRv);

        file.setPosition(0, File::PointerPosition::Begin);
        file.writeChar(ch);

        file.setPosition(0, File::PointerPosition::Begin);
        file.ungetChar(ch);
    }

    xTEST_CASE("clear")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.clear();
    }

    /*******************************************************************************
    *    formatted input/output
    *
    *******************************************************************************/

    xTEST_CASE("read")
    {
        std::ctstring_t testContent =
            xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            File file;
            file.create(filePath, File::OpenMode::CreateReadWrite);

            int_t iRv = file.write(testContent.c_str());
            xTEST_EQ(testContent.size(), size_t(iRv));
        }

        std::tstring_t content;

        {
            File file;
            file.create(filePath, File::OpenMode::Read);
            file.read(&content);
        }

        xTEST_EQ(testContent, content);
    }

    xTEST_CASE("write")
    {
        std::ctstring_t content = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467lsecfgsjk drbf");

        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        int_t iRv = file.write(xT("%s"), content.c_str());
        xTEST_EQ(content.size(), size_t(iRv));
    }

    xTEST_CASE("writeV")
    {
        struct Writer
        {
            static void_t
            doV(const File &file, cptr_ctchar_t format, ...)
            {
                va_list args;
                xVA_START(args, format);

                int_t iRv = file.writeV(format, args);
                xTEST_DIFF(- 1, iRv);

                xVA_END(args);
            };
        };

        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        Writer::doV(file, xT("%s"), xT("zzz"));
    }

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("locking")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.setSize(1024);
        file.locking(File::LockingMode::Lock, 10);
        file.locking(File::LockingMode::Unlock, 10);
    }

    xTEST_CASE("setPosition, position")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.setPosition(0, File::PointerPosition::Begin);

        long_t liRv = file.position();
        xTEST_EQ(0L, liRv);
    }

    xTEST_CASE("size")
	{
		clonglong_t newSize = 1024LL;

		File file;
		file.create(filePath, File::OpenMode::CreateReadWrite);
		file.setSize(newSize);

		clonglong_t llSize = file.size();
		xTEST_EQ(newSize, llSize);
	}

    xTEST_CASE("resize")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.setSize(0);
    }

    xTEST_CASE("setVBuff")
    {
        std::string buffRead;  buffRead.resize(BUFSIZ);

        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.setVBuff(File::BufferingMode::Full, &buffRead.at(0), buffRead.size() * 2);
    }

    /*******************************************************************************
    *    Error-handling:
    *
    *******************************************************************************/

    xTEST_CASE("isEmpty")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        m_bRv = file.isEmpty();
        xTEST_EQ(m_bRv, true);

        m_iRv = file.write(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRv);

        m_bRv = file.isEmpty();
        xTEST_EQ(m_bRv, false);

        file.clear();

        m_bRv = file.isEmpty();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("isEof")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        m_bRv = file.isEof();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isError")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);

        m_bRv = file.isError();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("clearError")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.clearError();
    }

    /*******************************************************************************
    *    closing
    *
    *******************************************************************************/

    xTEST_CASE("flush")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.flush();

        m_bRv = file.get().isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("close")
    {
        File file;
        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.close();

        m_bRv = file.get().isValid();
        xTEST_EQ(m_bRv, false);
    }

    m_bRv = unit1();
    xCHECK_RET(!m_bRv, false);

    m_bRv = unitPrivate();
    xCHECK_RET(!m_bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Test_File::unit1()
{
	std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");

	/*******************************************************************************
	*   static
	*
	*******************************************************************************/

	xTEST_CASE("rename")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		File::textWrite(filePath, xT("Simple text"), File::OpenMode::Write);

		{
			File file;
			file.create(newFilePath, File::OpenMode::Write);
			file.remove();
		}

		{
			File file;
			file.create(filePath, File::OpenMode::Write);
			file.rename(newFilePath);
		}

		{
			File file;
			file.create(newFilePath, File::OpenMode::Write);
			file.remove();
		}
	}

	xTEST_CASE("copy")
	{
		std::ctstring_t sFilePathFrom = getData().tempDirPath + Const::slash() + xT("test_copy.txt");
		std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name.txt");

		{
			File file;
			file.create(sFilePathFrom, File::OpenMode::BinCreateReadWrite, false);
			file.setSize(1024 * 5);
		}

		{
			File file;
			file.create(sFilePathFrom, File::OpenMode::Write);
			file.copy(sFilePathTo, false);
		}

		m_bRv = FileInfo(sFilePathTo).isExists();
		xTEST(m_bRv);

		{
			File file;
			file.create(sFilePathTo, File::OpenMode::Write);
			file.remove();
		}

		{
			File file;
			file.create(sFilePathFrom, File::OpenMode::Write);
			file.copy(sFilePathTo, true);
		}
	}

	xTEST_CASE("move")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		File::textWrite(newFilePath, xT("Simple text"), File::OpenMode::Write);

		{
			File file;
			file.create(getData().tempDirPath + Const::slash() + newFilePath, File::OpenMode::Write);
			file.remove();
		}

		{
			File file;
			file.create(newFilePath, File::OpenMode::Write);
			file.move(getData().tempDirPath);
		}
	}

	xTEST_CASE("unlink")
	{
	#if xTEMP_DISABLED
		File file;
		file.create(newFilePath, File::OpenMode::Write);
		m_bRv = file.unlink();
		xTEST(m_bRv);
	#endif
	}

	xTEST_CASE("clear")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		{
			File file;
			file.create(newFilePath, File::OpenMode::Write);
			file.clear();
		}
	}

	xTEST_CASE("remove")
	{
		std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		{
			File file;
			file.create(newFilePath, File::OpenMode::Write);
			file.remove();
			file.remove();
		}
	}

	xTEST_CASE("tryRemove")
	{
		std::ctstring_t tryfilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

		for (size_t i = 0; i < 20; ++ i) {
			if (i < 10) {
				File file;
				file.create(tryfilePath, File::OpenMode::CreateReadWrite);
				file.setSize(1024);
				file.locking(File::LockingMode::Lock, 10);

				{
					File lockedFile;
					lockedFile.create(tryfilePath, File::OpenMode::Write);
					lockedFile.tryRemove(10, 2000);
				}

				file.locking(File::LockingMode::Unlock, 10);
			} else {
				File file;
				file.create(tryfilePath, File::OpenMode::Write);
				file.tryRemove(10, 33);
			}
		}
	}

	xTEST_CASE("wipe")
	{
		{
			File file;
			file.create(filePath, File::OpenMode::BinCreateReadWrite);
			m_iRv = file.write(xT("0123456789"));
			xTEST_DIFF(- 1, m_iRv);
		}

		for (size_t i = 0; i < 3; ++ i) {
			File file;
			file.create(filePath, File::OpenMode::Write);
			file.wipe(10);
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
			File file;
			file.create(filePath, File::OpenMode::CreateReadWrite);

			for (size_t i = 0; i < 7; ++ i) {
				file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
			}
		}

		File::textRead(filePath, &content);
		File::textWrite(filePath, content, File::OpenMode::Write);

		std::tstring_t str;
		File::textRead(filePath, &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// empty content
		std::tstring_t content;

		{
			File file;
			file.create(filePath, File::OpenMode::CreateReadWrite);
		}

		File::textRead(filePath, &content);
		File::textWrite(filePath, content, File::OpenMode::Write);

		std::tstring_t str;
		File::textRead(filePath, &str);

		xTEST_EQ(content.size(), str.size());
		xTEST_EQ(content, str);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// std::vector
		std::vec_tstring_t content;

		{
			File file;
			file.create(filePath, File::OpenMode::CreateReadWrite);

			for (size_t i = 0; i < 10; ++ i) {
				file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
			}
		}

		File::textRead(filePath, &content);
		File::textWrite(filePath, content, File::OpenMode::Write);

		std::vec_tstring_t vec;
		File::textRead(filePath, &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST_EQ(true, content == vec);
	}

	xTEST_CASE("textRead, textWrite")
	{
		//  empty content
		std::vec_tstring_t content;

		{
			File file;
			file.create(filePath, File::OpenMode::CreateReadWrite);
		}

		File::textRead(filePath, &content);
		File::textWrite(filePath, content, File::OpenMode::Write);

		std::vec_tstring_t vec;
		File::textRead(filePath, &vec);

		xTEST_EQ(content.size(), vec.size());
		xTEST_EQ(true, content == vec);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// std::vector
		std::map_tstring_t content;
		std::ctstring_t    separator = Const::equal();

		{
			File file;
			file.create(filePath, File::OpenMode::CreateReadWrite);

			for (size_t i = 0; i < 10; ++ i) {
				file.writeLine(xT("asducfgnoawifg") + separator + xT("umoaeriuatgmoi"));
			}
		}

		File::textRead(filePath, separator, &content);
		File::textWrite(filePath, separator, content, File::OpenMode::Write);

		std::map_tstring_t msStr;
		File::textRead(filePath, separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST_EQ(true, content == msStr);
	}

	xTEST_CASE("textRead, textWrite")
	{
		// empty content
		std::map_tstring_t content;
		std::ctstring_t    separator = Const::equal();

		{
			File file;

			file.create(filePath, File::OpenMode::CreateReadWrite);
		}

		File::textRead(filePath, separator, &content);
		File::textWrite(filePath, separator, content, File::OpenMode::Write);

		std::map_tstring_t msStr;
		File::textRead(filePath, separator, &msStr);

		xTEST_EQ(content.size(), msStr.size());
		xTEST_EQ(true, content == msStr);
	}

	xTEST_CASE("binRead, binWrite")
	{
		// binary
		std::ustring_t content;   content.resize(1024 * 5);

		{
			File file;
			file.create(filePath, File::OpenMode::BinCreateReadWrite);

			m_iRv = file.write(xT("0123456789"));
			xTEST_LESS(0, m_iRv);

			file.setSize(1024 * 5);

			m_iRv = file.write(xT("0123456789"));
			xTEST_LESS(0, m_iRv);
		}

		File::binWrite(filePath, content, File::OpenMode::BinWrite);

		std::ustring_t str;
		File::binRead(filePath, &str);

		xTEST(content == str);
	}

	xTEST_CASE("binRead, binWrite")
	{
		// empty content
		std::ustring_t content;

		{
			File file;
			file.create(filePath, File::OpenMode::BinCreateReadWrite);
		}

		File::binWrite(filePath, content, File::OpenMode::BinWrite);

		std::ustring_t str;
		File::binRead(filePath, &str);

		xTEST_EQ(true, content == str);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Test_File::unitPrivate()
{
#if cmOPTION_TEST_PRIVATE
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");

    xTEST_CASE("_nativeHandle")
    {
        File file;
        file.create(filePath, File::OpenMode::Read);

        m_iRv = File::_nativeHandle( file.get() );
        xTEST_DIFF(m_iRv, - 1);
    }

    xTEST_CASE("_stdHandle")
    {
        // TEST: File::_stdHandle

    #if xTODO
        const File::OpenMode mode = File::OpenMode::OpenReadWrite;

        File file;
        file.create(filePath, mode, true);

        int_t nativeFile = File::_nativeHandle(file.get());
        xTEST_DIFF((int_t)File::etError, nativeFile);

        FILE *stdFile = File::_stdHandle(nativeFile, mode);
        xTEST_PTR(stdFile);
    #endif
    }

    xTEST_CASE("_openMode")
    {
        std::vector< std::pair<File::OpenMode, std::tstring_t>> data;

        data.push_back( std::make_pair(File::OpenMode::Read,               xT("r")) );
        data.push_back( std::make_pair(File::OpenMode::Write,              xT("w")) );
        data.push_back( std::make_pair(File::OpenMode::Append,             xT("a")) );
        data.push_back( std::make_pair(File::OpenMode::OpenReadWrite,      xT("r+")) );
        data.push_back( std::make_pair(File::OpenMode::CreateReadWrite,    xT("w+")) );
        data.push_back( std::make_pair(File::OpenMode::OpenReadAppend,     xT("a+")) );

        data.push_back( std::make_pair(File::OpenMode::BinRead,            xT("rb")) );
        data.push_back( std::make_pair(File::OpenMode::BinWrite,           xT("wb")) );
        data.push_back( std::make_pair(File::OpenMode::BinAppend,          xT("ab")) );
        data.push_back( std::make_pair(File::OpenMode::BinOpenReadWrite,   xT("rb+")) );
        data.push_back( std::make_pair(File::OpenMode::BinCreateReadWrite, xT("wb+")) );
        data.push_back( std::make_pair(File::OpenMode::BinOpenReadAppend,  xT("ab+")) );

        for (size_t i = 0; i < data.size(); ++ i) {
            File::OpenMode omRes = data.at(i).first;
            std::tstring_t sRv   = data.at(i).second;

            m_sRv = File::_openMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
