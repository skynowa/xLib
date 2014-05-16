/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#include <xLib/xLib.h>
#include <Test/CxTest_xLib.h>

//-------------------------------------------------------------------------------------------------
void
onTerminate()
{
    CxTrace() << xFUNCTION;
    CxTrace() << "Stack trace:\n" << CxStackTrace().toString();

    // abort();  // forces abnormal termination
}
void
onSignal(int sig)
{
    CxTrace() << xFUNCTION;
    CxTrace() << "Stack trace:\n " << CxStackTrace().toString();

    switch (sig) {
    case SIGABRT:
        CxTrace() << "Caught SIGABRT: usually caused by an abort() or assert()";
        break;
    case SIGFPE:
        CxTrace() << "Caught SIGFPE: arithmetic exception, such as divide by zero";
        break;
    case SIGILL:
        CxTrace() << "Caught SIGILL: illegal instruction";
        break;
    case SIGINT:
        CxTrace() << "Caught SIGINT: interactive attention signal, probably a ctrl+c";
        break;
    case SIGSEGV:
        CxTrace() << "Caught SIGSEGV: segfault";
        break;
    case SIGTERM:
    default:
        CxTrace() << "Caught SIGTERM: a termination request was sent to the program";
        break;
    }

    _Exit(1);
}
void
setSignalHandler()
{
    std::signal(SIGABRT, onSignal);
    std::signal(SIGFPE,  onSignal);
    std::signal(SIGILL,  onSignal);
    std::signal(SIGINT,  onSignal);
    std::signal(SIGSEGV, onSignal);
    std::signal(SIGTERM, onSignal);
}
//-------------------------------------------------------------------------------------------------
void
fail()
{
#if 0
    int *p = xPTR_NULL;
    *p=10;
#else
    throw 0;  // unhandled exception: calls terminate handler
#endif
}
void
foo1()
{
    fail();
}
void
foo2()
{
    foo1();
}
void
foo3()
{
    foo2();
}
//-------------------------------------------------------------------------------------------------
int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[])
{
    xUNUSED(a_argsNum);
    xUNUSED(a_args);

#if 0
    // FAQ: https://gist.github.com/jvranish/4441299
    // set handlers
    {
        std::set_terminate(onTerminate);
        setSignalHandler();
    }

    // test error
    foo3();
#endif

#if xHAVE_TESTS
    // checks
    {
    #if xENV_UNIX
        CxSystemInfo info;
        xCHECK_MSG_RET(info.isUserAdmin(), xT("xLib_test: Can't run as root"), EXIT_FAILURE);
    #endif
    }

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

        if (a_argsNum == 1) {
            // OK, run tests with default params
        }
        else if (a_argsNum == 2) {
            // usage
            bool_t bRv = CxStringCI::compare(xT("-h"),     args.at(1)) ||
                         CxStringCI::compare(xT("--help"), args.at(1));
            if (!bRv) {
                std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            } else {
                std::tcout << xT("\nUsage: ./xLib_test [is_tracing] [all_loops] [unit_loops]\n")
                              xT("  - xLib_test  (binary file path)\n")
                              xT("  - is_tracing (is tracing)\n")
                              xT("  - all_loops  (loops for all tests)\n")
                              xT("  - unit_loops (loops for unit test)\n")
                              xT("  - case_loops (loops for case test)\n") << std::endl;
            }

            return EXIT_SUCCESS;
        }
        else if (a_argsNum == 5) {
            // addition params
            isUseTracing = CxString::cast<bool_t>     ( args.at(1) );
            allLoops     = CxString::cast<ulonglong_t>( args.at(2) );
            unitLoops    = CxString::cast<ulonglong_t>( args.at(3) );
            caseLoops    = CxString::cast<ulonglong_t>( args.at(4) );
        }
        else {
            // fail
            std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            return EXIT_FAILURE;
        }
    }

    // add and run tests
    {
        CxTestManager manager(isUseTracing);

        // Test
        manager.add(new CxTest_xTest);

        // Core
        manager.add(new CxTest_xUnits);
        manager.add(new CxTest_xDefines);
        manager.add(new CxTest_xLimits);
        manager.add(new CxTest_CxUtils);
        manager.add(new CxTest_xStdStream);
        manager.add(new CxTest_CxHandleT);
        manager.add(new CxTest_CxType);
        manager.add(new CxTest_CxFlags);
        manager.add(new CxTest_CxArray);
        manager.add(new CxTest_CxAutoReset);
        manager.add(new CxTest_CxChar);
        manager.add(new CxTest_CxLocale);
        manager.add(new CxTest_CxString);
        manager.add(new CxTest_CxDateTime);
        manager.add(new CxTest_CxCom);

        // Crypt
        manager.add(new CxTest_CxBase64);
    #if xHAVE_OPENSSL_CRYPTO
        manager.add(new CxTest_CxBlowfish);
    #endif
        manager.add(new CxTest_CxCrc32);
        manager.add(new CxTest_CxGuid);
        manager.add(new CxTest_CxRandom);

        // Db
    #if xHAVE_MYSQL
        manager.add(new CxTest_CxMySql);
    #endif

        // Debug
        manager.add(new CxTest_xDebug);
        manager.add(new CxTest_CxBuildInfo);
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
        manager.add(new CxTest_CxConfig);
        manager.add(new CxTest_CxBackup);

        // Log
        manager.add(new CxTest_CxTrace);
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
        manager.add(new CxTest_CxObserver);
        manager.add(new CxTest_CxRaii);
        manager.add(new CxTest_CxSingleton);

        // Sync
        manager.add(new CxTest_CxAtomicLongInt);
        manager.add(new CxTest_CxThreadStorage);
        manager.add(new CxTest_CxMutex);
        manager.add(new CxTest_CxAutoMutex);
        manager.add(new CxTest_CxIpcMutex);
        manager.add(new CxTest_CxAutoIpcMutex);
        // manager.add(new CxTest_CxEvent);
        manager.add(new CxTest_CxCondition);
        manager.add(new CxTest_CxSemaphore);
        manager.add(new CxTest_CxIpcSemaphore);
        // manager.add(new CxTest_CxSleeper);
        // manager.add(new CxTest_CxThread);
        // manager.add(new CxTest_CxThreadPool);
        manager.add(new CxTest_CxProcess);

        // Gui
        manager.add(new CxTest_CxMsgBox);

        // System
        manager.add(new CxTest_CxEnvironment);
        manager.add(new CxTest_CxSystemInfo);
        manager.add(new CxTest_CxProcessInfo);
        manager.add(new CxTest_CxConsole);
        manager.add(new CxTest_CxShell);

        manager.run(allLoops, unitLoops, caseLoops);
    }
#endif

    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
