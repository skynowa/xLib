/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


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
#include <Test/Common/CxTest_CxType.h>
#include <Test/Common/CxTest_CxConsole.h>

#if defined(xOS_WIN)
    #include <Test/Common/Win/CxTest_CxClipboard.h>
    #include <Test/Common/Win/CxTest_CxCom.h>
    #include <Test/Common/Win/CxTest_CxHandleT.h>
    #include <Test/Common/Win/CxTest_CxShell.h>
    #include <Test/Common/Win/CxTest_CxComPort.h>
#elif defined(xOS_LINUX)

#endif

//Compress
#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include <Test/Compress/Linux/CxTest_CxGz.h>
#endif

//Crypt
#include <Test/Crypt/CxTest_CxBase64.h>
#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxBlowfish.h>
#include <Test/Crypt/CxTest_CxRandom.h>

//Db
#include <Test/Db/CxTest_CxConnectionString.h>
////#include <Test/Db/CxTest_CxMySql.h>

//Debug
#include <Test/Debug/CxTest_CxStdError.h>
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxReport.h>
#include <Test/Debug/CxTest_CxDebugger.h>
#include <Test/Debug/CxTest_CxProfiler.h>
#include <Test/Debug/CxTest_CxAutoProfiler.h>

//Filesystem
#include <Test/Filesystem/CxTest_CxPath.h>
#include <Test/Filesystem/CxTest_CxDir.h>
#include <Test/Filesystem/CxTest_CxEnvironment.h>
#include <Test/Filesystem/CxTest_CxFile.h>
#include <Test/Filesystem/CxTest_CxDll.h>
#include <Test/Filesystem/CxTest_CxFileAttribute.h>
#include <Test/Filesystem/CxTest_CxLocalStorage.h>
#include <Test/Filesystem/CxTest_CxVolume.h>

#if defined(xOS_WIN)
    #include <Test/Filesystem/Win/CxTest_CxIni.h>
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
#include <Test/Net/CxTest_CxHttpClient.h>

#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    ////#include <Test/Net/CxTest_CxGeoIp.h>
#endif

//Patterns
#include <Test/Patterns/CxTest_CxSingleton.h>

//Pkcs11
#if defined(xOS_WIN)
    #include <Test/Pkcs11/Win/CxTest_CxPkcs11.h>
#elif defined(xOS_LINUX)

#endif

//Sync
#include <Test/Sync/CxTest_CxProcess.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxCriticalSection.h>
#include <Test/Sync/CxTest_CxAutoCriticalSection.h>
#include <Test/Sync/CxTest_CxEvent.h>

#if defined(xOS_WIN)
    #include <Test/Sync/CxTest_CxMutex.h>
    #include <Test/Sync/CxTest_CxAutoMutex.h>
    #include <Test/Sync/CxTest_CxSleeper.h>
#elif defined(xOS_LINUX)

#endif

//Gui
#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>

#if defined(xOS_WIN)
    #include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>
    #include <Test/Gui/Win/Gdi+/CxTest_CxImage.h>
#endif

//Units
#if defined(xOS_WIN)
    //TODO: test Units
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
INT
_tmain(
    INT    iArgCount,
    TCHAR *paszArgs[]
)
{
    //--------------------------------------------------
    //set commandline args for xLib
    {
        BOOL bRes = CxEnvironment::bSetCommandLineArgs(iArgCount, paszArgs);
        xASSERT_NOT_EQ(FALSE, bRes);
    }


    BOOL bRes = FALSE;

    #if xTEMP_DISABLED
        std::tcout << "Content-type: text/html\n\n" << std::endl;
        std::tcout << "<pre>\n\n" << std::endl;
    #endif

    //--------------------------------------------------
    //options (default)
    BOOL      bIsUseTracing = TRUE;
    ULONGLONG ullAllLoops   = 1;
    ULONGLONG ullUnitLoops  = 1;
    ULONGLONG ullBlockLoops = 1;

    {
        std::vector<std::tstring> vsArgs;

        bRes = CxEnvironment::bGetCommandLineArgs(&vsArgs);
        xASSERT_NOT_EQ(FALSE, bRes);

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
    //start
    {
        CxTestManager tmManager(bIsUseTracing);

        //Common
        bRes = tmManager.bAdd(new CxTest_CxMacros);
        bRes = tmManager.bAdd(new CxTest_CxArray);
        bRes = tmManager.bAdd(new CxTest_CxChar);
        bRes = tmManager.bAdd(new CxTest_CxLocale);
        bRes = tmManager.bAdd(new CxTest_CxString);
        bRes = tmManager.bAdd(new CxTest_CxDateTime);
        bRes = tmManager.bAdd(new CxTest_CxFunctorT);
        bRes = tmManager.bAdd(new CxTest_CxSystemInfo);
        bRes = tmManager.bAdd(new CxTest_CxAutoMallocT);
        bRes = tmManager.bAdd(new CxTest_CxException);
        bRes = tmManager.bAdd(new CxTest_CxType);
        bRes = tmManager.bAdd(new CxTest_CxConsole);

    #if defined(xOS_WIN)
        ////bRes = tmManager.bAdd(new CxTest_CxClipboard);
        bRes = tmManager.bAdd(new CxTest_CxCom);
        bRes = tmManager.bAdd(new CxTest_CxHandleT);
        bRes = tmManager.bAdd(new CxTest_CxShell);
        bRes = tmManager.bAdd(new CxTest_CxComPort);
    #elif defined(xOS_LINUX)

    #endif

        //Compress
    #if defined(xOS_WIN)

    #elif defined(xOS_LINUX)
        bRes = tmManager.bAdd(new CxTest_CxGz);
    #endif

        //Crypt
        bRes = tmManager.bAdd(new CxTest_CxCrc32);
        bRes = tmManager.bAdd(new CxTest_CxBase64);
        bRes = tmManager.bAdd(new CxTest_CxCrc32);
        bRes = tmManager.bAdd(new CxTest_CxBlowfish);
        bRes = tmManager.bAdd(new CxTest_CxRandom);

        //Db
        bRes = tmManager.bAdd(new CxTest_CxConnectionString);
        ////bRes = tmManager.bAdd(new CxTest_CxMySql);

        //Debug
        bRes = tmManager.bAdd(new CxTest_CxStdError);
        bRes = tmManager.bAdd(new CxTest_CxLastError);
        bRes = tmManager.bAdd(new CxTest_CxDebugger);
        bRes = tmManager.bAdd(new CxTest_CxReport);
        bRes = tmManager.bAdd(new CxTest_CxProfiler);
        bRes = tmManager.bAdd(new CxTest_CxAutoProfiler);

        //Filesystem
        bRes = tmManager.bAdd(new CxTest_CxPath);
        bRes = tmManager.bAdd(new CxTest_CxFile);
        bRes = tmManager.bAdd(new CxTest_CxDir);
        bRes = tmManager.bAdd(new CxTest_CxEnvironment);
        bRes = tmManager.bAdd(new CxTest_CxDll);
        bRes = tmManager.bAdd(new CxTest_CxFileAttribute);
        bRes = tmManager.bAdd(new CxTest_CxLocalStorage);
        bRes = tmManager.bAdd(new CxTest_CxVolume);

    #if defined(xOS_WIN)
        bRes = tmManager.bAdd(new CxTest_CxIni);
    #elif defined(xOS_LINUX)

    #endif

        //Log
        bRes = tmManager.bAdd(new CxTest_CxFileLog);

        //Net
        bRes = tmManager.bAdd(new CxTest_CxCookiePv0);
        bRes = tmManager.bAdd(new CxTest_CxCookiePv1);
        bRes = tmManager.bAdd(new CxTest_CxCgi);
        bRes = tmManager.bAdd(new CxTest_CxSocketInit);
        bRes = tmManager.bAdd(new CxTest_CxDnsClient);
        ////bRes = tmManager.bAdd(new CxTest_CxTcpClientSocket);
        ////bRes = tmManager.bAdd(new CxTest_CxTcpServerSocket);
        bRes = tmManager.bAdd(new CxTest_CxHttpClient);
        ////bRes = tmManager.bAdd(new CxTest_CxGeoIp);

        //Patterns
        bRes = tmManager.bAdd(new CxTest_CxSingleton);

        //Pkcs11
    #if defined(xOS_WIN)
        ////bRes = tmManager.bAdd(new CxTest_CxPkcs11);
    #elif defined(xOS_LINUX)

    #endif

        //Sync
        bRes = tmManager.bAdd(new CxTest_CxProcess);
        bRes = tmManager.bAdd(new CxTest_CxThread);
        bRes = tmManager.bAdd(new CxTest_CxCriticalSection);
        bRes = tmManager.bAdd(new CxTest_CxAutoCriticalSection);
        bRes = tmManager.bAdd(new CxTest_CxEvent);

    #if defined(xOS_WIN)
        bRes = tmManager.bAdd(new CxTest_CxMutex);
        bRes = tmManager.bAdd(new CxTest_CxAutoMutex);
        bRes = tmManager.bAdd(new CxTest_CxSleeper);
    #elif defined(xOS_LINUX)

    #endif

        //Gui
        bRes = tmManager.bAdd(new CxTest_CxMsgBoxT);

    #if defined(xOS_WIN)
        bRes = tmManager.bAdd(new CxTest_CxGdiplus);
        bRes = tmManager.bAdd(new CxTest_CxImage);
    #endif

        //Units
    #if defined(xOS_WIN)
        //TODO: test Units
    #elif defined(xOS_LINUX)

    #endif

        bRes = tmManager.bRun(ullAllLoops, ullUnitLoops, ullBlockLoops);
    }

    return EXIT_SUCCESS;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
