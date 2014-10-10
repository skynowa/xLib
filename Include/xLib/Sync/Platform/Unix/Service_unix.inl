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
inline void_t
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
inline void_t
Service::_start_impl()
{
    int_t iRv = 0;

    // Our process ID and Session ID
    pid_t pid;
    pid_t sid;

    // Fork off the parent process
    pid = ::fork();
    if (pid < 0) {
        std::exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process.
    if (pid > 0) {
        std::exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    ::umask(0);

    // Open any logs here

    // Create a new SID for the child process
    sid = ::setsid();
    if (sid < 0) {
        // Log the failure
        std::exit(EXIT_FAILURE);
    }

    // Change the current working directory
    iRv = ::chdir("/");
    if (iRv < 0) {
        // Log the failure
        std::exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    ::close(STDIN_FILENO);
    ::close(STDOUT_FILENO);
    ::close(STDERR_FILENO);

    // Daemon-specific initialization goes here

    // The Big Loop
    while (1) {
       // Do some task here ...

       ::sleep(30);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::_stop_impl()
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::_close_impl()
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
