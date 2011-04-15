/****************************************************************************
* Class name:  CxTest_CxPop3
* Description: test CxPop3
* File name:   CxTest_CxPop3.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxPop3H
#define CxTest_CxPop3H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxPop3.h>
//---------------------------------------------------------------------------
class CxTest_CxPop3 : public CxTest {
	public:
		CxTest_CxPop3();
	   ~CxTest_CxPop3();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxPop3 (constructor)
CxTest_CxPop3::CxTest_CxPop3() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxPop3 (destructor)
CxTest_CxPop3::~CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxPop3::bUnit() {
	//-------------------------------------
	//
	//const tString csUser     = xT("Sergey");		//"test_1";
	//const tString csPass     = xT("12345");			//"test_1";
	//const tString csServer   = xT("192.168.1.47");	//"127.0.0.1";
	//const USHORT  cusPort    = 110;
	
	//-------------------------------------
	//CourierMS.exe
	//const tString csUser     = xT("test_1@serg.com");
	//const tString csPass     = xT("test_1");
	//const tString csServer   = xT("127.0.0.1");
	//const USHORT  cusPort    = 110;
	
	//-------------------------------------
	//IPNET
	const tString  csUser     = xT("domen");
	const tString  csPass     = xT("control6");
	const tString  csServer   = xT("mail.ipnet.kiev.ua");
	const USHORT   cusPort    = 110;
	
	//-------------------------------------
	//hMailServer
	////const tString  csUser     = xT("test_2@serg.com");
	////const tString  csPass     = xT("test_2");
	////const tString  csServer   = xT("127.0.0.1");
	////const USHORT   cusPort    = 110;

	
	//-------------------------------------
	//
	ULONG              ulSum      = 0;
	ULONG              ulSize     = 0;
	ULONG              ulMsgID    = 1;
	std::vector<ULONG> veculList;
	ULONG              ulIndex    = 1;
	INT                iNum       = 1;
	const tString      csDirPath  = xT("C:/Temp2");
	const tString      csFileName = xT("MailFileName");
	

	CxPop3 objPop3;

	//-------------------------------------
	//bCreate
	g_bRes = objPop3.bCreate(csUser, csPass, csServer, cusPort); 
	xASSERT(TRUE == g_bRes);
	
	//-------------------------------------
	//bConnect
	g_bRes = objPop3.bConnect(); 
	xASSERT(TRUE == g_bRes);
	
	//-------------------------------------
	//bLogin
	g_bRes = objPop3.bLogin(); 
	xASSERT(TRUE == g_bRes);
	
	//-------------------------------------
	//bStat
	g_bRes = objPop3.bStat(ulSum, ulSize);
	xASSERT(TRUE == g_bRes);
	
	//-------------------------------------
	//bList
	////g_bRes = objPop3.bList(veculList);
	////xASSERT(TRUE == g_bRes);
	
	//-------------------------------------
	//bListAt
	////g_bRes = objPop3.bListAt(ulIndex);
	////xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bNoop
	g_bRes = objPop3.bNoop();
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bDelete
	g_bRes = objPop3.bDelete(ulMsgID);
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bRset
	g_bRes = objPop3.bRset();
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bTop
	for (ULONG i = 1; i <= ulSum; i ++) {
		//////-------------------------------------
		//////CxMimeMessage
		////CxMimeMessage objMessage;
		////tString       sRawHeader;

		//////-------------------------------------
		//////CxMimeHeader
		////CxMimeHeader objHeader;

		////g_bRes = objPop3.bTop(iNum, 0, /*ref*/sRawHeader);        
		////xASSERT(TRUE == g_bRes);
		/////*LOG*/printf("bTop %i\n", i);  

		////g_bRes = objHeader.bParse(sRawHeader);
		////xASSERT(TRUE == g_bRes);

		////g_sRes = objHeader.sGetField(xT("Message-Id"));
		////xASSERT(FALSE == g_sRes.empty());


		//////-------------------------------------
		//////CxMimeBody
		////////CxMimeBody objBody;

		//////g_bRes = m_Body.bParse(sRawMessage);
		//////xASSERT(TRUE == g_bRes);
	}
		
	//-------------------------------------
	//bRetriveRaw
	for (ULONG i = 1; i <= ulSum; i ++) {  
	    CxDir::bCreateForce(csDirPath);

		g_bRes = objPop3.bRetriveRaw(i, csDirPath, csFileName + xT("_") + CxString::lexical_cast(i) + xT(".eml"));
		xASSERT(TRUE == g_bRes);

		/*LOG*/printf("bRetriveRaw %i\n", i); 
	}
	
	//-------------------------------------
	//bRetrieveHeader
	for (ULONG i = 1; i <= ulSum; i ++) {
		CxMimeHeader mhMimeHeader;

		g_bRes = objPop3.bRetrieveHeader(iNum, mhMimeHeader);
		xASSERT(TRUE == g_bRes);

		/*LOG*/printf("bRetrieveHeader %i\n", i); 
	}
	
	//-------------------------------------
	//bDisconnect
	g_bRes = objPop3.bDisconnect();
	xASSERT(TRUE == g_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxPop3H

