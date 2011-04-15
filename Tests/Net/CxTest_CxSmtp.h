/****************************************************************************
* Class name:  CxTest_CxSmtp
* Description: test CxSmtp
* File name:   CxTest_CxSmtp.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxSmtpH
#define CxTest_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
#include <xLib/Common/Debug/CxTest.h>
#include <xLib/Net/CxSmtp.h>
//---------------------------------------------------------------------------
class CxTest_CxSmtp : public CxTest {
	public:
		CxTest_CxSmtp();
	   ~CxTest_CxSmtp();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxSmtp (constructor)
CxTest_CxSmtp::CxTest_CxSmtp() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxSmtp (destructor)
CxTest_CxSmtp::~CxTest_CxSmtp() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxSmtp::bUnit() {
	//-------------------------------------
	//IPNET
	//const std::string  csUser     = "domen";
	//const std::string  csPass     = "control6";
	//const std::string  csServer   = "mail.ipnet.kiev.ua";
	//USHORT             usPort     = 25;
	//const std::string  csFrom     = "domen@ipnet.kiev.ua";
	//const std::string  csTo       = "dr.web.agent@gmail.com";
	//const std::string  csFilePath = "C:/Temp/test.eml";
	//const std::string  csDirPath  = "C:/Temp";
	
	//-------------------------------------
	//CourierMS
	const std::string  csUser     = "test_1";
	const std::string  csPass     = "test_1";
	const std::string  csServer   = "127.0.0.1";
	USHORT             usPort     = 25;
	const std::string  csFrom     = "test_1@serg.com";
	const std::string  csTo       = "test_2@serg.com";
	const std::string  csFilePath = "C:/Temp2/test.eml";
	const std::string  csDirPath  = "C:/Temp";
	
	//-------------------------------------
	//hMailServer
	//const std::string  csUser     = "test_1@serg.com";
	//const std::string  csPass     = "test_1";
	//const std::string  csServer   = "127.0.0.1";
	//USHORT             usPort     = 25;
	//const std::string  csFrom     = "test_1@serg.com";
	//const std::string  csTo       = "test_2@serg.com";
	//const std::string  csFilePath = "C:/Temp2/test.eml";
	//const std::string  csDirPath  = "C:/Temp";
	



	
	//-------------------------------------
	//
	ULONG              ulSum      = 0;
	ULONG              ulSize     = 0;
	ULONG              ulMsgID    = 1;
	std::vector<ULONG> veculList;
	ULONG              ulIndex    = 1;
	INT                iNum       = 1;
	const std::string  csText     = "HELO";
	
	CxSmtp objSmtp;
	
	//-------------------------------------
	//bCreate
	g_bRes = objSmtp.bCreate(csUser, csPass, csServer, usPort); 
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bConnect
	g_bRes = objSmtp.bConnect();
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bLogin
	////g_bRes = objSmtp.bLogin(); 
	////xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bSend
	g_bRes = objSmtp.bSend(csText, csFrom, csTo);
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bSendRaw
	g_vecsRes = CxDir::vecsListFiles(csDirPath, "*.eml"); 
	for (size_t i = 0; i < g_vecsRes.size(); i ++) {
		g_bRes = objSmtp.bSendRaw(csDirPath + "\\" + g_vecsRes.at(i), csFrom, csTo); 
		xASSERT(TRUE == g_bRes);
		/*LOG*///printf("Send msg %s\n", g_vecsRes.at(i).c_str());
	}

	//-------------------------------------
	//bNoop
	g_bRes = objSmtp.bNoop(); 
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bRset
	g_bRes = objSmtp.bRset(); 
	xASSERT(TRUE == g_bRes);

	//-------------------------------------
	//bDisconnect
	g_bRes = objSmtp.bDisconnect(); 
	xASSERT(TRUE == g_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSmtpH

