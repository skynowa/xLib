/****************************************************************************
* Class name:  CxTest_CxPop3
* Description: test CxPop3
* File name:   CxTest_CxPop3.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxPop3.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxPop3
CxTest_CxPop3::CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxPop3
CxTest_CxPop3::~CxTest_CxPop3() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxPop3::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
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
    m_bRes = objPop3.bCreate(csUser, csPass, csServer, cusPort);
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objPop3.bConnect();
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bLogin
    m_bRes = objPop3.bLogin();
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bStat
    m_bRes = objPop3.bStat(ulSum, ulSize);
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bList
    ////m_bRes = objPop3.bList(veculList);
    ////xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bListAt
    ////m_bRes = objPop3.bListAt(ulIndex);
    ////xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bNoop
    m_bRes = objPop3.bNoop();
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bDelete
    m_bRes = objPop3.bDelete(ulMsgID);
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

    //-------------------------------------
    //bRset
    m_bRes = objPop3.bRset();
    xASSERT_NOT_EQUAL(FALSE, m_bRes);

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

        ////m_bRes = objPop3.bTop(iNum, 0, /*ref*/sRawHeader);
        ////xASSERT_NOT_EQUAL(FALSE, m_bRes);
        /////*LOG*/printf("bTop %i\n", i);

        ////m_bRes = objHeader.bParse(sRawHeader);
        ////xASSERT_NOT_EQUAL(FALSE, m_bRes);

        ////m_sRes = objHeader.sGetField(xT("Message-Id"));
        ////xASSERT_EQUAL(FALSE, m_sRes.empty());


        //////-------------------------------------
        //////CxMimeBody
        ////////CxMimeBody objBody;

        //////m_bRes = m_Body.bParse(sRawMessage);
        //////xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //-------------------------------------
    //bRetriveRaw
    for (ULONG i = 1; i <= ulSum; i ++) {
        CxDir::bCreateForce(csDirPath);

        m_bRes = objPop3.bRetriveRaw(i, csDirPath, csFileName + xT("_") + CxString::lexical_cast(i) + xT(".eml"));
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        /*LOG*/printf("bRetriveRaw %i\n", i);
    }

    //-------------------------------------
    //bRetrieveHeader
    for (ULONG i = 1; i <= ulSum; i ++) {
        CxMimeHeader mhMimeHeader;

        m_bRes = objPop3.bRetrieveHeader(iNum, mhMimeHeader);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        /*LOG*/printf("bRetrieveHeader %i\n", i);
    }

    //-------------------------------------
    //bDisconnect
    m_bRes = objPop3.bDisconnect();
    xASSERT_NOT_EQUAL(FALSE, m_bRes);
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
