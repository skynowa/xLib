/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#include <xLib/Core/xCore.h>
#include <xLib/System/CxConsole.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/Test/CxTestManager.h>

// Core
#include <Test/Core/CxTest_CxNonCopyable.h>
#include <Test/Core/CxTest_CxNonAssignable.h>
#include <Test/Core/CxTest_CxNonHeap.h>
#include <Test/Core/CxTest_CxNonArrayHeap.h>
#include <Test/Core/CxTest_CxUtils.h>
#include <Test/Core/CxTest_CxHandleT.h>
#include <Test/Core/CxTest_CxType.h>
#include <Test/Core/CxTest_CxFlags.h>
#include <Test/Core/CxTest_CxFunctorT.h>
#include <Test/Core/CxTest_CxArray.h>
#include <Test/Core/CxTest_CxChar.h>
#include <Test/Core/CxTest_CxLocale.h>
#include <Test/Core/CxTest_CxString.h>
#include <Test/Core/CxTest_CxDateTime.h>
#include <Test/Core/Win/CxTest_CxCom.h>

// Crypt
#include <Test/Crypt/CxTest_CxBase64.h>

#if xARCH_X86

// #include <Test/Crypt/CxTest_CxBlowfish.h>

#endif

#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxRandom.h>
#include <Test/Crypt/Pkcs11/CxTest_CxPkcs11.h>

// Db
//#include <Test/Db/CxTest_CxMySql.h>

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
#include <Test/Filesystem/CxTest_CxFileType.h>
#include <Test/Filesystem/CxTest_CxFile.h>
#include <Test/Filesystem/CxTest_CxFileTemp.h>
#include <Test/Filesystem/CxTest_CxDll.h>
#include <Test/Filesystem/CxTest_CxFinder.h>
#include <Test/Filesystem/CxTest_CxDir.h>
#include <Test/Filesystem/CxTest_CxVolume.h>
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
#include <Test/Sync/CxTest_CxAtomicLongInt.h>
#include <Test/Sync/CxTest_CxThreadStorage.h>
#include <Test/Sync/CxTest_CxMutex.h>
#include <Test/Sync/CxTest_CxAutoMutex.h>
#include <Test/Sync/CxTest_CxIpcMutex.h>
#include <Test/Sync/CxTest_CxAutoIpcMutex.h>
#include <Test/Sync/CxTest_CxEvent.h>
#include <Test/Sync/CxTest_CxCondition.h>
#include <Test/Sync/CxTest_CxSleeper.h>
#include <Test/Sync/CxTest_CxSemaphore.h>
#include <Test/Sync/CxTest_CxIpcSemaphore.h>
#include <Test/Sync/CxTest_CxCurrentThread.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxThreadPool.h>
#include <Test/Sync/CxTest_CxProcess.h>

// Gui
#include <Test/Gui/Dialogs/CxTest_CxMsgBoxT.h>

// System
#include <Test/System/CxTest_CxEnvironment.h>
#include <Test/System/CxTest_CxSystemInfo.h>
#include <Test/System/CxTest_CxProcessInfo.h>
#include <Test/System/CxTest_CxConsole.h>
#include <Test/System/CxTest_CxShell.h>
//------------------------------------------------------------------------------
int_t xTMAIN(int_t argNum, tchar_t *args[])
{
    //--------------------------------------------------
    // options (default)
    bool_t        bIsUseTracing = true;
    ulonglong_t ullAllLoops   = 1UL;
    ulonglong_t ullUnitLoops  = 1UL;
    ulonglong_t ullCaseLoops  = 1UL;

    {
        std::vec_tstring_t args;

        CxProcessInfo info;
        info.setProcessId(CxProcess::currentId());
        info.commandLine(&args);

        // usage
        if (2 == argNum) {
            bool_t bRv = CxString::compareNoCase(xT("-h"), args.at(1));
            if (bRv) {
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
        if (5 == argNum) {
            bIsUseTracing = CxString::cast<bool_t>     ( args.at(1) );
            ullAllLoops   = CxString::cast<ulonglong_t>( args.at(2) );
            ullUnitLoops  = CxString::cast<ulonglong_t>( args.at(3) );
            ullCaseLoops  = CxString::cast<ulonglong_t>( args.at(4) );
        }
    }

    //--------------------------------------------------
    // add and run tests
    {
        CxTestManager tmManager(bIsUseTracing);

        // Core
        tmManager.add(new CxTest_CxNonCopyable);
        tmManager.add(new CxTest_CxNonAssignable);
        tmManager.add(new CxTest_CxNonHeap);
        tmManager.add(new CxTest_CxNonArrayHeap);
        tmManager.add(new CxTest_CxUtils);
        tmManager.add(new CxTest_CxHandleT);
        tmManager.add(new CxTest_CxType);
        tmManager.add(new CxTest_CxFlags);
        tmManager.add(new CxTest_CxFunctorT);
        tmManager.add(new CxTest_CxArray);
        tmManager.add(new CxTest_CxChar);
        tmManager.add(new CxTest_CxLocale);
        tmManager.add(new CxTest_CxString);
        tmManager.add(new CxTest_CxDateTime);
        tmManager.add(new CxTest_CxCom);

        // Crypt
        tmManager.add(new CxTest_CxCrc32);
        tmManager.add(new CxTest_CxRandom);
        tmManager.add(new CxTest_CxBase64);

    #if xARCH_X86 && !xCOMPILER_MINGW
        // tmManager.add(new CxTest_CxBlowfish);
    #endif

        // Db
        // tmManager.add(new CxTest_CxMySql);

        // Debug
        tmManager.add(new CxTest_xDebug);
        tmManager.add(new CxTest_CxStdError);
        tmManager.add(new CxTest_CxLastError);
        tmManager.add(new CxTest_CxException);
        tmManager.add(new CxTest_CxStackTrace);
        tmManager.add(new CxTest_CxDebugger);
        tmManager.add(new CxTest_CxErrorReport);
        tmManager.add(new CxTest_CxProfiler);
        tmManager.add(new CxTest_CxAutoProfiler);

        // File system
        tmManager.add(new CxTest_CxPath);
        tmManager.add(new CxTest_CxFileType);
        tmManager.add(new CxTest_CxFile);
        tmManager.add(new CxTest_CxFileTemp);
        tmManager.add(new CxTest_CxDll);
        tmManager.add(new CxTest_CxFinder);
        tmManager.add(new CxTest_CxDir);
        tmManager.add(new CxTest_CxVolume);
        tmManager.add(new CxTest_CxLocalStorage);
        tmManager.add(new CxTest_CxBackuper);

        // Log
        tmManager.add(new CxTest_CxTracer);
        tmManager.add(new CxTest_CxFileLog);
        tmManager.add(new CxTest_CxSystemLog);

        // Net
        tmManager.add(new CxTest_CxCookiePv0);
        tmManager.add(new CxTest_CxCookiePv1);
        tmManager.add(new CxTest_CxCgi);
        tmManager.add(new CxTest_CxSocketInit);
        tmManager.add(new CxTest_CxDnsClient);
        // tmManager.add(new CxTest_CxTcpClient);
        // tmManager.add(new CxTest_CxTcpServer);
        tmManager.add(new CxTest_CxHttpClient);

        // Patterns
        tmManager.add(new CxTest_CxSingleton);

        // Pkcs11
        // tmManager.add(new CxTest_CxPkcs11);

        // Sync
        tmManager.add(new CxTest_CxAtomicLongInt);
        tmManager.add(new CxTest_CxThreadStorage);
        tmManager.add(new CxTest_CxMutex);
        tmManager.add(new CxTest_CxAutoMutex);
        tmManager.add(new CxTest_CxIpcMutex);
        tmManager.add(new CxTest_CxAutoIpcMutex);
        tmManager.add(new CxTest_CxEvent);
        tmManager.add(new CxTest_CxCondition);
        tmManager.add(new CxTest_CxSemaphore);
        tmManager.add(new CxTest_CxIpcSemaphore);
        tmManager.add(new CxTest_CxSleeper);
        tmManager.add(new CxTest_CxCurrentThread);
        tmManager.add(new CxTest_CxThread);
        // tmManager.add(new CxTest_CxThreadPool);
        tmManager.add(new CxTest_CxProcess);

        // Gui
        tmManager.add(new CxTest_CxMsgBoxT);

        // System
        tmManager.add(new CxTest_CxEnvironment);
        tmManager.add(new CxTest_CxSystemInfo);
        tmManager.add(new CxTest_CxProcessInfo);
        tmManager.add(new CxTest_CxConsole);
        tmManager.add(new CxTest_CxShell);

        tmManager.run(ullAllLoops, ullUnitLoops, ullCaseLoops);
    }

    return EXIT_SUCCESS;
}
//------------------------------------------------------------------------------
