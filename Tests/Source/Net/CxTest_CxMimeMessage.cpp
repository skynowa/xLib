/**
 * \file   CxTest_CxMimeMessage.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxMimeMessage.h>


#if xOPENSSL_IS_USE

//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMimeMessage::unit(
    culonglong_t &a_cullCaseLoops
)
{
    std::tstring_t m_sRv;

    CxPop3 objPop3;

    //-------------------------------------
    //CourierMS.exe
    std::ctstring_t csUser   = xT("test_1@serg.com");
    std::ctstring_t csPass   = xT("test_1");
    std::ctstring_t csServer = xT("127.0.0.1");
    cushort_t       usPort   = 110;

    //-------------------------------------
    //IPNET
    //std::ctstring_t csUser   = "domen";
    //std::ctstring_t csPass   = "control6";
    //std::ctstring_t csServer = "mail.ipnet.kiev.ua";
    //ushort_t             usPort     = 110;

    std::ctstring_t csDirPath  = xT("C:/Temp");
    std::ctstring_t csFilePath = xT("C:/Temp/1.eml");
    ulong_t              ulSum      = 0;
    ulong_t              ulSize     = 0;



    /*******************************************************************************
    * CxMimeHeader
    *
    *******************************************************************************/

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

    std::ctstring_t csRawHeader =
        xT("+OK message 1 (570821 octets)\r\n")
        xT("Date: Mon, 6 Apr 2009 20:14:51 +0400\r\n")
        xT("From: Admin@localhost\r\n")
        xT("X-Mailer: The Bat! (v2.12.00) Educational\r\n")
        xT("Reply-To: Admin@localhost\r\n")
        xT("X-Priority: 3 (Normal)\r\n")
        xT("Message-ID: <431351461.20090406201451@localhost>\r\n")
        xT("To: test_1@localhost, test_2@localhost, test_3@localhost, test_4@localhost\r\n")
        xT("Subject: =?Windows-1251?B?0uXs4A==?=\r\n")
        xT("MIME-Version: 1.0\r\n")
        xT("Content-Type: multipart/mixed;\r\n")
        xT("  boundary=\"----------544A15625820D78")
        xT("")
        xT("")
        xT(".")
        xT("");

    //-------------------------------------
    //sGenerateMessageID
    {
        m_sRv = CxMimeHeader::generateMessageID();
        xTEST_EQ(false, m_sRv.empty());
    }


    //-------------------------------------
    //bCreate
    objPop3.create(csUser, csPass, csServer, usPort);

    //-------------------------------------
    //bConnect
    objPop3.connect();

    //-------------------------------------
    //bLogin
    objPop3.login();

    //-------------------------------------
    //bStat
    objPop3.stat(ulSum, ulSize);
    /*LOG*/printf("Mails %lu\n", ulSum);

    //-------------------------------------
    //bTop
    std::tstring_t sRawHeader;

    for (ulong_t i = 1; i <= ulSum; i ++) {
        //-------------------------------------
        //CxMimeMessage
        CxMimeMessage objMessage;

        //-------------------------------------
        //CxMimeHeader
        CxMimeHeader objHeader;

        objPop3.top(i, 0, /*ref*/sRawHeader);

        //-------------------------------------
        //bParse
        objHeader.parse(sRawHeader);

        //-------------------------------------
        //sGetField
        ////m_sRv = objHeader.sGetField("Message-Id");
        ////xTEST_EQ(false, m_sRv.empty());

        ////m_sRv = objHeader.sGetField("fRom");
        ////xTEST_EQ(false, m_sRv.empty());
        ////xTEST_EQ("\"Admin@localhost\" <Admin@localhost>", m_sRv);

        ////m_sRv = objHeader.sGetField("X-MailType");
        ////xTEST_EQ(false,         m_sRv.empty());
        ////xTEST_EQ("Mail bomber", m_sRv);

        ////m_sRv = objHeader.sGetField("To");
        ////xTEST_EQ(false,              m_sRv.empty());
        ////xTEST_EQ("test_1@localhost", m_sRv);

        ////m_sRv = objHeader.sGetField("Subject");
        ////xTEST_EQ(false,                   m_sRv.empty());
        ////xTEST_EQ("=?KOI8-R?B?8uXs4A==?=", m_sRv);

        ////m_sRv = objHeader.sGetField("Return-Path");
        ////xTEST_EQ(false,               m_sRv.empty());
        ////xTEST_EQ("<Admin@localhost>", m_sRv);

        /*LOG*/printf("bTop %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (ulong_t y = 1; y <= ulSum; y ++) {
        CxMimeHeader objHeader;

        //-------------------------------------
        //bRetrieveHeader
        objPop3.retrieveHeader(y, objHeader);

        //-------------------------------------
        //sGetField
        ////m_sRv = objHeader.sGetField("Message-Id");
        ////xTEST_EQ(false, m_sRv.empty());

        ////m_sRv = objHeader.sGetField("fRom");
        ////xTEST_EQ(false, m_sRv.empty());
        ////xTEST_EQ("\"Admin@localhost\" <Admin@localhost>", m_sRv);

        ////m_sRv = objHeader.sGetField("X-MailType");
        ////xTEST_EQ(false,         m_sRv.empty());
        ////xTEST_EQ("Mail bomber", m_sRv);

        ////m_sRv = objHeader.sGetField("To");
        ////xTEST_EQ(false,              m_sRv.empty());
        ////xTEST_EQ("test_1@localhost", m_sRv);

        ////m_sRv = objHeader.sGetField("Subject");
        ////xTEST_EQ(false,                   m_sRv.empty());
        ////xTEST_EQ("=?KOI8-R?B?8uXs4A==?=", m_sRv);

        ////m_sRv = objHeader.sGetField("Return-Path");
        ////xTEST_EQ(false,               m_sRv.empty());
        ////xTEST_EQ("<Admin@localhost>", m_sRv);

        /*LOG*/printf("bRetrieveHeader %lu\n", y);
    }

    //-------------------------------------
    //bDisconnect
    objPop3.disconnect();
}
//------------------------------------------------------------------------------

#endif // xOPENSSL_IS_USE
