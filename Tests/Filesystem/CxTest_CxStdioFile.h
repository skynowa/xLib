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
	   ~CxTest_CxStdioFile();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//iFprintfV
void
Test_iFprintfV(LPCTSTR pcszFormat, ...) {
    va_list args = NULL;

    va_start(args, pcszFormat);
    ////INT iRes = F.iFprintfV(pcszFormat, args);
    va_end(args);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//TODO: + CxTest_CxStdioFile
CxTest_CxStdioFile::CxTest_CxStdioFile() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxStdioFile
CxTest_CxStdioFile::~CxTest_CxStdioFile() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxStdioFile::bUnit() {
    const tString csStr         = xT("=Cоздаем новый проэкт MFC AppWizard(EXE)=");
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

    //-------------------------------------
    //bOpen
    {
        m_bRes = F.bOpen(csFilePath, CxStdioFile::CxOpenMode::omCreateReadWrite);
        xASSERT_MSG(FALSE != m_bRes, csFilePath.c_str());
    }

    //-------------------------------------
    //bReopen
    {
        m_bRes = F.bReopen(csFilePath, CxStdioFile::CxOpenMode::omOpenReadWrite);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //sGetPath
    {
        m_sRes = F.sGetPath();
        xASSERT(csFilePath == m_sRes);
    }

    //--------------------------------------------------
    //pGet
    {
        FILE *pFile = F.pGet();
        xASSERT(NULL != pFile);
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
        const size_t  uiBlockSize[] = {1, 2, 10, 20, 50, 64, 123, 512, 1024, 2356, 4096, 8192/*, 16384, 32768, 65536, 131072*/};
        const uString sContent(138699, 5);

        uString       sText1;
        uString       sText2;

        for (size_t i = 0; i < xARRAY_SIZE(uiBlockSize); ++ i) {
            //-------------------------------------
            //bWriteAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), CxStdioFile::CxOpenMode::omBinWrite);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bWriteAll(sContent, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //bReadAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), CxStdioFile::CxOpenMode::omBinRead);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bReadAll(&sText1, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //bWriteAll
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("DataNew.dat"), CxStdioFile::CxOpenMode::omBinWrite);
                xASSERT(FALSE != m_bRes);

                m_bRes = _F.bWriteAll(sText1, uiBlockSize[i]);
                xASSERT(FALSE != m_bRes);
            }

            //-------------------------------------
            //xASSERT
            {
                CxStdioFile _F;

                m_bRes = _F.bOpen(sGetWorkDirPath() + CxConst::xSLASH + xT("Data.dat"), xT("rb"));
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
    //iFprintf
    {
        INT iResFprintf = F.iFprintf(xT("%s"), xT("xxx"));
        xASSERT(0 < iResFprintf);
    }

    //-------------------------------------
    //iFprintfV
    {
        Test_iFprintfV(xT("%s"), xT("zzz"));
    }


    /****************************************************************************
    *	other
    *
    *****************************************************************************/

    //-------------------------------------
    //bLocking
    {
        ////m_bRes = F.bLocking(CxStdioFile::lmLock, 10);
        ////xASSERT(FALSE == m_bRes);

        ////m_bRes = F.bLocking(CxStdioFile::lmUnlock, 10);
        ////xASSERT(FALSE == m_bRes);
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
        ////m_bRes = F.bChsize(0);
        ////xASSERT(FALSE != m_bRes);
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
        ////m_bRes = F.bSetMode(CxStdioFile::tmBinary);
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetMode
    {
        ////m_bRes = F.bSetMode(CxStdioFile::tmText);
        ////xASSERT(FALSE != m_bRes);
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
    //bClearErr
    {
        m_bRes = F.bClearErr();
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
    }

    //-------------------------------------
    //bClose
    {
        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);
    }


















    /****************************************************************************
    *   static
    *
    *****************************************************************************/

    //-------------------------------------
    //bIsExists
    {
        m_bRes = CxStdioFile::bIsExists(csFilePath);
        xASSERT(FALSE != m_bRes);
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
////        m_bRes = CxStdioFile::bReadFile(csFilePath, &m_usRes);
//        xASSERT_MSG(FALSE != m_bRes, csFilePath.c_str());
//
//        m_bRes = CxStdioFile::bWriteFile(csNewFilePath, m_usRes);
////        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bUnlink
    {
        ////m_bRes = CxStdioFile::bUnlink(csNewFilePath);
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bRemove
    {
        m_bRes = CxStdioFile::bDelete(csNewFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bMove
    {
        ////m_bRes = CxStdioFile::bMove(xT("C:\\Текстовый документ.txt"), xT("C:\\My"));
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bCopy
    {
        ////m_bRes = CxStdioFile::bCopy(xT("C:\\Текстовый документ.txt"), xT("D:\\Текстовый документ.txt"));
        ////xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxStdioFileH
