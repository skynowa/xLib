/****************************************************************************
* Class name:
* Description: tests for xLib
* File name:   Test.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.01.2011
*
*****************************************************************************/


#ifndef xLib_UnitTestH
#define xLib_UnitTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

//Common
#include "../Include/Common/CxTest_CxMacros.h"
#include "../Include/Common/CxTest_CxArray.h"
#include "../Include/Common/CxTest_CxChar.h"
#include "../Include/Common/CxTest_CxLocale.h"
#include "../Include/Common/CxTest_CxString.h"
#include "../Include/Common/CxTest_CxDateTime.h"
#include "../Include/Common/CxTest_CxFunctorT.h"
#include "../Include/Common/CxTest_CxSystemInfo.h"
#include "../Include/Common/CxTest_CxAutoMallocT.h"
#include "../Include/Common/CxTest_CxException.h"
#if defined(xOS_WIN)
    #include "../Include/Common/CxTest_CxClipboard.h"
    #include "../Include/Common/CxTest_CxCom.h"
    #include "../Include/Common/CxTest_CxHandleT.h"
    #include "../Include/Common/CxTest_CxShell.h"
    #include "../Include/Common/CxTest_CxComPort.h"
    #include "../Include/Common/CxTest_CxConsole.h"
#elif defined(xOS_LINUX)

#endif

//Compress
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include "../Include/Compress/CxTest_CxGz.h"
#endif

//Crypt
#include "../Include/Crypt/CxTest_CxBase64.h"
#include "../Include/Crypt/CxTest_CxCrc32.h"
#include "../Include/Crypt/CxTest_CxBlowfish.h"
#include "../Include/Crypt/CxTest_CxRandom.h"

//Db
#include "../Include/Db/CxTest_CxConnectionString.h"
#include "../Include/Db/CxTest_CxMySql.h"

//Debug
#include "../Include/Debug/CxTest_CxLastError.h"
#include "../Include/Debug/CxTest_CxReport.h"
#include "../Include/Debug/CxTest_CxDebugger.h"
#include "../Include/Debug/CxTest_CxProfiler.h"
#include "../Include/Debug/CxTest_CxAutoProfiler.h"

//Filesystem
#include "../Include/Filesystem/CxTest_CxPath.h"
#include "../Include/Filesystem/CxTest_CxDir.h"
#include "../Include/Filesystem/CxTest_CxEnvironment.h"
#include "../Include/Filesystem/CxTest_CxStdioFile.h"
#include "../Include/Filesystem/CxTest_CxDll.h"
#include "../Include/Filesystem/CxTest_CxFileAttribute.h"
#include "../Include/Filesystem/CxTest_CxIni.h"
#include "../Include/Filesystem/CxTest_CxVolume.h"

#if defined(xOS_WIN)
    #include "../Include/Filesystem/Win/CxTest_CxFile.h"
    #include "../Include/Filesystem/Win/CxTest_CxIni.h"
#elif defined(xOS_LINUX)

#endif

//Log
#include "../Include/Log/CxTest_CxFileLog.h"

//Net
#include "../Include/Net/CxTest_CxCookiePv0.h"
#include "../Include/Net/CxTest_CxCookiePv1.h"
#include "../Include/Net/CxTest_CxCgi.h"
#include "../Include/Net/CxTest_CxSocketInit.h"
#include "../Include/Net/CxTest_CxSocket.h"
#include "../Include/Net/CxTest_CxDnsClient.h"
#include "../Include/Net/CxTest_CxTcpClientSocket.h"
#include "../Include/Net/CxTest_CxTcpServerSocket.h"
////#include "../Include/Net/CxTest_CxHttpClient.h"
////#include "../Include/Net/CxTest_CxGeoIp.h"

//Patterns
#include "../Include/Patterns/CxTest_CxSingleton.h"

//PKCS11
#if defined(xOS_WIN)
    #include "../Include/PKCS11/CxTest_CxPkcs11.h"
#elif defined(xOS_LINUX)

#endif

//Sync
#include "../Include/Sync/CxTest_CxProcess.h"
#include "../Include/Sync/CxTest_CxThread.h"

#if defined(xOS_WIN)
        #include "../Include/Sync/CxTest_CxEvent.h"
    #include "../Include/Sync/CxTest_CxMutex.h"
    #include "../Include/Sync/CxTest_CxAutoMutex.h"
    #include "../Include/Sync/CxTest_CxSleeper.h"
#elif defined(xOS_LINUX)

#endif

//Gui
#if defined(xOS_WIN)
    #include "../Include/Gui/GDI+/CxTest_CxGdiplus.h"
    #include "../Include/Gui/GDI+/CxTest_CxImage.h"
#endif

//Units
#include "../Include/Sync/CxTest_CxProcess.h"

#if defined(xOS_WIN)
    //TODO: test Units
#elif defined(xOS_LINUX)

#endif

//static libs
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    //-lssl -lGeoIP -lmysqlclient
#endif
//---------------------------------------------------------------------------
INT
_tmain(
    INT    argc,
    TCHAR *argv[]
)
{
    ////tcout << "Content-type: text/html\n\n" << tendl;

    extern int        __argc;   //count of cmd line args
    extern char    ** __argv;   //pointer to table of cmd line args


    {
        xTRACEV("argv[0]: %s", argv[0]);

        char szRealPath[PATH_MAX + 1] = {0};

        char *pszRes = realpath(argv[0], szRealPath);
        xASSERT(NULL != pszRes);

        xTRACEV("Real path: %s\n", szRealPath);

        //return 0;
    }

    {
        xTRACEV("CxPath::sGetExe(): %s\n", CxPath::sGetExe().c_str());
    }

    #if xTEMP_DISABLED
        //fprintf(stdout, "Content-type: text/html\n");
        //tcout << xT("##################") << tendl;
        fprintf(stdout, "Location: %s\n\n", "http://www.yandex.ru/");

        return EXIT_SUCCESS;
    #endif

    xTRACEV(xT("\n\n*** xLib v.%s (author: %s date: %s) ***"), xLIB_VERSION, xLIB_AUTHOR, xLIB_DATE);
    xTRACE(xT("Start all tests...\n"));

    //--------------------------------------------------
    //settings
    const ULONGLONG cullTimesForAll    = 1;
    const ULONGLONG cullTimesForSingle = 1;

    BOOL bRes = FALSE;

    std::vector<CxTest *> vptTests;
xTRACE_POINT;

        //--------------------------------------------------
        //Common
        vptTests.push_back( new CxTest_CxMacros );
    #if xTEMP_DISABLED
        vptTests.push_back( new CxTest_CxArray );
        vptTests.push_back( new CxTest_CxChar );
        vptTests.push_back( new CxTest_CxLocale );
        vptTests.push_back( new CxTest_CxString );
        vptTests.push_back( new CxTest_CxDateTime );
        vptTests.push_back( new CxTest_CxFunctorT );
        vptTests.push_back( new CxTest_CxSystemInfo );
        vptTests.push_back( new CxTest_CxException );

        #if defined(xOS_WIN)
        vptTests.push_back( new CxTest_CxClipboard );
        vptTests.push_back( new CxTest_CxCom );
        vptTests.push_back( new CxTest_CxHandleT );
        vptTests.push_back( new CxTest_CxShell );
        vptTests.push_back( new CxTest_CxComPort );
        ////vptTests.push_back( new CxTest_CxConsole );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Compress
        #if defined(xOS_WIN)

        #elif defined(xOS_LINUX)
        vptTests.push_back( new CxTest_CxGz );
        #endif

        //--------------------------------------------------
        //Crypt
        #if xTODO
            vptTests.push_back( new CxTest_CxCrc32 );
            vptTests.push_back( new CxTest_CxBlowfish );
        #endif

        vptTests.push_back( new CxTest_CxRandom );


        //--------------------------------------------------
        //Db
        vptTests.push_back( new CxTest_CxConnectionString );
        ////vptTests.push_back( new CxTest_CxMySql );

        //--------------------------------------------------
        //Debug
        vptTests.push_back( new CxTest_CxLastError );
        ////vptTests.push_back( new CxTest_CxDebugger );
        vptTests.push_back( new CxTest_CxReport );
        vptTests.push_back( new CxTest_CxProfiler );
        vptTests.push_back( new CxTest_CxAutoProfiler );

        //--------------------------------------------------
        //Filesystem
        vptTests.push_back( new CxTest_CxPath );
        vptTests.push_back( new CxTest_CxStdioFile );
        vptTests.push_back( new CxTest_CxDir );
        vptTests.push_back( new CxTest_CxEnvironment );
        vptTests.push_back( new CxTest_CxDll );
        vptTests.push_back( new CxTest_CxFileAttribute );
        vptTests.push_back( new CxTest_CxIni );
        vptTests.push_back( new CxTest_CxVolume );

        #if defined(xOS_WIN)
        vptTests.push_back( new CxTest_CxFile );
        ////vptTests.push_back( new CxTest_CxIni );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Log
        vptTests.push_back( new CxTest_CxFileLog );

        //--------------------------------------------------
        //Net
        vptTests.push_back( new CxTest_CxCookiePv0 );
        vptTests.push_back( new CxTest_CxCookiePv1 );
        #if xTEMP_DISABLED
            vptTests.push_back( new CxTest_CxCgi );
        #endif
        vptTests.push_back( new CxTest_CxSocketInit );
        vptTests.push_back( new CxTest_CxDnsClient );
        ////vptTests.push_back( new CxTest_CxTcpClientSocket );
        ////vptTests.push_back( new CxTest_CxTcpServerSocket );
        ////vptTests.push_back( new CxTest_CxHttpClient );
        ////vptTests.push_back( new CxTest_CxGeoIp );

        //--------------------------------------------------
        //Patterns
        vptTests.push_back( new CxTest_CxSingleton );

        //--------------------------------------------------
        //PKCS11
        #if defined(xOS_WIN)
        ////vptTests.push_back( new CxTest_CxPkcs11 );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Sync
        vptTests.push_back( new CxTest_CxProcess );
        vptTests.push_back( new CxTest_CxThread );

        #if defined(xOS_WIN)
        vptTests.push_back( new CxTest_CxEvent );
        vptTests.push_back( new CxTest_CxMutex );
        vptTests.push_back( new CxTest_CxAutoMutex );
        vptTests.push_back( new CxTest_CxSleeper );
        #elif defined(xOS_LINUX)

        #endif

        //--------------------------------------------------
        //Gui
        #if defined(xOS_WIN)
        vptTests.push_back( new CxTest_CxGdiplus );
        ////vptTests.push_back( new CxTest_CxImage );
        #endif

        //--------------------------------------------------
        //Units
        #if defined(xOS_WIN)
            //TODO: test Units
        #elif defined(xOS_LINUX)

        #endif
    #endif
xTRACE_POINT;
    //--------------------------------------------------
    //run all tests
    for (ULONGLONG i = 0; i < cullTimesForAll; ++ i) {
        for (std::vector<CxTest *>::iterator it = vptTests.begin(); it != vptTests.end(); ++ it) {
            bRes = (*it)->bRun(cullTimesForSingle);
            xASSERT_MSG_RET(FALSE != bRes, ( xT("Test (") + (*it)->sGetName() + xT(") not complete") ).c_str(), FALSE);
        }
    }
xTRACE_POINT;
    //--------------------------------------------------
    //free memory
    for (std::vector<CxTest *>::iterator it = vptTests.begin(); it != vptTests.end(); ++ it) {
        /*CxMacros::*/xPTR_DELETE(*it);
    }

    xTRACE(xT("All tests successful done.\n\n"));

    return 0;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
