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
BOOL
CxTest_CxFile::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bDelete(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);
    }


    /****************************************************************************
    *    open, get
    *
    *****************************************************************************/

    //-------------------------------------
    //bCreate
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        for (size_t i = 0; i < 1; ++ i) {
            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRes = F.bReopen(csFilePath, CxFile::omOpenReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile _F;

        m_bRes = _F.bAttach(stdout);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = _F.bIsValid();
        xTEST_DIFF(FALSE, m_bRes);

        FILE *pFile = _F.pDetach();
        xTEST_PTR(pFile);
        xTEST_EQ(stdout, pFile);
    }

    //--------------------------------------------------
    //pGet
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_sRes = F.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }


    /****************************************************************************
    *    read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite, uiRead
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::string_t sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xTEST_EQ(sBuffWrite, sBuffRead);
    }

    //-------------------------------------
    //bRead, bWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::ustring sContent(10, 5);

        std::ustring       usText1;
        std::ustring       usText2;

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bWrite(sContent);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bRead(&usText1);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bCreate(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bWrite(usText1);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinRead, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bRead(&usText2);
            xTEST_DIFF(FALSE, m_bRes);

            xTEST_EQ(usText1.size(), usText2.size());
            xASSERT(usText1 == usText2);
        }
    }

    //-------------------------------------
    //bWriteLine, bReadLine
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sBuffWrite = xT("<test1><test2><test3><...>");
        std::string_t sBuffRead  = xT("");

        //bWriteLine
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //bReadLine
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xTEST_DIFF(FALSE, m_bRes);
        }

        //assert
        xTEST_EQ(sBuffWrite.size(), sBuffRead.size());
        xTEST_EQ(sBuffWrite,        sBuffRead);
    }

    //-------------------------------------
    //bWriteChar, chReadChar, bUngetChar
    xTEST_BLOCK(cullBlockLoops)
    {
        const char_t chChar = xT('W');

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(FALSE, m_bRes);
        m_chRes = F.chReadChar();
        xTEST_EQ(chChar, m_chRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(FALSE, m_bRes);
        m_bRes = F.bWriteChar(chChar);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(FALSE, m_bRes);
        m_bRes = F.bUngetChar(chChar);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bClear();
        xTEST_DIFF(FALSE, m_bRes);
    }


    /****************************************************************************
    *    times
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bGetTime, bSetTime
    xTEST_BLOCK(cullBlockLoops)
    {
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, FALSE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        m_bRes = CxFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xTEST_DIFF(FALSE, m_bRes);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRes = CxFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
        xTEST_DIFF(FALSE, m_bRes);

    #if defined(xOS_ENV_WIN)
        xTEST_EQ(ctmCreate, tmCreate);
    #elif defined(xOS_ENV_UNIX)
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
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csTestContent = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            int iResFprintf = F.iWrite(csTestContent.c_str());
            xTEST_LESS(0, iResFprintf);
        }

        std::string_t sContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omRead, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bRead(&sContent);
            xTEST_DIFF(FALSE, m_bRes);
        }

        xTEST_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        int iResFprintf = F.iWrite(xT("%s"), xT("xxx"));
        xTEST_LESS(0, iResFprintf);
    }

    //-------------------------------------
    //iWriteV
    xTEST_BLOCK(cullBlockLoops)
    {
        struct SWriter {
            static void
            DoV(const CxFile &csfFile, const char_t *pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                int iRes = csfFile.iWriteV(pcszFormat, args);
                xTEST_DIFF((int)CxFile::etError, iRes);

                xVA_END(args);
            };
        };

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *    other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bResize(1024);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bLocking(CxFile::lmLock, 10);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bLocking(CxFile::lmUnlock, 10);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_DIFF(FALSE, m_bRes);

        LONG liRes = F.liGetPosition();
        xTEST_EQ(0L, liRes);
    }

    //-------------------------------------
    //liGetSize
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG culNewSize = 1024;

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bResize(culNewSize);
        xTEST_DIFF(FALSE, m_bRes);

        LONG liSize = F.liGetSize();
        xTEST_EQ(culNewSize, liSize);
    }

    //-------------------------------------
    //bResize
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bResize(0);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bSetVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        #if defined(xOS_ENV_WIN)
            m_bRes = F.bSetMode(CxFile::tmBinary);
            xTEST_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        #if defined(xOS_ENV_WIN)
            m_bRes = F.bSetMode(CxFile::tmText);
            xTEST_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: bSetMode
        #endif
    }


    /****************************************************************************
    *    Error-handling:
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsValid
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bIsValid();
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bIsOpen();
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsOpen();
        xTEST_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_DIFF(FALSE, m_bRes);

        m_iRes = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRes);

        m_bRes = F.bIsEmpty();
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = F.bClear();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsEmpty();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsEof
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsEof();
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsError
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsError();
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bErrorClear();
        xTEST_DIFF(FALSE, m_bRes);
    }


    /****************************************************************************
    *    closing
    *
    *****************************************************************************/

    //-------------------------------------
    //bFlush
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bFlush();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bClose
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xTEST_EQ(FALSE, m_bRes);
    }

    //bUnit1
    m_bRes = bUnit1(cullBlockLoops);
    xTEST_DIFF(FALSE, m_bRes);

    //bUnitePrivate
    m_bRes = bUnitPrivate(cullBlockLoops);
    xTEST_DIFF(FALSE, m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bUnit1 ()
BOOL
CxTest_CxFile::bUnit1(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bIsFile(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bIsFile(xT(""));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsFile(sGetWorkDirPath());
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bIsExists(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath + xT("wrong_path"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(xT(""));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(sGetWorkDirPath());
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxFile::sIsExists(csFilePath);
        xTEST_DIFF(FALSE, CxFile::bIsExists(csFilePath));
        xTEST_EQ(FALSE, CxFile::bIsExists(m_sRes));

        ////xTRACEV(xT("\tCxFile::sIsExists: %s"), m_sRes.c_str());
    }

    //-------------------------------------
    //bAccess
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bAccess(csFilePath, CxFile::amExistence);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bChmod
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bChmod(csFilePath, CxFile::pmReadWrite);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRename
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csFilePath, xT("Simple text"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bRename(csFilePath, csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_BLOCK(cullBlockLoops)
    {
        const ULONGLONG cullLinesNum = 17;
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
                xTEST_DIFF(FALSE, m_bRes);
            }
        }

        ULONGLONG ullLinesNum = CxFile::ullGetLines(csFilePath);
        xTEST_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::string_t sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            m_bRes = F.bCreate(sFilePathFrom, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, FALSE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(sFilePathTo);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, TRUE);
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(sGetWorkDirPath() + CxConst::xSLASH + csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bMove(csNewFilePath, sGetWorkDirPath());
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bUnlink
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            m_bRes = CxFile::bUnlink(csNewFilePath);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bClear(csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
                    xTEST_DIFF(FALSE, m_bRes);

                    m_bRes = F.bResize(1024);
                    xTEST_DIFF(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmLock, 10);
                    xTEST_DIFF(FALSE, m_bRes);

                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 2000);
                    xTEST_EQ(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmUnlock, 10);
                    xTEST_DIFF(FALSE, m_bRes);
                } else {
                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 33);
                    xTEST_DIFF(FALSE, m_bRes);
                }
            }
        #endif
    }

    //-------------------------------------
    //bWipe
    xTEST_BLOCK(cullBlockLoops)
    {
        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_DIFF(static_cast<int>( CxFile::etError ), m_iRes);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = CxFile::bWipe(csFilePath, 10);
            xTEST_DIFF(FALSE, m_bRes);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (std::string_t)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_DIFF(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::string_t sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::string_t sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::string_t> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_DIFF(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::vector<std::string_t> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::string_t> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::vector<std::string_t> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<std::string_t, std::string_t> cmsFileContent;
        const std::string_t              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xTEST_DIFF(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::map<std::string_t, std::string_t> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<std::string_t, std::string_t> cmsFileContent;
        const std::string_t              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::map<std::string_t, std::string_t> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_BLOCK(cullBlockLoops)
    {
        std::ustring usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);

            m_bRes = F.bResize(1024 * 5);
            xTEST_DIFF(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_DIFF(FALSE, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::ustring usFileContent;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_DIFF(FALSE, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_DIFF(FALSE, m_bRes);

        xASSERT(usFileContent == usStr);
    }


    /****************************************************************************
    *   other
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bBackup
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG cliFileSize = 100;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = F.bResize(cliFileSize);
            xTEST_DIFF(FALSE, m_bRes);
        }

        for (size_t i = 0; i < 10; ++ i) {
            m_sRes = CxFile::sBackup(csFilePath, sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"), TRUE);
            xTEST_EQ(false, m_sRes.empty());
        }

        m_bRes = CxDir::bDeleteForce(sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"));
        xTEST_DIFF(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnitPrivate ()
BOOL
CxTest_CxFile::bUnitPrivate(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, CxFile::omRead, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_iRes = CxFile::_iGetHandle( sfFile.pGet() );
        xTEST_DIFF((int)CxFile::etError, m_iRes);
    }

    //--------------------------------------------------
    //_pfGetHandle
#if xTODO
    xTEST_BLOCK(cullBlockLoops)
    {
        const CxFile::EOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        m_bRes = sfFile.bCreate(csFilePath, comMode, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        int iFile = CxFile::_iGetHandle(sfFile.pGet());
        xTEST_DIFF((int)CxFile::etError, iFile);

        FILE *pfFile = CxFile::_pfGetHandle(iFile, comMode);
        xTEST_PTR(pfFile);
    }
#endif

    //--------------------------------------------------
    //_sGetOpenMode
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector< std::pair<CxFile::EOpenMode, std::string_t> > vpData;

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
            std::string_t                sRes  = vpData.at(i).second;

            m_sRes = CxFile::_sGetOpenMode(omRes);
            xTEST_EQ(sRes, m_sRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
