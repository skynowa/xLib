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
bool
CxTest_CxFile::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_CASE(cullCaseLoops)
    {
        CxFile::vDelete(csFilePath);
    }


    /****************************************************************************
    *    open, get
    *
    *****************************************************************************/

    //-------------------------------------
    //bCreate
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        for (size_t i = 0; i < 1; ++ i) {
            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        for (size_t i = 0; i < 7; ++ i) {
            F.vReopen(csFilePath, CxFile::omOpenReadWrite, true);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_CASE(cullCaseLoops)
    {
        CxFile _F;

        _F.vAttach(stdout);

        m_bRv = _F.bIsValid();
        xTEST_EQ(true, m_bRv);

        FILE *pFile = _F.pDetach();
        xTEST_PTR(pFile);
        xTEST_EQ(stdout, pFile);
    }

    //--------------------------------------------------
    //pGet
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        FILE *pFile = F.pGet();
        xTEST_PTR(pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_sRv = F.sGetPath();
        xTEST_EQ(csFilePath, m_sRv);
    }


    /****************************************************************************
    *    read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite, uiRead
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring_t sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinRead, true);
            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xTEST_EQ(sBuffWrite, sBuffRead);
    }

    //-------------------------------------
    //bRead, bWrite
    xTEST_CASE(cullCaseLoops)
    {
        const std::ustring_t sContent(10, 5);

        std::ustring_t       usText1;
        std::ustring_t       usText2;

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinWrite, true);
            F.vWrite(sContent);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinRead, true);
            F.vRead(&usText1);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            F.vCreate(sGetTempDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, true);
            F.vWrite(usText1);
        }

        //-------------------------------------
        // bRead
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinRead, true);
            F.vRead(&usText2);

            xTEST_EQ(usText1.size(), usText2.size());
            xTEST_EQ(true, usText1 == usText2);
        }
    }

    //-------------------------------------
    //bWriteLine, bReadLine
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sBuffWrite = xT("<test1><test2><test3><...>");
        std::tstring_t sBuffRead  = xT("");

        //bWriteLine
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omWrite, true);
            F.vWriteLine(sBuffWrite);
        }

        //bReadLine
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omRead, true);
            F.vReadLine(&sBuffRead, sBuffWrite.size());
        }

        //assert
        xTEST_EQ(sBuffWrite.size(), sBuffRead.size());
        xTEST_EQ(sBuffWrite,        sBuffRead);
    }

    //-------------------------------------
    //bWriteChar, chReadChar, bUngetChar
    xTEST_CASE(cullCaseLoops)
    {
        const tchar_t chChar = xT('W');

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vWriteChar(chChar);
        F.vSetPosition(0, CxFile::ppBegin);

        m_chRv = F.chReadChar();
        xTEST_EQ(chChar, m_chRv);

        F.vSetPosition(0, CxFile::ppBegin);
        F.vWriteChar(chChar);

        F.vSetPosition(0, CxFile::ppBegin);
        F.vUngetChar(chChar);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vClear();
    }


    /****************************************************************************
    *    times
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bGetTime, bSetTime
    xTEST_CASE(cullCaseLoops)
    {
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, false);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        CxFile::vSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        CxFile::vGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);

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

    //--------------------------------------------------
    //bRead
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csTestContent = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

            int iResFprintf = F.iWrite(csTestContent.c_str());
            xTEST_LESS(0, iResFprintf);
        }

        std::tstring_t sContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omRead, true);
            F.vRead(&sContent);
        }

        xTEST_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        int iResFprintf = F.iWrite(xT("%s"), xT("xxx"));
        xTEST_LESS(0, iResFprintf);
    }

    //-------------------------------------
    //iWriteV
    xTEST_CASE(cullCaseLoops)
    {
        struct SWriter {
            static void
            DoV(const CxFile &csfFile, const tchar_t *pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                int iRv = csfFile.iWriteV(pcszFormat, args);
                xTEST_DIFF((int)CxFile::etError, iRv);

                xVA_END(args);
            };
        };

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *    other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vResize(1024);
        F.vLocking(CxFile::lmLock, 10);
        F.vLocking(CxFile::lmUnlock, 10);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vSetPosition(0, CxFile::ppBegin);

        long_t liRv = F.liGetPosition();
        xTEST_EQ(0L, liRv);
    }

    //-------------------------------------
    //llGetSize
    xTEST_CASE(cullCaseLoops)
    {
        const longlong_t cllNewSize = 1024LL;

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vResize(cllNewSize);

        longlong_t llSize = F.llGetSize();
        xTEST_EQ(cllNewSize, llSize);
    }

    //-------------------------------------
    //bResize
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vResize(0);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_CASE(cullCaseLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vSetVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            F.vSetMode(CxFile::tmBinary);
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        #if   xOS_ENV_WIN
            F.vSetMode(CxFile::tmText);
        #elif xOS_ENV_UNIX
            //TODO: bSetMode
        #endif
    }


    /****************************************************************************
    *    Error-handling:
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsValid
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bIsValid();
        xTEST_EQ(false, m_bRv);

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.bIsValid();
        xTEST_EQ(true, m_bRv);

        F.vClose();
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bIsOpen();
        xTEST_EQ(false, m_bRv);

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.bIsOpen();
        xTEST_EQ(true, m_bRv);

        F.vClose();

        m_bRv = F.bIsOpen();
        xTEST_EQ(false, m_bRv);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.bIsEmpty();
        xTEST_EQ(true, m_bRv);

        m_iRv = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRv);

        m_bRv = F.bIsEmpty();
        xTEST_EQ(false, m_bRv);

        F.vClear();

        m_bRv = F.bIsEmpty();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bIsEof
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.bIsEof();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bIsError
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

        m_bRv = F.bIsError();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vErrorClear();
    }


    /****************************************************************************
    *    closing
    *
    *****************************************************************************/

    //-------------------------------------
    //bFlush
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vFlush();

        m_bRv = F.bIsValid();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vClose();

        m_bRv = F.bIsValid();
        xTEST_EQ(false, m_bRv);
    }

    //bUnit1
    m_bRv = bUnit1(cullCaseLoops);
    xTEST_EQ(true, m_bRv);

    //bUnitePrivate
    m_bRv = bUnitPrivate(cullCaseLoops);
    xTEST_EQ(true, m_bRv);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxTest_CxFile::bUnit1(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFile::bIsFile(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bIsFile(xT(""));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxFile::bIsFile(sGetTempDirPath());
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bIsExists
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bIsExists(csFilePath + xT("wrong_path"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxFile::bIsExists(xT(""));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxFile::bIsExists(sGetTempDirPath());
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //sIsExists
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxFile::sIsExists(csFilePath);
        xTEST_EQ(true, CxFile::bIsExists(csFilePath));
        xTEST_EQ(false, CxFile::bIsExists(m_sRv));

        ////xTRACEV(xT("\tCxFile::sIsExists: %s"), m_sRv.c_str());
    }

    //-------------------------------------
    //bAccess
    xTEST_CASE(cullCaseLoops)
    {
        CxFile::vAccess(csFilePath, CxFile::amExistence);
    }

    //-------------------------------------
    //bChmod
    xTEST_CASE(cullCaseLoops)
    {
        CxFile::vChmod(csFilePath, CxFile::pmReadWrite);
    }

    //-------------------------------------
    //bRename
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::vTextWrite(csFilePath, xT("Simple text"));
        CxFile::vDelete(csNewFilePath);
        CxFile::vRename(csFilePath, csNewFilePath);
        CxFile::vDelete(csNewFilePath);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_CASE(cullCaseLoops)
    {
        const ulonglong_t cullLinesNum = 17;
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                F.vWriteLine( CxString::string_cast(i) );
            }
        }

        ulonglong_t ullLinesNum = CxFile::ullGetLines(csFilePath);
        xTEST_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sFilePathFrom = sGetTempDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::tstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            F.vCreate(sFilePathFrom, CxFile::omBinCreateReadWrite, true);
            F.vResize(1024 * 5);
        }

        CxFile::vCopy(sFilePathFrom, sFilePathTo, false);

        m_bRv = CxFile::bIsExists(sFilePathTo);
        xTEST_EQ(true, m_bRv);

        CxFile::vCopy(sFilePathFrom, sFilePathTo, true);
    }

    //-------------------------------------
    //bMove
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::vTextWrite(csNewFilePath, xT("Simple text"));
        CxFile::vDelete(sGetTempDirPath() + CxConst::xSLASH + csNewFilePath);
        CxFile::vMove(csNewFilePath, sGetTempDirPath());
    }

    //-------------------------------------
    //bUnlink
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEMP_DISABLED
            m_bRv = CxFile::bUnlink(csNewFilePath);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::vClear(csNewFilePath);
    }

    //-------------------------------------
    //bDelete
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        CxFile::vDelete(csNewFilePath);
        CxFile::vDelete(csNewFilePath);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
                    F.vResize(1024);
                    F.vLocking(CxFile::lmLock, 10);

                    //try
                    CxFile::vTryDelete(csFilePath, 2000);
                    F.vLocking(CxFile::lmUnlock, 10);
                } else {
                    //try
                    CxFile::vTryDelete(csFilePath, 33);
                }
            }
        #endif
    }

    //-------------------------------------
    //bWipe
    xTEST_CASE(cullCaseLoops)
    {
        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_DIFF(static_cast<int>( CxFile::etError ), m_iRv);
        }

        for (size_t i = 0; i < 3; ++ i) {
            CxFile::vWipe(csFilePath, 10);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (std::tstring_t)
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sFileContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 7; ++ i) {
                F.vWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::vTextRead(csFilePath, &sFileContent);
        CxFile::vTextWrite(csFilePath, sFileContent);

        std::tstring_t sStr;
        CxFile::vTextRead(csFilePath, &sStr);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sFileContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::vTextRead(csFilePath, &sFileContent);
        CxFile::vTextWrite(csFilePath, sFileContent);
        
        std::tstring_t sStr;
        CxFile::vTextRead(csFilePath, &sStr);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsFileContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                F.vWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
            }
        }

        CxFile::vTextRead(csFilePath, &vsFileContent);
        CxFile::vTextWrite(csFilePath, vsFileContent);

        std::vec_tstring_t vsStr;
        CxFile::vTextRead(csFilePath, &vsStr);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xTEST_EQ(true, vsFileContent == vsStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsFileContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::vTextRead(csFilePath, &vsFileContent);
        CxFile::vTextWrite(csFilePath, vsFileContent);

        std::vec_tstring_t vsStr;
        CxFile::vTextRead(csFilePath, &vsStr);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xTEST_EQ(true, vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullCaseLoops)
    {
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);

            for (size_t i = 0; i < 10; ++ i) {
                F.vWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
            }
        }

        CxFile::vTextRead(csFilePath, csSeparator, &cmsFileContent);
        CxFile::vTextWrite(csFilePath, csSeparator, cmsFileContent);

        std::map_tstring_t msStr;
        CxFile::vTextRead(csFilePath, csSeparator, &msStr);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xTEST_EQ(true, cmsFileContent == msStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        }

        CxFile::vTextRead(csFilePath, csSeparator, &cmsFileContent);
        CxFile::vTextWrite(csFilePath, csSeparator, cmsFileContent);

        std::map_tstring_t msStr;
        CxFile::vTextRead(csFilePath, csSeparator, &msStr);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xTEST_EQ(true, cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_CASE(cullCaseLoops)
    {
        std::ustring_t usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinCreateReadWrite, true);

            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRv);

            F.vResize(1024 * 5);

            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRv);
        }

        CxFile::vBinWrite(csFilePath, usFileContent);

        std::ustring_t usStr;
        CxFile::vBinRead(csFilePath, &usStr);

        xTEST_EQ(true, usFileContent == usStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::ustring_t usFileContent;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
        }

        CxFile::vBinWrite(csFilePath, usFileContent);

        std::ustring_t usStr;
        CxFile::vBinRead(csFilePath, &usStr);

        xTEST_EQ(true, usFileContent == usStr);
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxTest_CxFile::bUnitPrivate(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

#if xTEST_PRIVATE_DATA
    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxFile sfFile;

        sfFile.vCreate(csFilePath, CxFile::omRead, true);

        m_iRv = CxFile::_iGetHandle( sfFile.pGet() );
        xTEST_DIFF((int)CxFile::etError, m_iRv);
    }

    //--------------------------------------------------
    //_pfGetHandle
    #if xTODO
    xTEST_CASE(cullCaseLoops)
    {
        const CxFile::ExOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        sfFile.vCreate(csFilePath, comMode, true);

        int iFile = CxFile::_iGetHandle(sfFile.pGet());
        xTEST_DIFF((int)CxFile::etError, iFile);

        FILE *pfFile = CxFile::_pfGetHandle(iFile, comMode);
        xTEST_PTR(pfFile);
    }
    #endif

    //--------------------------------------------------
    //_sGetOpenMode
    xTEST_CASE(cullCaseLoops)
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
            CxFile::EOpenMode omRes = vpData.at(i).first;
            std::tstring_t    sRv   = vpData.at(i).second;

            m_sRv = CxFile::_sGetOpenMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
