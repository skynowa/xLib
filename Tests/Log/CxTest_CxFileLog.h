/****************************************************************************
* Class name:  CxTest_CxFileLog
* Description: test CxFileLog
* File name:   CxFileLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef CxTest_CxFileLogH
#define CxTest_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Log/CxFileLog.h>
//---------------------------------------------------------------------------
class CxTest_CxFileLog :
    public CxTest
{
	public:
		         CxTest_CxFileLog();
	    virtual ~CxTest_CxFileLog();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxFileLog
CxTest_CxFileLog::CxTest_CxFileLog() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFileLog
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxFileLog::bUnit() {
    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    {
        m_bRes = flLog.bSetFilePath(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_sRes = flLog.sGetFilePath();
        xASSERT(csFilePath == m_sRes);
    }

    //--------------------------------------------------
    //bWrite
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xASSERT(FALSE != m_bRes);
            xASSERT(0L    <  CxStdioFile::liGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    {
        m_bRes = flLog.bClear();
        xASSERT(FALSE != m_bRes);
        xASSERT(0     == CxStdioFile::liGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    {
        m_bRes = flLog.bDelete();
        xASSERT(FALSE != m_bRes);
        xASSERT(FALSE == CxStdioFile::bIsExists( flLog.sGetFilePath()) );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxFileLogH
