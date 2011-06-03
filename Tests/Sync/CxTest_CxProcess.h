/****************************************************************************
* Class name:  CxTest_CxProcess
* Description: test CxTest_CxProcess
* File name:   CxTest_CxProcess.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTest_CxProcessH
#define CxTest_CxTest_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
class CxTest_CxProcess :
    public CxTest
{
	public:
		CxTest_CxProcess();
		virtual     ~CxTest_CxProcess();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxProcess (constructor)
CxTest_CxProcess::CxTest_CxProcess() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxProcess (destructor)
CxTest_CxProcess::~CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxProcess::bUnit() {
    //--------------------------------------------------
    //ulGetCurrId
    {
        m_ulRes = CxProcess::ulGetCurrId();
        xASSERT(0 <= m_ulRes);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    {
        m_ulRes = CxProcess::ulGetCurrParentId();
        xASSERT(0 <= m_ulRes);
    }

    //--------------------------------------------------
    //bExec
    {
    #if defined(xOS_WIN)
        const tString csFilePath = xT("explorer.exe");
        const tString csCmdLine  = xT("");
    #elif defined(xOS_LINUX)
        const tString csFilePath = xT("dolphin");
        const tString csCmdLine  = xT("");
    #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bExit
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxTest_CxProcessH
