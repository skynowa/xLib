/**
 * \file   CxTest_CxFile.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxFile::CxTest_CxFile() {

}
//---------------------------------------------------------------------------
CxTest_CxFile::~CxTest_CxFile() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxFile::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFile::bDelete(csFilePath);
        xTEST_EQ(true, m_bRes);
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
            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRes = F.bReopen(csFilePath, CxFile::omOpenReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_CASE(cullCaseLoops)
    {
        CxFile _F;

        m_bRes = _F.bAttach(stdout);
        xTEST_EQ(true, m_bRes);

        m_bRes = _F.bIsValid();
        xTEST_EQ(true, m_bRes);

        FILE *pFile = _F.pDetach();
        xTEST_PTR(pFile);
        xTEST_EQ(stdout, pFile);
    }

    //--------------------------------------------------
    //pGet
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        FILE *pFile = F.pGet();
        xTEST_PTR(pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_sRes = F.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
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

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRes);

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

            m_bRes = F.bCreate(csFilePath, CxFile::omBinWrite, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bWrite(sContent);
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bRead(&usText1);
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bCreate(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bWrite(usText1);
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bRead(&usText2);
            xTEST_EQ(true, m_bRes);

            xTEST_EQ(usText1.size(), usText2.size());
            xASSERT(usText1 == usText2);
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

            m_bRes = F.bCreate(csFilePath, CxFile::omWrite, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xTEST_EQ(true, m_bRes);
        }

        //bReadLine
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xTEST_EQ(true, m_bRes);
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

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRes);
        m_chRes = F.chReadChar();
        xTEST_EQ(chChar, m_chRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRes);
        m_bRes = F.bWriteChar(chChar);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRes);
        m_bRes = F.bUngetChar(chChar);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bClear();
        xTEST_EQ(true, m_bRes);
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

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, false);
            xTEST_EQ(true, m_bRes);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        m_bRes = CxFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xTEST_EQ(true, m_bRes);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRes = CxFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
        xTEST_EQ(true, m_bRes);

    #if xOS_ENV_WIN
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

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            int iResFprintf = F.iWrite(csTestContent.c_str());
            xTEST_LESS(0, iResFprintf);
        }

        std::tstring_t sContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bRead(&sContent);
            xTEST_EQ(true, m_bRes);
        }

        xTEST_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

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

                int iRes = csfFile.iWriteV(pcszFormat, args);
                xTEST_DIFF((int)CxFile::etError, iRes);

                xVA_END(args);
            };
        };

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

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

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bResize(1024);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bLocking(CxFile::lmLock, 10);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bLocking(CxFile::lmUnlock, 10);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRes);

        long_t liRes = F.liGetPosition();
        xTEST_EQ(0L, liRes);
    }

    //-------------------------------------
    //liGetSize
    xTEST_CASE(cullCaseLoops)
    {
        const long_t culNewSize = 1024;

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bResize(culNewSize);
        xTEST_EQ(true, m_bRes);

        long_t liSize = F.liGetSize();
        xTEST_EQ(culNewSize, liSize);
    }

    //-------------------------------------
    //bResize
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bResize(0);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_CASE(cullCaseLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bSetVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        #if xOS_ENV_WIN
            m_bRes = F.bSetMode(CxFile::tmBinary);
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        #if xOS_ENV_WIN
            m_bRes = F.bSetMode(CxFile::tmText);
            xTEST_EQ(true, m_bRes);
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

        m_bRes = F.bIsValid();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bClose();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bIsOpen();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bClose();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_EQ(true, m_bRes);

        m_iRes = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRes);

        m_bRes = F.bIsEmpty();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bClear();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bIsEof
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsEof();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bIsError
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsError();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bErrorClear();
        xTEST_EQ(true, m_bRes);
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

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bFlush();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bClose();
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_EQ(false, m_bRes);
    }

    //bUnit1
    m_bRes = bUnit1(cullCaseLoops);
    xTEST_EQ(true, m_bRes);

    //bUnitePrivate
    m_bRes = bUnitPrivate(cullCaseLoops);
    xTEST_EQ(true, m_bRes);

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

    const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFile::bIsFile(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bIsFile(xT(""));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsFile(sGetWorkDirPath());
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath + xT("wrong_path"));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsExists(xT(""));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsExists(sGetWorkDirPath());
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //sIsExists
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxFile::sIsExists(csFilePath);
        xTEST_EQ(true, CxFile::bIsExists(csFilePath));
        xTEST_EQ(false, CxFile::bIsExists(m_sRes));

        ////xTRACEV(xT("\tCxFile::sIsExists: %s"), m_sRes.c_str());
    }

    //-------------------------------------
    //bAccess
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFile::bAccess(csFilePath, CxFile::amExistence);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bChmod
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFile::bChmod(csFilePath, CxFile::pmReadWrite);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bRename
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csFilePath, xT("Simple text"));
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bRename(csFilePath, csNewFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_CASE(cullCaseLoops)
    {
        const ulonglong_t cullLinesNum = 17;
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
                xTEST_EQ(true, m_bRes);
            }
        }

        ulonglong_t ullLinesNum = CxFile::ullGetLines(csFilePath);
        xTEST_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::tstring_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            m_bRes = F.bCreate(sFilePathFrom, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, false);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bIsExists(sFilePathTo);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, true);
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bDelete(sGetWorkDirPath() + CxConst::xSLASH + csNewFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bMove(csNewFilePath, sGetWorkDirPath());
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bUnlink
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEMP_DISABLED
            m_bRes = CxFile::bUnlink(csNewFilePath);
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bClear(csNewFilePath);
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
                    xTEST_EQ(true, m_bRes);

                    m_bRes = F.bResize(1024);
                    xTEST_EQ(true, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmLock, 10);
                    xTEST_EQ(true, m_bRes);

                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 2000);
                    xTEST_EQ(false, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmUnlock, 10);
                    xTEST_EQ(true, m_bRes);
                } else {
                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 33);
                    xTEST_EQ(true, m_bRes);
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

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_DIFF(static_cast<int>( CxFile::etError ), m_iRes);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = CxFile::bWipe(csFilePath, 10);
            xTEST_EQ(true, m_bRes);
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

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_EQ(true, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_EQ(true, m_bRes);

        std::tstring_t sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_EQ(true, m_bRes);

        std::tstring_t sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_EQ(true, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_EQ(true, m_bRes);

        std::vector<std::tstring_t> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_EQ(true, m_bRes);

        std::vector<std::tstring_t> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullCaseLoops)
    {
        std::map<std::tstring_t, std::tstring_t> cmsFileContent;
        const std::tstring_t              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xTEST_EQ(true, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_EQ(true, m_bRes);

        std::map<std::tstring_t, std::tstring_t> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::map<std::tstring_t, std::tstring_t> cmsFileContent;
        const std::tstring_t              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_EQ(true, m_bRes);

        std::map<std::tstring_t, std::tstring_t> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_CASE(cullCaseLoops)
    {
        std::ustring_t usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_EQ(true, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_EQ(true, m_bRes);

        std::ustring_t usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_EQ(true, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::ustring_t usFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_EQ(true, m_bRes);

        std::ustring_t usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_EQ(true, m_bRes);

        xASSERT(usFileContent == usStr);
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
    const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, CxFile::omRead, true);
        xTEST_EQ(true, m_bRes);

        m_iRes = CxFile::_iGetHandle( sfFile.pGet() );
        xTEST_DIFF((int)CxFile::etError, m_iRes);
    }

    //--------------------------------------------------
    //_pfGetHandle
    #if xTODO
    xTEST_CASE(cullCaseLoops)
    {
        const CxFile::EOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, comMode, true);
        xTEST_EQ(true, m_bRes);

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
        std::vector< std::pair<CxFile::EOpenMode, std::tstring_t> > vpData;

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
            std::tstring_t                sRes  = vpData.at(i).second;

            m_sRes = CxFile::_sGetOpenMode(omRes);
            xTEST_EQ(sRes, m_sRes);
        }
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
