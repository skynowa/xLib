/****************************************************************************
* Class name:  CxTest_CxStdioFile
* Description: test CxStdioFile
* File name:   CxTest_CxStdioFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxStdioFile.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxStdioFile
CxTest_CxStdioFile::CxTest_CxStdioFile() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxStdioFile
CxTest_CxStdioFile::~CxTest_CxStdioFile() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxStdioFile::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *	prepare
    *
    *****************************************************************************/

    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxStdioFile::bDelete(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *	open, get
    *
    *****************************************************************************/

    //-------------------------------------
    //bOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        for (size_t i = 0; i < 1; ++ i) {
            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRes = F.bReopen(csFilePath, CxStdioFile::omOpenReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            CxStdioFile _F;

            m_bRes = _F.bAttach(stdout);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = _F.bIsValid();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //pGet
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_sRes = F.sGetPath();
        xASSERT_EQ(csFilePath, m_sRes);
    }


    /****************************************************************************
    *	read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite, uiRead
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        tString sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xASSERT_EQ(sBuffWrite, sBuffRead);
    }

    //-------------------------------------
    //bRead, bWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        const uString sContent(10, 5);

        uString       usText1;
        uString       usText2;

        //-------------------------------------
        //bWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWrite(sContent);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bRead(&usText1);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxStdioFile::omBinWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWrite(usText1);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bRead(&usText2);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            xASSERT_EQ(usText1.size(), usText2.size());
            xASSERT(usText1 == usText2);
        }
    }

    //-------------------------------------
    //bWriteLine, bReadLine
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sBuffWrite = xT("<test1><test2><test3><...>");
        tString sBuffRead  = xT("");

        //bWriteLine
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //bReadLine
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //assert
        xASSERT_EQ(sBuffWrite.size(), sBuffRead.size());
        xASSERT_EQ(sBuffWrite,        sBuffRead);
    }

    //-------------------------------------
    //bWriteChar, chReadChar, bUngetChar
    xTEST_BLOCK(cullBlockLoops)
    {
        const TCHAR chChar = xT('W');

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_chRes = F.chReadChar();
        xASSERT_EQ(chChar, m_chRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = F.bWriteChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = F.bUngetChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *	times
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bGetTime, bSetTime
    xTEST_BLOCK(cullBlockLoops)
    {
    #if xTODO
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        const time_t ctmCreate   = 1305748663;
        const time_t ctmAccess   = 1305753000;
        const time_t ctmModified = 1305753052;

        m_bRes = CxStdioFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRes = CxStdioFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        #if xTODO
            xASSERT_EQ(ctmCreate, tmCreate);
        #endif
        xASSERT_EQ(ctmAccess,   tmAccess);
        xASSERT_EQ(ctmModified, tmModified);
    #endif
    }


    /****************************************************************************
    *	formatted input/output
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bRead
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csTestContent = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            INT iResFprintf = F.iWrite(csTestContent.c_str());
            xASSERT_LESS(0, iResFprintf);
        }

        tString sContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bRead(&sContent);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        xASSERT_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        INT iResFprintf = F.iWrite(xT("%s"), xT("xxx"));
        xASSERT_LESS(0, iResFprintf);
    }

    //-------------------------------------
    //iWriteV
    xTEST_BLOCK(cullBlockLoops)
    {
        struct SWriter {
            static void
            DoV(const CxStdioFile &csfFile, LPCTSTR pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                INT iRes = csfFile.iWriteV(pcszFormat, args);
                xASSERT_NOT_EQ((INT)CxStdioFile::etError, iRes);

                xVA_END(args);
            };
        };

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *	other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bResize(1024);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bLocking(CxStdioFile::lmLock, 10);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bLocking(CxStdioFile::lmUnlock, 10);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        LONG liRes = F.liGetPosition();
        xASSERT_EQ(0L, liRes);
    }

    //-------------------------------------
    //liGetSize
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG culNewSize = 1024;

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bResize(culNewSize);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        LONG liSize = F.liGetSize();
        xASSERT_EQ(culNewSize, liSize);
    }

    //-------------------------------------
    //bResize
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bResize(0);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sBuffRead;       sBuffRead.resize(1024);

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetVBuff(&sBuffRead.at(0), CxStdioFile::bmFull, sBuffRead.size() * 2);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxStdioFile::tmBinary);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxStdioFile::tmText);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: bSetMode
        #endif
    }


    /****************************************************************************
    *	Error-handling:
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsValid
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bIsValid();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bClose();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bIsOpen();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsOpen();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bClose();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsOpen();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsEmpty();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_iRes = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xASSERT_LESS(0, m_iRes);

        m_bRes = F.bIsEmpty();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = F.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsEmpty();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsEof
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsEof();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsError
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsError();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bErrorClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *	closing
    *
    *****************************************************************************/

    //-------------------------------------
    //bFlush
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bFlush();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bClose
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bClose();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsValid();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //bUnit1
    m_bRes = bUnit1(cullBlockLoops);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    //bUnitePrivate
    m_bRes = bUnitePrivate(cullBlockLoops);
    xASSERT_NOT_EQ(FALSE, m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bUnit1 ()
BOOL
CxTest_CxStdioFile::bUnit1(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxStdioFile::bIsFile(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsFile(xT(""));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsFile(sGetWorkDirPath());
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxStdioFile::bIsExists(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsExists(csFilePath + xT("wrong_path"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsExists(xT(""));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsExists(sGetWorkDirPath());
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bAccess
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxStdioFile::bAccess(csFilePath, CxStdioFile::amExistence);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bChmod
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxStdioFile::bChmod(csFilePath, CxStdioFile::pmReadWrite);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRename
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bTextWrite(csFilePath, xT("Simple text"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bRename(csFilePath, csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sTempCreate, bTempClose
    xTEST_BLOCK(cullBlockLoops)
    {
        INT iFileHandle = - 1;

        tString sTempFilePath = CxStdioFile::sTempCreate(CxPath::sGetExe(), sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"), &iFileHandle);
        #if xTEST_IGNORE
            xTRACEV(xT("\tsTemp: %s"), sTempFilePath.c_str());
        #endif

        xASSERT_EQ(false, sTempFilePath.empty());
        xASSERT_NOT_EQ(FALSE, CxStdioFile::bIsExists(sTempFilePath));

        m_bRes = CxStdioFile::bTempClose(&iFileHandle);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bDelete(sTempFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_BLOCK(cullBlockLoops)
    {
        const ULONGLONG cullLinesNum = 17;
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        ULONGLONG ullLinesNum = CxStdioFile::ullGetLines(csFilePath);
        xASSERT_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const tString sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxStdioFile F;

            m_bRes = F.bOpen(sFilePathFrom, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bResize(1024 * 5);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxStdioFile::bCopy(sFilePathFrom, sFilePathTo, FALSE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bIsExists(sFilePathTo);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bCopy(sFilePathFrom, sFilePathTo, TRUE);
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bDelete(sGetWorkDirPath() + CxConst::xSLASH + csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bMove(csNewFilePath, sGetWorkDirPath());
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bUnlink
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            m_bRes = CxStdioFile::bUnlink(csNewFilePath);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bClear(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxStdioFile F;

                    m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    m_bRes = F.bResize(1024);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxStdioFile::lmLock, 10);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    //try
                    m_bRes = CxStdioFile::bTryDelete(csFilePath, 2000);
                    xASSERT_EQ(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxStdioFile::lmUnlock, 10);
                    xASSERT_NOT_EQ(FALSE, m_bRes);
                } else {
                    //try
                    m_bRes = CxStdioFile::bTryDelete(csFilePath, 33);
                    xASSERT_NOT_EQ(FALSE, m_bRes);
                }
            }
        #endif
    }

    //-------------------------------------
    //bWipe
    xTEST_BLOCK(cullBlockLoops)
    {
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_NOT_EQ(static_cast<INT>( CxStdioFile::etError ), m_iRes);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = CxStdioFile::bWipe(csFilePath, 10);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (tString)
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        tString sStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &sStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(sFileContent.size(), sStr.size());
        xASSERT_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        tString sStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &sStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(sFileContent.size(), sStr.size());
        xASSERT_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<tString> vsFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::vector<tString> vsStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &vsStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<tString> vsFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::vector<tString> vsStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &vsStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<tString, tString> cmsFileContent;
        const tString              csSeparator = CxConst::xEQUAL;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::map<tString, tString> msStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &msStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<tString, tString> cmsFileContent;
        const tString              csSeparator = CxConst::xEQUAL;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::map<tString, tString> msStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &msStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_BLOCK(cullBlockLoops)
    {
        uString usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_LESS(0, m_iRes);

            m_bRes = F.bResize(1024 * 5);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_LESS(0, m_iRes);
        }

        m_bRes = CxStdioFile::bBinWrite(csFilePath, usFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        uString usStr;
        m_bRes = CxStdioFile::bBinRead(csFilePath, &usStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        uString usFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxStdioFile::bBinWrite(csFilePath, usFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        uString usStr;
        m_bRes = CxStdioFile::bBinRead(csFilePath, &usStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

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
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bResize(cliFileSize);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        for (size_t i = 0; i < 10; ++ i) {
            m_sRes = CxStdioFile::sBackup(csFilePath, sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"), TRUE);
            xASSERT_EQ(false, m_sRes.empty());
        }

        m_bRes = CxDir::bDeleteForce(sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"));
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnitePrivate ()
BOOL
CxTest_CxStdioFile::bUnitePrivate(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStdioFile sfFile;

        m_bRes = sfFile.bOpen(csFilePath, CxStdioFile::omRead, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_iRes = CxStdioFile::_iGetHandle( sfFile.pGet() );
        xASSERT_NOT_EQ((INT)CxStdioFile::etError, m_iRes);
    }

    //--------------------------------------------------
    //_pfGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        const CxStdioFile::EOpenMode comMode = CxStdioFile::omRead;

        CxStdioFile sfFile;

        m_bRes = sfFile.bOpen(csFilePath, comMode, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        INT iFile = CxStdioFile::_iGetHandle(sfFile.pGet());
        xASSERT_NOT_EQ((INT)CxStdioFile::etError, iFile);

        FILE *pfFile = CxStdioFile::_pfGetHandle(iFile, comMode);
        xASSERT_PTR(pfFile);
    }

    //--------------------------------------------------
    //_sGetOpenMode
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector< std::pair<CxStdioFile::EOpenMode, tString> > vpData;

        vpData.push_back( std::make_pair(CxStdioFile::omRead,               xT("r")) );
        vpData.push_back( std::make_pair(CxStdioFile::omWrite,              xT("w")) );
        vpData.push_back( std::make_pair(CxStdioFile::omAppend,             xT("a")) );
        vpData.push_back( std::make_pair(CxStdioFile::omOpenReadWrite,      xT("r+")) );
        vpData.push_back( std::make_pair(CxStdioFile::omCreateReadWrite,    xT("w+")) );
        vpData.push_back( std::make_pair(CxStdioFile::omOpenReadAppend,     xT("a+")) );

        vpData.push_back( std::make_pair(CxStdioFile::omBinRead,            xT("rb")) );
        vpData.push_back( std::make_pair(CxStdioFile::omBinWrite,           xT("wb")) );
        vpData.push_back( std::make_pair(CxStdioFile::omBinAppend,          xT("ab")) );
        vpData.push_back( std::make_pair(CxStdioFile::omBinOpenReadWrite,   xT("rb+")) );
        vpData.push_back( std::make_pair(CxStdioFile::omBinCreateReadWrite, xT("wb+")) );
        vpData.push_back( std::make_pair(CxStdioFile::omBinOpenReadAppend,  xT("ab+")) );

        for (size_t i = 0; i < vpData.size(); ++ i) {
            CxStdioFile::EOpenMode omRes = vpData.at(i).first;
            tString                sRes  = vpData.at(i).second;

            m_sRes = CxStdioFile::_sGetOpenMode(omRes);
            xASSERT_EQ(sRes, m_sRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
