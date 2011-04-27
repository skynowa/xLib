/****************************************************************************
* Class name:  CxTest_CxStdioFile
* Description: test CxStdioFile
* File name:   CxTest_CxStdioFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxStdioFileH
#define CxTest_CxStdioFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxStdioFile.h>
//---------------------------------------------------------------------------
class CxTest_CxStdioFile : public CxTest {
	public:
		CxTest_CxStdioFile();
		virtual     ~CxTest_CxStdioFile();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxStdioFile
CxTest_CxStdioFile::CxTest_CxStdioFile() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxStdioFile
CxTest_CxStdioFile::~CxTest_CxStdioFile() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxStdioFile::bUnit() {
    const tString csStr         = xT("=New test string bl-bla-bla=");
    const tString csFilePath    = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");
    const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");
    const tString csEofStr      = xT("\r\n\r\n");

    tString sBuffWrite          = xT("<test1>\n<test2>\n<test3>\n\n<...>");
    tString sBuffRead           = xT("");       sBuffRead.resize(1024);

    CxStdioFile F;


    /****************************************************************************
    *	open, get
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsValid()
    {
        m_bRes = F.bIsValid();
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT_MSG(FALSE != m_bRes, csFilePath.c_str());

        m_bRes = F.bIsValid();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bReopen
    {
        m_bRes = F.bReopen(csFilePath, CxStdioFile::omOpenReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsValid();
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bAttach
    {
        #if xTEMP_DISABLED
            CxStdioFile _F;

            m_bRes = _F.bAttach(stdout);
            xASSERT(FALSE != m_bRes);

            m_bRes = _F.bIsValid();
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //--------------------------------------------------
    //pGet
    {
        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    {
        m_sRes = F.sGetPath();
        xASSERT(csFilePath == m_sRes);
    }


    /****************************************************************************
    *	read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite
    {
        size_t uiW = F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size() * sizeof(tString::value_type));
        xUNUSED(uiW);
    }

    //-------------------------------------
    //uiRead
    {
        size_t uiR = F.uiRead(&sBuffRead.at(0), sBuffRead.size());
        xUNUSED(uiR);
    }

    //-------------------------------------
    //bReadAll, bWriteAll
    {
        //TODO: BOOL bReadAll     (LPVOID pvBuff,        const size_t cuiBuffSize, const size_t uiBlockSize) const;
        //TODO: BOOL bWriteAll    (const LPVOID pcvBuf,  const size_t cuiBuffSize, const size_t uiBlockSize) const;
    }

    //-------------------------------------
    //bReadAll, bWriteAll
    {
        const size_t  uiBlockSize[] = {1, 2, 10, 20, 50, 64, 123, 512, 1024, 2356, 4096, 8192/*, 16384, 32768, 65536, 131072*/};
        const uString sContent(138699, 5);

        uString       sText1;
        uString       sText2;

        for (size_t i = 0; i < xARRAY_SIZE(uiBlockSize); ++ i) {
            //-------------------------------------
            //bWriteAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), CxStdioFile::omBinWrite);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bWriteAll(sContent, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //bReadAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), CxStdioFile::omBinRead);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bReadAll(&sText1, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //bWriteAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxStdioFile::omBinWrite);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bWriteAll(sText1, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //xASSERT
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), CxStdioFile::omBinRead);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bReadAll(&sText2, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);

                xASSERT(sText1.size() == sText2.size());
                xASSERT(sText1        == sText2);
            }
        } //for
    }

    //-------------------------------------
    //bWriteLine
    {
        m_bRes = F.bWriteLine(sBuffWrite);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bReadLine
    {
        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bReadLine(&sBuffRead.at(0), sBuffRead.size() * sizeof(tString::value_type));
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bWriteString
    {
        m_bRes = F.bWriteString(xT("qwerty..."));
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bWriteChar
    {
        m_bRes = F.bWriteChar(xT('W'));
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //cReadChar, bUngetChar
    {
        TCHAR chChar = F.cReadChar();

        m_bRes = F.bUngetChar(chChar);
        xASSERT(FALSE != m_bRes);
    }


    /****************************************************************************
    *	formatted input/output
    *
    *****************************************************************************/

    //-------------------------------------
    //iWrite
    {
        INT iResFprintf = F.iWrite(xT("%s"), xT("xxx"));
        xASSERT(0 < iResFprintf);
    }

    //-------------------------------------
    //iWriteV
    {
        struct SWriter {
            static void
            DoV(const CxStdioFile &csfFile, LPCTSTR pcszFormat, ...) {
                va_list args = NULL;
                va_start(args, pcszFormat);

                INT iRes = csfFile.iWriteV(pcszFormat, args);
                xASSERT(CxStdioFile::etError != iRes);

                va_end(args);
            };
        };

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *	other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    {
        m_bRes = F.bLocking(CxStdioFile::lmLock, 10);
        xASSERT(FALSE == m_bRes);

        m_bRes = F.bLocking(CxStdioFile::lmUnlock, 10);
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bSetPosition
    {
        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //liGetPosition
    {
        LONG liRes = F.liGetPosition();
        xASSERT(0 == liRes);
    }

    //-------------------------------------
    //liGetSize
    {
        LONG _liSize = F.liGetSize();
        xASSERT(0 <= _liSize);
    }

    //-------------------------------------
    //bChsize
    {
        m_bRes = F.bChsize(0);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    {
        m_bRes = F.bSetVBuff(NULL/*&sBuffRead.at(0)*/, CxStdioFile::bmFull, sBuffRead.size() * 2);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetMode
    {
        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxStdioFile::tmBinary);
            xASSERT(FALSE != m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: xOS_LINUX
        #endif
    }

    //-------------------------------------
    //bSetMode
    {
        #if defined(xOS_WIN)
            m_bRes = F.bSetMode(CxStdioFile::tmText);
            xASSERT(FALSE != m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: xOS_LINUX
        #endif
    }


    /****************************************************************************
    *	Error-handling:
    *
    *****************************************************************************/

    //-------------------------------------
    //bIsEof
    {
        m_bRes = F.bIsEof();
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bIsError
    {
        m_bRes = F.bIsError();
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    {
        m_bRes = F.bErrorClear();
        xASSERT(FALSE != m_bRes);
    }


    /****************************************************************************
    *	closing
    *
    *****************************************************************************/

    //-------------------------------------
    //bFlush
    {
        m_bRes = F.bFlush();
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsValid();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bClose
    {
        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsValid();
        xASSERT(FALSE == m_bRes);
    }


    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsFile
    {
        m_bRes = CxStdioFile::bIsFile(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bIsFile(xT(""));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxStdioFile::bIsFile(sGetWorkDirPath());
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bIsExists
    {
        m_bRes = CxStdioFile::bIsExists(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bIsExists(csFilePath + xT("wrong_path"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxStdioFile::bIsExists(xT(""));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxStdioFile::bIsExists(sGetWorkDirPath());
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bAccess
    {
        m_bRes = CxStdioFile::bAccess(csFilePath, CxStdioFile::amExistence);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bChmod
    {
        m_bRes = CxStdioFile::bChmod(csFilePath, CxStdioFile::pmReadWrite);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bRename
    {
        m_bRes = CxStdioFile::bRename(csFilePath, csNewFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //sCreateTempFileName
    {
        tString sTemp = CxStdioFile::sCreateTemp(CxPath::sGetExe(), sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"));
        //xTRACEV(xT("sTemp: %s"), sTemp.c_str());
        xASSERT(false                  == sTemp.empty());
        ////xASSERT(CxPath::sGetDir(sTemp) == sGetWorkDirPath() + CxConst::xSLASH + xT("Temp"));
        ////xASSERT(TRUE                   == CxStdioFile::bIsExists(sTemp));
    }

    //-------------------------------------
    //bReadFile
    {
        //////std::vector<tString> vecsFile;
        //////m_bRes = CxStdioFile::bReadFile(csNewFilePath, &vecsFile);
        //////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bReadFile
    {
        std::vector<TCHAR> vecchVector;
        m_bRes = CxStdioFile::bReadFile(csNewFilePath, &vecchVector);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bReadFile
    {
        tString sFile;
        m_bRes = CxStdioFile::bReadFile(csNewFilePath, &sFile);
        xASSERT(TRUE  == m_bRes);
        xASSERT(false == sFile.empty());
    }

    //-------------------------------------
    //bReadFile, bWriteFile (uString)
    {
        #if xTEMP_DISABLED
            m_bRes = CxStdioFile::bReadFile(csFilePath, &m_usRes);
            xASSERT_MSG(FALSE != m_bRes, csFilePath.c_str());

            m_bRes = CxStdioFile::bWriteFile(csNewFilePath, m_usRes);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bCopy
    {
        CxStdioFile   _F;
        const tString sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const tString sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        m_bRes = _F.bOpen(sFilePathFrom, CxStdioFile::omBinCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = _F.bChsize(1024 * 1024 * 5);
        xASSERT(FALSE != m_bRes);

        m_bRes = _F.bClose();
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bCopy(sFilePathFrom, sFilePathTo);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bMove
    {
        m_bRes = CxStdioFile::bMove(csNewFilePath, sGetWorkDirPath());
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bUnlink
    {
        #if xTEMP_DISABLED
            m_bRes = CxStdioFile::bUnlink(csNewFilePath);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    //-------------------------------------
    //bRemove
    {
        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //TODO: bWipe
    {
        #if xTEMP_DISABLED
            m_bRes = CxStdioFile::bWipe(csNewFilePath, 10);
            xASSERT(FALSE != m_bRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxStdioFileH
