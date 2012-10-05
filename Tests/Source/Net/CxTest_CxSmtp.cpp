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
#if   xOS_ENV_WIN
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
    ushort_t           usPort     = 25;
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
    objSmtp.vCreate(csUser, csPass, csServer, usPort);

    //-------------------------------------
    //bConnect
    objSmtp.vConnect();

    //-------------------------------------
    //bLogin
    ////objSmtp.vLogin();

    //-------------------------------------
    //bSend
    objSmtp.vSend(csText, csFrom, csTo);

    //-------------------------------------
    //bSendRaw
#if xTODO
    g_vsRes = CxDir::vsListFiles(csDirPath, "*.eml");
    for (size_t i = 0; i < g_vsRes.size(); i ++) {
        objSmtp.vSendRaw(csDirPath + "\\" + g_vsRes.at(i), csFrom, csTo);
        /*LOG*///printf("Send msg %s\n", g_vsRes.at(i).c_str());
    }
#endif

    //-------------------------------------
    //bNoop
    objSmtp.vNoop();

    //-------------------------------------
    //bRset
    objSmtp.vRset();

    //-------------------------------------
    //bDisconnect
    objSmtp.vDisconnect();
#elif xOS_ENV_UNIX

#endif
}
//---------------------------------------------------------------------------
