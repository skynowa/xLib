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
#include <xLib/Debug/CxTestManager.h>

//Common
#include <Test/Common/CxTest_CxMacros.h>
#include <Test/Common/CxTest_CxArray.h>
#include <Test/Common/CxTest_CxChar.h>
#include <Test/Common/CxTest_CxLocale.h>
#include <Test/Common/CxTest_CxString.h>
#include <Test/Common/CxTest_CxDateTime.h>
#include <Test/Common/CxTest_CxFunctorT.h>
#include <Test/Common/CxTest_CxSystemInfo.h>
#include <Test/Common/CxTest_CxAutoMallocT.h>
#include <Test/Common/CxTest_CxException.h>
#if defined(xOS_WIN)
    #include <Test/Common/CxTest_CxClipboard.h>
    #include <Test/Common/CxTest_CxCom.h>
    #include <Test/Common/CxTest_CxHandleT.h>
    #include <Test/Common/CxTest_CxShell.h>
    #include <Test/Common/CxTest_CxComPort.h>
    #include <Test/Common/CxTest_CxConsole.h>
#elif defined(xOS_LINUX)

#endif

//Compress
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include <Test/Compress/CxTest_CxGz.h>
#endif

//Crypt
#include <Test/Crypt/CxTest_CxBase64.h>
#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxBlowfish.h>
#include <Test/Crypt/CxTest_CxRandom.h>

//Db
#include <Test/Db/CxTest_CxConnectionString.h>
#include <Test/Db/CxTest_CxMySql.h>

//Debug
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxReport.h>
#include <Test/Debug/CxTest_CxDebugger.h>
#include <Test/Debug/CxTest_CxProfiler.h>
#include <Test/Debug/CxTest_CxAutoProfiler.h>

//Filesystem
#include <Test/Filesystem/CxTest_CxPath.h>
#include <Test/Filesystem/CxTest_CxDir.h>
#include <Test/Filesystem/CxTest_CxEnvironment.h>
#include <Test/Filesystem/CxTest_CxStdioFile.h>
#include <Test/Filesystem/CxTest_CxDll.h>
#include <Test/Filesystem/CxTest_CxFileAttribute.h>
#include <Test/Filesystem/CxTest_CxIni.h>
#include <Test/Filesystem/CxTest_CxVolume.h>

#if defined(xOS_WIN)
    #include <Test/Filesystem/Win/CxTest_CxFile.h>
    ////#include <Test/Filesystem/Win/CxTest_CxIni.h>
#elif defined(xOS_LINUX)

#endif

//Log
#include <Test/Log/CxTest_CxFileLog.h>

//Net
#include <Test/Net/CxTest_CxCookiePv0.h>
#include <Test/Net/CxTest_CxCookiePv1.h>
#include <Test/Net/CxTest_CxCgi.h>
#include <Test/Net/CxTest_CxSocketInit.h>
#include <Test/Net/CxTest_CxSocket.h>
#include <Test/Net/CxTest_CxDnsClient.h>
#include <Test/Net/CxTest_CxTcpClientSocket.h>
#include <Test/Net/CxTest_CxTcpServerSocket.h>
////#include <Test/Net/CxTest_CxHttpClient.h>
////#include <Test/Net/CxTest_CxGeoIp.h>

//Patterns
#include <Test/Patterns/CxTest_CxSingleton.h>

//PKCS11
#if defined(xOS_WIN)
    #include <Test/PKCS11/CxTest_CxPkcs11.h>
#elif defined(xOS_LINUX)

#endif

//Sync
#include <Test/Sync/CxTest_CxProcess.h>
#include <Test/Sync/CxTest_CxThread.h>

#if defined(xOS_WIN)
    #include <Test/Sync/CxTest_CxEvent.h>
    #include <Test/Sync/CxTest_CxMutex.h>
    #include <Test/Sync/CxTest_CxAutoMutex.h>
    #include <Test/Sync/CxTest_CxSleeper.h>
#elif defined(xOS_LINUX)

#endif

//Gui
#if defined(xOS_WIN)
    #include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>
    #include <Test/Gui/Win/Gdi+/CxTest_CxImage.h>
#endif

//Units
#include <Test/Sync/CxTest_CxProcess.h>

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
    {
        BOOL bRes = CxEnvironment::bSetCommandLineArgs(argc, argv);
        xASSERT(FALSE != bRes);
    }

    #if xTEMP_DISABLED
        tcout << "Content-type: text/html\n\n" << tendl;
        tcout << "<pre>\n\n" << tendl;
    #endif

    //--------------------------------------------------
    //settings
    const ULONGLONG cullTimesForAll    = 1;
    const ULONGLONG cullTimesForSingle = 1;


    BOOL bRes = FALSE;

    CxTestManager tmManager(TRUE);

    //--------------------------------------------------
    //Common
    bRes = tmManager.bAdd(new CxTest_CxMacros);
    bRes = tmManager.bAdd(new CxTest_CxArray);
    bRes = tmManager.bAdd(new CxTest_CxChar);
    bRes = tmManager.bAdd(new CxTest_CxLocale);
    bRes = tmManager.bAdd(new CxTest_CxString);
    bRes = tmManager.bAdd(new CxTest_CxDateTime);
    bRes = tmManager.bAdd(new CxTest_CxFunctorT);
    ////bRes = tmManager.bAdd(new CxTest_CxSystemInfo);
    bRes = tmManager.bAdd(new CxTest_CxException);

    #if defined(xOS_WIN)
    bRes = tmManager.bAdd(new CxTest_CxClipboard);
    bRes = tmManager.bAdd(new CxTest_CxCom);
    bRes = tmManager.bAdd(new CxTest_CxHandleT);
    bRes = tmManager.bAdd(new CxTest_CxShell);
    bRes = tmManager.bAdd(new CxTest_CxComPort);
    ////bRes = tmManager.bAdd(new CxTest_CxConsole);
    #elif defined(xOS_LINUX)

    #endif

    //--------------------------------------------------
    //Compress
    #if defined(xOS_WIN)

    #elif defined(xOS_LINUX)
    bRes = tmManager.bAdd(new CxTest_CxGz);
    #endif

    //--------------------------------------------------
    //Crypt
    ////bRes = tmManager.bAdd(new CxTest_CxCrc32);
    ////bRes = tmManager.bAdd(new CxTest_CxBlowfish);

    bRes = tmManager.bAdd(new CxTest_CxRandom);

    //--------------------------------------------------
    //Db
    bRes = tmManager.bAdd(new CxTest_CxConnectionString);
    ////bRes = tmManager.bAdd(new CxTest_CxMySql);

    //--------------------------------------------------
    //Debug
    bRes = tmManager.bAdd(new CxTest_CxLastError);
    ////bRes = tmManager.bAdd(new CxTest_CxDebugger);
    bRes = tmManager.bAdd(new CxTest_CxReport);
    bRes = tmManager.bAdd(new CxTest_CxProfiler);
    bRes = tmManager.bAdd(new CxTest_CxAutoProfiler);

    //--------------------------------------------------
    //Filesystem
    bRes = tmManager.bAdd(new CxTest_CxPath);
    bRes = tmManager.bAdd(new CxTest_CxStdioFile);
    bRes = tmManager.bAdd(new CxTest_CxDir);
    bRes = tmManager.bAdd(new CxTest_CxEnvironment);
    ////bRes = tmManager.bAdd(new CxTest_CxDll);
    bRes = tmManager.bAdd(new CxTest_CxFileAttribute);
    bRes = tmManager.bAdd(new CxTest_CxIni);
    bRes = tmManager.bAdd(new CxTest_CxVolume);
#if 1
    #if defined(xOS_WIN)
    bRes = tmManager.bAdd(new CxTest_CxFile);
    ////bRes = tmManager.bAdd(new CxTest_CxIni);
    #elif defined(xOS_LINUX)

    #endif

    //--------------------------------------------------
    //Log
    bRes = tmManager.bAdd(new CxTest_CxFileLog);

    //--------------------------------------------------
    //Net
    bRes = tmManager.bAdd(new CxTest_CxCookiePv0);
    bRes = tmManager.bAdd(new CxTest_CxCookiePv1);
    ////bRes = tmManager.bAdd(new CxTest_CxCgi);
    bRes = tmManager.bAdd(new CxTest_CxSocketInit);
    bRes = tmManager.bAdd(new CxTest_CxDnsClient);
    ////bRes = tmManager.bAdd(new CxTest_CxTcpClientSocket);
    ////bRes = tmManager.bAdd(new CxTest_CxTcpServerSocket);
    ////bRes = tmManager.bAdd(new CxTest_CxHttpClient);
    ////bRes = tmManager.bAdd(new CxTest_CxGeoIp);

    //--------------------------------------------------
    //Patterns
    bRes = tmManager.bAdd(new CxTest_CxSingleton);

    //--------------------------------------------------
    //PKCS11
    #if defined(xOS_WIN)
    ////bRes = tmManager.bAdd(new CxTest_CxPkcs11);
    #elif defined(xOS_LINUX)

    #endif

    //--------------------------------------------------
    //Sync
    bRes = tmManager.bAdd(new CxTest_CxProcess);
    bRes = tmManager.bAdd(new CxTest_CxThread);

    #if defined(xOS_WIN)
    bRes = tmManager.bAdd(new CxTest_CxEvent);
    bRes = tmManager.bAdd(new CxTest_CxMutex);
    bRes = tmManager.bAdd(new CxTest_CxAutoMutex);
    bRes = tmManager.bAdd(new CxTest_CxSleeper);
    #elif defined(xOS_LINUX)

    #endif

    //--------------------------------------------------
    //Gui
    #if defined(xOS_WIN)
    bRes = tmManager.bAdd(new CxTest_CxGdiplus);
    bRes = tmManager.bAdd(new CxTest_CxImage);
    #endif

    //--------------------------------------------------
    //Units
    #if defined(xOS_WIN)
        //TODO: test Units
    #elif defined(xOS_LINUX)

    #endif
#endif

    bRes = tmManager.bRun(cullTimesForAll, cullTimesForSingle);

    return 0;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
