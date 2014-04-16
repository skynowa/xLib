/**
 * \file   CxTest_CxPop3.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxPop3.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


#if xHAVE_OPENSSL_CRYPTO

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxPop3::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

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
    int_t                iNum       = 1;
    std::ctstring_t      csDirPath  = xT("C:/Temp2");
    std::ctstring_t      csFileName = xT("MailFileName");


    CxPop3 objPop3;

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
    ////xTEST_EQ(m_bRv, true);

    //-------------------------------------
    //bListAt
    ////m_bRv = objPop3.listAt(ulIndex);
    ////xTEST_EQ(m_bRv, true);

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
        //////CxMimeMessage
        ////CxMimeMessage objMessage;
        ////std::tstring_t       sRawHeader;

        //////-------------------------------------
        //////CxMimeHeader
        ////CxMimeHeader objHeader;

        ////m_bRv = objPop3.top(iNum, 0, /*ref*/sRawHeader);
        ////xTEST_EQ(m_bRv, true);
        /////*LOG*/printf("bTop %i\n", i);

        ////m_bRv = objHeader.parse(sRawHeader);
        ////xTEST_EQ(m_bRv, true);

        ////m_sRv = objHeader.field(xT("Message-Id"));
        ////xTEST_EQ(false, m_sRv.empty());


        //////-------------------------------------
        //////CxMimeBody
        ////////CxMimeBody objBody;

        //////m_bRv = m_Body.parse(sRawMessage);
        //////xTEST_EQ(m_bRv, true);
    }

    //-------------------------------------
    //bRetriveRaw
    for (std::size_t i = 1; i <= ulSum; i ++) {
        CxDir(csDirPath).pathCreate();

        objPop3.retriveRaw(i, csDirPath, csFileName + xT("_") + CxString::cast(i) + xT(".eml"));
        /*LOG*/printf("retriveRaw %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (std::size_t i = 1; i <= ulSum; i ++) {
        CxMimeHeader mhMimeHeader;

        objPop3.retrieveHeader(iNum, mhMimeHeader);
        /*LOG*/printf("retrieveHeader %lu\n", i);
    }

    //-------------------------------------
    //bDisconnect
    objPop3.disconnect();
}
//-------------------------------------------------------------------------------------------------

#endif // xHAVE_OPENSSL_CRYPTO
