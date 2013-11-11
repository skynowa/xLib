/**
 * \file  CxIpcMutex.cpp
 * \brief mutex
 */


#if !xOS_ENV_WIN
    // lib: -lrt
#endif

#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO const CxIpcMutex::handle_t &
CxIpcMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxIpcMutex::create(
    std::ctstring_t &a_name
)
{
    ////xTEST_EQ(false, _handle.bIsValid(), false);
#if xOS_ENV_WIN
    // name
#else
    xTEST_GR(xNAME_MAX - 4, a_name.size());
#endif

#if xOS_ENV_WIN
    ctchar_t       *winName = NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::CreateMutex(NULL, FALSE, winName);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _handle.set(hRv);
    _name = a_name;
#else
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hHandle = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, 1U);
    xTEST_DIFF(SEM_FAILED, hHandle);

    _handle = hHandle;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxIpcMutex::open(
    std::ctstring_t &a_name
)
{
#if xOS_ENV_WIN
    ctchar_t *winName = NULL;
    std::tstring_t _winName;

    if (a_name.empty()) {
        winName = NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _handle.set(hRv);
    _name = a_name;
#else
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hHandle = ::sem_open(unixName.c_str(), O_RDWR, 0777, 1U);
    xTEST_DIFF(SEM_FAILED, hHandle);

    _handle = hHandle;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxIpcMutex::lock(
    culong_t &a_timeoutMsec
) const
{
    ////xTEST_EQ(true, _handle.bIsValid(), false);
    //culTimeout - n/a

#if   xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
    xTEST_DIFF(WAIT_ABANDONED, ulRv);
#elif xOS_ENV_UNIX
    struct _SFunctor
    {
        static void_t
        timespecAddMsec(
            struct timespec *a_ts,
            long             a_ms
        )
        {
            int_t sec = 0;

            sec  = a_ms / 1000;
            a_ms = a_ms - sec * 1000;

            // perform the addition
            a_ts->tv_nsec += a_ms * 1000000;

            // adjust the time
            a_ts->tv_sec += a_ts->tv_nsec / 1000000000 + sec;
            a_ts->tv_nsec = a_ts->tv_nsec % 1000000000;
        }
    };


    int_t           iRv         = - 1;
    struct timespec timeoutMsec = {0};

    // add msec to struct timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &timeoutMsec);
        xTEST_DIFF(- 1, iRv);

        (void_t)_SFunctor::timespecAddMsec(&timeoutMsec, a_timeoutMsec);
    }

    while (- 1 == (iRv = ::sem_timedwait(_handle, &timeoutMsec)) && (EINTR == errno)) {
        // Restart if interrupted by handler
        continue;
    }

    if (- 1 == iRv) {
        if (ETIMEDOUT == errno) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxIpcMutex::unlock() const
{
    ////xTEST_EQ(true, _handle.bIsValid(), false);

#if xOS_ENV_WIN
    BOOL blRv = ::ReleaseMutex(_handle.get());
    xTEST_DIFF(FALSE, blRv);
#else
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
