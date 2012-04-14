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
#include <Test/Common/CxTest_CxHandleT.h>
#include <Test/Common/CxTest_CxException.h>
#include <Test/Common/CxTest_CxType.h>
#include <Test/Common/CxTest_CxFunctorT.h>
#include <Test/Common/CxTest_CxArray.h>
#include <Test/Common/CxTest_CxChar.h>
#include <Test/Common/CxTest_CxLocale.h>
#include <Test/Common/CxTest_CxString.h>
#include <Test/Common/CxTest_CxDateTime.h>
#include <Test/Common/CxTest_CxSystemInfo.h>
#include <Test/Common/CxTest_CxProcessInfo.h>
#include <Test/Common/CxTest_CxConsole.h>
#include <Test/Common/CxTest_CxCommandLine.h>
#include <Test/Common/CxTest_CxShell.h>

#if xOS_ENV_WIN
    #include <Test/Common/Win/CxTest_CxCom.h>
#endif

//Crypt
#include <Test/Crypt/CxTest_CxBase64.h>
#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxBlowfish.h>
#include <Test/Crypt/CxTest_CxRandom.h>
#include <Test/Crypt/Pkcs11/CxTest_CxPkcs11.h>

//Db
#include <Test/Db/CxTest_CxConnectionString.h>
#include <Test/Db/CxTest_CxMySql.h>

//Debug
#include <Test/Debug/CxTest_CxStdError.h>
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxStackTrace.h>
#include <Test/Debug/CxTest_CxErrorReport.h>
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
#include <Test/Filesystem/CxTest_CxBackuper.h>

#if xOS_ENV_WIN
    #include <Test/Filesystem/Win/CxTest_CxIni.h>
#endif

//Log
#include <Test/Log/CxTest_CxTracer.h>
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

//Patterns
#include <Test/Patterns/CxTest_CxSingleton.h>

//Sync
#include <Test/Sync/CxTest_CxAtomicLongInt.h>
#include <Test/Sync/CxTest_CxThreadStorage.h>
#include <Test/Sync/CxTest_CxCriticalSection.h>
#include <Test/Sync/CxTest_CxAutoCriticalSection.h>
#include <Test/Sync/CxTest_CxEvent.h>
#include <Test/Sync/CxTest_CxSleeper.h>
#include <Test/Sync/CxTest_CxCurrentThread.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxCurrentProcess.h>
#include <Test/Sync/CxTest_CxProcess.h>

#if xOS_ENV_WIN
    #include <Test/Sync/CxTest_CxMutex.h>
    #include <Test/Sync/CxTest_CxAutoMutex.h>
#endif

//Gui
#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>

#if xOS_ENV_WIN
    #include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>
    #include <Test/Gui/Win/Gdi+/CxTest_CxImage.h>
#endif

//Units
//TODO: test Units
#include <Test/Units/CxTest_Draft.h>
//---------------------------------------------------------------------------
int
xTMAIN(
    int      iArgCount,
    tchar_t *paszArgs[]
)
{
    //--------------------------------------------------
    // set commandline args for xLib
    {
        bool bRes = CxCommandLine::bSetArgs(iArgCount, paszArgs);
        xTEST_EQ(true, bRes);
    }

    #if xTEMP_DISABLED
        std::tcout << "Content-type: text/html\n\n" << std::endl;
        std::tcout << "<pre>\n\n"                   << std::endl;
    #endif

    //--------------------------------------------------
    // options (default)
    bool        bIsUseTracing = true;
    ulonglong_t ullAllLoops   = 1UL;
    ulonglong_t ullUnitLoops  = 1UL;
    ulonglong_t ullBlockLoops = 1UL;

    {
        std::vector<std::tstring_t> vsArgs;

        bool bRes = CxCommandLine::bGetArgs(&vsArgs);
        xTEST_EQ(true, bRes);

        // usage
        if (2 == iArgCount) {
            bRes = CxString::bCompareNoCase(xT("-h"), vsArgs.at(1));
            if (true == bRes) {
                std::tcout << xT("\nUsage: xlib_r is_tracing all_loops unit_loops\n")
                              xT("  - xlib_r      (binary file path)\n")
                              xT("  - is_tracing  (is tracing)\n")
                              xT("  - all_loops   (loops for all tests)\n")
                              xT("  - unit_loops  (loops for unit test)\n")
                              xT("  - case_loops  (loops for unit test)\n") << std::endl;
            } else {
                std::tcout << xT("\nUnknown switches\n") << std::endl;
            }

            return true;
        }

        // loops number
        if (5 == iArgCount) {
            bIsUseTracing = CxString::lexical_cast<bool>       ( vsArgs.at(1) );
            ullAllLoops   = CxString::lexical_cast<ulonglong_t>( vsArgs.at(2) );
            ullUnitLoops  = CxString::lexical_cast<ulonglong_t>( vsArgs.at(3) );
            ullBlockLoops = CxString::lexical_cast<ulonglong_t>( vsArgs.at(4) );
        }
    }

    //--------------------------------------------------
    // add and run tests
    {
        CxTestManager tmManager(bIsUseTracing);

        //Common
        (void)tmManager.bAdd(new CxTest_CxMacros);
        (void)tmManager.bAdd(new CxTest_CxHandleT);
        (void)tmManager.bAdd(new CxTest_CxException);
        (void)tmManager.bAdd(new CxTest_CxType);
        (void)tmManager.bAdd(new CxTest_CxFunctorT);
        (void)tmManager.bAdd(new CxTest_CxArray);
        (void)tmManager.bAdd(new CxTest_CxChar);
        (void)tmManager.bAdd(new CxTest_CxLocale);
        (void)tmManager.bAdd(new CxTest_CxString);
        (void)tmManager.bAdd(new CxTest_CxDateTime);
        (void)tmManager.bAdd(new CxTest_CxSystemInfo);
        (void)tmManager.bAdd(new CxTest_CxProcessInfo);
        (void)tmManager.bAdd(new CxTest_CxConsole);
        (void)tmManager.bAdd(new CxTest_CxCommandLine);
        (void)tmManager.bAdd(new CxTest_CxShell);

    #if xOS_ENV_WIN
        (void)tmManager.bAdd(new CxTest_CxCom);
    #elif xOS_ENV_UNIX

    #endif

        // Crypt
        (void)tmManager.bAdd(new CxTest_CxCrc32);
        (void)tmManager.bAdd(new CxTest_CxRandom);
    #if !xCOMPILER_MINGW32
        (void)tmManager.bAdd(new CxTest_CxBase64);
        (void)tmManager.bAdd(new CxTest_CxBlowfish);
    #endif

        // Db
        (void)tmManager.bAdd(new CxTest_CxConnectionString);
        //(void)tmManager.bAdd(new CxTest_CxMySql);

        // Debug
        (void)tmManager.bAdd(new CxTest_CxStdError);
        (void)tmManager.bAdd(new CxTest_CxLastError);
        (void)tmManager.bAdd(new CxTest_CxStackTrace);
        (void)tmManager.bAdd(new CxTest_CxDebugger);
        (void)tmManager.bAdd(new CxTest_CxErrorReport);
        (void)tmManager.bAdd(new CxTest_CxProfiler);
        (void)tmManager.bAdd(new CxTest_CxAutoProfiler);

        // Filesystem
        (void)tmManager.bAdd(new CxTest_CxPath);
        (void)tmManager.bAdd(new CxTest_CxFileAttribute);
        (void)tmManager.bAdd(new CxTest_CxFile);
        (void)tmManager.bAdd(new CxTest_CxFileTemp);
        (void)tmManager.bAdd(new CxTest_CxDll);
        (void)tmManager.bAdd(new CxTest_CxDir);
        (void)tmManager.bAdd(new CxTest_CxVolume);
        (void)tmManager.bAdd(new CxTest_CxEnvironment);
        (void)tmManager.bAdd(new CxTest_CxLocalStorage);
        (void)tmManager.bAdd(new CxTest_CxBackuper);

    #if xOS_ENV_WIN
        (void)tmManager.bAdd(new CxTest_CxIni);
    #elif xOS_ENV_UNIX

    #endif

        // Log
        (void)tmManager.bAdd(new CxTest_CxTracer);
        (void)tmManager.bAdd(new CxTest_CxFileLog);

        // Net
        (void)tmManager.bAdd(new CxTest_CxCookiePv0);
        (void)tmManager.bAdd(new CxTest_CxCookiePv1);
        (void)tmManager.bAdd(new CxTest_CxCgi);
        (void)tmManager.bAdd(new CxTest_CxSocketInit);
        (void)tmManager.bAdd(new CxTest_CxDnsClient);
        //(void)tmManager.bAdd(new CxTest_CxTcpClient);
        //(void)tmManager.bAdd(new CxTest_CxTcpServer);
        //(void)tmManager.bAdd(new CxTest_CxHttpClient);

        // Patterns
        (void)tmManager.bAdd(new CxTest_CxSingleton);

        // Pkcs11
    #if xOS_ENV_WIN
        ////(void)tmManager.bAdd(new CxTest_CxPkcs11);
    #elif xOS_ENV_UNIX

    #endif

        // Sync
        (void)tmManager.bAdd(new CxTest_CxAtomicLongInt);
        (void)tmManager.bAdd(new CxTest_CxThreadStorage);
        (void)tmManager.bAdd(new CxTest_CxCriticalSection);
        (void)tmManager.bAdd(new CxTest_CxAutoCriticalSection);
        (void)tmManager.bAdd(new CxTest_CxEvent);
        (void)tmManager.bAdd(new CxTest_CxSleeper);
        (void)tmManager.bAdd(new CxTest_CxCurrentThread);
        (void)tmManager.bAdd(new CxTest_CxThread);
        (void)tmManager.bAdd(new CxTest_CxCurrentProcess);
        (void)tmManager.bAdd(new CxTest_CxProcess);

    #if xOS_ENV_WIN
        (void)tmManager.bAdd(new CxTest_CxMutex);
        (void)tmManager.bAdd(new CxTest_CxAutoMutex);
    #elif xOS_ENV_UNIX

    #endif

        // Gui
        (void)tmManager.bAdd(new CxTest_CxMsgBoxT);

    #if xOS_ENV_WIN
        (void)tmManager.bAdd(new CxTest_CxGdiplus);
        (void)tmManager.bAdd(new CxTest_CxImage);
    #endif

        // Units
        (void)tmManager.bAdd(new CxTest_Draft);


        (void)tmManager.bRun(ullAllLoops, ullUnitLoops, ullBlockLoops);
    }

    return true;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
