/**
 * \file   CxTest_CxSmtp.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSmtp.h>


#if xOPENSSL_IS_USE

//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSmtp::unit(
    culonglong_t &a_cullCaseLoops
)
{
    //-------------------------------------
    //IPNET
    //std::ctstring_t  csUser     = "domen";
    //std::ctstring_t  csPass     = "control6";
    //std::ctstring_t  csServer   = "mail.ipnet.kiev.ua";
    //ushort_t             usPort     = 25;
    //std::ctstring_t  csFrom     = "domen@ipnet.kiev.ua";
    //std::ctstring_t  csTo       = "skynowa@gmail.com";
    //std::ctstring_t  csFilePath = "C:/Temp/test.eml";
    //std::ctstring_t  csDirPath  = "C:/Temp";

    //-------------------------------------
    //CourierMS
    std::ctstring_t  csUser     = xT("test_1");
    std::ctstring_t  csPass     = xT("test_1");
    std::ctstring_t  csServer   = xT("127.0.0.1");
    ushort_t              usPort     = 25;
    std::ctstring_t  csFrom     = xT("test_1@serg.com");
    std::ctstring_t  csTo       = xT("test_2@serg.com");
    std::ctstring_t  csFilePath = xT("C:/Temp2/test.eml");
    std::ctstring_t  csDirPath  = xT("C:/Temp");

    //-------------------------------------
    //hMailServer
    //std::ctstring_t  csUser     = "test_1@serg.com";
    //std::ctstring_t  csPass     = "test_1";
    //std::ctstring_t  csServer   = "127.0.0.1";
    //ushort_t             usPort     = 25;
    //std::ctstring_t  csFrom     = "test_1@serg.com";
    //std::ctstring_t  csTo       = "test_2@serg.com";
    //std::ctstring_t  csFilePath = "C:/Temp2/test.eml";
    //std::ctstring_t  csDirPath  = "C:/Temp";

    //-------------------------------------
    //
    ulong_t              ulSum      = 0;    xUNUSED(ulSum);
    ulong_t              ulSize     = 0;    xUNUSED(ulSize);
    ulong_t              ulMsgID    = 1;    xUNUSED(ulMsgID);
    std::vector<ulong_t> veculList;
    ulong_t              ulIndex    = 1;    xUNUSED(ulIndex);
    int_t                  iNum       = 1;    xUNUSED(iNum);
    std::ctstring_t csText     = xT("HELO");

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
//------------------------------------------------------------------------------

#endif // xOPENSSL_IS_USE
