/**
 * \file  Test.cpp
 * \brief tests for xLib
 */


#include <xLib/xLib.h>
#include <Test/Test_xLib.h>

//-------------------------------------------------------------------------------------------------
xLIB_CORE_APPLICATION_STATIC_DECLARE

class SignalFunctor
{
public:
    static void_t onSignals(int a_signal)
    {
        Trace() << xFUNCTION << "\nStack trace:\n " << StackTrace().toString();

        switch (a_signal) {
        case SIGABRT:
            Trace() << "Caught SIGABRT: usually caused by an abort() or assert()";
            break;
        case SIGFPE:
            Trace() << "Caught SIGFPE: arithmetic exception, such as divide by zero";
            break;
        case SIGILL:
            Trace() << "Caught SIGILL: illegal instruction";
            break;
        case SIGINT:
            Trace() << "Caught SIGINT: interactive attention signal, probably a ctrl+c";
            break;
        case SIGSEGV:
            Trace() << "Caught SIGSEGV: segfault";
            break;
        case SIGTERM:
        default:
            Trace() << "Caught SIGTERM: a termination request was sent to the program";
            break;
        }

        ::_exit(EXIT_FAILURE);
    }

    static void_t onExit()
    {
        Trace() << xFUNCTION << "\nStack trace:\n" << StackTrace().toString();

        // std::abort();  // forces abnormal termination
    }

    static void_t onTerminate()
    {
        Trace() << xFUNCTION << "\nStack trace:\n" << StackTrace().toString();

        // std::abort();  // forces abnormal termination
    }
};
//-------------------------------------------------------------------------------------------------
class TestFail
{
public:
    void_t fail()
    {
    #if 1
        int *p = xPTR_NULL;
        *p = 10;
    #else
        throw 0;  // unhandled exception: calls terminate handler
    #endif
    }

    void_t foo1()
    {
        fail();
    }

    void_t foo2()
    {
        foo1();
    }

    void_t foo3()
    {
        foo2();
    }
};
//-------------------------------------------------------------------------------------------------
int_t xTMAIN(int_t a_argsNum, tchar_t *a_args[])
{
    xUNUSED(a_argsNum);
    xUNUSED(a_args);

    {
    #if 1
        std::vector<int_t> signalNums;
        signalNums.push_back(SIGHUP);      // Hangup (POSIX)
        signalNums.push_back(SIGINT);      // Interrupt (ANSI)
        signalNums.push_back(SIGQUIT);     // Quit (POSIX)
        signalNums.push_back(SIGILL);      // Illegal instruction (ANSI)
        signalNums.push_back(SIGTRAP);     // Trace trap (POSIX)
        signalNums.push_back(SIGABRT);     // Abort (ANSI)
        signalNums.push_back(SIGIOT);      // IOT trap (4.2 BSD)
        signalNums.push_back(SIGBUS);      // BUS error (4.2 BSD)
        signalNums.push_back(SIGFPE);      // Floating-point exception (ANSI)
        signalNums.push_back(SIGKILL);     // Kill); unblockable (POSIX)
        signalNums.push_back(SIGUSR1);     // User-defined signal 1 (POSIX)
        signalNums.push_back(SIGSEGV);     // Segmentation violation (ANSI)
        signalNums.push_back(SIGUSR2);     // User-defined signal 2 (POSIX)
        signalNums.push_back(SIGPIPE);     // Broken pipe (POSIX)
        signalNums.push_back(SIGALRM);     // Alarm clock (POSIX)
        signalNums.push_back(SIGTERM);     // Termination (ANSI)
        signalNums.push_back(SIGSTKFLT);   // Stack fault
        signalNums.push_back(SIGCLD);      // Same as SIGCHLD (System V)
        signalNums.push_back(SIGCHLD);     // Child status has changed (POSIX)
        signalNums.push_back(SIGCONT);     // Continue (POSIX)
        signalNums.push_back(SIGSTOP);     // Stop); unblockable (POSIX)
        signalNums.push_back(SIGTSTP);     // Keyboard stop (POSIX)
        signalNums.push_back(SIGTTIN);     // Background read from tty (POSIX)
        signalNums.push_back(SIGTTOU);     // Background write to tty (POSIX)
        signalNums.push_back(SIGURG);      // Urgent condition on socket (4.2 BSD)
        signalNums.push_back(SIGXCPU);     // CPU limit exceeded (4.2 BSD)
        signalNums.push_back(SIGXFSZ);     // File size limit exceeded (4.2 BSD)
        signalNums.push_back(SIGVTALRM);   // Virtual alarm clock (4.2 BSD)
        signalNums.push_back(SIGPROF);     // Profiling alarm clock (4.2 BSD)
        signalNums.push_back(SIGWINCH);    // Window size change (4.3 BSD); Sun)
        signalNums.push_back(SIGPOLL);     // Pollable event occurred (System V)
        signalNums.push_back(SIGIO);       // I/O now possible (4.2 BSD)
        signalNums.push_back(SIGPWR);      // Power failure restart (System V)
        signalNums.push_back(SIGSYS);      // Bad system call

        Application application(xT("[app_name]_guid"));
        Application::setName(xT("[app_name]"));
    #if 0
        application.setName(xT("[app_name]"));
        application.setDecription(xT("[decription]"));
        application.setUsage(xT("[usage]"));
        application.setHelp(xT("[help]"));
        application.setCopyrightYears(xT("[2008-2014]"));
        application.setVersionMajor(xT("[1]"));
        application.setVersionMinor(xT("[0]"));
        application.setVersionPatch(xT("[0]"));
        application.setVersionType(xT("[alpha]"));
        application.setVersionRevision(xT("[develop/970f53b]"));
        application.setVendorName(xT("[Skynowa Studio]"));
        application.setVendorDomain(xT("[com]"));
        application.setVendorAuthor(xT("[skynowa]"));
        application.setVendorUrl(xT("[http://bitbucket.org/skynowa/xlib]"));
        application.setVendorEmail(xT("[skynowa@gmail.com]"));
        application.setVendorSkype(xT("[skynowa777]"));
    #endif

    #if 0
        Trace()
            << xTRACE_VAR(application.name())            << xT("\n")
            << xTRACE_VAR(application.decription())      << xT("\n")
            << xTRACE_VAR(application.usage())           << xT("\n")
            << xTRACE_VAR(application.help())            << xT("\n")
            << xTRACE_VAR(application.copyrightYears())  << xT("\n")
            << xTRACE_VAR(application.versionMajor())    << xT("\n")
            << xTRACE_VAR(application.versionMinor())    << xT("\n")
            << xTRACE_VAR(application.versionPatch())    << xT("\n")
            << xTRACE_VAR(application.versionType())     << xT("\n")
            << xTRACE_VAR(application.versionRevision()) << xT("\n")
            << xTRACE_VAR(application.vendorName())      << xT("\n")
            << xTRACE_VAR(application.vendorDomain())    << xT("\n")
            << xTRACE_VAR(application.vendorAuthor())    << xT("\n")
            << xTRACE_VAR(application.vendorUrl())       << xT("\n")
            << xTRACE_VAR(application.vendorEmail())     << xT("\n")
            << xTRACE_VAR(application.vendorSkype());
    #endif

        application.setOnSignals(signalNums, SignalFunctor::onSignals);
        application.setOnTerminate(SignalFunctor::onTerminate);
        application.setOnExit(SignalFunctor::onExit);

        // test error
        TestFail testFail;
        testFail.foo3();
    #endif
    }

#if xOPTION_TESTS
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
        TestManager manager(isUseTracing);

        // Test
    #if 1
        manager.add(new Test_Test);
    #endif

        // Core
    #if 1
        manager.add(new Test_Units);
        manager.add(new Test_Defines);
        manager.add(new Test_Limits);
        manager.add(new Test_Utils);
        manager.add(new Test_StdStream);
        manager.add(new Test_HandleT);
        manager.add(new Test_Type);
        manager.add(new Test_Flags);
        manager.add(new Test_Array);
        manager.add(new Test_AutoReset);
        manager.add(new Test_Char);
        manager.add(new Test_Locale);
        manager.add(new Test_String);
        manager.add(new Test_DateTime);
        manager.add(new Test_Com);
        manager.add(new Test_Application);
    #endif

        // Crypt
    #if 1
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
    #endif

        // Debug
    #if 1
        manager.add(new Test_Debug);
        manager.add(new Test_BuildInfo);
        manager.add(new Test_StdError);
        manager.add(new Test_LastError);
        manager.add(new Test_Exception);
        manager.add(new Test_StackTrace);
        manager.add(new Test_Debugger);
        manager.add(new Test_ErrorReport);
        manager.add(new Test_Profiler);
        manager.add(new Test_AutoProfiler);
    #endif

        // File system
    #if 1
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
    #endif

        // Log
    #if 1
        manager.add(new Test_Trace);
        manager.add(new Test_FileLog);
        manager.add(new Test_SystemLog);
    #endif

        // Net
    #if 1
        manager.add(new Test_CookiePv0);
        manager.add(new Test_CookiePv1);
        manager.add(new Test_Cgi);
        manager.add(new Test_SocketInit);
        manager.add(new Test_DnsClient);
        // manager.add(new Test_TcpClient);
        // manager.add(new Test_TcpServer);
        manager.add(new Test_HttpClient);
    #endif

        // Patterns
    #if 1
        manager.add(new Test_Observer);
        manager.add(new Test_Raii);
        manager.add(new Test_Singleton);
    #endif

        // Sync
    #if 1
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
    #endif

        // Gui
    #if 1
        manager.add(new Test_MsgBox);
    #endif

        // System
    #if 1
        manager.add(new Test_Environment);
        manager.add(new Test_SystemInfo);
        manager.add(new Test_ProcessInfo);
        manager.add(new Test_Console);
        manager.add(new Test_Shell);
    #endif

        manager.run(allLoops, unitLoops, caseLoops);
    }
#endif // xOPTION_TESTS

    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
