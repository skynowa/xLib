/**
 * \file   Test_Pop3Client.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Pop3Client)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Pop3Client::unit()
{
#if cmOPENSSL_CRYPTO_FOUND
	{
		// TODO: Test_Pop3Client - fix tests
		xTRACE_NOT_IMPLEMENTED

		return true;
	}

    //-------------------------------------
    //
    //std::ctstring_t csUser     = xT("Sergey");        //"test_1";
    //std::ctstring_t csPass     = xT("12345");            //"test_1";
    //std::ctstring_t csServer   = xT("192.168.1.47");    //"127.0.0.1";
    //cushort_t  cusPort    = 110;

    //-------------------------------------
    //CourierMS.exe
    //std::ctstring_t csUser     = xT("test_1@serg.com");
    //std::ctstring_t csPass     = xT("test_1");
    //std::ctstring_t csServer   = xT("127.0.0.1");
    //cushort_t  cusPort    = 110;

    //-------------------------------------
    //IPNET
    std::ctstring_t csUser     = xT("domen");
    std::ctstring_t csPass     = xT("control6");
    std::ctstring_t csServer   = xT("mail.ipnet.kiev.ua");
    cushort_t       cusPort    = 110;

    //-------------------------------------
    //hMailServer
    ////std::ctstring_t  csUser     = xT("test_2@serg.com");
    ////std::ctstring_t  csPass     = xT("test_2");
    ////std::ctstring_t  csServer   = xT("127.0.0.1");
    ////cushort_t   cusPort    = 110;


    //-------------------------------------
    //
    std::size_t          ulSum      = 0;
    std::size_t          ulSize     = 0;
    std::size_t          ulMsgID    = 1;
    std::vector<ulong_t> veculList;
    ////std::size_t              ulIndex    = 1;
    std::size_t          uiNum      = 1;
    std::ctstring_t      csDirPath  = xT("C:/Temp2");
    std::ctstring_t      csFileName = xT("MailFileName");


    Pop3Client objPop3;

    //-------------------------------------
    //bCreate
    objPop3.create(csUser, csPass, csServer, cusPort);

    //-------------------------------------
    //bConnect
    objPop3.connect();

    //-------------------------------------
    //bLogin
    objPop3.login();

    //-------------------------------------
    //bStat
    objPop3.stat(ulSum, ulSize);

    //-------------------------------------
    //bList
    ////m_bRv = objPop3.list(veculList);
    ////xTEST(m_bRv);

    //-------------------------------------
    //bListAt
    ////m_bRv = objPop3.listAt(ulIndex);
    ////xTEST(m_bRv);

    //-------------------------------------
    //bNoop
    objPop3.noop();

    //-------------------------------------
    //bDelete
    objPop3.del(ulMsgID);

    //-------------------------------------
    //bRset
    objPop3.rset();

    //-------------------------------------
    //bTop
    for (std::size_t i = 1; i <= ulSum; i ++) {
        //////-------------------------------------
        //////MimeMessage
        ////MimeMessage objMessage;
        ////std::tstring_t       sRawHeader;

        //////-------------------------------------
        //////MimeHeader
        ////MimeHeader objHeader;

        ////m_bRv = objPop3.top(uiNum, 0, /*ref*/sRawHeader);
        ////xTEST(m_bRv);
        /////*LOG*/printf("bTop %i\n", i);

        ////m_bRv = objHeader.parse(sRawHeader);
        ////xTEST(m_bRv);

        ////m_sRv = objHeader.field(xT("Message-Id"));
        ////xTEST(!m_sRv.empty());


        //////-------------------------------------
        //////MimeBody
        ////////MimeBody objBody;

        //////m_bRv = m_Body.parse(sRawMessage);
        //////xTEST(m_bRv);
    }

    //-------------------------------------
    //bRetriveRaw
    for (std::size_t i = 1; i <= ulSum; i ++) {
        Dir(csDirPath).pathCreate();

        objPop3.retriveRaw(i, csDirPath, csFileName + xT("_") + String::cast(i) + xT(".eml"));
        /*LOG*/printf("retriveRaw %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (std::size_t i = 1; i <= ulSum; i ++) {
        MimeHeader mhMimeHeader;

        objPop3.retrieveHeader(uiNum, mhMimeHeader);
        /*LOG*/printf("retrieveHeader %lu\n", i);
    }

    //-------------------------------------
    //bDisconnect
    objPop3.disconnect();
#else
    Trace() << xT("[skip]");
#endif // cmOPENSSL_CRYPTO_FOUND

    return true;
}
//-------------------------------------------------------------------------------------------------

