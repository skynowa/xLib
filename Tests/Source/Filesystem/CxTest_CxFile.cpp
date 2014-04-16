/**
 * \file   CxTest_CxFile.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFile.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFile::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath() + CxConst::slash() + xT("Test.txt");


    /*******************************************************************************
    *    prepare
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::remove", a_caseLoops)
    {
        CxFile::remove(filePath);
    }


    /*******************************************************************************
    *    open, get
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::create", a_caseLoops)
    {
        CxFile file;

        for (size_t i = 0; i < 1; ++ i) {
            file.create(filePath, CxFile::omCreateReadWrite, true);
        }
    }

    xTEST_CASE("CxFile::reopen", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        for (size_t i = 0; i < 7; ++ i) {
            file.reopen(filePath, CxFile::omOpenReadWrite, true);
        }
    }

    xTEST_CASE("CxFile::attach", a_caseLoops)
    {
        CxFile file;

        file.attach(stdout);

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);

        FILE *stdFile = file.detach();
        xTEST_PTR(stdFile);
        xTEST_EQ(stdout, stdFile);
    }

    xTEST_CASE("CxFile::get", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        FILE *stdFile = file.get();
        xTEST_PTR(stdFile);
    }

    xTEST_CASE("CxFile::path", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        m_sRv = file.path();
        xTEST_EQ(filePath, m_sRv);
    }


    /*******************************************************************************
    *    read, write
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::write read", a_caseLoops)
    {
        std::tstring_t buffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring_t buffRead  = xT("");       buffRead.resize(buffWrite.size());

        // write
        {
            CxFile file;

            file.create(filePath, CxFile::omBinCreateReadWrite, true);
            m_stRv = file.write((cvoid_t *)&buffWrite.at(0), buffWrite.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        // read
        {
            CxFile file;

            file.create(filePath, CxFile::omBinRead, true);
            m_stRv = file.read(&buffRead.at(0), buffRead.size() * sizeof(std::tstring_t::value_type));
            xUNUSED(m_stRv);
        }

        xTEST_EQ(buffWrite, buffRead);
    }

    xTEST_CASE("CxFile::write read", a_caseLoops)
    {
        std::custring_t content(10, 5);

        std::ustring_t  text1;
        std::ustring_t  text2;

        // write
        {
            CxFile file;

            file.create(filePath, CxFile::omBinWrite, true);
            file.write(content);
        }

        // read
        {
            CxFile file;

            file.create(filePath, CxFile::omBinRead, true);
            file.read(&text1);
        }

        // write
        {
            CxFile file;

            file.create(tempDirPath() + CxConst::slash() + xT("DataNew.dat"), CxFile::omBinWrite, true);
            file.write(text1);
        }

        // read
        {
            CxFile file;

            file.create(filePath, CxFile::omBinRead, true);
            file.read(&text2);

            xTEST_EQ(text1.size(), text2.size());
            xTEST_EQ(true, text1 == text2);
        }
    }

    xTEST_CASE("CxFile::readLine writeLine", a_caseLoops)
    {
        std::tstring_t buffWrite = xT("<test1><test2><test3><...>");
        std::tstring_t buffRead  = xT("");

        // writeLine
        {
            CxFile file;

            file.create(filePath, CxFile::omWrite, true);
            file.writeLine(buffWrite);
        }

        // readLine
        {
            CxFile file;

            file.create(filePath, CxFile::omRead, true);
            file.readLine(&buffRead, 1024);
        }

        xTEST_EQ(buffWrite.size(), buffRead.size());
        xTEST_EQ(buffWrite,        buffRead);
    }

    xTEST_CASE("CxFile::writeChar readChar ungetChar", a_caseLoops)
    {
        ctchar_t ch = xT('W');

        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.writeChar(ch);
        file.setPosition(0, CxFile::ppBegin);

        m_chRv = file.readChar();
        xTEST_EQ(ch, m_chRv);

        file.setPosition(0, CxFile::ppBegin);
        file.writeChar(ch);

        file.setPosition(0, CxFile::ppBegin);
        file.ungetChar(ch);
    }

    xTEST_CASE("CxFile::clear", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.clear();
    }

    /*******************************************************************************
    *    times
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::time CxFile::setTime", a_caseLoops)
    {
        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, false);
        }

        const time_t create   = 1319714265;
        const time_t acess    = 1319714452;
        const time_t modified = 1319714452;

        CxFile::setTime(filePath, create, acess, modified);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        CxFile::time(filePath, &tmCreate, &tmAccess, &tmModified);

    #if   xOS_ENV_WIN
        xTEST_EQ(create, tmCreate);
    #elif xOS_ENV_UNIX
        xUNUSED(tmCreate);
    #endif

        xTEST_EQ(acess,    tmAccess);
        xTEST_EQ(modified, tmModified);
    }


    /*******************************************************************************
    *    formatted input/output
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::read", a_caseLoops)
    {
        std::ctstring_t testContent =
            xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);

            int_t iRv = file.write(testContent.c_str());
            xTEST_EQ(testContent.size(), size_t(iRv));
        }

        std::tstring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omRead, true);
            file.read(&content);
        }

        xTEST_EQ(testContent, content);
    }

    xTEST_CASE("CxFile::write", a_caseLoops)
    {
        std::ctstring_t content = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467lsecfgsjk drbf");

        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        int_t iRv = file.write(xT("%s"), content.c_str());
        xTEST_EQ(content.size(), size_t(iRv));
    }

    xTEST_CASE("CxFile::writeV", a_caseLoops)
    {
        struct Writer
        {
            static void_t
            doV(const CxFile &file, ctchar_t *format, ...)
            {
                va_list args;
                xVA_START(args, format);

                int_t iRv = file.writeV(format, args);
                xTEST_DIFF(- 1, iRv);

                xVA_END(args);
            };
        };

        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        Writer::doV(file, xT("%s"), xT("zzz"));
    }

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::locking", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.resize(1024);
        file.locking(CxFile::lmLock, 10);
        file.locking(CxFile::lmUnlock, 10);
    }

    xTEST_CASE("CxFile::setPosition getPosition", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.setPosition(0, CxFile::ppBegin);

        long_t liRv = file.position();
        xTEST_EQ(0L, liRv);
    }

    xTEST_CASE("CxFile::getSize", a_caseLoops)
    {
        clonglong_t newSize = 1024LL;

        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.resize(newSize);

        longlong_t llSize = file.size();
        xTEST_EQ(newSize, llSize);
    }

    xTEST_CASE("CxFile::resize", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.resize(0);
    }

    xTEST_CASE("CxFile::setVBuff", a_caseLoops)
    {
        std::string buffRead;       buffRead.resize(1024);

        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.setVBuff(&buffRead.at(0), CxFile::bmFull, buffRead.size() * 2);
    }

    xTEST_CASE("CxFile::setMode", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            file.setMode(CxFile::tmBinary);
            xTEST_EQ(m_bRv, true);
        #elif xOS_ENV_UNIX
            // TEST: CxFile::setMode()
        #endif
    }

    xTEST_CASE("CxFile::setMode", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            file.setMode(CxFile::tmText);
        #elif xOS_ENV_UNIX
            // TEST: CxFile::setMode()
        #endif
    }


    /*******************************************************************************
    *    Error-handling:
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::isValid", a_caseLoops)
    {
        CxFile file;

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, false);

        file.create(filePath, CxFile::omCreateReadWrite, true);

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);

        file.close();
    }

    xTEST_CASE("CxFile::isOpen", a_caseLoops)
    {
        CxFile file;

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, false);

        file.create(filePath, CxFile::omCreateReadWrite, true);

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, true);

        file.close();

        m_bRv = file.isOpen();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxFile::isEmpty", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

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

    xTEST_CASE("CxFile::isEof", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        m_bRv = file.isEof();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxFile::isError", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);

        m_bRv = file.isError();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxFile::errorClear", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.errorClear();
    }

    /*******************************************************************************
    *    closing
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::flush", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.flush();

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("CxFile::close", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omCreateReadWrite, true);
        file.close();

        m_bRv = file.isValid();
        xTEST_EQ(m_bRv, false);
    }

    // vUnit1
    unit1(a_caseLoops);

    // vUnitPrivate
    unitPrivate(a_caseLoops);
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
CxTest_CxFile::unit1(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath() + CxConst::slash() + xT("Test.txt");

    /*******************************************************************************
    *   static
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::isFile", a_caseLoops)
    {
        m_bRv = CxFile::isFile(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = CxFile::isFile(tempDirPath());
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxFile::isExists", a_caseLoops)
    {
        m_bRv = CxFile::isExists(filePath);
        xTEST_EQ(m_bRv, true);

        m_bRv = CxFile::isExists(filePath + xT("wrong_path"));
        xTEST_EQ(m_bRv, false);

        m_bRv = CxFile::isExists(tempDirPath());
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("CxFile::isExistsEx", a_caseLoops)
    {
        m_sRv = CxFile::isExistsEx(filePath);
        xTEST_EQ(true,  CxFile::isExists(filePath));
        xTEST_EQ(false, CxFile::isExists(m_sRv));
    }

    xTEST_CASE("CxFile::access", a_caseLoops)
    {
        CxFile::access(filePath, CxFile::amExistence);
    }

    xTEST_CASE("CxFile::chmod", a_caseLoops)
    {
        CxFile::chmod(filePath, CxFile::pmReadWrite);
    }

    xTEST_CASE("CxFile::rename", a_caseLoops)
    {
        std::ctstring_t newFilePath = tempDirPath() + CxConst::slash() + xT("New.Test.txt");

        CxFile::textWrite(filePath, xT("Simple text"), CxFile::omWrite);
        CxFile::remove(newFilePath);
        CxFile::rename(filePath, newFilePath);
        CxFile::remove(newFilePath);
    }

    xTEST_CASE("CxFile::lines", a_caseLoops)
    {
        culonglong_t cullLinesNum = 17;
        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                file.writeLine( CxString::cast(i) );
            }
        }

        ulonglong_t linesNum = CxFile::lines(filePath);
        xTEST_EQ(cullLinesNum, linesNum);
    }

    xTEST_CASE("CxFile::copy", a_caseLoops)
    {
        std::ctstring_t sFilePathFrom = tempDirPath() + CxConst::slash() + xT("test_copy.txt");
        std::ctstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile file;

            file.create(sFilePathFrom, CxFile::omBinCreateReadWrite, false);
            file.resize(1024 * 5);
        }

        CxFile::copy(sFilePathFrom, sFilePathTo, false);

        m_bRv = CxFile::isExists(sFilePathTo);
        xTEST_EQ(m_bRv, true);

        CxFile::remove(sFilePathTo);
        CxFile::copy(sFilePathFrom, sFilePathTo, true);
    }

    xTEST_CASE("CxFile::move", a_caseLoops)
    {
        std::ctstring_t newFilePath = tempDirPath() + CxConst::slash() + xT("New.Test.txt");

        CxFile::textWrite(newFilePath, xT("Simple text"), CxFile::omWrite);
        CxFile::remove(tempDirPath() + CxConst::slash() + newFilePath);
        CxFile::move(newFilePath, tempDirPath());
    }

    xTEST_CASE("CxFile::unlink", a_caseLoops)
    {
        #if xTEMP_DISABLED
            m_bRv = CxFile::unlink(newFilePath);
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("CxFile::clear", a_caseLoops)
    {
        std::ctstring_t newFilePath = tempDirPath() + CxConst::slash() + xT("New.Test.txt");

        CxFile::clear(newFilePath);
    }

    xTEST_CASE("CxFile::remove", a_caseLoops)
    {
        std::ctstring_t newFilePath = tempDirPath() + CxConst::slash() + xT("New.Test.txt");

        CxFile::remove(newFilePath);
        CxFile::remove(newFilePath);
    }

    xTEST_CASE("CxFile::tryRemove", a_caseLoops)
    {
        std::ctstring_t tryfilePath = tempDirPath() + CxConst::slash() + xT("New.Test.txt");

        for (size_t i = 0; i < 20; ++ i) {
            if (i < 10) {
                CxFile file;

                file.create(tryfilePath, CxFile::omCreateReadWrite, true);
                file.resize(1024);
                file.locking(CxFile::lmLock, 10);

                CxFile::tryRemove(tryfilePath, 10, 2000);
                file.locking(CxFile::lmUnlock, 10);
            } else {
                CxFile::tryRemove(tryfilePath, 10, 33);
            }
        }
    }

    xTEST_CASE("CxFile::wipe", a_caseLoops)
    {
        {
            CxFile file;

            file.create(filePath, CxFile::omBinCreateReadWrite, true);
            m_iRv = file.write(xT("0123456789"));
            xTEST_DIFF(- 1, m_iRv);
        }

        for (size_t i = 0; i < 3; ++ i) {
            CxFile::wipe(filePath, 10);
        }
    }


    /*******************************************************************************
    *   static: utils
    *
    *******************************************************************************/

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        std::tstring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 7; ++ i) {
                file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::textRead(filePath, &content);
        CxFile::textWrite(filePath, content, CxFile::omWrite);

        std::tstring_t str;
        CxFile::textRead(filePath, &str);

        xTEST_EQ(content.size(), str.size());
        xTEST_EQ(content, str);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // empty content
        std::tstring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(filePath, &content);
        CxFile::textWrite(filePath, content, CxFile::omWrite);

        std::tstring_t str;
        CxFile::textRead(filePath, &str);

        xTEST_EQ(content.size(), str.size());
        xTEST_EQ(content, str);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // std::vector
        std::vec_tstring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                file.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::textRead(filePath, &content);
        CxFile::textWrite(filePath, content, CxFile::omWrite);

        std::vec_tstring_t vec;
        CxFile::textRead(filePath, &vec);

        xTEST_EQ(content.size(), vec.size());
        xTEST_EQ(true, content == vec);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        //  empty content
        std::vec_tstring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(filePath, &content);
        CxFile::textWrite(filePath, content, CxFile::omWrite);

        std::vec_tstring_t vec;
        CxFile::textRead(filePath, &vec);

        xTEST_EQ(content.size(), vec.size());
        xTEST_EQ(true, content == vec);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // std::vector
        std::map_tstring_t content;
        std::ctstring_t    separator = CxConst::equal();

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                file.writeLine(xT("asducfgnoawifg") + separator + xT("umoaeriuatgmoi"));
            }
        }

        CxFile::textRead(filePath, separator, &content);
        CxFile::textWrite(filePath, separator, content, CxFile::omWrite);

        std::map_tstring_t msStr;
        CxFile::textRead(filePath, separator, &msStr);

        xTEST_EQ(content.size(), msStr.size());
        xTEST_EQ(true, content == msStr);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // empty content
        std::map_tstring_t content;
        std::ctstring_t    separator = CxConst::equal();

        {
            CxFile file;

            file.create(filePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(filePath, separator, &content);
        CxFile::textWrite(filePath, separator, content, CxFile::omWrite);

        std::map_tstring_t msStr;
        CxFile::textRead(filePath, separator, &msStr);

        xTEST_EQ(content.size(), msStr.size());
        xTEST_EQ(true, content == msStr);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // binary
        std::ustring_t content;   content.resize(1024 * 5);

        {
            CxFile file;

            file.create(filePath, CxFile::omBinCreateReadWrite, true);

            m_iRv = file.write(xT("0123456789"));
            xTEST_LESS(0, m_iRv);

            file.resize(1024 * 5);

            m_iRv = file.write(xT("0123456789"));
            xTEST_LESS(0, m_iRv);
        }

        CxFile::binWrite(filePath, content);

        std::ustring_t str;
        CxFile::binRead(filePath, &str);

        xTEST_EQ(true, content == str);
    }

    xTEST_CASE("CxFile::textRead textWrite", a_caseLoops)
    {
        // empty content
        std::ustring_t content;

        {
            CxFile file;

            file.create(filePath, CxFile::omBinCreateReadWrite, true);
        }

        CxFile::binWrite(filePath, content);

        std::ustring_t str;
        CxFile::binRead(filePath, &str);

        xTEST_EQ(true, content == str);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
CxTest_CxFile::unitPrivate(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if xHAVE_TEST_PRIVATE
    std::ctstring_t filePath = tempDirPath() + CxConst::slash() + xT("Test.txt");

    xTEST_CASE("CxFile::_nativeHandle", a_caseLoops)
    {
        CxFile file;

        file.create(filePath, CxFile::omRead, true);

        m_iRv = CxFile::_nativeHandle( file.get() );
        xTEST_DIFF((int_t)CxFile::etError, m_iRv);
    }

    xTEST_CASE("CxFile::_stdHandle", a_caseLoops)
    {
        // TEST: CxFile::_stdHandle

    #if xTODO
        const CxFile::ExOpenMode mode = CxFile::omOpenReadWrite;

        CxFile file;

        file.create(filePath, mode, true);

        int_t nativeFile = CxFile::_nativeHandle(file.get());
        xTEST_DIFF((int_t)CxFile::etError, nativeFile);

        FILE *stdFile = CxFile::_stdHandle(nativeFile, mode);
        xTEST_PTR(stdFile);
    #endif
    }

    xTEST_CASE("CxFile::_openMode", a_caseLoops)
    {
        std::vector< std::pair<CxFile::ExOpenMode, std::tstring_t> > data;

        data.push_back( std::make_pair(CxFile::omRead,               xT("r")) );
        data.push_back( std::make_pair(CxFile::omWrite,              xT("w")) );
        data.push_back( std::make_pair(CxFile::omAppend,             xT("a")) );
        data.push_back( std::make_pair(CxFile::omOpenReadWrite,      xT("r+")) );
        data.push_back( std::make_pair(CxFile::omCreateReadWrite,    xT("w+")) );
        data.push_back( std::make_pair(CxFile::omOpenReadAppend,     xT("a+")) );

        data.push_back( std::make_pair(CxFile::omBinRead,            xT("rb")) );
        data.push_back( std::make_pair(CxFile::omBinWrite,           xT("wb")) );
        data.push_back( std::make_pair(CxFile::omBinAppend,          xT("ab")) );
        data.push_back( std::make_pair(CxFile::omBinOpenReadWrite,   xT("rb+")) );
        data.push_back( std::make_pair(CxFile::omBinCreateReadWrite, xT("wb+")) );
        data.push_back( std::make_pair(CxFile::omBinOpenReadAppend,  xT("ab+")) );

        for (size_t i = 0; i < data.size(); ++ i) {
            CxFile::ExOpenMode omRes = data.at(i).first;
            std::tstring_t     sRv   = data.at(i).second;

            m_sRv = CxFile::_openMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif
}
//-------------------------------------------------------------------------------------------------
