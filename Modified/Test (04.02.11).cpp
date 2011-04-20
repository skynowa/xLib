/****************************************************************************
*
*
*****************************************************************************/


#include <xLib/Common/xCommon.h>

//Other
#include "CxTest_CxMacros.h"
#include "CxTest_CxLocale.h"
#include "CxTest_CxString.h"
#include "CxTest_CxDateTime.h"
#include "CxTest_CxFunctorT.h"
#include "CxTest_CxSystemInfo.h"
#include "CxTest_CxAutoMallocT.h"
#include "CxTest_CxException.h"
#if defined(xOS_WIN)
    #include "CxTest_CxClipboard.h"
    #include "CxTest_CxCom.h"
    #include "CxTest_CxHandleT.h"
    #include "CxTest_CxShell.h"
    #include "CxTest_CxComPort.h"
    #include "CxTest_CxConsole.h"
#elif defined(xOS_LINUX)

#endif

//Debug
#include "Debug/CxTest_CxLastError.h"
#include "Debug/CxTest_CxReport.h"
#include "Debug/CxTest_CxDebugger.h"
#include "Debug/CxTest_CxProfiler.h"
#include "Debug/CxTest_CxAutoProfiler.h"

//Fso
#include "Fso/CxTest_CxPath.h"
#include "Fso/CxTest_CxDir.h"
#include "Fso/CxTest_CxEnvironment.h"
#include "Fso/CxTest_CxStdioFile.h"
#include "Fso/CxTest_CxDll.h"

#if defined(xOS_WIN)
    #include "Fso/CxTest_CxDrive.h"
    #include "Fso/CxTest_CxFile.h"
    #include "Fso/CxTest_CxIni.h"
    #include "Fso/CxTest_CxMemoryIni.h"
#elif defined(xOS_LINUX)

#endif

//GDI+
#if defined(xOS_WIN)
    #include "GDI+/CxTest_CxGdiplus.h"
    #include "GDI+/CxTest_CxImage.h"
#endif

//Log


//Net
#include "Net/CxTest_CxSocketInit.h"
#include "Net/CxTest_CxSocket.h"
#include "Net/CxTest_CxDnsClient.h"
//#include "Net/CxTest_CxTcpClientSocket.h"
//#include "Net/CxTest_CxTcpServerSocket.h"

//Crypt
#include "Crypt/CxTest_CxBase64.h"
#include "Crypt/CxTest_CxCrc32.h"
#include "Crypt/CxTest_CxRandom.h"
////#include "Crypt/CxTest_CxBlowfish.h"

//Db
#include "Db/CxTest_CxConnectionString.h"
#include "Db/CxTest_CxMySql.h"

//Sync
#include "Sync/CxTest_CxProcess.h"

//Patterns
#include "Patterns/CxTest_CxSingleton.h"

//PKCS11
#if defined(xOS_WIN)
    #include "PKCS11/CxTest_CxPkcs11.h"
#elif defined(xOS_LINUX)

#endif

//---------------------------------------------------------------------------
INT
main(INT argc, TCHAR *argv[]) {
    //--------------------------------------------------
    //settings
    const ULONGLONG ullTimesForAll    = 1;    //number of tests for all units
    const ULONGLONG ullTimesForSingle = 1;    //number of tests for a unit

    BOOL bRes = FALSE;


    std::vector<VOID *> vecpvContainer;


    //--------------------------------------------------
    //run all tests
    for (ULONGLONG i = 0; i < ullTimesForAll; ++ i) {
        //--------------------------------------------------
        //Other
        CxTest_CxMacros tsCxMacros;
        bRes = tsCxMacros.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxLocale tsCxLocale;
        bRes = tsCxLocale.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxString tsCxString;
        bRes = tsCxString.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxDateTime tsCxDateTime;
        bRes = tsCxDateTime.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxFunctorT  tsCxFunctorT;
        bRes = tsCxFunctorT.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxSystemInfo tsCxSystemInfo;
        bRes = tsCxSystemInfo.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxException tsCxException;
        bRes = tsCxException.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

    #if defined(xOS_WIN)
        CxTest_CxClipboard tsCxClipboard;
        bRes = tsCxClipboard.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxCom tsCxCom;
        bRes = tsCxCom.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxHandleT tsCxHandleT;
        bRes = tsCxHandleT.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxShell tsCxShell;
        bRes = tsCxShell.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxComPort tsCxComPort;
        bRes = tsCxComPort.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxConsole tsCxConsole;
        bRes = tsCxConsole.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);
    #elif defined(xOS_LINUX)

    #endif

        //--------------------------------------------------
        //Debug
        CxTest_CxLastError tsCxLastError;
        bRes = tsCxLastError.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxDebugger tsCxDebugger;
        ////bRes = tsCxDebugger.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxReport tsCxReport;
        bRes = tsCxReport.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxProfiler tsCxProfiler;
        bRes = tsCxProfiler.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxAutoProfiler tsCxAutoProfiler;
        bRes = tsCxAutoProfiler.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //Fso
        CxTest_CxPath tsCxPath;
        bRes = tsCxPath.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxDir tsCxDir;
        bRes = tsCxDir.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxEnvironment tsCxEnvironment;
        bRes = tsCxEnvironment.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxStdioFile tsCxStdioFile;
        bRes = tsCxStdioFile.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxDll tsCxDll;
        bRes = tsCxDll.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

    #if defined(xOS_WIN)
        CxTest_CxDrive tsCxDrive;
        bRes = tsCxDrive.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxFile tsCxFile;
        bRes = tsCxFile.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxIni tsCxIni;
        bRes = tsCxIni.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxMemoryIni tsCxMemoryIni;
        bRes = tsCxMemoryIni.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);
    #elif defined(xOS_LINUX)

    #endif

        //--------------------------------------------------
        //GDI+
    #if defined(xOS_WIN)
        CxTest_CxGdiplus tsCxGdiplus;
        bRes = tsCxGdiplus.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxImage tsCxImage;
        bRes = tsCxImage.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);
    #endif

        //--------------------------------------------------
        //Log


        //--------------------------------------------------
        //Net
        CxTest_CxSocketInit tsCxSocketInit;
        bRes = tsCxSocketInit.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxDnsClient tsCxTest_CxDnsClient;
        bRes = tsCxTest_CxDnsClient.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //CxTest_CxTcpClientSocket tsCxTcpClientSocket;
        //bRes = tsCxTcpClientSocket.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //CxTest_CxTcpServerSocket tsCxTcpServerSocket;
        //bRes = tsCxTcpServerSocket.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //Crypt
        CxTest_CxCrc32 tsCxCrc32;
        bRes = tsCxCrc32.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        ////CxTest_CxBlowfish CxBlowfish;
        ////bRes = CxBlowfish.bRun(ullTimesForSingle);
        /////*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //Db
        CxTest_CxConnectionString tsCxConnectionString;
        bRes = tsCxConnectionString.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        CxTest_CxMySql tsCxMySql;
        bRes = tsCxMySql.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //Sync
        CxTest_CxProcess tsCxProcess;
        bRes = tsCxProcess.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //Patterns
        CxTest_CxSingleton tsCxSingleton;
        bRes = tsCxSingleton.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);

        //--------------------------------------------------
        //PKCS11
    #if defined(xOS_WIN)
        CxTest_CxPkcs11 tsCxPKCS11;
        bRes = tsCxPKCS11.bRun(ullTimesForSingle);
        /*DEBUG*/xASSERT_MSG_RET(FALSE != bRes, xT("Test not complete"), FALSE);
    #elif defined(xOS_LINUX)

    #endif
    }

    xSTD_COUT(xT("All tests successful done...\n\n"));

    //system("pause");
    return 0;
}
//---------------------------------------------------------------------------
