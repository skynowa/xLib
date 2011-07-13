/****************************************************************************
* Class name:  CxTest_CxMimeMessage
* Description: test CxMimeMessage
* File name:   CxTest_CxMimeMessage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxMimeMessage (constructor)
CxTest_CxMimeMessage::CxTest_CxMimeMessage() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxMimeMessage (destructor)
CxTest_CxMimeMessage::~CxTest_CxMimeMessage() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxMimeMessage::bUnit() {
	CxPop3 objPop3;


	//-------------------------------------
	//CourierMS.exe
	const std::string csUser     = "test_1@serg.com";
	const std::string csPass     = "test_1";
	const std::string csServer   = "127.0.0.1";
	const USHORT      usPort     = 110;

	//-------------------------------------
	//IPNET
	//const std::string csUser     = "domen";
	//const std::string csPass     = "control6";
	//const std::string csServer   = "mail.ipnet.kiev.ua";
	//USHORT            usPort     = 110;


	const std::string csDirPath  = "C:/Temp";
	const std::string csFilePath = "C:/Temp/1.eml";
	ULONG             ulSum      = 0;
	ULONG             ulSize     = 0;



	/****************************************************************************
	* CxMimeHeader
	*
	*****************************************************************************/

	/*
	+OK message 1 (570821 octets)
	Return-Path: <Administrator@localhost>
	Received: from SERGEY ([192.168.1.48])
	by Sergey (Kerio MailServer 6.7.0);
	Thu, 11 Jun 2009 15:13:38 +0400
	Date: Thu, 9 Apr 2009 13:53:34 +0400
	From: Administrator <Administrator@localhost>
	X-Mailer: The Bat! (v2.12.00) Educational
	Reply-To: Administrator <Administrator@localhost>
	X-Priority: 3 (Normal)
	Message-ID: <936634544.20090409135334@localhost>
	To: test_1@localhost, test_2@localhost, test_3@localhost, test_4@localhost
	Subject: =?Windows-1251?B?8uXs4A==?=
	MIME-Version: 1.0
	Content-Type: multipart/mixed;
	boundary="----------544A15625820D78"


	.

	*/

	const std::string csRawHeader =
		"+OK message 1 (570821 octets)\r\n"
		"Date: Mon, 6 Apr 2009 20:14:51 +0400\r\n"
		"From: Admin@localhost\r\n"
		"X-Mailer: The Bat! (v2.12.00) Educational\r\n"
		"Reply-To: Admin@localhost\r\n"
		"X-Priority: 3 (Normal)\r\n"
		"Message-ID: <431351461.20090406201451@localhost>\r\n"
		"To: test_1@localhost, test_2@localhost, test_3@localhost, test_4@localhost\r\n"
		"Subject: =?Windows-1251?B?0uXs4A==?=\r\n"
		"MIME-Version: 1.0\r\n"
		"Content-Type: multipart/mixed;\r\n"
		"  boundary=\"----------544A15625820D78"
		""
		""
		"."
		"";

	//-------------------------------------
	//sGenerateMessageID
	{
		g_sRes = CxMimeHeader::sGenerateMessageID();
		xASSERT(false == g_sRes.empty());
	}


	//-------------------------------------
	//bCreate
	g_bRes = objPop3.bCreate(csUser, csPass, csServer, usPort);
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
	/*LOG*/printf("Mails %i\n", ulSum);

	//-------------------------------------
	//bTop
	std::string sRawHeader = "";

	for (ULONG i = 1; i <= ulSum; i ++) {
		//-------------------------------------
		//CxMimeMessage
		CxMimeMessage objMessage;

		//-------------------------------------
		//CxMimeHeader
		CxMimeHeader objHeader;

		g_bRes = objPop3.bTop(i, 0, /*ref*/sRawHeader);
		xASSERT(TRUE == g_bRes);

		//-------------------------------------
		//bParse
		g_bRes = objHeader.bParse(sRawHeader);
		xASSERT(TRUE == g_bRes);

		//-------------------------------------
		//sGetField
		////g_sRes = objHeader.sGetField("Message-Id");
		////xASSERT(false == g_sRes.empty());

		////g_sRes = objHeader.sGetField("fRom");
		////xASSERT(false == g_sRes.empty());
		////xASSERT("\"Admin@localhost\" <Admin@localhost>" == g_sRes);

		////g_sRes = objHeader.sGetField("X-MailType");
		////xASSERT(false         == g_sRes.empty());
		////xASSERT("Mail bomber" == g_sRes);

		////g_sRes = objHeader.sGetField("To");
		////xASSERT(false              == g_sRes.empty());
		////xASSERT("test_1@localhost" == g_sRes);

		////g_sRes = objHeader.sGetField("Subject");
		////xASSERT(false              == g_sRes.empty());
		////xASSERT("=?KOI8-R?B?8uXs4A==?=" == g_sRes);

		////g_sRes = objHeader.sGetField("Return-Path");
		////xASSERT(false               == g_sRes.empty());
		////xASSERT("<Admin@localhost>" == g_sRes);

		/*LOG*/printf("bTop %i\n", i);
	}

	//-------------------------------------
	//bRetrieveHeader
	for (ULONG y = 1; y <= ulSum; y ++) {
		CxMimeHeader objHeader;

		//-------------------------------------
		//bRetrieveHeader
		g_bRes = objPop3.bRetrieveHeader(y, objHeader);
		xASSERT(TRUE == g_bRes);

		//-------------------------------------
		//sGetField
		////g_sRes = objHeader.sGetField("Message-Id");
		////xASSERT(false == g_sRes.empty());

		////g_sRes = objHeader.sGetField("fRom");
		////xASSERT(false == g_sRes.empty());
		////xASSERT("\"Admin@localhost\" <Admin@localhost>" == g_sRes);

		////g_sRes = objHeader.sGetField("X-MailType");
		////xASSERT(false         == g_sRes.empty());
		////xASSERT("Mail bomber" == g_sRes);

		////g_sRes = objHeader.sGetField("To");
		////xASSERT(false              == g_sRes.empty());
		////xASSERT("test_1@localhost" == g_sRes);

		////g_sRes = objHeader.sGetField("Subject");
		////xASSERT(false              == g_sRes.empty());
		////xASSERT("=?KOI8-R?B?8uXs4A==?=" == g_sRes);

		////g_sRes = objHeader.sGetField("Return-Path");
		////xASSERT(false               == g_sRes.empty());
		////xASSERT("<Admin@localhost>" == g_sRes);

		/*LOG*/printf("bRetrieveHeader %i\n", y);
	}

	//-------------------------------------
	//bDisconnect
	g_bRes = objPop3.bDisconnect();
	xASSERT(TRUE == g_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
