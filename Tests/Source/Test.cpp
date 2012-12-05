/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#ifndef xLib_UnitTestH
#define xLib_UnitTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxConsole.h>
#include <xLib/Common/CxCommandLine.h>
#include <xLib/Test/CxTestManager.h>

// Common
#include <Test/Common/CxTest_CxNonCopyable.h>
#include <Test/Common/CxTest_CxNonAssignable.h>
#include <Test/Common/CxTest_CxNonHeap.h>
#include <Test/Common/CxTest_CxNonArrayHeap.h>
#include <Test/Common/CxTest_CxUtils.h>
#include <Test/Common/CxTest_CxHandleT.h>
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
#include <Test/Common/Win/CxTest_CxCom.h>

// Crypt
#include <Test/Crypt/CxTest_CxBase64.h>
#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxBlowfish.h>
#include <Test/Crypt/CxTest_CxRandom.h>
#include <Test/Crypt/Pkcs11/CxTest_CxPkcs11.h>

// Db
#include <Test/Db/CxTest_CxConnectionString.h>
#include <Test/Db/CxTest_CxMySql.h>

// Debug
#include <Test/Debug/CxTest_xDebug.h>
#include <Test/Debug/CxTest_CxStdError.h>
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxException.h>
#include <Test/Debug/CxTest_CxStackTrace.h>
#include <Test/Debug/CxTest_CxErrorReport.h>
#include <Test/Debug/CxTest_CxDebugger.h>
#include <Test/Debug/CxTest_CxProfiler.h>
#include <Test/Debug/CxTest_CxAutoProfiler.h>

// Filesystem
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

// Log
#include <Test/Log/CxTest_CxTracer.h>
#include <Test/Log/CxTest_CxFileLog.h>
#include <Test/Log/CxTest_CxSystemLog.h>

// Net
#include <Test/Net/CxTest_CxCookiePv0.h>
#include <Test/Net/CxTest_CxCookiePv1.h>
#include <Test/Net/CxTest_CxCgi.h>
#include <Test/Net/CxTest_CxSocketInit.h>
#include <Test/Net/CxTest_CxSocket.h>
#include <Test/Net/CxTest_CxDnsClient.h>
#include <Test/Net/CxTest_CxTcpClient.h>
#include <Test/Net/CxTest_CxTcpServer.h>
#include <Test/Net/CxTest_CxHttpClient.h>

// Patterns
#include <Test/Patterns/CxTest_CxSingleton.h>

// Sync
#if xOS_ENV_UNIX
#include <Test/Sync/Unix/CxTest_CxCondition.h>
#endif

#include <Test/Sync/CxTest_CxAtomicLongInt.h>
#include <Test/Sync/CxTest_CxThreadStorage.h>
#include <Test/Sync/CxTest_CxMutex.h>
#include <Test/Sync/CxTest_CxAutoMutex.h>
#include <Test/Sync/CxTest_CxIpcMutex.h>
#include <Test/Sync/CxTest_CxAutoIpcMutex.h>
#include <Test/Sync/CxTest_CxEvent.h>
#include <Test/Sync/CxTest_CxSleeper.h>
#include <Test/Sync/CxTest_CxSemaphore.h>
#include <Test/Sync/CxTest_CxIpcSemaphore.h>
#include <Test/Sync/CxTest_CxCurrentThread.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxThreadPool.h>
#include <Test/Sync/CxTest_CxCurrentProcess.h>
#include <Test/Sync/CxTest_CxProcess.h>

// Gui
#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>
//---------------------------------------------------------------------------
int
xTMAIN(int iArgCount, tchar_t *paszArgs[]) {
    //--------------------------------------------------
    // set commandline args for xLib
    CxCommandLine::vSetArgs(iArgCount, paszArgs);

    //--------------------------------------------------
    // options (default)
    bool        bIsUseTracing = true;
    ulonglong_t ullAllLoops   = 1UL;
    ulonglong_t ullUnitLoops  = 1UL;
    ulonglong_t ullCaseLoops  = 1UL;

    {
        std::vec_tstring_t vsArgs;

        CxCommandLine::vArgs(&vsArgs);

        // usage
        if (2 == iArgCount) {
            bool bRv = CxString::bCompareNoCase(xT("-h"), vsArgs.at(1));
            if (true == bRv) {
                std::tcout << xT("\nUsage: xlib_r is_tracing all_loops unit_loops\n")
                              xT("  - xlib_r      (binary file path)\n")
                              xT("  - is_tracing  (is tracing)\n")
                              xT("  - all_loops   (loops for all tests)\n")
                              xT("  - unit_loops  (loops for unit test)\n")
                              xT("  - case_loops  (loops for case test)\n") << std::endl;
            } else {
                std::tcout << xT("\nUnknown switches\n") << std::endl;
            }

            return EXIT_SUCCESS;
        }

        // loops number
        if (5 == iArgCount) {
            bIsUseTracing = CxString::cast<bool>       ( vsArgs.at(1) );
            ullAllLoops   = CxString::cast<ulonglong_t>( vsArgs.at(2) );
            ullUnitLoops  = CxString::cast<ulonglong_t>( vsArgs.at(3) );
            ullCaseLoops  = CxString::cast<ulonglong_t>( vsArgs.at(4) );
        }
    }

    //--------------------------------------------------
    // add and run tests
    {
        CxTestManager tmManager(bIsUseTracing);

        // Common
        tmManager.vAdd(new CxTest_CxNonCopyable);
        tmManager.vAdd(new CxTest_CxNonAssignable);
        tmManager.vAdd(new CxTest_CxNonHeap);
        tmManager.vAdd(new CxTest_CxNonArrayHeap);
        tmManager.vAdd(new CxTest_CxUtils);
        tmManager.vAdd(new CxTest_CxHandleT);
        tmManager.vAdd(new CxTest_CxType);
        tmManager.vAdd(new CxTest_CxFunctorT);
        tmManager.vAdd(new CxTest_CxArray);
        tmManager.vAdd(new CxTest_CxChar);
        tmManager.vAdd(new CxTest_CxLocale);
        tmManager.vAdd(new CxTest_CxString);
        tmManager.vAdd(new CxTest_CxDateTime);
        tmManager.vAdd(new CxTest_CxSystemInfo);
        tmManager.vAdd(new CxTest_CxProcessInfo);
        tmManager.vAdd(new CxTest_CxConsole);
        tmManager.vAdd(new CxTest_CxCommandLine);
        tmManager.vAdd(new CxTest_CxShell);
        tmManager.vAdd(new CxTest_CxCom);

        // Crypt
        tmManager.vAdd(new CxTest_CxCrc32);
        tmManager.vAdd(new CxTest_CxRandom);
    #if !xCOMPILER_MINGW32
        tmManager.vAdd(new CxTest_CxBase64);
        tmManager.vAdd(new CxTest_CxBlowfish);
    #endif

        // Db
        tmManager.vAdd(new CxTest_CxConnectionString);
        // tmManager.vAdd(new CxTest_CxMySql);

        // Debug
        tmManager.vAdd(new CxTest_xDebug);
        tmManager.vAdd(new CxTest_CxStdError);
        tmManager.vAdd(new CxTest_CxLastError);
        tmManager.vAdd(new CxTest_CxException);
        tmManager.vAdd(new CxTest_CxStackTrace);
        tmManager.vAdd(new CxTest_CxDebugger);
        tmManager.vAdd(new CxTest_CxErrorReport);
        tmManager.vAdd(new CxTest_CxProfiler);
        tmManager.vAdd(new CxTest_CxAutoProfiler);

        // Filesystem
        tmManager.vAdd(new CxTest_CxPath);
        tmManager.vAdd(new CxTest_CxFileAttribute);
        tmManager.vAdd(new CxTest_CxFile);
        tmManager.vAdd(new CxTest_CxFileTemp);
        tmManager.vAdd(new CxTest_CxDll);
        tmManager.vAdd(new CxTest_CxDir);
        tmManager.vAdd(new CxTest_CxVolume);
        tmManager.vAdd(new CxTest_CxEnvironment);
        tmManager.vAdd(new CxTest_CxLocalStorage);
        tmManager.vAdd(new CxTest_CxBackuper);

        // Log
        tmManager.vAdd(new CxTest_CxTracer);
        tmManager.vAdd(new CxTest_CxFileLog);
        tmManager.vAdd(new CxTest_CxSystemLog);

        // Net
        tmManager.vAdd(new CxTest_CxCookiePv0);
        tmManager.vAdd(new CxTest_CxCookiePv1);
        tmManager.vAdd(new CxTest_CxCgi);
        tmManager.vAdd(new CxTest_CxSocketInit);
        tmManager.vAdd(new CxTest_CxDnsClient);
        // tmManager.vAdd(new CxTest_CxTcpClient);
        // tmManager.vAdd(new CxTest_CxTcpServer);
        // tmManager.vAdd(new CxTest_CxHttpClient);

        // Patterns
        tmManager.vAdd(new CxTest_CxSingleton);

        // Pkcs11
        // tmManager.vAdd(new CxTest_CxPkcs11);

        // Sync
	#if xOS_ENV_UNIX
        tmManager.vAdd(new CxTest_CxCondition);
	#endif

        tmManager.vAdd(new CxTest_CxAtomicLongInt);
        tmManager.vAdd(new CxTest_CxThreadStorage);
        tmManager.vAdd(new CxTest_CxMutex);
        tmManager.vAdd(new CxTest_CxAutoMutex);
        tmManager.vAdd(new CxTest_CxIpcMutex);
        tmManager.vAdd(new CxTest_CxAutoIpcMutex);
        tmManager.vAdd(new CxTest_CxEvent);
        tmManager.vAdd(new CxTest_CxSemaphore);
        tmManager.vAdd(new CxTest_CxIpcSemaphore);
        tmManager.vAdd(new CxTest_CxSleeper);
        tmManager.vAdd(new CxTest_CxCurrentThread);
        tmManager.vAdd(new CxTest_CxThread);
        // tmManager.vAdd(new CxTest_CxThreadPool);
        tmManager.vAdd(new CxTest_CxCurrentProcess);
        tmManager.vAdd(new CxTest_CxProcess);

        // Gui
        tmManager.vAdd(new CxTest_CxMsgBoxT);

        tmManager.vRun(ullAllLoops, ullUnitLoops, ullCaseLoops);
    }

    return EXIT_SUCCESS;
}
//---------------------------------------------------------------------------
#endif //xLib_UnitTestH
