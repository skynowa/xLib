/**
 * \file  main. cpp
 * \brief tests for xLib
 */


#include <Test/main.h>

//-------------------------------------------------------------------------------------------------
int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[])
{
    xUNUSED(a_argsNum);
    xUNUSED(a_args);

    // checks
    {
    #if xENV_UNIX
        SystemInfo info;
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

        ProcessInfo info;
        info.setProcessId(Process::currentId());
        info.commandLine(&args);

        if (a_argsNum == 1) {
            // OK, run tests with default params
        }
        else if (a_argsNum == 2) {
            // usage
            bool_t bRv = StringCI::compare(xT("-h"),     args.at(1)) ||
                         StringCI::compare(xT("--help"), args.at(1));
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
            isUseTracing = String::cast<bool_t>     ( args.at(1) );
            allLoops     = String::cast<ulonglong_t>( args.at(2) );
            unitLoops    = String::cast<ulonglong_t>( args.at(3) );
            caseLoops    = String::cast<ulonglong_t>( args.at(4) );
        }
        else {
            // fail
            std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            return EXIT_FAILURE;
        }
    }

    // add and run tests
    {
        Manager manager(isUseTracing);

        // Test
        manager.add(new Test_xTest);

        // Core
        manager.add(new Test_Units);
        manager.add(new Test_Defines);
        manager.add(new Test_Limits);
        manager.add(new Test_Operators);
        manager.add(new Test_Utils);
        manager.add(new Test_StdStream);
        manager.add(new Test_HandleT);
        manager.add(new Test_Type);
        manager.add(new Test_Flags);
        manager.add(new Test_Array);
        manager.add(new Test_AutoReset);
        manager.add(new Test_Char);
        manager.add(new Test_Locale);
        manager.add(new Test_Format);
        manager.add(new Test_String);
        manager.add(new Test_DateTime);
        manager.add(new Test_Com);
        // manager.add(new Test_Application);
        manager.add(new Test_CoreApplication);

        // Crypt
        manager.add(new Test_Base64);
    #if xHAVE_OPENSSL_CRYPTO
        manager.add(new Test_Blowfish);
    #endif
        manager.add(new Test_Crc32);
        manager.add(new Test_Guid);
        manager.add(new Test_Random);

        // Db
    #if xHAVE_MYSQL
        manager.add(new Test_MySql);
    #endif

        // Debug
        manager.add(new Test_Debug);
        manager.add(new Test_SourceInfo);
        manager.add(new Test_BuildInfo);
        manager.add(new Test_StdError);
        manager.add(new Test_NativeError);
        manager.add(new Test_Exception);
        manager.add(new Test_StackTrace);
        manager.add(new Test_Debugger);
        manager.add(new Test_ErrorReport);
        manager.add(new Test_Profiler);
        manager.add(new Test_AutoProfiler);

        // File system
        manager.add(new Test_Path);
        manager.add(new Test_FileType);
        manager.add(new Test_File);
        manager.add(new Test_FileTemp);
        manager.add(new Test_Dll);
        manager.add(new Test_Finder);
        manager.add(new Test_Dir);
        manager.add(new Test_Volume);
        manager.add(new Test_Config);
        manager.add(new Test_Backup);

        // Log
        manager.add(new Test_Trace);
        manager.add(new Test_FileLog);
        manager.add(new Test_SystemLog);

        // Net
        manager.add(new Test_CookiePv0);
        manager.add(new Test_CookiePv1);
        manager.add(new Test_Cgi);
        manager.add(new Test_SocketInit);
        manager.add(new Test_DnsClient);
        // manager.add(new Test_TcpClient);
        // manager.add(new Test_TcpServer);
        manager.add(new Test_HttpClient);

        // Patterns
        manager.add(new Test_Observer);
        manager.add(new Test_Raii);
        manager.add(new Test_Singleton);

        // Sync
        manager.add(new Test_AtomicLongInt);
        manager.add(new Test_ThreadStorage);
        manager.add(new Test_Mutex);
        manager.add(new Test_AutoMutex);
        manager.add(new Test_IpcMutex);
        manager.add(new Test_AutoIpcMutex);
        // manager.add(new Test_Event);
        manager.add(new Test_Condition);
        manager.add(new Test_Semaphore);
        manager.add(new Test_IpcSemaphore);
        // manager.add(new Test_Sleeper);
        // manager.add(new Test_Thread);
        // manager.add(new Test_ThreadPool);
        manager.add(new Test_Process);
        manager.add(new Test_Signal);
        manager.add(new Test_Service);

        // Gui
        manager.add(new Test_MsgBox);

        // System
        manager.add(new Test_Environment);
        manager.add(new Test_SystemInfo);
        manager.add(new Test_ProcessInfo);
        manager.add(new Test_Console);
        manager.add(new Test_Shell);

        // Package
        manager.add(new Test_Csv);

        manager.run(allLoops, unitLoops, caseLoops);
    }

    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
