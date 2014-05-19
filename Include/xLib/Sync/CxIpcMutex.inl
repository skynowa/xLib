/**
 * \file  CxIpcMutex.inl
 * \brief mutex
 */


#if !xENV_WIN
    // lib: -lrt
#endif

#include <xLib/Core/CxConst.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline const CxIpcMutex::handle_t &
CxIpcMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::create(
    std::ctstring_t &a_name
)
{
    ////xTEST_EQ(_handle.isValid(), false);
#if   xENV_WIN
    // name
#elif xENV_UNIX
    xTEST_GR(xNAME_MAX - 4, a_name.size());
#endif

#if   xENV_WIN
    ctchar_t       *winName = xPTR_NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::CreateMutex(xPTR_NULL, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
#elif xENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hHandle = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, 1U);
    xTEST_DIFF(hHandle, SEM_FAILED);

    _handle = hHandle;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::open(
    std::ctstring_t &a_name
)
{
#if   xENV_WIN
    ctchar_t *winName = xPTR_NULL;
    std::tstring_t _winName;

    if (a_name.empty()) {
        winName = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
#elif xENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hHandle = ::sem_open(unixName.c_str(), O_RDWR, 0777, 1U);
    xTEST_DIFF(hHandle, SEM_FAILED);

    _handle = hHandle;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::lock(
    culong_t &a_timeoutMsec
) const
{
    ////xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_timeoutMsec);

#if   xENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
    xTEST_DIFF(dwRv, WAIT_ABANDONED);
#elif xENV_UNIX
    struct _Functor
    {
        static void_t
        timespecAddMsec(
            timespec *a_ts,
            long      a_ms
        )
        {
            long_t sec = 0L;

            sec  = a_ms / 1000;
            a_ms = a_ms - sec * 1000;

            // perform the addition
            a_ts->tv_nsec += a_ms * 1000000;

            // adjust the time
            a_ts->tv_sec += a_ts->tv_nsec / 1000000000 + sec;
            a_ts->tv_nsec = a_ts->tv_nsec % 1000000000;
        }
    };


    int_t    iRv         = - 1;
    timespec timeoutMsec = {0, 0};

    // add msec to timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &timeoutMsec);
        xTEST_DIFF(iRv, - 1);

        (void_t)_Functor::timespecAddMsec(&timeoutMsec, a_timeoutMsec);
    }

    while ((iRv = ::sem_timedwait(_handle, &timeoutMsec)) == - 1 && (errno == EINTR)) {
        // Restart if interrupted by handler
        continue;
    }

    if (iRv == - 1) {
        if (errno == ETIMEDOUT) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
#elif xENV_APPLE
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::unlock() const
{
    ////xTEST_EQ(_handle.isValid(), true);

#if   xENV_WIN
    BOOL blRv = ::ReleaseMutex(_handle.get());
    xTEST_DIFF(blRv, FALSE);
#elif xENV_UNIX
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
