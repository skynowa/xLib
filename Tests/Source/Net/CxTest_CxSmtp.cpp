/**
 * \file   CxTest_CxSmtp.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSmtp.h>


//---------------------------------------------------------------------------
CxTest_CxSmtp::CxTest_CxSmtp() {

}
//---------------------------------------------------------------------------
CxTest_CxSmtp::~CxTest_CxSmtp() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxSmtp::bUnit(
    const ulonglong_t cullBlockLoops
)
{
#if xOS_ENV_WIN
    //-------------------------------------
    //IPNET
    //const std::string  csUser     = "domen";
    //const std::string  csPass     = "control6";
    //const std::string  csServer   = "mail.ipnet.kiev.ua";
    //ushort_t             usPort     = 25;
    //const std::string  csFrom     = "domen@ipnet.kiev.ua";
    //const std::string  csTo       = "skynowa@gmail.com";
    //const std::string  csFilePath = "C:/Temp/test.eml";
    //const std::string  csDirPath  = "C:/Temp";

    //-------------------------------------
    //CourierMS
    const std::string  csUser     = "test_1";
    const std::string  csPass     = "test_1";
    const std::string  csServer   = "127.0.0.1";
    ushort_t             usPort     = 25;
    const std::string  csFrom     = "test_1@serg.com";
    const std::string  csTo       = "test_2@serg.com";
    const std::string  csFilePath = "C:/Temp2/test.eml";
    const std::string  csDirPath  = "C:/Temp";

    //-------------------------------------
    //hMailServer
    //const std::string  csUser     = "test_1@serg.com";
    //const std::string  csPass     = "test_1";
    //const std::string  csServer   = "127.0.0.1";
    //ushort_t             usPort     = 25;
    //const std::string  csFrom     = "test_1@serg.com";
    //const std::string  csTo       = "test_2@serg.com";
    //const std::string  csFilePath = "C:/Temp2/test.eml";
    //const std::string  csDirPath  = "C:/Temp";

    //-------------------------------------
    //
    ulong_t              ulSum      = 0;
    ulong_t              ulSize     = 0;
    ulong_t              ulMsgID    = 1;
    std::vector<ulong_t> veculList;
    ulong_t              ulIndex    = 1;
    int                iNum       = 1;
    const std::string  csText     = "HELO";

    CxSmtp objSmtp;

    //-------------------------------------
    //bCreate
    m_bRes = objSmtp.bCreate(csUser, csPass, csServer, usPort);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objSmtp.bConnect();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bLogin
    ////m_bRes = objSmtp.bLogin();
    ////xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bSend
    m_bRes = objSmtp.bSend(csText, csFrom, csTo);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bSendRaw
#if xTODO
    g_vsRes = CxDir::vsListFiles(csDirPath, "*.eml");
    for (size_t i = 0; i < g_vsRes.size(); i ++) {
        m_bRes = objSmtp.bSendRaw(csDirPath + "\\" + g_vsRes.at(i), csFrom, csTo);
        xTEST_DIFF(false, m_bRes);
        /*LOG*///printf("Send msg %s\n", g_vsRes.at(i).c_str());
    }
#endif

    //-------------------------------------
    //bNoop
    m_bRes = objSmtp.bNoop();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bRset
    m_bRes = objSmtp.bRset();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bDisconnect
    m_bRes = objSmtp.bDisconnect();
    xTEST_DIFF(false, m_bRes);
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
