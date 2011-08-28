/****************************************************************************
* Class name:  CxTest_CxFile
* Description: test CxFile
* File name:   CxTest_CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxFile.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxFile
CxTest_CxFile::CxTest_CxFile() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFile
CxTest_CxFile::~CxTest_CxFile() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxFile::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *	prepare
    *
    *****************************************************************************/

    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bDelete(csFilePath);
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
        CxFile F;

        for (size_t i = 0; i < 1; ++ i) {
            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRes = F.bReopen(csFilePath, CxFile::omOpenReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            CxFile _F;

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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        std::tstring sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        std::tstring sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xASSERT_EQ(sBuffWrite, sBuffRead);
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

            m_bRes = F.bOpen(csFilePath, CxFile::omBinWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWrite(sContent);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinRead, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bRead(&usText1);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRes = F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWrite(usText1);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinRead, TRUE);
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
        std::tstring sBuffWrite = xT("<test1><test2><test3><...>");
        std::tstring sBuffRead  = xT("");

        //bWriteLine
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //bReadLine
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omRead, TRUE);
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

        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_chRes = F.chReadChar();
        xASSERT_EQ(chChar, m_chRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = F.bWriteChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = F.bUngetChar(chChar);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        const time_t ctmCreate   = 1305748663;
        const time_t ctmAccess   = 1305753000;
        const time_t ctmModified = 1305753052;

        m_bRes = CxFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRes = CxFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
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
        const std::tstring csTestContent = xT("sz dkfjhsld2345234kfjfsd\tfjklg    23hsd5467ml ksd\tfcsjklsecfgsjk drbf");

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            INT iResFprintf = F.iWrite(csTestContent.c_str());
            xASSERT_LESS(0, iResFprintf);
        }

        std::tstring sContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omRead, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
            DoV(const CxFile &csfFile, LPCTSTR pcszFormat, ...) {
                va_list args;
                xVA_START(args, pcszFormat);

                INT iRes = csfFile.iWriteV(pcszFormat, args);
                xASSERT_NOT_EQ((INT)CxFile::etError, iRes);

                xVA_END(args);
            };
        };

        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bResize(1024);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bLocking(CxFile::lmLock, 10);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bLocking(CxFile::lmUnlock, 10);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetPosition(0, CxFile::ppBegin);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        LONG liRes = F.liGetPosition();
        xASSERT_EQ(0L, liRes);
    }

    //-------------------------------------
    //liGetSize
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG culNewSize = 1024;

        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bResize(0);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sBuffRead;       sBuffRead.resize(1024);

        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bSetVBuff(&sBuffRead.at(0), CxFile::bmFull, sBuffRead.size() * 2);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxFile::tmBinary);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: bSetMode
        #endif
    }

    //-------------------------------------
    //bSetMode
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxFile::tmText);
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
        CxFile F;

        m_bRes = F.bIsValid();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bIsOpen();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsEof();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsError
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bIsError();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
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
    m_bRes = bUnitPrivate(cullBlockLoops);
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
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bIsFile(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsFile(xT(""));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsFile(sGetWorkDirPath());
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bIsExists(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath + xT("wrong_path"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(xT(""));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(sGetWorkDirPath());
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bAccess
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bAccess(csFilePath, CxFile::amExistence);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bChmod
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFile::bChmod(csFilePath, CxFile::pmReadWrite);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRename
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csFilePath, xT("Simple text"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bRename(csFilePath, csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sTempCreate, bTempClose
    xTEST_BLOCK(cullBlockLoops)
    {
        #if 1
            FILE *pfFileHandle = NULL;

            std::tstring sTempFilePath = CxFile::sTempCreate(CxPath::sGetExe(), sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"), &pfFileHandle);
            #if xTEST_IGNORE
                xTRACEV(xT("\tsTemp: %s"), sTempFilePath.c_str());
            #endif

            m_bRes = CxFile::bTempClose(&pfFileHandle);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFile::bDelete(sTempFilePath);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_BLOCK(cullBlockLoops)
    {
        const ULONGLONG cullLinesNum = 17;
        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        ULONGLONG ullLinesNum = CxFile::ullGetLines(csFilePath);
        xASSERT_EQ(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const std::tstring sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        {
            CxFile F;

            m_bRes = F.bOpen(sFilePathFrom, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bResize(1024 * 5);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, FALSE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(sFilePathTo);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bCopy(sFilePathFrom, sFilePathTo, TRUE);
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(sGetWorkDirPath() + CxConst::xSLASH + csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bMove(csNewFilePath, sGetWorkDirPath());
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bUnlink
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEMP_DISABLED
            m_bRes = CxFile::bUnlink(csNewFilePath);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bClear(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bDelete(csNewFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTryDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

            for (size_t i = 0; i < 20; ++ i) {
                if (i < 10) {
                    CxFile F;

                    m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    m_bRes = F.bResize(1024);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmLock, 10);
                    xASSERT_NOT_EQ(FALSE, m_bRes);

                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 2000);
                    xASSERT_EQ(FALSE, m_bRes);

                    m_bRes = F.bLocking(CxFile::lmUnlock, 10);
                    xASSERT_NOT_EQ(FALSE, m_bRes);
                } else {
                    //try
                    m_bRes = CxFile::bTryDelete(csFilePath, 33);
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
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_NOT_EQ(static_cast<INT>( CxFile::etError ), m_iRes);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRes = CxFile::bWipe(csFilePath, 10);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }


    /****************************************************************************
    *   static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (std::tstring)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sFileContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::tstring sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(sFileContent.size(), sStr.size());
        xASSERT_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sFileContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, sFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::tstring sStr;
        m_bRes = CxFile::bTextRead(csFilePath, &sStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(sFileContent.size(), sStr.size());
        xASSERT_EQ(sFileContent, sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::tstring> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::vector<std::tstring> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::tstring> vsFileContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, &vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, vsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::vector<std::tstring> vsStr;
        m_bRes = CxFile::bTextRead(csFilePath, &vsStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<std::tstring, std::tstring> cmsFileContent;
        const std::tstring              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::map<std::tstring, std::tstring> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::map<std::tstring, std::tstring> cmsFileContent;
        const std::tstring              csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::map<std::tstring, std::tstring> msStr;
        m_bRes = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //-------------------------------------
    //binary
    xTEST_BLOCK(cullBlockLoops)
    {
        std::ustring usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_LESS(0, m_iRes);

            m_bRes = F.bResize(1024 * 5);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT_LESS(0, m_iRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_BLOCK(cullBlockLoops)
    {
        std::ustring usFileContent;

        {
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        m_bRes = CxFile::bBinWrite(csFilePath, usFileContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        std::ustring usStr;
        m_bRes = CxFile::bBinRead(csFilePath, &usStr);
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
            CxFile F;

            m_bRes = F.bOpen(csFilePath, CxFile::omBinCreateReadWrite, TRUE);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = F.bResize(cliFileSize);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        for (size_t i = 0; i < 10; ++ i) {
            m_sRes = CxFile::sBackup(csFilePath, sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"), TRUE);
            xASSERT_EQ(false, m_sRes.empty());
        }

        m_bRes = CxDir::bDeleteForce(sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir"));
        xASSERT_NOT_EQ(FALSE, m_bRes);
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

    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFile sfFile;

        m_bRes = sfFile.bOpen(csFilePath, CxFile::omRead, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_iRes = CxFile::_iGetHandle( sfFile.pGet() );
        xASSERT_NOT_EQ((INT)CxFile::etError, m_iRes);
    }

    //--------------------------------------------------
    //_pfGetHandle
#if xTODO
    xTEST_BLOCK(cullBlockLoops)
    {
        const CxFile::EOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        m_bRes = sfFile.bOpen(csFilePath, comMode, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        INT iFile = CxFile::_iGetHandle(sfFile.pGet());
        xASSERT_NOT_EQ((INT)CxFile::etError, iFile);

        FILE *pfFile = CxFile::_pfGetHandle(iFile, comMode);
        xASSERT_PTR(pfFile);
    }
#endif

    //--------------------------------------------------
    //_sGetOpenMode
    xTEST_BLOCK(cullBlockLoops)
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
            xASSERT_EQ(sRes, m_sRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
