/**
 * \file  Thread_unix.inl
 * \brief thread
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Service::_create_impl()
{
   /**
    * Write the pid of the daemon to /var/run/mydaemonname.pid so that you can easily look up
    * the pid later.
    * Set up a signal handler for SIGUSR1 and SIGUSR2.
    * When you get SIGUSR1, toggle a stop flag.
    * When you get SIGUSR2, set a report flag.
    * In your while loop, check each flag.
    * If the stop flag is set, stop until it is cleared.
    * If the report flag it set, clear the flag and do your report.
    */
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Service::_start_impl()
{
    // http://www.microhowto.info/howto/cause_a_process_to_become_a_daemon_in_c.html

    // Fork, allowing the parent process to terminate.
    pid_t pid = ::fork();
    if (pid == -1) {
        std::printf("failed to fork while daemonising (errno=%d)",errno);
    } else if (pid != 0) {
        ::_exit(0);
    }

    // Start a new session for the daemon.
    if (::setsid()==-1) {
        std::printf("failed to become a session leader while daemonising(errno=%d)",errno);
    }

    // Fork again, allowing the parent process to terminate.
    std::signal(SIGHUP,SIG_IGN);
    pid=::fork();
    if (pid == -1) {
        std::printf("failed to fork while daemonising (errno=%d)",errno);
    } else if (pid != 0) {
        ::_exit(0);
    }

    // Set the current working directory to the root directory.
    if (chdir("/") == -1) {
        std::printf("failed to change working directory while daemonising (errno=%d)",errno);
    }

    // Set the user file creation mask to zero.
    ::umask(0);

    // Close then reopen standard file descriptors.
    ::close(STDIN_FILENO);
    ::close(STDOUT_FILENO);
    ::close(STDERR_FILENO);
    if (::open("/dev/null",O_RDONLY) == -1) {
        std::printf("failed to reopen stdin while daemonising (errno=%d)",errno);
    }
    if (::open("/dev/null",O_WRONLY) == -1) {
        std::printf("failed to reopen stdout while daemonising (errno=%d)",errno);
    }
    if (::open("/dev/null",O_RDWR) == -1) {
        std::printf("failed to reopen stderr while daemonising (errno=%d)",errno);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Service::_stop_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Service::_close_impl()
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
