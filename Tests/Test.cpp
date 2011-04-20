/****************************************************************************
*
*
*****************************************************************************/


#ifndef xLib_UnitTestH
#define xLib_UnitTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

//Other
#include "Common/CxTest_CxMacros.h"
#include "Common/CxTest_CxArray.h"
#include "Common/CxTest_CxChar.h"
#include "Common/CxTest_CxLocale.h"
#include "Common/CxTest_CxString.h"
#include "Common/CxTest_CxDateTime.h"
#include "Common/CxTest_CxFunctorT.h"
#include "Common/CxTest_CxSystemInfo.h"
#include "Common/CxTest_CxAutoMallocT.h"
#include "Common/CxTest_CxException.h"
#if defined(xOS_WIN)
    #include "Common/CxTest_CxClipboard.h"
    #include "Common/CxTest_CxCom.h"
    #include "Common/CxTest_CxHandle.h"
    #include "Common/CxTest_CxShell.h"
    #include "Common/CxTest_CxComPort.h"
    #include "Common/CxTest_CxConsole.h"
#elif defined(xOS_LINUX)

#endif

//Debug
#include "Debug/CxTest_CxLastError.h"
#include "Debug/CxTest_CxReport.h"
#include "Debug/CxTest_CxDebugger.h"
#include "Debug/CxTest_CxProfiler.h"
#include "Debug/CxTest_CxAutoProfiler.h"

//Filesystem
#include "Filesystem/CxTest_CxPath.h"
#include "Filesystem/CxTest_CxDir.h"
#include "Filesystem/CxTest_CxEnvironment.h"
#include "Filesystem/CxTest_CxStdioFile.h"
#include "Filesystem/CxTest_CxDll.h"

#if defined(xOS_WIN)
    #include "Filesystem/CxTest_CxDrive.h"
    #include "Filesystem/CxTest_CxFile.h"
    #include "Filesystem/CxTest_CxIni.h"
    #include "Filesystem/CxTest_CxMemoryIni.h"
#elif defined(xOS_LINUX)

#endif

//GDI+
#if defined(xOS_WIN)
    //#include "GDI+/CxTest_CxGdiplus.h"
    //#include "GDI+/CxTest_CxImage.h"
#endif

//Log


//Net
#include "Net/CxTest_CxCookiePv0.h"
#include "Net/CxTest_CxCookiePv1.h"
#include "Net/CxTest_CxCgi.h"
#include "Net/CxTest_CxSocketInit.h"
#include "Net/CxTest_CxSocket.h"
#include "Net/CxTest_CxDnsClient.h"
#include "Net/CxTest_CxTcpClientSocket.h"
#include "Net/CxTest_CxTcpServerSocket.h"
#include "Net/CxTest_CxHttpClient.h"

//Compress
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include "Compress/CxTest_CxGz.h"
#endif


//Crypt
#include "Crypt/CxTest_CxBase64.h"
#include "Crypt/CxTest_CxCrc32.h"
#include "Crypt/CxTest_CxRandom.h"
#include "Crypt/CxTest_CxBlowfish.h"

//Db
#include "Db/CxTest_CxConnectionString.h"
#include "Db/CxTest_CxMySql.h"

//Sync
#include "Sync/CxTest_CxProcess.h"
#if defined(xOS_WIN)
    /////#include "Sync/CxTest_CxThread.h"
#elif defined(xOS_LINUX)

#endif

//Patterns
#include "Patterns/CxTest_CxSingleton.h"

//PKCS11
#if defined(xOS_WIN)
    ////#include "PKCS11/CxTest_CxPkcs11.h"
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
INT
_tmain(INT argc, TCHAR *argv[]) {
    tcout << "Content-type: text/html\n\n" << tendl;

    #if xTEMP_DISABLED
        //fprintf(stdout, "Content-type: text/html\n");
        //tcout << xT("##################") << tendl;
        fprintf(stdout, "Location: %s\n\n", "http://www.yandex.ru/");

        return EXIT_SUCCESS;
    #endif


    #if xTEMP_DISABLED
        xTRACEV(xT("\n\n*** xLib v.%s (author: %s date: %s) ***"), xLIB_VERSION, xLIB_AUTHOR, xLIB_DATE);
        xTRACE(xT("Start all tests..."));
    #endif

    //--------------------------------------------------
    //settings
    const ULONGLONG ullTimesForAll    = 1;    //number of tests for all units
    const ULONGLONG ullTimesForSingle = 1;    //number of tests for a unit

    BOOL bRes = FALSE;

    std::vector<CxTest *> vecpvTests;


    #if xTEMP_ENABLED
        //--------------------------------------------------
        //Other
        vecpvTests.push_back( new CxTest_CxMacros );
        vecpvTests.push_back( new CxTest_CxArray );
        vecpvTests.push_back( new CxTest_CxChar );
        vecpvTests.push_back( new CxTest_CxLocale );
        vecpvTests.push_back( new CxTest_CxString );
        vecpvTests.push_back( new CxTest_CxDateTime );
        vecpvTests.push_back( new CxTest_CxFunctorT );
        vecpvTests.push_back( new CxTest_CxSystemInfo );
        vecpvTests.push_back( new CxTest_CxException );

        #if defined(xOS_WIN)
        vecpvTests.push_back( new CxTest_CxClipboard );
        vecpvTests.push_back( new CxTest_CxCom );
        vecpvTests.push_back( new CxTest_CxHandleT );
        vecpvTests.push_back( new CxTest_CxShell );
        vecpvTests.push_back( new CxTest_CxComPort );
        ////vecpvTests.push_back( new CxTest_CxConsole );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Debug
        vecpvTests.push_back( new CxTest_CxLastError );
        ////vecpvTests.push_back( new CxTest_CxDebugger );
        vecpvTests.push_back( new CxTest_CxReport );
        vecpvTests.push_back( new CxTest_CxProfiler );
        vecpvTests.push_back( new CxTest_CxAutoProfiler );

        //--------------------------------------------------
        //Filesystem
        vecpvTests.push_back( new CxTest_CxPath );
        vecpvTests.push_back( new CxTest_CxStdioFile );
        vecpvTests.push_back( new CxTest_CxDir );
        vecpvTests.push_back( new CxTest_CxEnvironment );
        vecpvTests.push_back( new CxTest_CxDll );

        #if defined(xOS_WIN)
        vecpvTests.push_back( new CxTest_CxDrive );
        vecpvTests.push_back( new CxTest_CxFile );
        vecpvTests.push_back( new CxTest_CxIni );
        vecpvTests.push_back( new CxTest_CxMemoryIni );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //GDI+
        #if defined(xOS_WIN)
        //vecpvTests.push_back( new CxTest_CxGdiplus );
        //vecpvTests.push_back( new CxTest_CxImage );
        #endif

        //--------------------------------------------------
        //Log


        //--------------------------------------------------
        //Net
        vecpvTests.push_back( new CxTest_CxCookiePv0 );
        vecpvTests.push_back( new CxTest_CxCookiePv1 );
        vecpvTests.push_back( new CxTest_CxCgi );
        vecpvTests.push_back( new CxTest_CxSocketInit );
        vecpvTests.push_back( new CxTest_CxDnsClient );
        ////vecpvTests.push_back( new CxTest_CxTcpClientSocket );
        ////vecpvTests.push_back( new CxTest_CxTcpServerSocket );
        vecpvTests.push_back( new CxTest_CxHttpClient );

        //--------------------------------------------------
        //Compress
        #if defined(xOS_WIN)

        #elif defined(xOS_LINUX)
        vecpvTests.push_back( new CxTest_CxGz );
        #endif

        //--------------------------------------------------
        //Crypt
        vecpvTests.push_back( new CxTest_CxCrc32 );
        ////vecpvTests.push_back( new CxTest_CxBlowfish );

        //--------------------------------------------------
        //Db
        vecpvTests.push_back( new CxTest_CxConnectionString );
        vecpvTests.push_back( new CxTest_CxMySql );

        //--------------------------------------------------
        //Sync
        vecpvTests.push_back( new CxTest_CxProcess );
        #if defined(xOS_WIN)
        ////vecpvTests.push_back( new CxTest_CxThread );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Patterns
        vecpvTests.push_back( new CxTest_CxSingleton );

        //--------------------------------------------------
        //PKCS11
        #if defined(xOS_WIN)
        ////vecpvTests.push_back( new CxTest_CxPkcs11 );
        #elif defined(xOS_LINUX)

        #endif
    #endif

    //--------------------------------------------------
    //run all tests
    for (ULONGLONG i = 0; i < ullTimesForAll; ++ i) {
        for (std::vector<CxTest *>::iterator it = vecpvTests.begin(); it != vecpvTests.end(); ++ it) {
            xTRACEV("Test (%s) begin.", (*it)->sGetName().c_str());

            bRes = (*it)->bRun(ullTimesForSingle);
            xASSERT_MSG_RET(FALSE != bRes, ( xT("Test (") + (*it)->sGetName() + xT(") not complete") ).c_str(), FALSE);

            xTRACEV("Test (%s) end.\n", (*it)->sGetName().c_str());
        }
    }

    //--------------------------------------------------
    //free memory
    for (std::vector<CxTest *>::iterator it = vecpvTests.begin(); it != vecpvTests.end(); ++ it) {
        /*CxMacros::*/xPTR_DELETE(*it);
    }

    xTRACE(xT("All tests successful done.\n\n"));

    return 0;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH


