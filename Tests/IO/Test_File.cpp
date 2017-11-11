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
    std::ctstring_t filePath = data.tempDirPath + Const::slash() + xT("Test.txt");
    std::cout << xTRACE_VAR(filePath) << std::endl;

    {
    #if 1
        File file;
        file.create(filePath, File::omCreateReadWrite);
        file.close();
        file.create(filePath, File::omCreateReadWrite);
        file.close();

        return false;
    #endif
    }

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

    xTEST_CASE("create")
    {
        File file;

        for (size_t i = 0; i < 1; ++ i) {
            file.create(filePath, File::omCreateReadWrite);
        }
    }

    xTEST_CASE("reopen")
    {
        File file;
        file.create(filePath, File::omCreateReadWrite);

        for (size_t i = 0; i < 7; ++ i) {
            file.reopen(filePath, File::omOpenReadWrite);
        }
    }

    xTEST_CASE("attach")
    {
        File file;
        file.attach(stdout, std::tstring_t());

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);

        FILE *stdFile = file.detach();
        xTEST_PTR(stdFile);
        xTEST_EQ(stdout, stdFile);
    }

    xTEST_CASE("get")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

        FILE *stdFile = file.get();
        xTEST_PTR(stdFile);
    }

    xTEST_CASE("path")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

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

            file.create(filePath, File::omBinCreateReadWrite);
            m_stRv = file.write((cptr_cvoid_t)&buffWrite.at(0), buffWrite.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        // read
        {
            File file;

            file.create(filePath, File::omBinRead);
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

            file.create(filePath, File::omBinWrite);
            file.write(content);
        }

        // read
        {
            File file;

            file.create(filePath, File::omBinRead);
            file.read(&text1);
        }

        // write
        {
            File file;

            file.create(data.tempDirPath + Const::slash() + xT("DataNew.dat"), File::omBinWrite);
            file.write(text1);
        }

        // read
        {
            File file;

            file.create(filePath, File::omBinRead);
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

            file.create(filePath, File::omWrite);
            file.writeLine(buffWrite);
        }

        // readLine
        {
            File file;

            file.create(filePath, File::omRead);
            file.readLine(&buffRead, 1024);
        }

        xTEST_EQ(buffWrite.size(), buffRead.size());
        xTEST_EQ(buffWrite,        buffRead);
    }

    xTEST_CASE("writeChar, readChar, ungetChar")
    {
        ctchar_t ch = xT('W');

        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.writeChar(ch);
        file.setPosition(0, File::ppBegin);

        m_chRv = file.readChar();
        xTEST_EQ(ch, m_chRv);

        file.setPosition(0, File::ppBegin);
        file.writeChar(ch);

        file.setPosition(0, File::ppBegin);
        file.ungetChar(ch);
    }

    xTEST_CASE("clear")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
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
            file.create(filePath, File::omCreateReadWrite);
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

            file.create(filePath, File::omCreateReadWrite);

            int_t iRv = file.write(testContent.c_str());
            xTEST_EQ(testContent.size(), size_t(iRv));
        }

        std::tstring_t content;

        {
            File file;

            file.create(filePath, File::omRead);
            file.read(&content);
        }

        xTEST_EQ(testContent, content);
    }

    xTEST_CASE("write")
    {
        std::ctstring_t content = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467lsecfgsjk drbf");

        File file;

        file.create(filePath, File::omCreateReadWrite);

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

        file.create(filePath, File::omCreateReadWrite);
        Writer::doV(file, xT("%s"), xT("zzz"));
    }

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("locking")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.resize(1024);
        file.locking(File::lmLock, 10);
        file.locking(File::lmUnlock, 10);
    }

    xTEST_CASE("setPosition, position")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.setPosition(0, File::ppBegin);

        long_t liRv = file.position();
        xTEST_EQ(0L, liRv);
    }

    xTEST_CASE("size")
    {
        clonglong_t newSize = 1024LL;

        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.resize(newSize);

        longlong_t llSize = file.size();
        xTEST_EQ(newSize, llSize);
    }

    xTEST_CASE("resize")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.resize(0);
    }

    xTEST_CASE("setVBuff")
    {
        std::string buffRead;       buffRead.resize(1024);

        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.setVBuff(&buffRead.at(0), File::bmFull, buffRead.size() * 2);
    }

    xTEST_CASE("setMode")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

    #if   xENV_WIN
        file.setMode(File::tmBinary);
        xTEST_EQ(m_bRv, true);
    #elif xENV_UNIX
        // TEST: File::setMode()
    #endif
    }

    xTEST_CASE("setMode")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

    #if   xENV_WIN
        file.setMode(File::tmText);
    #elif xENV_UNIX
        // TEST: File::setMode()
    #endif
    }


    /*******************************************************************************
    *    Error-handling:
    *
    *******************************************************************************/

    xTEST_CASE("isValid")
    {
        File file;

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, false);

        file.create(filePath, File::omCreateReadWrite);

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);

        file.close();
    }

    xTEST_CASE("isOpen")
    {
        File file;

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, false);

        file.create(filePath, File::omCreateReadWrite);

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, true);

        file.close();

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isEmpty")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

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

        file.create(filePath, File::omCreateReadWrite);

        m_bRv = file.isEof();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isError")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);

        m_bRv = file.isError();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("errorClear")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.errorClear();
    }

    /*******************************************************************************
    *    closing
    *
    *******************************************************************************/

    xTEST_CASE("flush")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.flush();

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("close")
    {
        File file;

        file.create(filePath, File::omCreateReadWrite);
        file.close();

        m_bRv = file.isValid();
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
    std::ctstring_t filePath = data.tempDirPath + Const::slash() + xT("Test.txt");

    /*******************************************************************************
    *   static
    *
    *******************************************************************************/

    xTEST_CASE("isFile")
    {
        m_bRv = File::isFile(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = File::isFile(data.tempDirPath);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isExists")
    {
        m_bRv = File::isExists(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = File::isExists(filePath + xT("wrong_path"));
        xTEST_EQ(m_bRv, false);

        m_bRv = File::isExists(data.tempDirPath);
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
        File::access(filePath, File::amExistence);
    }

    xTEST_CASE("chmod")
    {
        File::chmod(filePath, File::pmReadWrite);
    }

    xTEST_CASE("rename")
    {
        std::ctstring_t newFilePath = data.tempDirPath + Const::slash() + xT("New.Test.txt");

        File::textWrite(filePath, xT("Simple text"), File::omWrite);
        File::remove(newFilePath);
        File::rename(filePath, newFilePath);
        File::remove(newFilePath);
    }

    xTEST_CASE("lines")
    {
        culonglong_t cullLinesNum = 17;
        {
            File file;

            file.create(filePath, File::omCreateReadWrite);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                file.writeLine( String::cast(i) );
            }
        }

        ulonglong_t linesNum = File::lines(filePath);
        xTEST_EQ(cullLinesNum, linesNum);
    }

    xTEST_CASE("copy")
    {
        std::ctstring_t sFilePathFrom = data.tempDirPath + Const::slash() + xT("test_copy.txt");
        std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            File file(false);
            file.create(sFilePathFrom, File::omBinCreateReadWrite);
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
        std::ctstring_t newFilePath = data.tempDirPath + Const::slash() + xT("New.Test.txt");

        File::textWrite(newFilePath, xT("Simple text"), File::omWrite);
        File::remove(data.tempDirPath + Const::slash() + newFilePath);
        File::move(newFilePath, data.tempDirPath);
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
        std::ctstring_t newFilePath = data.tempDirPath + Const::slash() + xT("New.Test.txt");

        File::clear(newFilePath);
    }

    xTEST_CASE("remove")
    {
        std::ctstring_t newFilePath = data.tempDirPath + Const::slash() + xT("New.Test.txt");

        File::remove(newFilePath);
        File::remove(newFilePath);
    }

    xTEST_CASE("tryRemove")
    {
        std::ctstring_t tryfilePath = data.tempDirPath + Const::slash() + xT("New.Test.txt");

        for (size_t i = 0; i < 20; ++ i) {
            if (i < 10) {
                File file;

                file.create(tryfilePath, File::omCreateReadWrite);
                file.resize(1024);
                file.locking(File::lmLock, 10);

                File::tryRemove(tryfilePath, 10, 2000);
                file.locking(File::lmUnlock, 10);
            } else {
                File::tryRemove(tryfilePath, 10, 33);
            }
        }
    }

    xTEST_CASE("wipe")
    {
        {
            File file;

            file.create(filePath, File::omBinCreateReadWrite);
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

            file.create(filePath, File::omCreateReadWrite);

            for (size_t i = 0; i < 7; ++ i) {
                file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        File::textRead(filePath, &content);
        File::textWrite(filePath, content, File::omWrite);

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

            file.create(filePath, File::omCreateReadWrite);
        }

        File::textRead(filePath, &content);
        File::textWrite(filePath, content, File::omWrite);

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

            file.create(filePath, File::omCreateReadWrite);

            for (size_t i = 0; i < 10; ++ i) {
                file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        File::textRead(filePath, &content);
        File::textWrite(filePath, content, File::omWrite);

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

            file.create(filePath, File::omCreateReadWrite);
        }

        File::textRead(filePath, &content);
        File::textWrite(filePath, content, File::omWrite);

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

            file.create(filePath, File::omCreateReadWrite);

            for (size_t i = 0; i < 10; ++ i) {
                file.writeLine(xT("asducfgnoawifg") + separator + xT("umoaeriuatgmoi"));
            }
        }

        File::textRead(filePath, separator, &content);
        File::textWrite(filePath, separator, content, File::omWrite);

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

            file.create(filePath, File::omCreateReadWrite);
        }

        File::textRead(filePath, separator, &content);
        File::textWrite(filePath, separator, content, File::omWrite);

        std::map_tstring_t msStr;
        File::textRead(filePath, separator, &msStr);

        xTEST_EQ(content.size(), msStr.size());
        xTEST_EQ(true, content == msStr);
    }

    xTEST_CASE("textRead, textWrite")
    {
        // binary
        std::ustring_t content;   content.resize(1024 * 5);

        {
            File file;

            file.create(filePath, File::omBinCreateReadWrite);

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

    xTEST_CASE("textRead, textWrite")
    {
        // empty content
        std::ustring_t content;

        {
            File file;

            file.create(filePath, File::omBinCreateReadWrite);
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
    std::ctstring_t filePath = data.tempDirPath + Const::slash() + xT("Test.txt");

    xTEST_CASE("_nativeHandle")
    {
        File file;

        file.create(filePath, File::omRead);

        m_iRv = File::_nativeHandle( file.get() );
        xTEST_DIFF(m_iRv, - 1);
    }

    xTEST_CASE("_stdHandle")
    {
        // TEST: File::_stdHandle

    #if xTODO
        const File::OpenMode mode = File::omOpenReadWrite;

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

        data.push_back( std::make_pair(File::omRead,               xT("r")) );
        data.push_back( std::make_pair(File::omWrite,              xT("w")) );
        data.push_back( std::make_pair(File::omAppend,             xT("a")) );
        data.push_back( std::make_pair(File::omOpenReadWrite,      xT("r+")) );
        data.push_back( std::make_pair(File::omCreateReadWrite,    xT("w+")) );
        data.push_back( std::make_pair(File::omOpenReadAppend,     xT("a+")) );

        data.push_back( std::make_pair(File::omBinRead,            xT("rb")) );
        data.push_back( std::make_pair(File::omBinWrite,           xT("wb")) );
        data.push_back( std::make_pair(File::omBinAppend,          xT("ab")) );
        data.push_back( std::make_pair(File::omBinOpenReadWrite,   xT("rb+")) );
        data.push_back( std::make_pair(File::omBinCreateReadWrite, xT("wb+")) );
        data.push_back( std::make_pair(File::omBinOpenReadAppend,  xT("ab+")) );

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
