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
    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");


    /****************************************************************************
    *	open, get
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bIsValid
    {
        CxStdioFile F;

        m_bRes = F.bIsValid();
        xASSERT(FALSE == m_bRes);

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsValid();
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bReopen
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bReopen(csFilePath, CxStdioFile::omOpenReadWrite);
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
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
    }

    //-------------------------------------
    //sGetPath
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_sRes = F.sGetPath();
        xASSERT(csFilePath == m_sRes);
    }


    /****************************************************************************
    *	read, write
    *
    *****************************************************************************/

    //-------------------------------------
    //uiWrite, uiRead
    {
        tString sBuffWrite = xT("<test1>\n<test2>\n<test3>\n\n<...>");
        tString sBuffRead  = xT("");       sBuffRead.resize(sBuffWrite.size());

        //uiWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite);
            xASSERT(FALSE != m_bRes);

            F.uiWrite(&sBuffWrite.at(0), sBuffWrite.size());
        }

        //uiRead
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead);
            xASSERT(FALSE != m_bRes);

            F.uiRead(&sBuffRead.at(0), sBuffWrite.size());
        }

        xASSERT_EQUAL(sBuffWrite, sBuffRead);
    }

    //-------------------------------------
    //bRead, bWrite
    {
        const uString sContent(138699, 5);

        uString       sText1;
        uString       sText2;

        //-------------------------------------
        //bWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinWrite);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bWrite(sContent);
            xASSERT(FALSE != m_bRes);
        }

        //-------------------------------------
        //bRead
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bRead(&sText1);
            xASSERT(FALSE != m_bRes);
        }

        //-------------------------------------
        //bWrite
        {
            CxStdioFile F;

            m_bRes = F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxStdioFile::omBinWrite);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bWrite(sText1);
            xASSERT(FALSE != m_bRes);
        }

        //-------------------------------------
        //xASSERT
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinRead);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bRead(&sText2);
            xASSERT(FALSE != m_bRes);

            xASSERT(sText1.size() == sText2.size());
            xASSERT(sText1        == sText2);
        }
    }

    //-------------------------------------
    //bWriteLine, bReadLine
    {
        tString sBuffWrite = xT("<test1><test2><test3><...>");
        tString sBuffRead  = xT("");

        //bWriteLine
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omWrite);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bWriteLine(sBuffWrite);
            xASSERT(FALSE != m_bRes);
        }

        //bReadLine
        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omRead);
            xASSERT(FALSE != m_bRes);

            m_bRes = F.bReadLine(&sBuffRead, sBuffWrite.size());
            xASSERT(FALSE != m_bRes);
        }

        //assert
        xASSERT_EQUAL(sBuffWrite.size(), sBuffRead.size());
        xASSERT_EQUAL(sBuffWrite,        sBuffRead);
    }

    //-------------------------------------
    //bWriteChar, cReadChar, bUngetChar
    {
        const TCHAR chChar = xT('W');

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bWriteChar(chChar);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT(FALSE != m_bRes);

        m_chRes = F.cReadChar();
        xASSERT(chChar == m_chRes);

        m_bRes = F.bWriteChar(chChar);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bUngetChar(chChar);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bClear
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bClear();
        xASSERT(FALSE != m_bRes);
    }


    /****************************************************************************
    *	formatted input/output
    *
    *****************************************************************************/

    //-------------------------------------
    //iWrite
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

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

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        SWriter::DoV(F, xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *	other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bResize(1024);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bLocking(CxStdioFile::lmLock, 10);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bLocking(CxStdioFile::lmUnlock, 10);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetPosition, liGetPosition
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bSetPosition(0, CxStdioFile::ppBegin);
        xASSERT(FALSE != m_bRes);

        LONG liRes = F.liGetPosition();
        xASSERT(0 == liRes);
    }

    //-------------------------------------
    //liGetSize
    {
        const LONG culNewSize = 1024;

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bResize(culNewSize);
        xASSERT(FALSE != m_bRes);

        LONG liSize = F.liGetSize();
        xASSERT(culNewSize == liSize);
    }

    //-------------------------------------
    //bResize
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bResize(0);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetVBuff
    {
        tString sBuffRead;       sBuffRead.resize(1024);

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bSetVBuff(&sBuffRead.at(0), CxStdioFile::bmFull, sBuffRead.size() * 2);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetMode
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

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
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

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
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsEof();
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bIsError
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsError();
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bErrorClear
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

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
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bFlush();
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bIsValid();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bClose
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

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
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

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

    //--------------------------------------------------
    //ullGetLines
    {
        const ULONGLONG cullLinesNum = 33;

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        for (size_t i = 0; i < cullLinesNum; ++ i) {
            m_bRes = F.bWriteLine( CxString::lexical_cast(i) );
            xASSERT(FALSE != m_bRes);
        }

        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);

        ULONGLONG ullLinesNum = CxStdioFile::ullGetLines(csFilePath);

        xASSERT_EQUAL(cullLinesNum, ullLinesNum);
    }

    //-------------------------------------
    //bCopy
    {
        const tString sFilePathFrom = sGetWorkDirPath() + CxConst::xSLASH + xT("test_copy.txt");
        const tString sFilePathTo   = sFilePathFrom + xT("_addition_to_name");

        CxStdioFile F;

        m_bRes = F.bOpen(sFilePathFrom, CxStdioFile::omBinCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bResize(1024 * 1024 * 5);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);


        m_bRes = CxStdioFile::bCopy(sFilePathFrom, sFilePathTo, FALSE);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bIsExists(sFilePathTo);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bCopy(sFilePathFrom, sFilePathTo, TRUE);
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //bMove
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

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

    //--------------------------------------------------
    //bClear
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bClear(csNewFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bDelete
    {
        const tString csNewFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("New.Test.txt");

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bWipe
    {
        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite);
        xASSERT(FALSE != m_bRes);

        m_iRes = F.iWrite(xT("0123456789"));
        xASSERT(FALSE != m_iRes);

        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bWipe(csFilePath, 10);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bWipe(csFilePath, 10);
        xASSERT(FALSE != m_bRes);
    }

    /****************************************************************************
    *	static: utils
    *
    *****************************************************************************/

    //-------------------------------------
    //bTextRead, bTextWrite (tString)
    {
        tString sFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
            xASSERT(FALSE != m_bRes);

            for (size_t i = 0; i < 100; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT(FALSE != m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &sFileContent);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, sFileContent);
        xASSERT(FALSE != m_bRes);

        tString sStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &sStr);
        xASSERT(FALSE != m_bRes);

        xASSERT_EQUAL(sFileContent.size(), sStr.size());
        xASSERT(sFileContent == sStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    {
        std::vector<tString> vecsFileContent;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
            xASSERT(FALSE != m_bRes);

            for (size_t i = 0; i < 100; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifgumoaeriuatgmoi"));
                xASSERT(FALSE != m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, &vecsFileContent);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, vecsFileContent);
        xASSERT(FALSE != m_bRes);

        std::vector<tString> vecsStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, &vecsStr);
        xASSERT(FALSE != m_bRes);

        xASSERT_EQUAL(vecsFileContent.size(), vecsStr.size());
        xASSERT(vecsFileContent == vecsStr);
    }

    //--------------------------------------------------
    //bTextRead, bTextWrite (std::vector)
    {
        std::map<tString, tString> cmapsFileContent;
        const tString              csSeparator = CxConst::xEQUAL;

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite);
            xASSERT(FALSE != m_bRes);

            for (size_t i = 0; i < 100; ++ i) {
                m_bRes = F.bWriteLine(xT("asducfgnoawifg") + csSeparator + xT("umoaeriuatgmoi"));
                xASSERT(FALSE != m_bRes);
            }
        }

        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &cmapsFileContent);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bTextWrite(csFilePath, csSeparator, cmapsFileContent);
        xASSERT(FALSE != m_bRes);

        std::map<tString, tString> mapsStr;
        m_bRes = CxStdioFile::bTextRead(csFilePath, csSeparator, &mapsStr);
        xASSERT(FALSE != m_bRes);

        xASSERT_EQUAL(cmapsFileContent.size(), mapsStr.size());
        xASSERT(cmapsFileContent == mapsStr);
    }

    //-------------------------------------
    //binary
    {
        uString usFileContent;   usFileContent.resize(1024 * 5);

        {
            CxStdioFile F;

            m_bRes = F.bOpen(csFilePath, CxStdioFile::omBinCreateReadWrite);
            xASSERT(FALSE != m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT(0 < m_iRes);

            m_bRes = F.bResize(1024 * 50);
            xASSERT(FALSE != m_bRes);

            m_iRes = F.iWrite(xT("0123456789"));
            xASSERT(0 < m_iRes);
        }

        m_bRes = CxStdioFile::bBinWrite(csFilePath, usFileContent);
        xASSERT(FALSE != m_bRes);

        uString usStr;
        m_bRes = CxStdioFile::bBinRead(csFilePath, &usStr);
        xASSERT(FALSE != m_bRes);

        xASSERT(usFileContent == usStr);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxStdioFileH
