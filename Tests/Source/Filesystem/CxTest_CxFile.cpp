/**
 * \file   CxTest_CxFile.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFile.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>

//---------------------------------------------------------------------------
CxTest_CxFile::CxTest_CxFile() {

}
//---------------------------------------------------------------------------
CxTest_CxFile::~CxTest_CxFile() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxFile::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::remove", cullCaseLoops)
    {
        CxFile::remove(csFilePath);
    }


    /****************************************************************************
    *    open, get
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::create", cullCaseLoops)
    {
        CxFile F;

        for (size_t i = 0; i < 1; ++ i) {
            F.create(csFilePath, CxFile::omCreateReadWrite, true);
        }
    }

    xTEST_CASE("CxFile::reopen", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        for (size_t i = 0; i < 7; ++ i) {
            F.reopen(csFilePath, CxFile::omOpenReadWrite, true);
        }
    }

    xTEST_CASE("CxFile::attach", cullCaseLoops)
    {
        CxFile _F;

        _F.attach(stdout);

        m_bRv = _F.isValid();
        xTEST_EQ(true, m_bRv);

        FILE *pFile = _F.detach();
        xTEST_PTR(pFile);
        xTEST_EQ(stdout, pFile);
    }

    xTEST_CASE("CxFile::get", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        FILE *pFile = F.get();
        xTEST_PTR(pFile);
    }

    xTEST_CASE("CxFile::path", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_sRv = F.path();
        xTEST_EQ(csFilePath, m_sRv);
    }


    /****************************************************************************
    *    read, write
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::write CxFile::read", cullCaseLoops)
    {
        std::tstring_t sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring_t sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);
            F.write((const void *)&sBuffWrite.at(0), sBuffWrite.size() * sizeof(std::tstring_t::value_type));
        }

        //uiRead
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinRead, true);
            F.read(&sBuffRead.at(0), sBuffWrite.size() * sizeof(std::tstring_t::value_type));
        }

        xTEST_EQ(sBuffWrite, sBuffRead);
    }

    xTEST_CASE("CxFile::write CxFile::read", cullCaseLoops)
    {
        const std::ustring_t sContent(10, 5);

        std::ustring_t       usText1;
        std::ustring_t       usText2;

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinWrite, true);
            F.write(sContent);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinRead, true);
            F.read(&usText1);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            F.create(sTempDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, true);
            F.write(usText1);
        }

        //-------------------------------------
        // bRead
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinRead, true);
            F.read(&usText2);

            xTEST_EQ(usText1.size(), usText2.size());
            xTEST_EQ(true, usText1 == usText2);
        }
    }

    xTEST_CASE("CxFile::readLine CxFile::writeLine", cullCaseLoops)
    {
        std::tstring_t sBuffWrite = xT("<test1><test2><test3><...>");
        std::tstring_t sBuffRead  = xT("");

        // writeLine
        {
            CxFile F;

            F.create(csFilePath, CxFile::omWrite, true);
            F.writeLine(sBuffWrite);
        }

        // readLine
        {
            CxFile F;

            F.create(csFilePath, CxFile::omRead, true);
            F.readLine(&sBuffRead, sBuffWrite.size());
        }

        xTEST_EQ(sBuffWrite.size(), sBuffRead.size());
        xTEST_EQ(sBuffWrite,        sBuffRead);
    }

    xTEST_CASE("CxFile::writeChar chReadChar ungetChar", cullCaseLoops)
    {
        const tchar_t chChar = xT('W');

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.writeChar(chChar);
        F.setPosition(0, CxFile::ppBegin);

        m_chRv = F.readChar();
        xTEST_EQ(chChar, m_chRv);

        F.setPosition(0, CxFile::ppBegin);
        F.writeChar(chChar);

        F.setPosition(0, CxFile::ppBegin);
        F.ungetChar(chChar);
    }

    xTEST_CASE("CxFile::clear", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.clear();
    }

    /****************************************************************************
    *    times
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::time CxFile::setTime", cullCaseLoops)
    {
        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, false);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        CxFile::setTime(csFilePath, ctmCreate, ctmAccess, ctmModified);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        CxFile::time(csFilePath, &tmCreate, &tmAccess, &tmModified);

    #if   xOS_ENV_WIN
        xTEST_EQ(ctmCreate, tmCreate);
    #elif xOS_ENV_UNIX
        xUNUSED(tmCreate);
    #endif

        xTEST_EQ(ctmAccess,   tmAccess);
        xTEST_EQ(ctmModified, tmModified);
    }


    /****************************************************************************
    *    formatted input/output
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::read", cullCaseLoops)
    {
        const std::tstring_t csTestContent = 
            xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);

            int iResFprintf = F.write(csTestContent.c_str());
            xTEST_EQ(csTestContent.size(), size_t(iResFprintf));
        }

        std::tstring_t sContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omRead, true);
            F.read(&sContent);
        }

        // TODO: xTEST_EQ(csTestContent, sContent);
    }

    xTEST_CASE("CxFile::write", cullCaseLoops)
    {
        const std::tstring_t csTestContent = 
                xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        int iResFprintf = F.write(xT("%s"), csTestContent.c_str());
        xTEST_EQ(csTestContent.size(), size_t(iResFprintf));
    }

    xTEST_CASE("CxFile::writeV", cullCaseLoops)
    {
        struct SWriter {
            static void
            DoV(const CxFile &csfFile, const tchar_t *pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                int iRv = csfFile.writeV(pcszFormat, args);
                xTEST_DIFF(- 1, iRv);

                xVA_END(args);
            };
        };

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }

    /****************************************************************************
    *    other
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::locking", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.resize(1024);
        F.locking(CxFile::lmLock, 10);
        F.locking(CxFile::lmUnlock, 10);
    }

    xTEST_CASE("CxFile::setPosition CxFile::getPosition", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.setPosition(0, CxFile::ppBegin);

        long_t liRv = F.position();
        xTEST_EQ(0L, liRv);
    }

    xTEST_CASE("CxFile::getSize", cullCaseLoops)
    {
        const longlong_t cllNewSize = 1024LL;

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.resize(cllNewSize);

        longlong_t llSize = F.size();
        xTEST_EQ(cllNewSize, llSize);
    }

    xTEST_CASE("CxFile::resize", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.resize(0);
    }

    xTEST_CASE("CxFile::setVBuff", cullCaseLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.setVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
    }

    xTEST_CASE("CxFile::setMode", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            F.setMode(CxFile::tmBinary);
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX
            // TODO: setMode
        #endif
    }

    xTEST_CASE("CxFile::setMode", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            F.setMode(CxFile::tmText);
        #elif xOS_ENV_UNIX
            // TODO: setMode
        #endif
    }


    /****************************************************************************
    *    Error-handling:
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::isValid", cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.isValid();
        xTEST_EQ(false, m_bRv);

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.isValid();
        xTEST_EQ(true, m_bRv);

        F.close();
    }

    xTEST_CASE("CxFile::isOpen", cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.isOpen();
        xTEST_EQ(false, m_bRv);

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.isOpen();
        xTEST_EQ(true, m_bRv);

        F.close();

        m_bRv = F.isOpen();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxFile::isEmpty", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.isEmpty();
        xTEST_EQ(true, m_bRv);

        m_iRv = F.write(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRv);

        m_bRv = F.isEmpty();
        xTEST_EQ(false, m_bRv);

        F.clear();

        m_bRv = F.isEmpty();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFile::isEof", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.isEof();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxFile::isError", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.isError();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxFile::errorClear", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.errorClear();
    }

    /****************************************************************************
    *    closing
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::flush", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.flush();

        m_bRv = F.isValid();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFile::close", cullCaseLoops)
    {
        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.close();

        m_bRv = F.isValid();
        xTEST_EQ(false, m_bRv);
    }

    // vUnit1
    vUnit1(cullCaseLoops);

    // vUnitPrivate
    vUnitPrivate(cullCaseLoops);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxTest_CxFile::vUnit1(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::isFile", cullCaseLoops)
    {
        m_bRv = CxFile::isFile(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::isFile(sTempDirPath());
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxFile::isExists", cullCaseLoops)
    {
        m_bRv = CxFile::isExists(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::isExists(csFilePath + xT("wrong_path"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxFile::isExists(sTempDirPath());
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxFile::isExistsEx", cullCaseLoops)
    {
        m_sRv = CxFile::isExistsEx(csFilePath);
        xTEST_EQ(true, CxFile::isExists(csFilePath));
        xTEST_EQ(false, CxFile::isExists(m_sRv));

        ////xTRACEV(xT("\tCxFile::isExistsEx: %s"), m_sRv.c_str());
    }

    xTEST_CASE("CxFile::access", cullCaseLoops)
    {
        CxFile::access(csFilePath, CxFile::amExistence);
    }

    xTEST_CASE("CxFile::chmod", cullCaseLoops)
    {
        CxFile::chmod(csFilePath, CxFile::pmReadWrite);
    }

    xTEST_CASE("CxFile::rename", cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::textWrite(csFilePath, xT("Simple text"));
        CxFile::remove(csNewFilePath);
        CxFile::rename(csFilePath, csNewFilePath);
        CxFile::remove(csNewFilePath);
    }

    xTEST_CASE("CxFile::lines", cullCaseLoops)
    {
        const ulonglong_t cullLinesNum = 17;
        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                F.writeLine( CxString::cast(i) );
            }
        }

        ulonglong_t ullLinesNum = CxFile::lines(csFilePath);
        xTEST_EQ(cullLinesNum, ullLinesNum);
    }

    xTEST_CASE("CxFile::copy", cullCaseLoops)
    {
        const std::tstring_t sFilePathFrom = sTempDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::tstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            F.create(sFilePathFrom, CxFile::omBinCreateReadWrite, true);
            F.resize(1024 * 5);
        }

        CxFile::copy(sFilePathFrom, sFilePathTo, false);

        m_bRv = CxFile::isExists(sFilePathTo);
        xTEST_EQ(true, m_bRv);

        CxFile::copy(sFilePathFrom, sFilePathTo, true);
    }

    xTEST_CASE("CxFile::move", cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::textWrite(csNewFilePath, xT("Simple text"));
        CxFile::remove(sTempDirPath() + CxConst::xSLASH + csNewFilePath);
        CxFile::move(csNewFilePath, sTempDirPath());
    }

    xTEST_CASE("CxFile::unlink", cullCaseLoops)
    {
        #if xTEMP_DISABLED
            m_bRv = CxFile::unlink(csNewFilePath);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    xTEST_CASE("CxFile::clear", cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::clear(csNewFilePath);
    }

    xTEST_CASE("CxFile::remove", cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::remove(csNewFilePath);
        CxFile::remove(csNewFilePath);
    }

    xTEST_CASE("CxFile::tryRemove", cullCaseLoops)
    {
        // TEST: CxFile::tryRemove

        #if xTODO
            const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    F.create(csFilePath, CxFile::omCreateReadWrite, true);
                    F.resize(1024);
                    F.locking(CxFile::lmLock, 10);

                    //try
                    CxFile::tryRemove(csFilePath, 2000);
                    F.locking(CxFile::lmUnlock, 10);
                } else {
                    //try
                    CxFile::tryRemove(csFilePath, 33);
                }
            }
        #endif
    }

    xTEST_CASE("CxFile::wipe", cullCaseLoops)
    {
        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);
            m_iRv = F.write(xT("0123456789"));
            xTEST_DIFF(- 1, m_iRv);
        }

        for (size_t i = 0; i < 3; ++ i) {
            CxFile::wipe(csFilePath, 10);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        std::tstring_t sFileContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 7; ++ i) {
                F.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::textRead(csFilePath, &sFileContent);
        CxFile::textWrite(csFilePath, sFileContent);

        std::tstring_t sStr;
        CxFile::textRead(csFilePath, &sStr);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        // empty content
        std::tstring_t sFileContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(csFilePath, &sFileContent);
        CxFile::textWrite(csFilePath, sFileContent);
        
        std::tstring_t sStr;
        CxFile::textRead(csFilePath, &sStr);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        // std::vector
        std::vec_tstring_t vsFileContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                F.writeLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::textRead(csFilePath, &vsFileContent);
        CxFile::textWrite(csFilePath, vsFileContent);

        std::vec_tstring_t vsStr;
        CxFile::textRead(csFilePath, &vsStr);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xTEST_EQ(true, vsFileContent == vsStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        //  empty content
        std::vec_tstring_t vsFileContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(csFilePath, &vsFileContent);
        CxFile::textWrite(csFilePath, vsFileContent);

        std::vec_tstring_t vsStr;
        CxFile::textRead(csFilePath, &vsStr);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xTEST_EQ(true, vsFileContent == vsStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {   
        // std::vector
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                F.writeLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
            }
        }

        CxFile::textRead(csFilePath, csSeparator, &cmsFileContent);
        CxFile::textWrite(csFilePath, csSeparator, cmsFileContent);

        std::map_tstring_t msStr;
        CxFile::textRead(csFilePath, csSeparator, &msStr);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xTEST_EQ(true, cmsFileContent == msStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        // empty content
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::textRead(csFilePath, csSeparator, &cmsFileContent);
        CxFile::textWrite(csFilePath, csSeparator, cmsFileContent);

        std::map_tstring_t msStr;
        CxFile::textRead(csFilePath, csSeparator, &msStr);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xTEST_EQ(true, cmsFileContent == msStr);
    }

    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {  
        // binary
        std::ustring_t usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);

            m_iRv = F.write(xT("0123456789"));
            xTEST_LESS(0, m_iRv);

            F.resize(1024 * 5);

            m_iRv = F.write(xT("0123456789"));
            xTEST_LESS(0, m_iRv);
        }

        CxFile::binWrite(csFilePath, usFileContent);

        std::ustring_t usStr;
        CxFile::binRead(csFilePath, &usStr);

        xTEST_EQ(true, usFileContent == usStr);
    }
    
    xTEST_CASE("CxFile::textRead CxFile::textWrite", cullCaseLoops)
    {
        // empty content
        std::ustring_t usFileContent;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);
        }

        CxFile::binWrite(csFilePath, usFileContent);

        std::ustring_t usStr;
        CxFile::binRead(csFilePath, &usStr);

        xTEST_EQ(true, usFileContent == usStr);
    }
}
//---------------------------------------------------------------------------
void
CxTest_CxFile::vUnitPrivate(
    const ulonglong_t &cullCaseLoops
)
{
#if xTEST_PRIVATE_DATA
    const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.txt");

    xTEST_CASE("CxFile::_nativeHandle", cullCaseLoops)
    {
        CxFile sfFile;

        sfFile.create(csFilePath, CxFile::omRead, true);

        m_iRv = CxFile::_nativeHandle( sfFile.get() );
        xTEST_DIFF((int)CxFile::etError, m_iRv);
    }
   
    xTEST_CASE("CxFile::_stdHandle", cullCaseLoops)
    {
        // TEST: CxFile::_stdHandle

    #if xTODO
        const CxFile::ExOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        sfFile.create(csFilePath, comMode, true);

        int iFile = CxFile::_nativeHandle(sfFile.get());
        xTEST_DIFF((int)CxFile::etError, iFile);

        FILE *pfFile = CxFile::_stdHandle(iFile, comMode);
        xTEST_PTR(pfFile);
    #endif
    }

    xTEST_CASE("CxFile::_openMode", cullCaseLoops)
    {
        std::vector< std::pair<CxFile::ExOpenMode, std::tstring_t> > vpData;

        vpData.push_back( std::make_pair(CxFile::omRead,               xT("r")) );
        vpData.push_back( std::make_pair(CxFile::omWrite,              xT("w")) );
        vpData.push_back( std::make_pair(CxFile::omAppend,             xT("a")) );
        vpData.push_back( std::make_pair(CxFile::omOpenReadWrite,      xT("r+")) );
        vpData.push_back( std::make_pair(CxFile::omCreateReadWrite,    xT("w+")) );
        vpData.push_back( std::make_pair(CxFile::omOpenReadAppend,     xT("a+")) );

        vpData.push_back( std::make_pair(CxFile::omBinRead,            xT("rb")) );
        vpData.push_back( std::make_pair(CxFile::omBinWrite,           xT("wb")) );
        vpData.push_back( std::make_pair(CxFile::omBinAppend,          xT("ab")) );
        vpData.push_back( std::make_pair(CxFile::omBinOpenReadWrite,   xT("rb+")) );
        vpData.push_back( std::make_pair(CxFile::omBinCreateReadWrite, xT("wb+")) );
        vpData.push_back( std::make_pair(CxFile::omBinOpenReadAppend,  xT("ab+")) );

        for (size_t i = 0; i < vpData.size(); ++ i) {
            CxFile::ExOpenMode omRes = vpData.at(i).first;
            std::tstring_t     sRv   = vpData.at(i).second;

            m_sRv = CxFile::_openMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif
}
//---------------------------------------------------------------------------
