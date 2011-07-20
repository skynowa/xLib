/****************************************************************************
* Class name:  CxTest_CxCrc32
* Description: test CxCrc32
* File name:   CxTest_CxCrc32.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Crypt/CxTest_CxCrc32.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCrc32
CxTest_CxCrc32::CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCrc32
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL 
CxTest_CxCrc32::bUnit() {
	/*DEBUG*/

	const tString csFilePath = sGetWorkDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    //Prepare
    {
    	CxStdioFile flFile;

        m_bRes = flFile.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT(FALSE != m_bRes);

        m_bRes = flFile.bResize(1333);
        xASSERT(FALSE != m_bRes);
    }

	//-------------------------------------
	//ulCalc
	{

	}

	//-------------------------------------
	//ulCalcFile, sFormatHex
	{
		m_ulRes = CxCrc32::ulCalcFile(csFilePath);
		xASSERT(0 < m_ulRes);
	    //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xASSERT(false == m_sRes.empty());
	}

	//-------------------------------------
	//ulCalcFast
	{

	}

	//------------------------------------
	//ulCalcFileFast, sFormatHex
	{
	    m_ulRes = CxCrc32::ulCalcFileFast(csFilePath);
        xASSERT(0 < m_ulRes);
        //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xASSERT(false == m_sRes.empty());
	}

	return TRUE;
}
//---------------------------------------------------------------------------
