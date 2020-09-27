/**
 * \file   Test_File.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

class Test_FileIO :
    public Unit
{
public:
           Test_FileIO() {}

    bool_t unit() override;
};
//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileIO)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileIO::unit()
{
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");

    /*******************************************************************************
    *    prepare
    *
    *******************************************************************************/

    {
        File(filePath).remove();
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
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadWrite);
            file.close();
            file.open(FileIO::OpenMode::ReadWrite);
            file.close();
        }
    }

    xTEST_CASE("create")
    {
        FileIO file(filePath);

        for (size_t i = 0; i < 1; ++ i) {
            file.open(FileIO::OpenMode::ReadWrite);
        }
    }

    // TDOO: test
    xTEST_CASE("attach")
    {
    #if xTEMP_DISABLED
        HandleStdFile handle(stdout);

        std::ctstring_t filePath;

        FileIO file;
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
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);

        FILE *stdFile = file.get().get();
        xTEST_PTR(stdFile);
    }

    xTEST_CASE("path")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
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
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadWrite);
            m_stRv = file.write((cptr_cvoid_t)&buffWrite.at(0), buffWrite.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        // read
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadOnly);
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
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinWrite);
            file.write(content);
        }

        // read
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadOnly);
            file.read(&text1);
        }

        // write
        {
            std::ctstring_t dataNewPath = getData().tempDirPath + Const::slash() + xT("DataNew.dat");

            FileIO file(dataNewPath);
            file.open(FileIO::OpenMode::BinWrite);
            file.write(text1);

            File(dataNewPath).remove();
        }

        // read
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadOnly);
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
            FileIO file(filePath);
            file.open(FileIO::OpenMode::Write);
            file.writeLine(buffWrite);
        }

        // readLine
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadOnly);
            file.readLine(&buffRead, 1024);
        }

        xTEST_EQ(buffWrite.size(), buffRead.size());
        xTEST_EQ(buffWrite,        buffRead);
    }

    xTEST_CASE("writeChar, readChar, ungetChar")
    {
        ctchar_t ch = xT('W');

        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.writeChar(ch);
        file.setPosition(0, FileIO::PointerPosition::Begin);

        m_chRv = file.readChar();
        xTEST_EQ(ch, m_chRv);

        file.setPosition(0, FileIO::PointerPosition::Begin);
        file.writeChar(ch);

        file.setPosition(0, FileIO::PointerPosition::Begin);
        file.ungetChar(ch);
    }

    xTEST_CASE("clear")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
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
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadWrite);

            int_t iRv = file.write(testContent.c_str());
            xTEST_EQ(testContent.size(), size_t(iRv));
        }

        std::tstring_t content;

        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadOnly);
            file.read(&content);
        }

        xTEST_EQ(testContent, content);
    }

    xTEST_CASE("write")
    {
        std::ctstring_t content = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467lsecfgsjk drbf");

        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);

        int_t iRv = file.write(xT("%s"), content.c_str());
        xTEST_EQ(content.size(), size_t(iRv));
    }

    xTEST_CASE("writeV")
    {
        struct Writer
        {
            static void_t
            doV(const FileIO &file, cptr_ctchar_t format, ...)
            {
                va_list args;
                xVA_START(args, format);

                int_t iRv = file.writeV(format, args);
                xTEST_DIFF(- 1, iRv);

                xVA_END(args);
            };
        };

        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        Writer::doV(file, xT("%s"), xT("zzz"));
    }

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("locking")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.setSize(1024);
        file.locking(FileIO::LockingMode::Lock, 10);
        file.locking(FileIO::LockingMode::Unlock, 10);
    }

    xTEST_CASE("setPosition, position")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.setPosition(0, FileIO::PointerPosition::Begin);

        long_t liRv = file.position();
        xTEST_EQ(0L, liRv);
    }

    xTEST_CASE("size")
	{
		clonglong_t newSize = 1024LL;

		FileIO file(filePath);
		file.open(FileIO::OpenMode::ReadWrite);
		file.setSize(newSize);

		clonglong_t llSize = file.size();
		xTEST_EQ(newSize, llSize);
	}

    xTEST_CASE("resize")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.setSize(0);
    }

    xTEST_CASE("setVBuff")
    {
        std::string buffRead;  buffRead.resize(BUFSIZ);

        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.setVBuff(FileIO::BufferingMode::Full, &buffRead.at(0), buffRead.size() * 2);
    }

    /*******************************************************************************
    *    Error-handling:
    *
    *******************************************************************************/

    xTEST_CASE("isEmpty")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);

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
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);

        m_bRv = file.isEof();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isError")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);

        m_bRv = file.isError();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("clearError")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.clearError();
    }

    /*******************************************************************************
    *    closing
    *
    *******************************************************************************/

    xTEST_CASE("flush")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.flush();

        m_bRv = file.get().isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("close")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.close();

        m_bRv = file.get().isValid();
        xTEST_EQ(m_bRv, false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
