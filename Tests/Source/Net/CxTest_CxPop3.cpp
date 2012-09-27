/**
 * \file   CxTest_CxPop3.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxPop3.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


//---------------------------------------------------------------------------
CxTest_CxPop3::CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
CxTest_CxPop3::~CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxPop3::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if xOS_ENV_WIN
    //-------------------------------------
    //
    //const std::tstring_t csUser     = xT("Sergey");        //"test_1";
    //const std::tstring_t csPass     = xT("12345");            //"test_1";
    //const std::tstring_t csServer   = xT("192.168.1.47");    //"127.0.0.1";
    //const ushort_t  cusPort    = 110;

    //-------------------------------------
    //CourierMS.exe
    //const std::tstring_t csUser     = xT("test_1@serg.com");
    //const std::tstring_t csPass     = xT("test_1");
    //const std::tstring_t csServer   = xT("127.0.0.1");
    //const ushort_t  cusPort    = 110;

    //-------------------------------------
    //IPNET
    const std::tstring_t  csUser     = xT("domen");
    const std::tstring_t  csPass     = xT("control6");
    const std::tstring_t  csServer   = xT("mail.ipnet.kiev.ua");
    const ushort_t   cusPort    = 110;

    //-------------------------------------
    //hMailServer
    ////const std::tstring_t  csUser     = xT("test_2@serg.com");
    ////const std::tstring_t  csPass     = xT("test_2");
    ////const std::tstring_t  csServer   = xT("127.0.0.1");
    ////const ushort_t   cusPort    = 110;


    //-------------------------------------
    //
    ulong_t              ulSum      = 0;
    ulong_t              ulSize     = 0;
    ulong_t              ulMsgID    = 1;
    std::vector<ulong_t> veculList;
    ////ulong_t              ulIndex    = 1;
    int                iNum       = 1;
    const std::tstring_t      csDirPath  = xT("C:/Temp2");
    const std::tstring_t      csFileName = xT("MailFileName");


    CxPop3 objPop3;

    //-------------------------------------
    //bCreate
    m_bRv = objPop3.bCreate(csUser, csPass, csServer, cusPort);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bConnect
    m_bRv = objPop3.bConnect();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bLogin
    m_bRv = objPop3.bLogin();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bStat
    m_bRv = objPop3.bStat(ulSum, ulSize);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bList
    ////m_bRv = objPop3.bList(veculList);
    ////xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bListAt
    ////m_bRv = objPop3.bListAt(ulIndex);
    ////xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bNoop
    m_bRv = objPop3.bNoop();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bDelete
    m_bRv = objPop3.bDelete(ulMsgID);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bRset
    m_bRv = objPop3.bRset();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bTop
    for (ulong_t i = 1; i <= ulSum; i ++) {
        //////-------------------------------------
        //////CxMimeMessage
        ////CxMimeMessage objMessage;
        ////std::tstring_t       sRawHeader;

        //////-------------------------------------
        //////CxMimeHeader
        ////CxMimeHeader objHeader;

        ////m_bRv = objPop3.bTop(iNum, 0, /*ref*/sRawHeader);
        ////xTEST_EQ(true, m_bRv);
        /////*LOG*/printf("bTop %i\n", i);

        ////m_bRv = objHeader.bParse(sRawHeader);
        ////xTEST_EQ(true, m_bRv);

        ////m_sRv = objHeader.sGetField(xT("Message-Id"));
        ////xTEST_EQ(false, m_sRv.empty());


        //////-------------------------------------
        //////CxMimeBody
        ////////CxMimeBody objBody;

        //////m_bRv = m_Body.bParse(sRawMessage);
        //////xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bRetriveRaw
    for (ulong_t i = 1; i <= ulSum; i ++) {
        CxDir::bCreateForce(csDirPath);

        m_bRv = objPop3.bRetriveRaw(i, csDirPath, csFileName + xT("_") + CxString::string_cast(i) + xT(".eml"));
        xTEST_EQ(true, m_bRv);

        /*LOG*/printf("bRetriveRaw %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (ulong_t i = 1; i <= ulSum; i ++) {
        CxMimeHeader mhMimeHeader;

        m_bRv = objPop3.bRetrieveHeader(iNum, mhMimeHeader);
        xTEST_EQ(true, m_bRv);

        /*LOG*/printf("bRetrieveHeader %lu\n", i);
    }

    //-------------------------------------
    //bDisconnect
    m_bRv = objPop3.bDisconnect();
    xTEST_EQ(true, m_bRv);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
