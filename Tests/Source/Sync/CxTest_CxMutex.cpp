/****************************************************************************
* Class name:  CxTest_CxMutex
* Description: test CxMutex
* File name:   CxTest_CxMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxMutex (constructor)
CxTest_CxMutex::CxTest_CxMutex() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxMutex (destructor)
CxTest_CxMutex::~CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxMutex::bUnit() {
	const tString csName = CxString::sCreateGuid();
	
	
	CxMutex mtMutex;

	//-------------------------------------
	//hGetHandle
	{
		m_hRes = mtMutex.hGetHandle();
        xASSERT(NULL == m_hRes);
	}
	
	//-------------------------------------
	//bCreate
	{
		const LPSECURITY_ATTRIBUTES lpcsaAttributes = NULL; 
		const BOOL                  cbInitialOwner  = FALSE;

		m_bRes = mtMutex.bCreate(lpcsaAttributes, cbInitialOwner, csName.c_str());
		xASSERT(FALSE != m_bRes);
	}
	
	//-------------------------------------
	//bOpen
	{
		const ULONG culAccess       = MUTEX_ALL_ACCESS; 
		const BOOL  cbInheritHandle = FALSE; 
		
		m_bRes = mtMutex.bOpen(culAccess, cbInheritHandle,  csName.c_str());
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bWait
	{
		const ULONG culTimeout = 1000;
		
		m_bRes = mtMutex.bWait(culTimeout);
		xASSERT(FALSE != m_bRes);
	}
    	
	//-------------------------------------
	//bRelease
	{
		m_bRes = mtMutex.bRelease();
		xASSERT(FALSE != m_bRes);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
