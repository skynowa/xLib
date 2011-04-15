/****************************************************************************
* Class name:  CxTest_CxCrc32
* Description: test CxCrc32
* File name:   CxTest_CxCrc32.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxCrc32H
#define CxTest_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/CxCrc32.h>
//---------------------------------------------------------------------------
class CxTest_CxCrc32 : public CxTest {
	public:
		CxTest_CxCrc32();
	   ~CxTest_CxCrc32();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxCrc32 (comment)
CxTest_CxCrc32::CxTest_CxCrc32() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxCrc32 (comment)
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxCrc32::bUnit() {
	/*DEBUG*/

	tString sFilePath;

    //-------------------------------------
    //Prepare
    {
    	CxStdioFile flFile;
        uString     usFileContent;

        sFilePath = sGetWorkDirPath()  + CxConst::xSLASH + xT("Test.txt");
        usFileContent.resize(1024);

        flFile.bOpen(sFilePath, CxStdioFile::CxOpenMode::omCreateReadWrite);
        flFile.bWriteAll(usFileContent, 1);
    }

	//-------------------------------------
	//ulCalc
	{

	}

	//-------------------------------------
	//ulCalcFile, sFormatHex
	{
		m_ulRes = CxCrc32::ulCalcFile(sFilePath);
		xASSERT(0 < m_ulRes);
	    //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        //xTRACE(m_sRes);
	}

	//-------------------------------------
	//ulCalcFast 
	{

	}

	//------------------------------------
	//ulCalcFileFast, sFormatHex
	{
	    m_ulRes = CxCrc32::ulCalcFileFast(sFilePath);
        xASSERT(0 < m_ulRes);
        //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        //xTRACE(m_sRes);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxCrc32H

