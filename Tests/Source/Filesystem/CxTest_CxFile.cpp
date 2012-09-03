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
    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFile::bDelete(csFilePath);
        xTEST_EQ(true, m_bRv);
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
            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }
    }

    //-------------------------------------
    //bReopen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        for (size_t i = 0; i < 7; ++ i) {
            m_bRv = F.bReopen(csFilePath, CxFile::omOpenReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }
    }

    //--------------------------------------------------
    //bAttach
    xTEST_CASE(cullCaseLoops)
    {
        CxFile _F;

        m_bRv = _F.bAttach(stdout);
        xTEST_EQ(true, m_bRv);

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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        FILE *pFile = F.pGet();
        xTEST_PTR(pFile);
    }

    //-------------------------------------
    //sGetPath
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omBinWrite, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bWrite(sContent);
            xTEST_EQ(true, m_bRv);
        }

        //-------------------------------------
        //bRead
        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bRead(&usText1);
            xTEST_EQ(true, m_bRv);
        }

        //-------------------------------------
        //bWrite
        {
            CxFile F;

            m_bRv = F.bCreate(sGetTempDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxFile::omBinWrite, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bWrite(usText1);
            xTEST_EQ(true, m_bRv);
        }

        //-------------------------------------
        //xASSERT
        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omBinRead, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bRead(&usText2);
            xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omWrite, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bWriteLine(sBuffWrite);
            xTEST_EQ(true, m_bRv);
        }

        //bReadLine
        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xTEST_EQ(true, m_bRv);
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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bWriteChar(chChar);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRv);
        m_chRv = F.chReadChar();
        xTEST_EQ(chChar, m_chRv);

        m_bRv = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRv);
        m_bRv = F.bWriteChar(chChar);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRv);
        m_bRv = F.bUngetChar(chChar);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bClear();
        xTEST_EQ(true, m_bRv);
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

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, false);
            xTEST_EQ(true, m_bRv);
        }

        const time_t ctmCreate   = 1319714265;
        const time_t ctmAccess   = 1319714452;
        const time_t ctmModified = 1319714452;

        m_bRv = CxFile::bSetTime(csFilePath, ctmCreate, ctmAccess, ctmModified);
        xTEST_EQ(true, m_bRv);

        time_t tmCreate   = 0;
        time_t tmAccess   = 0;
        time_t tmModified = 0;

        m_bRv = CxFile::bGetTime(csFilePath, &tmCreate, &tmAccess, &tmModified);
        xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            int iResFprintf = F.iWrite(csTestContent.c_str());
            xTEST_LESS(0, iResFprintf);
        }

        std::tstring_t sContent;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omRead, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bRead(&sContent);
            xTEST_EQ(true, m_bRv);
        }

        xTEST_EQ(csTestContent, sContent);
    }

    //-------------------------------------
    //iWrite
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bResize(1024);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bLocking(CxFile::lmLock, 10);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bLocking(CxFile::lmUnlock, 10);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bSetPosition(0, CxFile::ppBegin);
        xTEST_EQ(true, m_bRv);

        long_t liRv = F.liGetPosition();
        xTEST_EQ(0L, liRv);
    }

    //-------------------------------------
    //llGetSize
    xTEST_CASE(cullCaseLoops)
    {
        const longlong_t cllNewSize = 1024LL;

        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bResize(cllNewSize);
        xTEST_EQ(true, m_bRv);

        longlong_t llSize = F.llGetSize();
        xTEST_EQ(cllNewSize, llSize);
    }

    //-------------------------------------
    //bResize
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bResize(0);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bSetVBuff
    xTEST_CASE(cullCaseLoops)
    {
        std::string asBuffRead;       asBuffRead.resize(1024);

        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bSetVBuff(&asBuffRead.at(0), CxFile::bmFull, asBuffRead.size() * 2);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bSetMode
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        #if xOS_ENV_WIN
            m_bRv = F.bSetMode(CxFile::tmBinary);
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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        #if xOS_ENV_WIN
            m_bRv = F.bSetMode(CxFile::tmText);
            xTEST_EQ(true, m_bRv);
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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsValid();
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bClose();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bIsOpen
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bIsOpen();
        xTEST_EQ(false, m_bRv);

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsOpen();
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bClose();
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsOpen();
        xTEST_EQ(false, m_bRv);
    }

    //--------------------------------------------------
    //bIsEmpty
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsEmpty();
        xTEST_EQ(true, m_bRv);

        m_iRv = F.iWrite(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRv);

        m_bRv = F.bIsEmpty();
        xTEST_EQ(false, m_bRv);

        m_bRv = F.bClear();
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsEmpty();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bIsEof
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsEof();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bIsError
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsError();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bErrorClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bErrorClear();
        xTEST_EQ(true, m_bRv);
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

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bFlush();
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bIsValid();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bClose
    xTEST_CASE(cullCaseLoops)
    {
        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bClose();
        xTEST_EQ(true, m_bRv);

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
        m_bRv = CxFile::bAccess(csFilePath, CxFile::amExistence);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bChmod
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFile::bChmod(csFilePath, CxFile::pmReadWrite);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bRename
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRv = CxFile::bTextWrite(csFilePath, xT("Simple text"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bRename(csFilePath, csNewFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //ullGetLines
    xTEST_CASE(cullCaseLoops)
    {
        const ulonglong_t cullLinesNum = 17;
        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                m_bRv = F.bWriteLine( CxString::lexical_cast(i) );
                xTEST_EQ(true, m_bRv);
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

            m_bRv = F.bCreate(sFilePathFrom, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bResize(1024 * 5);
            xTEST_EQ(true, m_bRv);
        }

        m_bRv = CxFile::bCopy(sFilePathFrom, sFilePathTo, false);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bIsExists(sFilePathTo);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bCopy(sFilePathFrom, sFilePathTo, true);
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //bMove
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRv = CxFile::bTextWrite(csNewFilePath, xT("Simple text"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bDelete(sGetTempDirPath() + CxConst::xSLASH + csNewFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bMove(csNewFilePath, sGetTempDirPath());
        xTEST_EQ(true, m_bRv);
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

        m_bRv = CxFile::bClear(csNewFilePath);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bDelete
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csNewFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRv = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bDelete(csNewFilePath);
        xTEST_EQ(true, m_bRv);
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

                    m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
                    xTEST_EQ(true, m_bRv);

                    m_bRv = F.bResize(1024);
                    xTEST_EQ(true, m_bRv);

                    m_bRv = F.bLocking(CxFile::lmLock, 10);
                    xTEST_EQ(true, m_bRv);

                    //try
                    m_bRv = CxFile::bTryDelete(csFilePath, 2000);
                    xTEST_EQ(false, m_bRv);

                    m_bRv = F.bLocking(CxFile::lmUnlock, 10);
                    xTEST_EQ(true, m_bRv);
                } else {
                    //try
                    m_bRv = CxFile::bTryDelete(csFilePath, 33);
                    xTEST_EQ(true, m_bRv);
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

            m_bRv = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_DIFF(static_cast<int>( CxFile::etError ), m_iRv);
        }

        for (size_t i = 0; i < 3; ++ i) {
            m_bRv = CxFile::bWipe(csFilePath, 10);
            xTEST_EQ(true, m_bRv);
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

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            for (size_t i = 0; i < 7; ++ i) {
                m_bRv = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_EQ(true, m_bRv);
            }
        }

        m_bRv = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_EQ(true, m_bRv);

        std::tstring_t sStr;
        m_bRv = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_EQ(true, m_bRv);

        xTEST_EQ(sFileContent.size(), sStr.size());
        xTEST_EQ(sFileContent, sStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sFileContent;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }

        m_bRv = CxFile::bTextRead(csFilePath, &sFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, sFileContent);
        xTEST_EQ(true, m_bRv);

        std::tstring_t sStr;
        m_bRv = CxFile::bTextRead(csFilePath, &sStr);
        xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRv = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xTEST_EQ(true, m_bRv);
            }
        }

        m_bRv = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_EQ(true, m_bRv);

        std::vec_tstring_t vsStr;
        m_bRv = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_EQ(true, m_bRv);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsFileContent;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }

        m_bRv = CxFile::bTextRead(csFilePath, &vsFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, vsFileContent);
        xTEST_EQ(true, m_bRv);

        std::vec_tstring_t vsStr;
        m_bRv = CxFile::bTextRead(csFilePath, &vsStr);
        xTEST_EQ(true, m_bRv);

        xTEST_EQ(vsFileContent.size(), vsStr.size());
        xASSERT(vsFileContent == vsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    xTEST_CASE(cullCaseLoops)
    {
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            for (size_t i = 0; i < 10; ++ i) {
                m_bRv = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xTEST_EQ(true, m_bRv);
            }
        }

        m_bRv = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_EQ(true, m_bRv);

        std::map_tstring_t msStr;
        m_bRv = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_EQ(true, m_bRv);

        xTEST_EQ(cmsFileContent.size(), msStr.size());
        xASSERT(cmsFileContent == msStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::map_tstring_t   cmsFileContent;
        const std::tstring_t csSeparator = CxConst::xEQUAL;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }

        m_bRv = CxFile::bTextRead(csFilePath, csSeparator, &cmsFileContent);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bTextWrite(csFilePath, csSeparator, cmsFileContent);
        xTEST_EQ(true, m_bRv);

        std::map_tstring_t msStr;
        m_bRv = CxFile::bTextRead(csFilePath, csSeparator, &msStr);
        xTEST_EQ(true, m_bRv);

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

            m_bRv = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRv);

            m_bRv = F.bResize(1024 * 5);
            xTEST_EQ(true, m_bRv);

            m_iRv = F.iWrite(xT("0123456789"));
            xTEST_LESS(0, m_iRv);
        }

        m_bRv = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_EQ(true, m_bRv);

        std::ustring_t usStr;
        m_bRv = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_EQ(true, m_bRv);

        xASSERT(usFileContent == usStr);
    }

    //empty content
    xTEST_CASE(cullCaseLoops)
    {
        std::ustring_t usFileContent;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);
        }

        m_bRv = CxFile::bBinWrite(csFilePath, usFileContent);
        xTEST_EQ(true, m_bRv);

        std::ustring_t usStr;
        m_bRv = CxFile::bBinRead(csFilePath, &usStr);
        xTEST_EQ(true, m_bRv);

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
    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");


    //--------------------------------------------------
    //_iGetHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxFile sfFile;

        m_bRv = sfFile.bCreate(csFilePath, CxFile::omRead, true);
        xTEST_EQ(true, m_bRv);

        m_iRv = CxFile::_iGetHandle( sfFile.pGet() );
        xTEST_DIFF((int)CxFile::etError, m_iRv);
    }

    //--------------------------------------------------
    //_pfGetHandle
    #if xTODO
    xTEST_CASE(cullCaseLoops)
    {
        const CxFile::EOpenMode comMode = CxFile::omOpenReadWrite;

        CxFile sfFile;

        m_bRv = sfFile.bCreate(csFilePath, comMode, true);
        xTEST_EQ(true, m_bRv);

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
            std::tstring_t                sRv  = vpData.at(i).second;

            m_sRv = CxFile::_sGetOpenMode(omRes);
            xTEST_EQ(sRv, m_sRv);
        }
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
