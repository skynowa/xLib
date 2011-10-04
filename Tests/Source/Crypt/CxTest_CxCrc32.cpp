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
CxTest_CxCrc32::CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
CxTest_CxCrc32::~CxTest_CxCrc32() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxCrc32::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	/*DEBUG*/

	const std::tstring csFilePath = sGetWorkDirPath()  + CxConst::xSLASH + xT("Test.txt");;

    //-------------------------------------
    //Prepare
    {
    	CxFile flFile;

        m_bRes = flFile.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = flFile.bResize(1333);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

	//-------------------------------------
	//ulCalc
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//ulCalcFile, sFormatHex
    xTEST_BLOCK(cullBlockLoops)
	{
		m_ulRes = CxCrc32::ulCalcFile(csFilePath);
		xASSERT_LESS(0UL, m_ulRes);
	    //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xASSERT_EQ(false, m_sRes.empty());
	}

	//-------------------------------------
	//ulCalcFast
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//------------------------------------
	//ulCalcFileFast, sFormatHex
    xTEST_BLOCK(cullBlockLoops)
	{
	    m_ulRes = CxCrc32::ulCalcFileFast(csFilePath);
        xASSERT_LESS(0UL, m_ulRes);
        //xTRACE(m_ulRes);

        m_sRes = CxCrc32::sFormatHex(m_ulRes);
        xASSERT_EQ(false, m_sRes.empty());
	}

	return TRUE;
}
//---------------------------------------------------------------------------
