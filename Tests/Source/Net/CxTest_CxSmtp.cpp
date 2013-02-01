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
/* virtual */
void
CxTest_CxSmtp::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //-------------------------------------
    //IPNET
    //const std::tstring_t  csUser     = "domen";
    //const std::tstring_t  csPass     = "control6";
    //const std::tstring_t  csServer   = "mail.ipnet.kiev.ua";
    //ushort_t             usPort     = 25;
    //const std::tstring_t  csFrom     = "domen@ipnet.kiev.ua";
    //const std::tstring_t  csTo       = "skynowa@gmail.com";
    //const std::tstring_t  csFilePath = "C:/Temp/test.eml";
    //const std::tstring_t  csDirPath  = "C:/Temp";

    //-------------------------------------
    //CourierMS
    const std::tstring_t  csUser     = xT("test_1");
    const std::tstring_t  csPass     = xT("test_1");
    const std::tstring_t  csServer   = xT("127.0.0.1");
    ushort_t              usPort     = 25;
    const std::tstring_t  csFrom     = xT("test_1@serg.com");
    const std::tstring_t  csTo       = xT("test_2@serg.com");
    const std::tstring_t  csFilePath = xT("C:/Temp2/test.eml");
    const std::tstring_t  csDirPath  = xT("C:/Temp");

    //-------------------------------------
    //hMailServer
    //const std::tstring_t  csUser     = "test_1@serg.com";
    //const std::tstring_t  csPass     = "test_1";
    //const std::tstring_t  csServer   = "127.0.0.1";
    //ushort_t             usPort     = 25;
    //const std::tstring_t  csFrom     = "test_1@serg.com";
    //const std::tstring_t  csTo       = "test_2@serg.com";
    //const std::tstring_t  csFilePath = "C:/Temp2/test.eml";
    //const std::tstring_t  csDirPath  = "C:/Temp";

    //-------------------------------------
    //
    ulong_t              ulSum      = 0;    xUNUSED(ulSum);
    ulong_t              ulSize     = 0;    xUNUSED(ulSize);
    ulong_t              ulMsgID    = 1;    xUNUSED(ulMsgID);
    std::vector<ulong_t> veculList;
    ulong_t              ulIndex    = 1;    xUNUSED(ulIndex);
    int                  iNum       = 1;    xUNUSED(iNum);
    const std::tstring_t csText     = xT("HELO");

    CxSmtp objSmtp;

    //-------------------------------------
    //bCreate
    objSmtp.create(csUser, csPass, csServer, usPort);

    //-------------------------------------
    //bConnect
    objSmtp.connect();

    //-------------------------------------
    //bLogin
    ////objSmtp.vLogin();

    //-------------------------------------
    //bSend
    objSmtp.send(csText, csFrom, csTo);

    //-------------------------------------
    // vSendRaw
    // TEST: CxSmtp::vSendRaw
#if xTODO
    g_vsRes = CxDir::vsListFiles(csDirPath, "*.eml");
    for (size_t i = 0; i < g_vsRes.size(); i ++) {
        objSmtp.vSendRaw(csDirPath + "\\" + g_vsRes.at(i), csFrom, csTo);
        /*LOG*///printf("Send msg %s\n", g_vsRes.at(i).c_str());
    }
#endif

    //-------------------------------------
    //bNoop
    objSmtp.noop();

    //-------------------------------------
    //bRset
    objSmtp.rset();

    //-------------------------------------
    //bDisconnect
    objSmtp.disconnect();
}
//---------------------------------------------------------------------------
