/**
 * \file  CxCompletionPort.cpp
 * \brief completion port
 */


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxCompletionPort::create(
    culong_t &a_threadsNum
)
{
    // _handle      - n/a
    // ulThreadsNum - n/a

    _handle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, a_threadsNum);
    xTEST_EQ(true, _handle.isValid());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCompletionPort::associate(
    const HANDLE  &a_file,
    ULONG_PTR      a_completionKey
) const
{
    xTEST_EQ(true, _handle.isValid());
    // a_file

#if xARCH_X86
    xTEST_DIFF(0UL, a_completionKey);
#else
    xTEST_PTR(a_completionKey);
#endif

    HANDLE hRv = ::CreateIoCompletionPort(a_file, _handle.get(), a_completionKey, 0);
    xTEST_EQ(xNATIVE_HANDLE_INVALID, hRv);
    xTEST_EQ(_handle.get(), hRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCompletionPort::status(
    LPDWORD       a_numberOfBytes,
    PULONG_PTR    a_completionKey,
    LPOVERLAPPED *a_overlapped,
    culong_t     &a_msec
) const
{
    xTEST_EQ(true, _handle.isValid());
    xTEST_PTR(a_numberOfBytes);
    xTEST_PTR(a_completionKey);
    xTEST_PTR(a_overlapped);
    xTEST_NA(a_msec);

    BOOL blRv = ::GetQueuedCompletionStatus(_handle.get(), a_numberOfBytes, a_completionKey,
        a_overlapped, a_msec);
    xTEST_DIFF(FALSE, blRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCompletionPort::postStatus(
    culong_t     &a_numOfBytesTransferred,
    ULONG_PTR     a_completionKey,
    LPOVERLAPPED  a_overlapped
) const
{
    xTEST_EQ(true, _handle.isValid());
    xTEST_NA( a_numOfBytesTransferred);
    xTEST_NA(a_completionKey);
    xTEST_PTR(a_overlapped);

    BOOL blRv = ::PostQueuedCompletionStatus(_handle.get(), a_numOfBytesTransferred,
        a_completionKey, a_overlapped);
    xTEST_DIFF(FALSE, blRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
