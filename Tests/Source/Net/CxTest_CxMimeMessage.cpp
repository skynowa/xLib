/**
 * \file   CxTest_CxMimeMessage.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxMimeMessage.h>


//---------------------------------------------------------------------------
CxTest_CxMimeMessage::CxTest_CxMimeMessage() {

}
//---------------------------------------------------------------------------
CxTest_CxMimeMessage::~CxTest_CxMimeMessage() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxMimeMessage::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    std::string m_sRes;

    CxPop3 objPop3;

    //-------------------------------------
    //CourierMS.exe
    const std::string csUser     = "test_1@serg.com";
    const std::string csPass     = "test_1";
    const std::string csServer   = "127.0.0.1";
    const ushort_t      usPort     = 110;

    //-------------------------------------
    //IPNET
    //const std::string csUser     = "domen";
    //const std::string csPass     = "control6";
    //const std::string csServer   = "mail.ipnet.kiev.ua";
    //ushort_t            usPort     = 110;


    const std::string csDirPath  = "C:/Temp";
    const std::string csFilePath = "C:/Temp/1.eml";
    ulong_t             ulSum      = 0;
    ulong_t             ulSize     = 0;



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
        m_sRes = CxMimeHeader::sGenerateMessageID();
        xTEST_EQ(false, m_sRes.empty());
    }


    //-------------------------------------
    //bCreate
    m_bRes = objPop3.bCreate(csUser, csPass, csServer, usPort);
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objPop3.bConnect();
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bLogin
    m_bRes = objPop3.bLogin();
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bStat
    m_bRes = objPop3.bStat(ulSum, ulSize);
    xTEST_EQ(true, m_bRes);
    /*LOG*/printf("Mails %lu\n", ulSum);

    //-------------------------------------
    //bTop
    std::string sRawHeader = "";

    for (ulong_t i = 1; i <= ulSum; i ++) {
        //-------------------------------------
        //CxMimeMessage
        CxMimeMessage objMessage;

        //-------------------------------------
        //CxMimeHeader
        CxMimeHeader objHeader;

        m_bRes = objPop3.bTop(i, 0, /*ref*/sRawHeader);
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //bParse
        m_bRes = objHeader.bParse(sRawHeader);
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //sGetField
        ////m_sRes = objHeader.sGetField("Message-Id");
        ////xTEST_EQ(false, m_sRes.empty());

        ////m_sRes = objHeader.sGetField("fRom");
        ////xTEST_EQ(false, m_sRes.empty());
        ////xTEST_EQ("\"Admin@localhost\" <Admin@localhost>", m_sRes);

        ////m_sRes = objHeader.sGetField("X-MailType");
        ////xTEST_EQ(false,         m_sRes.empty());
        ////xTEST_EQ("Mail bomber", m_sRes);

        ////m_sRes = objHeader.sGetField("To");
        ////xTEST_EQ(false,              m_sRes.empty());
        ////xTEST_EQ("test_1@localhost", m_sRes);

        ////m_sRes = objHeader.sGetField("Subject");
        ////xTEST_EQ(false,                   m_sRes.empty());
        ////xTEST_EQ("=?KOI8-R?B?8uXs4A==?=", m_sRes);

        ////m_sRes = objHeader.sGetField("Return-Path");
        ////xTEST_EQ(false,               m_sRes.empty());
        ////xTEST_EQ("<Admin@localhost>", m_sRes);

        /*LOG*/printf("bTop %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (ulong_t y = 1; y <= ulSum; y ++) {
        CxMimeHeader objHeader;

        //-------------------------------------
        //bRetrieveHeader
        m_bRes = objPop3.bRetrieveHeader(y, objHeader);
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //sGetField
        ////m_sRes = objHeader.sGetField("Message-Id");
        ////xTEST_EQ(false, m_sRes.empty());

        ////m_sRes = objHeader.sGetField("fRom");
        ////xTEST_EQ(false, m_sRes.empty());
        ////xTEST_EQ("\"Admin@localhost\" <Admin@localhost>", m_sRes);

        ////m_sRes = objHeader.sGetField("X-MailType");
        ////xTEST_EQ(false,         m_sRes.empty());
        ////xTEST_EQ("Mail bomber", m_sRes);

        ////m_sRes = objHeader.sGetField("To");
        ////xTEST_EQ(false,              m_sRes.empty());
        ////xTEST_EQ("test_1@localhost", m_sRes);

        ////m_sRes = objHeader.sGetField("Subject");
        ////xTEST_EQ(false,                   m_sRes.empty());
        ////xTEST_EQ("=?KOI8-R?B?8uXs4A==?=", m_sRes);

        ////m_sRes = objHeader.sGetField("Return-Path");
        ////xTEST_EQ(false,               m_sRes.empty());
        ////xTEST_EQ("<Admin@localhost>", m_sRes);

        /*LOG*/printf("bRetrieveHeader %lu\n", y);
    }

    //-------------------------------------
    //bDisconnect
    m_bRes = objPop3.bDisconnect();
    xTEST_EQ(true, m_bRes);

    return true;
}
//---------------------------------------------------------------------------
