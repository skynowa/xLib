/**
 * \file   Test_Signal.cpp
 * \brief  test Signal
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Signal)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Signal::unit()
{
#if   xENV_WIN
    // TODO: [Win] Signal tests
#elif xENV_UNIX
    xTEST_CASE("decription")
    {
        std::vector<int_t> signalNums;
        signalNums.push_back(SIGHUP);
        signalNums.push_back(SIGINT);
        signalNums.push_back(SIGQUIT);
        signalNums.push_back(SIGILL);
        signalNums.push_back(SIGTRAP);
        signalNums.push_back(SIGABRT);
        signalNums.push_back(SIGIOT);
        signalNums.push_back(SIGBUS);
        signalNums.push_back(SIGFPE);
        signalNums.push_back(SIGKILL);
        signalNums.push_back(SIGUSR1);
        signalNums.push_back(SIGSEGV);
        signalNums.push_back(SIGUSR2);
        signalNums.push_back(SIGPIPE);
        signalNums.push_back(SIGALRM);
        signalNums.push_back(SIGTERM);
        signalNums.push_back(SIGCHLD);
        signalNums.push_back(SIGCONT);
        signalNums.push_back(SIGSTOP);
        signalNums.push_back(SIGTSTP);
        signalNums.push_back(SIGTTIN);
        signalNums.push_back(SIGTTOU);
        signalNums.push_back(SIGURG);
        signalNums.push_back(SIGXCPU);
        signalNums.push_back(SIGXFSZ);
        signalNums.push_back(SIGVTALRM);
        signalNums.push_back(SIGPROF);
        signalNums.push_back(SIGWINCH);
        signalNums.push_back(SIGIO);
        signalNums.push_back(SIGSYS);
	#if !xENV_BSD
        signalNums.push_back(SIGPOLL);
        signalNums.push_back(SIGPWR);
        signalNums.push_back(SIGSTKFLT);
        signalNums.push_back(SIGCLD);
	#endif

        for (const auto &it : signalNums) {
            m_sRv = Signal::decription(it);
            // std::cout << xTRACE_VAR2(it, m_sRv) << std::endl;
            xTEST(!m_sRv.empty());
        }
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
