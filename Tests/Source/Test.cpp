/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#include <xLib/Core/xCore.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/Test/CxTestManager.h>

// Core
#include <Test/Core/CxTest_CxUtils.h>
#include <Test/Core/CxTest_xStdStream.h>
#include <Test/Core/CxTest_CxHandleT.h>
#include <Test/Core/CxTest_CxType.h>
#include <Test/Core/CxTest_CxFlags.h>
#include <Test/Core/CxTest_CxFunctorT.h>
#include <Test/Core/CxTest_CxArray.h>
#include <Test/Core/CxTest_CxAutoReset.h>
#include <Test/Core/CxTest_CxChar.h>
#include <Test/Core/CxTest_CxLocale.h>
#include <Test/Core/CxTest_CxString.h>
#include <Test/Core/CxTest_CxDateTime.h>
#include <Test/Core/Win/CxTest_CxCom.h>

// Crypt
#include <Test/Crypt/CxTest_CxBase64.h>

#if xHAVE_OPENSSL_CRYPTO

#include <Test/Crypt/CxTest_CxBlowfish.h>

#endif

#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxRandom.h>

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
int_t xTMAIN(int_t a_argNum, tchar_t *a_args[])
{
    xUNUSED(a_args);

    //--------------------------------------------------
    // checks
    {
    #if xOS_ENV_UNIX
        CxSystemInfo info;
        xCHECK_MSG_RET(info.isUserAdmin(), xT("xLib_test: Can't run as root"), EXIT_FAILURE);
    #endif
    }

    //--------------------------------------------------
    // options (default)
    bool_t      isUseTracing = true;
    ulonglong_t allLoops     = 1ULL;
    ulonglong_t unitLoops    = 1ULL;
    ulonglong_t caseLoops    = 1ULL;

    {
        std::vec_tstring_t args;

        CxProcessInfo info;
        info.setProcessId(CxProcess::currentId());
        info.commandLine(&args);

        // usage
        if (2 == a_argNum) {
            bool_t bRv = CxString::compareNoCase(xT("-h"), args.at(1));
            if (!bRv) {
                std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            } else {
                std::tcout << xT("\nUsage: ./xLib_test is_tracing all_loops unit_loops\n")
                              xT("  - xLib_test  (binary file path)\n")
                              xT("  - is_tracing (is tracing)\n")
                              xT("  - all_loops  (loops for all tests)\n")
                              xT("  - unit_loops (loops for unit test)\n")
                              xT("  - case_loops (loops for case test)\n") << std::endl;
            }

            return EXIT_SUCCESS;
        }

        // loops number
        if (5 == a_argNum) {
            isUseTracing = CxString::cast<bool_t>     ( args.at(1) );
            allLoops     = CxString::cast<ulonglong_t>( args.at(2) );
            unitLoops    = CxString::cast<ulonglong_t>( args.at(3) );
            caseLoops    = CxString::cast<ulonglong_t>( args.at(4) );
        }
    }

    //--------------------------------------------------
    // add and run tests
    {
        CxTestManager manager(isUseTracing);

        // Core
        manager.add(new CxTest_CxUtils);
        manager.add(new CxTest_xStdStream);
        manager.add(new CxTest_CxHandleT);
        manager.add(new CxTest_CxType);
        manager.add(new CxTest_CxFlags);
        manager.add(new CxTest_CxFunctorT);
        manager.add(new CxTest_CxArray);
        manager.add(new CxTest_CxAutoReset);
        manager.add(new CxTest_CxChar);
        manager.add(new CxTest_CxLocale);
        manager.add(new CxTest_CxString);
        manager.add(new CxTest_CxDateTime);
        manager.add(new CxTest_CxCom);

        // Crypt
        manager.add(new CxTest_CxCrc32);
        manager.add(new CxTest_CxRandom);
        manager.add(new CxTest_CxBase64);

    #if xHAVE_OPENSSL_CRYPTO
        manager.add(new CxTest_CxBlowfish);
    #endif

        // Db
        // manager.add(new CxTest_CxMySql);

        // Debug
        manager.add(new CxTest_xDebug);
        manager.add(new CxTest_CxStdError);
        manager.add(new CxTest_CxLastError);
        manager.add(new CxTest_CxException);
        manager.add(new CxTest_CxStackTrace);
        manager.add(new CxTest_CxDebugger);
        manager.add(new CxTest_CxErrorReport);
        manager.add(new CxTest_CxProfiler);
        manager.add(new CxTest_CxAutoProfiler);

        // File system
        manager.add(new CxTest_CxPath);
        manager.add(new CxTest_CxFileType);
        manager.add(new CxTest_CxFile);
        manager.add(new CxTest_CxFileTemp);
        manager.add(new CxTest_CxDll);
        manager.add(new CxTest_CxFinder);
        manager.add(new CxTest_CxDir);
        manager.add(new CxTest_CxVolume);
        manager.add(new CxTest_CxLocalStorage);
        manager.add(new CxTest_CxBackuper);

        // Log
        manager.add(new CxTest_CxTracer);
        manager.add(new CxTest_CxFileLog);
        manager.add(new CxTest_CxSystemLog);

        // Net
        manager.add(new CxTest_CxCookiePv0);
        manager.add(new CxTest_CxCookiePv1);
        manager.add(new CxTest_CxCgi);
        manager.add(new CxTest_CxSocketInit);
        manager.add(new CxTest_CxDnsClient);
        // manager.add(new CxTest_CxTcpClient);
        // manager.add(new CxTest_CxTcpServer);
        manager.add(new CxTest_CxHttpClient);

        // Patterns
        manager.add(new CxTest_CxSingleton);

        // Sync
        manager.add(new CxTest_CxAtomicLongInt);
        manager.add(new CxTest_CxThreadStorage);
        manager.add(new CxTest_CxMutex);
        manager.add(new CxTest_CxAutoMutex);
        manager.add(new CxTest_CxIpcMutex);
        manager.add(new CxTest_CxAutoIpcMutex);
        manager.add(new CxTest_CxEvent);
        manager.add(new CxTest_CxCondition);
        manager.add(new CxTest_CxSemaphore);
        manager.add(new CxTest_CxIpcSemaphore);
        manager.add(new CxTest_CxSleeper);
        manager.add(new CxTest_CxThread);
        // manager.add(new CxTest_CxThreadPool);
        manager.add(new CxTest_CxProcess);

        // Gui
        manager.add(new CxTest_CxMsgBoxT);

        // System
        manager.add(new CxTest_CxEnvironment);
        manager.add(new CxTest_CxSystemInfo);
        manager.add(new CxTest_CxProcessInfo);
        manager.add(new CxTest_CxConsole);
        manager.add(new CxTest_CxShell);

        manager.run(allLoops, unitLoops, caseLoops);
    }

    return EXIT_SUCCESS;
}
//------------------------------------------------------------------------------
