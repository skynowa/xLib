/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#ifndef xLib_UnitTestH
#define xLib_UnitTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTestManager.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Common/CxCommandLine.h>

//Common
#include <Test/Common/CxTest_CxMacros.h>
#include <Test/Common/CxTest_CxException.h>
#include <Test/Common/CxTest_CxType.h>
#include <Test/Common/CxTest_CxFunctorT.h>
#include <Test/Common/CxTest_CxArray.h>
#include <Test/Common/CxTest_CxChar.h>
#include <Test/Common/CxTest_CxLocale.h>
#include <Test/Common/CxTest_CxAutoMallocT.h>
#include <Test/Common/CxTest_CxString.h>
#include <Test/Common/CxTest_CxDateTime.h>
#include <Test/Common/CxTest_CxSystemInfo.h>
#include <Test/Common/CxTest_CxConsole.h>
#include <Test/Common/CxTest_CxCommandLine.h>

#if defined(xOS_ENV_WIN)
    #include <Test/Common/Win/CxTest_CxHandleT.h>
    #include <Test/Common/Win/CxTest_CxCom.h>
    #include <Test/Common/Win/CxTest_CxClipboard.h>
    #include <Test/Common/Win/CxTest_CxShell.h>
    #include <Test/Common/Win/CxTest_CxComPort.h>
#endif

//Crypt
#include <Test/Crypt/CxTest_CxBase64.h>
#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxBlowfish.h>
#include <Test/Crypt/CxTest_CxRandom.h>
#include <Test/Crypt/Pkcs11/Win/CxTest_CxPkcs11.h>

//Db
#include <Test/Db/CxTest_CxConnectionString.h>
#include <Test/Db/CxTest_CxMySql.h>

//Debug
#include <Test/Debug/CxTest_CxStdError.h>
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxStackTrace.h>
#include <Test/Debug/CxTest_CxReport.h>
#include <Test/Debug/CxTest_CxDebugger.h>
#include <Test/Debug/CxTest_CxProfiler.h>
#include <Test/Debug/CxTest_CxAutoProfiler.h>

//Filesystem
#include <Test/Filesystem/CxTest_CxPath.h>
#include <Test/Filesystem/CxTest_CxFileAttribute.h>
#include <Test/Filesystem/CxTest_CxFile.h>
#include <Test/Filesystem/CxTest_CxFileTemp.h>
#include <Test/Filesystem/CxTest_CxDll.h>
#include <Test/Filesystem/CxTest_CxDir.h>
#include <Test/Filesystem/CxTest_CxVolume.h>
#include <Test/Filesystem/CxTest_CxEnvironment.h>
#include <Test/Filesystem/CxTest_CxLocalStorage.h>

#if defined(xOS_ENV_WIN)
    #include <Test/Filesystem/Win/CxTest_CxIni.h>
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
#include <Test/Net/CxTest_CxTcpClient.h>
#include <Test/Net/CxTest_CxTcpServer.h>
#include <Test/Net/CxTest_CxHttpClient.h>
#include <Test/Net/CxTest_CxGeoIp.h>

//Patterns
#include <Test/Patterns/CxTest_CxSingleton.h>

//Sync
#include <Test/Sync/CxTest_CxThreadStorage.h>
#include <Test/Sync/CxTest_CxCriticalSection.h>
#include <Test/Sync/CxTest_CxAutoCriticalSection.h>
#include <Test/Sync/CxTest_CxEvent.h>
#include <Test/Sync/CxTest_CxSleeper.h>
#include <Test/Sync/CxTest_CxCurrentThread.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxProcess.h>

#if defined(xOS_ENV_WIN)
    #include <Test/Sync/CxTest_CxMutex.h>
    #include <Test/Sync/CxTest_CxAutoMutex.h>
#endif

//Gui
#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>

#if defined(xOS_ENV_WIN)
    #include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>
    #include <Test/Gui/Win/Gdi+/CxTest_CxImage.h>
#endif

//Units
//TODO: test Units
#include <Test/Units/CxTest_Draft.h>
//---------------------------------------------------------------------------
INT
xTMAIN(
    INT    iArgCount,
    char_t *paszArgs[]
)
{
    //--------------------------------------------------
    //set commandline args for xLib
    {
        BOOL bRes = CxCommandLine::bSetArgs(iArgCount, paszArgs);
        xTEST_DIFF(FALSE, bRes);
    }


    #if xTEMP_DISABLED
        std::tcout << "Content-type: text/html\n\n" << std::endl;
        std::tcout << "<pre>\n\n"                   << std::endl;
    #endif

    //--------------------------------------------------
    //options (default)
    BOOL      bIsUseTracing = TRUE;
    ULONGLONG ullAllLoops   = 1UL;
    ULONGLONG ullUnitLoops  = 1UL;
    ULONGLONG ullBlockLoops = 1UL;

    {
        std::vector<std::string_t> vsArgs;

        BOOL bRes = CxCommandLine::bGetArgs(&vsArgs);
        xTEST_DIFF(FALSE, bRes);

        //usage
        if (2 == iArgCount) {
            bRes = CxString::bCompareNoCase(xT("-h"), vsArgs.at(1));
            if (TRUE == bRes) {
                std::tcout << "\nUsage: xlib_r is_tracing all_loops unit_loops\n"
                              "  - xlib_r      (binary file path)\n"
                              "  - is_tracing  (is tracing)\n"
                              "  - all_loops   (loops for all tests)\n"
                              "  - unit_loops  (loops for unit test)\n"
                              "  - block_loops (loops for unit test)\n" << std::endl;
            } else {
                std::tcout << "\nUnknown switches\n" << std::endl;
            }

            return TRUE;
        }

        //loops number
        if (5 == iArgCount) {
            bIsUseTracing = static_cast<BOOL>( CxString::lexical_cast<INT>( vsArgs.at(1) ) );
            ullAllLoops   = CxString::lexical_cast<ULONGLONG>( vsArgs.at(2) );
            ullUnitLoops  = CxString::lexical_cast<ULONGLONG>( vsArgs.at(3) );
            ullBlockLoops = CxString::lexical_cast<ULONGLONG>( vsArgs.at(4) );
        }
    }

    //--------------------------------------------------
    //add and run tests
    {
        CxTestManager tmManager(bIsUseTracing);

        //Common
        (VOID)tmManager.bAdd(new CxTest_CxMacros);
        (VOID)tmManager.bAdd(new CxTest_CxException);
        (VOID)tmManager.bAdd(new CxTest_CxType);
        (VOID)tmManager.bAdd(new CxTest_CxFunctorT);
        (VOID)tmManager.bAdd(new CxTest_CxArray);
        (VOID)tmManager.bAdd(new CxTest_CxChar);
        (VOID)tmManager.bAdd(new CxTest_CxLocale);
        (VOID)tmManager.bAdd(new CxTest_CxAutoMallocT);
        (VOID)tmManager.bAdd(new CxTest_CxString);
        (VOID)tmManager.bAdd(new CxTest_CxDateTime);
        (VOID)tmManager.bAdd(new CxTest_CxSystemInfo);
        (VOID)tmManager.bAdd(new CxTest_CxConsole);
        (VOID)tmManager.bAdd(new CxTest_CxCommandLine);

    #if defined(xOS_ENV_WIN)
        (VOID)tmManager.bAdd(new CxTest_CxHandleT);
        (VOID)tmManager.bAdd(new CxTest_CxCom);
        (VOID)tmManager.bAdd(new CxTest_CxClipboard);
        (VOID)tmManager.bAdd(new CxTest_CxShell);
        (VOID)tmManager.bAdd(new CxTest_CxComPort);
    #elif defined(xOS_ENV_UNIX)

    #endif

        //Crypt
        (VOID)tmManager.bAdd(new CxTest_CxCrc32);
        (VOID)tmManager.bAdd(new CxTest_CxBase64);
        (VOID)tmManager.bAdd(new CxTest_CxCrc32);
        (VOID)tmManager.bAdd(new CxTest_CxBlowfish);
        (VOID)tmManager.bAdd(new CxTest_CxRandom);

        //Db
        (VOID)tmManager.bAdd(new CxTest_CxConnectionString);
        //(VOID)tmManager.bAdd(new CxTest_CxMySql);

        //Debug
        (VOID)tmManager.bAdd(new CxTest_CxStdError);
        (VOID)tmManager.bAdd(new CxTest_CxLastError);
        (VOID)tmManager.bAdd(new CxTest_CxStackTrace);
        (VOID)tmManager.bAdd(new CxTest_CxDebugger);
        (VOID)tmManager.bAdd(new CxTest_CxReport);
        (VOID)tmManager.bAdd(new CxTest_CxProfiler);
        (VOID)tmManager.bAdd(new CxTest_CxAutoProfiler);

        //Filesystem
        (VOID)tmManager.bAdd(new CxTest_CxPath);
        (VOID)tmManager.bAdd(new CxTest_CxFileAttribute);
        (VOID)tmManager.bAdd(new CxTest_CxFile);
        (VOID)tmManager.bAdd(new CxTest_CxFileTemp);
        (VOID)tmManager.bAdd(new CxTest_CxDll);
        (VOID)tmManager.bAdd(new CxTest_CxDir);
        (VOID)tmManager.bAdd(new CxTest_CxVolume);
        (VOID)tmManager.bAdd(new CxTest_CxEnvironment);
        (VOID)tmManager.bAdd(new CxTest_CxLocalStorage);

    #if defined(xOS_ENV_WIN)
        (VOID)tmManager.bAdd(new CxTest_CxIni);
    #elif defined(xOS_ENV_UNIX)

    #endif

        //Log
        (VOID)tmManager.bAdd(new CxTest_CxFileLog);

        //Net
        (VOID)tmManager.bAdd(new CxTest_CxCookiePv0);
        (VOID)tmManager.bAdd(new CxTest_CxCookiePv1);
        (VOID)tmManager.bAdd(new CxTest_CxCgi);
        (VOID)tmManager.bAdd(new CxTest_CxSocketInit);
        (VOID)tmManager.bAdd(new CxTest_CxDnsClient);
        //(VOID)tmManager.bAdd(new CxTest_CxTcpClient);
        //(VOID)tmManager.bAdd(new CxTest_CxTcpServer);
        (VOID)tmManager.bAdd(new CxTest_CxHttpClient);
        //(VOID)tmManager.bAdd(new CxTest_CxGeoIp);

        //Patterns
        (VOID)tmManager.bAdd(new CxTest_CxSingleton);

        //Pkcs11
    #if defined(xOS_ENV_WIN)
        ////(VOID)tmManager.bAdd(new CxTest_CxPkcs11);
    #elif defined(xOS_ENV_UNIX)

    #endif

        //Sync
        (VOID)tmManager.bAdd(new CxTest_CxThreadStorage);
        (VOID)tmManager.bAdd(new CxTest_CxCriticalSection);
        (VOID)tmManager.bAdd(new CxTest_CxAutoCriticalSection);
        (VOID)tmManager.bAdd(new CxTest_CxEvent);
        (VOID)tmManager.bAdd(new CxTest_CxSleeper);
        (VOID)tmManager.bAdd(new CxTest_CxCurrentThread);
        (VOID)tmManager.bAdd(new CxTest_CxThread);
        (VOID)tmManager.bAdd(new CxTest_CxProcess);

    #if defined(xOS_ENV_WIN)
        (VOID)tmManager.bAdd(new CxTest_CxMutex);
        (VOID)tmManager.bAdd(new CxTest_CxAutoMutex);
    #elif defined(xOS_ENV_UNIX)

    #endif

        //Gui
        (VOID)tmManager.bAdd(new CxTest_CxMsgBoxT);

    #if defined(xOS_ENV_WIN)
        (VOID)tmManager.bAdd(new CxTest_CxGdiplus);
        (VOID)tmManager.bAdd(new CxTest_CxImage);
    #endif

        //Units
        (VOID)tmManager.bAdd(new CxTest_Draft);


        (VOID)tmManager.bRun(ullAllLoops, ullUnitLoops, ullBlockLoops);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
