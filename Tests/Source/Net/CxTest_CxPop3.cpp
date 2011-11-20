/**
 * \file   CxTest_CxPop3.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxPop3.h>


//---------------------------------------------------------------------------
CxTest_CxPop3::CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
CxTest_CxPop3::~CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxPop3::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if xOS_ENV_WIN
    //-------------------------------------
    //
    //const std::tstring csUser     = xT("Sergey");        //"test_1";
    //const std::tstring csPass     = xT("12345");            //"test_1";
    //const std::tstring csServer   = xT("192.168.1.47");    //"127.0.0.1";
    //const USHORT  cusPort    = 110;

    //-------------------------------------
    //CourierMS.exe
    //const std::tstring csUser     = xT("test_1@serg.com");
    //const std::tstring csPass     = xT("test_1");
    //const std::tstring csServer   = xT("127.0.0.1");
    //const USHORT  cusPort    = 110;

    //-------------------------------------
    //IPNET
    const std::tstring  csUser     = xT("domen");
    const std::tstring  csPass     = xT("control6");
    const std::tstring  csServer   = xT("mail.ipnet.kiev.ua");
    const USHORT   cusPort    = 110;

    //-------------------------------------
    //hMailServer
    ////const std::tstring  csUser     = xT("test_2@serg.com");
    ////const std::tstring  csPass     = xT("test_2");
    ////const std::tstring  csServer   = xT("127.0.0.1");
    ////const USHORT   cusPort    = 110;


    //-------------------------------------
    //
    ULONG              ulSum      = 0;
    ULONG              ulSize     = 0;
    ULONG              ulMsgID    = 1;
    std::vector<ULONG> veculList;
    ////ULONG              ulIndex    = 1;
    int                iNum       = 1;
    const std::tstring      csDirPath  = xT("C:/Temp2");
    const std::tstring      csFileName = xT("MailFileName");


    CxPop3 objPop3;

    //-------------------------------------
    //bCreate
    m_bRes = objPop3.bCreate(csUser, csPass, csServer, cusPort);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objPop3.bConnect();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bLogin
    m_bRes = objPop3.bLogin();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bStat
    m_bRes = objPop3.bStat(ulSum, ulSize);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bList
    ////m_bRes = objPop3.bList(veculList);
    ////xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bListAt
    ////m_bRes = objPop3.bListAt(ulIndex);
    ////xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bNoop
    m_bRes = objPop3.bNoop();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bDelete
    m_bRes = objPop3.bDelete(ulMsgID);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bRset
    m_bRes = objPop3.bRset();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bTop
    for (ULONG i = 1; i <= ulSum; i ++) {
        //////-------------------------------------
        //////CxMimeMessage
        ////CxMimeMessage objMessage;
        ////std::tstring       sRawHeader;

        //////-------------------------------------
        //////CxMimeHeader
        ////CxMimeHeader objHeader;

        ////m_bRes = objPop3.bTop(iNum, 0, /*ref*/sRawHeader);
        ////xTEST_DIFF(false, m_bRes);
        /////*LOG*/printf("bTop %i\n", i);

        ////m_bRes = objHeader.bParse(sRawHeader);
        ////xTEST_DIFF(false, m_bRes);

        ////m_sRes = objHeader.sGetField(xT("Message-Id"));
        ////xTEST_EQ(false, m_sRes.empty());


        //////-------------------------------------
        //////CxMimeBody
        ////////CxMimeBody objBody;

        //////m_bRes = m_Body.bParse(sRawMessage);
        //////xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bRetriveRaw
    for (ULONG i = 1; i <= ulSum; i ++) {
        CxDir::bCreateForce(csDirPath);

        m_bRes = objPop3.bRetriveRaw(i, csDirPath, csFileName + xT("_") + CxString::lexical_cast(i) + xT(".eml"));
        xTEST_DIFF(false, m_bRes);

        /*LOG*/printf("bRetriveRaw %lu\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (ULONG i = 1; i <= ulSum; i ++) {
        CxMimeHeader mhMimeHeader;

        m_bRes = objPop3.bRetrieveHeader(iNum, mhMimeHeader);
        xTEST_DIFF(false, m_bRes);

        /*LOG*/printf("bRetrieveHeader %lu\n", i);
    }

    //-------------------------------------
    //bDisconnect
    m_bRes = objPop3.bDisconnect();
    xTEST_DIFF(false, m_bRes);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
