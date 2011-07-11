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
#include "../Tests/Common/CxTest_CxMacros.h"
#include "../Tests/Common/CxTest_CxArray.h"
#include "../Tests/Common/CxTest_CxChar.h"
#include "../Tests/Common/CxTest_CxLocale.h"
#include "../Tests/Common/CxTest_CxString.h"
#include "../Tests/Common/CxTest_CxDateTime.h"
#include "../Tests/Common/CxTest_CxFunctorT.h"
#include "../Tests/Common/CxTest_CxSystemInfo.h"
#include "../Tests/Common/CxTest_CxAutoMallocT.h"
#include "../Tests/Common/CxTest_CxException.h"
#if defined(xOS_WIN)
    #include "../Tests/Common/CxTest_CxClipboard.h"
    #include "../Tests/Common/CxTest_CxCom.h"
    #include "../Tests/Common/CxTest_CxHandleT.h"
    #include "../Tests/Common/CxTest_CxShell.h"
    #include "../Tests/Common/CxTest_CxComPort.h"
    #include "../Tests/Common/CxTest_CxConsole.h"
#elif defined(xOS_LINUX)

#endif

//Compress
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include "../Tests/Compress/CxTest_CxGz.h"
#endif

//Crypt
#include "../Tests/Crypt/CxTest_CxBase64.h"
#include "../Tests/Crypt/CxTest_CxCrc32.h"
#include "../Tests/Crypt/CxTest_CxBlowfish.h"
#include "../Tests/Crypt/CxTest_CxRandom.h"

//Db
#include "../Tests/Db/CxTest_CxConnectionString.h"
#include "../Tests/Db/CxTest_CxMySql.h"

//Debug
#include "../Tests/Debug/CxTest_CxLastError.h"
#include "../Tests/Debug/CxTest_CxReport.h"
#include "../Tests/Debug/CxTest_CxDebugger.h"
#include "../Tests/Debug/CxTest_CxProfiler.h"
#include "../Tests/Debug/CxTest_CxAutoProfiler.h"

//Filesystem
#include "../Tests/Filesystem/CxTest_CxPath.h"
#include "../Tests/Filesystem/CxTest_CxDir.h"
#include "../Tests/Filesystem/CxTest_CxEnvironment.h"
#include "../Tests/Filesystem/CxTest_CxStdioFile.h"
#include "../Tests/Filesystem/CxTest_CxDll.h"
#include "../Tests/Filesystem/CxTest_CxFileAttribute.h"
#include "../Tests/Filesystem/CxTest_CxIni.h"
#include "../Tests/Filesystem/CxTest_CxVolume.h"

#if defined(xOS_WIN)
    #include "../Tests/Filesystem/Win/CxTest_CxFile.h"
    #include "../Tests/Filesystem/Win/CxTest_CxIni.h"
#elif defined(xOS_LINUX)

#endif

//Log
#include "../Tests/Log/CxTest_CxFileLog.h"

//Net
#include "../Tests/Net/CxTest_CxCookiePv0.h"
#include "../Tests/Net/CxTest_CxCookiePv1.h"
#include "../Tests/Net/CxTest_CxCgi.h"
#include "../Tests/Net/CxTest_CxSocketInit.h"
#include "../Tests/Net/CxTest_CxSocket.h"
#include "../Tests/Net/CxTest_CxDnsClient.h"
#include "../Tests/Net/CxTest_CxTcpClientSocket.h"
#include "../Tests/Net/CxTest_CxTcpServerSocket.h"
////#include "../Tests/Net/CxTest_CxHttpClient.h"
////#include "../Tests/Net/CxTest_CxGeoIp.h"

//Patterns
#include "../Tests/Patterns/CxTest_CxSingleton.h"

//PKCS11
#if defined(xOS_WIN)
    #include "../Tests/PKCS11/CxTest_CxPkcs11.h"
#elif defined(xOS_LINUX)

#endif

//Sync
#include "../Tests/Sync/CxTest_CxProcess.h"
#include "../Tests/Sync/CxTest_CxThread.h"

#if defined(xOS_WIN)
	#include "../Tests/Sync/CxTest_CxEvent.h"
    #include "../Tests/Sync/CxTest_CxMutex.h"
    #include "../Tests/Sync/CxTest_CxAutoMutex.h"
    #include "../Tests/Sync/CxTest_CxSleeper.h"
#elif defined(xOS_LINUX)

#endif

//Gui
#if defined(xOS_WIN)
    #include "../Tests/Gui/GDI+/CxTest_CxGdiplus.h"
    #include "../Tests/Gui/GDI+/CxTest_CxImage.h"
#endif

//Units
#include "../Tests/Sync/CxTest_CxProcess.h"

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

    //--------------------------------------------------
    //run all tests
    for (ULONGLONG i = 0; i < cullTimesForAll; ++ i) {
        for (std::vector<CxTest *>::iterator it = vptTests.begin(); it != vptTests.end(); ++ it) {
            bRes = (*it)->bRun(cullTimesForSingle);
            xASSERT_MSG_RET(FALSE != bRes, ( xT("Test (") + (*it)->sGetName() + xT(") not complete") ).c_str(), FALSE);
        }
    }

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
