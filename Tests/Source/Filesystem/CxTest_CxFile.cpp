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
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxFile::bDelete(csFilePath);
        xTEST_DIFF(false, m_bRes);
    }


    /****************************************************************************
    *    open, get
    *
    *****************************************************************************/

    //-------------------------------------
    //bCreate
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        for (size_t i = 0; i < 1; ++ i) {
            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRes = F.bReopen(csFilePath, CxFile::omOpenReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_CASE(cullBlockLoops)
    {
        CxFile _F;

        m_bRes = _F.bAttach(stdout);
        xTEST_DIFF(false, m_bRes);

        m_bRes = _F.bIsValid();
        xTEST_DIFF(false, m_bRes);

        FILE *pFile = _F.pDetach();
        xTEST_PTR(pFile);
        xTEST_EQ(stdout, pFile);
    }

    //--------------------------------------------------
    //pGet
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_sRes = F.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }


    /****************************************************************************
    *    read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite, uiRead
    xTEST_CASE(cullBlockLoops)
    {
        std::tstring sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_DIFF(false, m_bRes);

            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xTEST_EQ(sBuffWrite, sBuffRead);
    }

    //-------------------------------------
    //bRead, bWrite
    xTEST_CASE(cullBlockLoops)
    {
        const std::ustring sContent(10, 5);

        std::ustring       usText1;
        std::ustring       usText2;

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bWrite(sContent);
            xTEST_DIFF(false, m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bRead(&usText1);
            xTEST_DIFF(false, m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bCreate(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bWrite(usText1);
            xTEST_DIFF(false, m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bRead(&usText2);
            xTEST_DIFF(false, m_bRes);

            xTEST_EQ(usText1.size(), usText2.size());
            xASSERT(usText1 == usText2);
        }
    }

    //-------------------------------------
    //bWriteLine, bReadLine
    xTEST_CASE(cullBlockLoops)
    {
        std::tstring sBuffWrite = xT("<test1><test2><test3><...>");
        std::tstring sBuffRead  = xT("");

        //bWriteLine
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xTEST_DIFF(false, m_bRes);
        }

        //bReadLine
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xTEST_DIFF(false, m_bRes);
        }

        //assert
        xTEST_EQ(sBuffWrite.size(), sBuffRead.size());
        xTEST_EQ(sBuffWrite,        sBuffRead);
    }

    //-------------------------------------
    //bWriteChar, chReadChar, bUngetChar
    xTEST_CASE(cullBlockLoops)
    {
        const tchar chChar = xT('W');

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(false, m_bRes);
        m_chRes = F.chReadChar();
        xTEST_EQ(chChar, m_chRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(false, m_bRes);
        m_bRes = F.bWriteChar(chChar);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(false, m_bRes);
        m_bRes = F.bUngetChar(chChar);
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bClear();
        xTEST_DIFF(false, m_bRes);
    }


    /****************************************************************************
    *    times
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bGetTime, bSetTime
    xTEST_CASE(cullBlockLoops)
    {
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, false);
            xTEST_DIFF(false, m_bRes);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        m_bRes = CxFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xTEST_DIFF(false, m_bRes);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRes = CxFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
        xTEST_DIFF(false, m_bRes);

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
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csTestContent = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            int iResFprintf = F.iWrite(csTestContent.c_str());
            xTEST_LESS(0, iResFprintf);
        }

        std::tstring sContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bRead(&sContent);
            xTEST_DIFF(false, m_bRes);
        }

        xTEST_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        int iResFprintf = F.iWrite(xT("%s"), xT("xxx"));
        xTEST_LESS(0, iResFprintf);
    }

    //-------------------------------------
    //iWriteV
    xTEST_CASE(cullBlockLoops)
    {
        struct SWriter {
            static void
            DoV(const CxFile &csfFile, const tchar *pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                int iRes = csfFile.iWriteV(pcszFormat, args);
                xTEST_DIFF((int)CxFile::etError, iRes);

                xVA_END(args);
            };
        };

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *    other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bResize(1024);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bLocking(CxFile::lmLock, 10);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bLocking(CxFile::lmUnlock, 10);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(false, m_bRes);

        LONG liRes = F.liGetPosition();
        xTEST_EQ(0L, liRes);
    }

    //-------------------------------------
    //liGetSize
    xTEST_CASE(cullBlockLoops)
    {
        const LONG culNewSize = 1024;

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bResize(culNewSize);
        xTEST_DIFF(false, m_bRes);

        LONG liSize = F.liGetSize();
        xTEST_EQ(culNewSize, liSize);
    }

    //-------------------------------------
    //bResize
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bResize(0);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_CASE(cullBlockLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bSetVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        #if xOS_ENV_WIN
            m_bRes = F.bSetMode(CxFile::tmBinary);
            xTEST_DIFF(false, m_bRes);
        #elif xOS_ENV_UNIX
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        #if xOS_ENV_WIN
            m_bRes = F.bSetMode(CxFile::tmText);
            xTEST_DIFF(false, m_bRes);
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
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bIsValid();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bIsOpen();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_DIFF(false, m_bRes);

        m_iRes = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRes);

        m_bRes = F.bIsEmpty();
        xTEST_EQ(false, m_bRes);

        m_bRes = F.bClear();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bIsEof
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsEof();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bIsError
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsError();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bErrorClear();
        xTEST_DIFF(false, m_bRes);
    }


    /****************************************************************************
    *    closing
    *
    *****************************************************************************/

    //-------------------------------------
    //bFlush
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bFlush();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(false, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_EQ(false, m_bRes);
    }

    //bUnit1
    m_bRes = bUnit1(cullBlockLoops);
    xTEST_DIFF(false, m_bRes);

    //bUnitePrivate
    m_bRes = bUnitPrivate(cullBlockLoops);
    xTEST_DIFF(false, m_bRes);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bUnit1 ()
bool
CxTest_CxFile::bUnit1(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxFile::bIsFile(csFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bIsFile(xT(""));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsFile(sGetWorkDirPath());
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxFile::bIsExists(csFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath + xT("wrong_path"));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsExists(xT(""));
        xTEST_EQ(false, m_bRes);

        m_bRes = CxFile::bIsExists(sGetWorkDirPath());
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //sIsExists
    xTEST_CASE(cullBlockLoops)
    {
        m_sRes = CxFile::sIsExists(csFilePath);
        xTEST_DIFF(false, CxFile::bIsExists(csFilePath));
        xTEST_EQ(false, CxFile::bIsExists(m_sRes));

        ////xTRACEV(xT("\tCxFile::sIsExists: %s"), m_sRes.c_str());
    }

    //-------------------------------------
    //bAccess
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxFile::bAccess(csFilePath, CxFile::amExistence);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bChmod
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxFile::bChmod(csFilePath, CxFile::pmReadWrite);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bRename
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csFilePath, xT("Simple text"));
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bRename(csFilePath, csNewFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_CASE(cullBlockLoops)
    {
        const ULONGLONG cullLinesNum = 17;
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
                xTEST_DIFF(false, m_bRes);
            }
        }

        ULONGLONG ullLinesNum = CxFile::ullGetLines(csFilePath);
        xTEST_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::tstring sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            m_bRes = F.bCreate(sFilePathFrom, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_DIFF(false, m_bRes);
        }

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, false);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bIsExists(sFilePathTo);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, true);
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bDelete(sGetWorkDirPath() + CxConst::xSLASH + csNewFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bMove(csNewFilePath, sGetWorkDirPath());
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bUnlink
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            m_bRes = CxFile::bUnlink(csNewFilePath);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bClear(csNewFilePath);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_CASE(cullBlockLoops)
    {
        #if xTODO
            const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
                    xTEST_DIFF(false, m_bRes);

                    m_bRes = F.bResize(1024);
                    xTEST_DIFF(false, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmLock, 10);
                    xTEST_DIFF(false, m_bRes);

                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 2000);
                    xTEST_EQ(false, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmUnlock, 10);
                    xTEST_DIFF(false, m_bRes);
                } else {
                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 33);
                    xTEST_DIFF(false, m_bRes);
                }
            }
        #endif
    }

    //-------------------------------------
    //bWipe
    xTEST_CASE(cullBlockLoops)
    {
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_DIFF(static_cast<int>( CxFile::etError ), m_iRes);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = CxFile::bWipe(csFilePath, 10);
            xTEST_DIFF(false, m_bRes);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (std::tstring)
    xTEST_CASE(cullBlockLoops)
    {
        std::tstring sFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_DIFF(false, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_DIFF(false, m_bRes);

        std::tstring sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_CASE(cullBlockLoops)
    {
        std::tstring sFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_DIFF(false, m_bRes);

        std::tstring sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullBlockLoops)
    {
        std::vector<std::tstring> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_DIFF(false, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_DIFF(false, m_bRes);

        std::vector<std::tstring> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_CASE(cullBlockLoops)
    {
        std::vector<std::tstring> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_DIFF(false, m_bRes);

        std::vector<std::tstring> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullBlockLoops)
    {
        std::map<std::tstring, std::tstring> cmsFileContent;
        const std::tstring              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xTEST_DIFF(false, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_DIFF(false, m_bRes);

        std::map<std::tstring, std::tstring> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_CASE(cullBlockLoops)
    {
        std::map<std::tstring, std::tstring> cmsFileContent;
        const std::tstring              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_DIFF(false, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_DIFF(false, m_bRes);

        std::map<std::tstring, std::tstring> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_DIFF(false, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_CASE(cullBlockLoops)
    {
        std::ustring usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_DIFF(false, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_DIFF(false, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_DIFF(false, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_CASE(cullBlockLoops)
    {
        std::ustring usFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_DIFF(false, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_DIFF(false, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bUnitPrivate ()
bool
CxTest_CxFile::bUnitPrivate(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_CASE(cullBlockLoops)
    {
        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, CxFile::omRead, true);
        xTEST_DIFF(false, m_bRes);

        m_iRes = CxFile::_iGetHandle( sfFile.pGet() );
        xTEST_DIFF((int)CxFile::etError, m_iRes);
    }

    //--------------------------------------------------
    //_pfGetHandle
#if xTODO
    xTEST_CASE(cullBlockLoops)
    {
        const CxFile::EOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, comMode, true);
        xTEST_DIFF(false, m_bRes);

        int iFile = CxFile::_iGetHandle(sfFile.pGet());
        xTEST_DIFF((int)CxFile::etError, iFile);

        FILE *pfFile = CxFile::_pfGetHandle(iFile, comMode);
        xTEST_PTR(pfFile);
    }
#endif

    //--------------------------------------------------
    //_sGetOpenMode
    xTEST_CASE(cullBlockLoops)
    {
        std::vector< std::pair<CxFile::EOpenMode, std::tstring> > vpData;

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
            std::tstring                sRes  = vpData.at(i).second;

            m_sRes = CxFile::_sGetOpenMode(omRes);
            xTEST_EQ(sRes, m_sRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
