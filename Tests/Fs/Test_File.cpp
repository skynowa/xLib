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

    virtual bool_t unit();

private:
    bool_t         unit1();
    bool_t         unitPrivate();
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
        File::remove(filePath);
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

        m_sRv = file.path();
        xTEST_EQ(filePath, m_sRv);
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
            File file;

            file.create(getData().tempDirPath + Const::slash() + xT("DataNew.dat"), File::OpenMode::BinWrite);
            file.write(text1);
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
    *    times
    *
    *******************************************************************************/

    xTEST_CASE("time, setTime")
    {
        {
            File file(false);
            file.create(filePath, File::OpenMode::CreateReadWrite);
        }

        const time_t create   = 1319714265;
        const time_t acess    = 1319714452;
        const time_t modified = 1319714452;

        File::setTime(filePath, create, acess, modified);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        File::time(filePath, &tmCreate, &tmAccess, &tmModified);

    #if   xENV_WIN
        xTEST_EQ(create, tmCreate);
    #elif xENV_UNIX
        xUNUSED(tmCreate);
    #endif

        xTEST_EQ(acess,    tmAccess);
        xTEST_EQ(modified, tmModified);
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
        file.resize(1024);
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
        file.resize(newSize);

        longlong_t llSize = file.size();
        xTEST_EQ(newSize, llSize);
    }

    xTEST_CASE("resize")
    {
        File file;

        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.resize(0);
    }

    xTEST_CASE("setVBuff")
    {
        std::string buffRead;       buffRead.resize(1024);

        File file;

        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.setVBuff(&buffRead.at(0), File::BufferingMode::Full, buffRead.size() * 2);
    }

    xTEST_CASE("setMode")
    {
        File file;

        file.create(filePath, File::OpenMode::CreateReadWrite);

    #if   xENV_WIN
        file.setMode(File::Binary);
        xTEST_EQ(m_bRv, true);
    #elif xENV_UNIX
        // TEST: File::setMode()
    #endif
    }

    xTEST_CASE("setMode")
    {
        File file;

        file.create(filePath, File::OpenMode::CreateReadWrite);

    #if   xENV_WIN
        file.setMode(File::Text);
    #elif xENV_UNIX
        // TEST: File::setMode()
    #endif
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

    xTEST_CASE("errorClear")
    {
        File file;

        file.create(filePath, File::OpenMode::CreateReadWrite);
        file.errorClear();
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

    xTEST_CASE("isFile")
    {
        m_bRv = File::isFile(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = File::isFile(getData().tempDirPath);
        xTEST_EQ(m_bRv, false);
    }

	xTEST_CASE("isExecutable")
	{
		const Data2<std::tstring_t, bool_t> datas[]
		{
			{filePath,         false},
			{getData().tempDirPath, false},
			{xT("wrong_path"), false},
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), true},
		#elif xENV_UNIX
			{xT("/bin/ls"),    true},
		#endif
			{xT("."),          false}
		};

		for (auto &it_data : datas) {
			m_bRv = File::isExecutable(it_data.test);
			xTEST_EQ(m_bRv, it_data.expect);
		}
	}

    xTEST_CASE("isExists")
    {
        m_bRv = File::isExists(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = File::isExists(filePath + xT("wrong_path"));
        xTEST_EQ(m_bRv, false);

        m_bRv = File::isExists(getData().tempDirPath);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isExistsEx")
    {
        m_sRv = File::isExistsEx(filePath);
        xTEST_EQ(true,  File::isExists(filePath));
        xTEST_EQ(false, File::isExists(m_sRv));
    }

    xTEST_CASE("access")
    {
        File::access(filePath, File::AccessMode::Existence);
    }

    xTEST_CASE("chmod")
    {
        File::chmod(filePath, File::PermissionMode::ReadWrite);
    }

    xTEST_CASE("rename")
    {
        std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

        File::textWrite(filePath, xT("Simple text"), File::OpenMode::Write);
        File::remove(newFilePath);
        File::rename(filePath, newFilePath);
        File::remove(newFilePath);
    }

    xTEST_CASE("lines")
    {
        culonglong_t cullLinesNum = 17;
        {
            File file;

            file.create(filePath, File::OpenMode::CreateReadWrite);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                file.writeLine( String::cast(i) );
            }
        }

        ulonglong_t linesNum = File::lines(filePath);
        xTEST_EQ(cullLinesNum, linesNum);
    }

    xTEST_CASE("copy")
    {
        std::ctstring_t sFilePathFrom = getData().tempDirPath + Const::slash() + xT("test_copy.txt");
        std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            File file(false);
            file.create(sFilePathFrom, File::OpenMode::BinCreateReadWrite);
            file.resize(1024 * 5);
        }

        File::copy(sFilePathFrom, sFilePathTo, false);

        m_bRv = File::isExists(sFilePathTo);
        xTEST_EQ(m_bRv, true);

        File::remove(sFilePathTo);
        File::copy(sFilePathFrom, sFilePathTo, true);
    }

    xTEST_CASE("move")
    {
        std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

        File::textWrite(newFilePath, xT("Simple text"), File::OpenMode::Write);
        File::remove(getData().tempDirPath + Const::slash() + newFilePath);
        File::move(newFilePath, getData().tempDirPath);
    }

    xTEST_CASE("unlink")
    {
        #if xTEMP_DISABLED
            m_bRv = File::unlink(newFilePath);
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("clear")
    {
        std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

        File::clear(newFilePath);
    }

    xTEST_CASE("remove")
    {
        std::ctstring_t newFilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

        File::remove(newFilePath);
        File::remove(newFilePath);
    }

    xTEST_CASE("tryRemove")
    {
        std::ctstring_t tryfilePath = getData().tempDirPath + Const::slash() + xT("New.Test.txt");

        for (size_t i = 0; i < 20; ++ i) {
            if (i < 10) {
                File file;

                file.create(tryfilePath, File::OpenMode::CreateReadWrite);
                file.resize(1024);
                file.locking(File::LockingMode::Lock, 10);

                File::tryRemove(tryfilePath, 10, 2000);
                file.locking(File::LockingMode::Unlock, 10);
            } else {
                File::tryRemove(tryfilePath, 10, 33);
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
            File::wipe(filePath, 10);
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

            file.resize(1024 * 5);

            m_iRv = file.write(xT("0123456789"));
            xTEST_LESS(0, m_iRv);
        }

        File::binWrite(filePath, content);

        std::ustring_t str;
        File::binRead(filePath, &str);

        xTEST_EQ(true, content == str);
    }

    xTEST_CASE("binRead, binWrite")
    {
        // empty content
        std::ustring_t content;

        {
            File file;

            file.create(filePath, File::OpenMode::BinCreateReadWrite);
        }

        File::binWrite(filePath, content);

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
        std::vector< std::pair<File::OpenMode, std::tstring_t> > data;

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
            std::tstring_t     sRv   = data.at(i).second;

            m_sRv = File::_openMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
