/**
 * \file  CxCompletionPort.cpp
 * \brief completion port
 */


#include <xLib/Sync/Win/CxCompletionPort.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCompletionPort::CxCompletionPort() :
    _m_hHandle()
{
    /*DEBUG*/
}
//---------------------------------------------------------------------------
/* virtual */
CxCompletionPort::~CxCompletionPort() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vCreate(
    const ulong_t &a_culThreadsNum
)
{
    /*DEBUG*/// _m_hCP       - n/a
    /*DEBUG*/// ulThreadsNum - n/a

    _m_hHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, a_culThreadsNum);
    /*DEBUG*/xTEST_EQ(true, _m_hHandle.bIsValid());
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vAssociate(
    const HANDLE  &a_chFile,
    ULONG_PTR      a_pulCompletionKey
)
{
    /*DEBUG*/xTEST_EQ(true, _m_hHandle.bIsValid());
    /*DEBUG*/// hFile
    /*DEBUG*/xTEST_PTR(a_pulCompletionKey);

    HANDLE hRv = ::CreateIoCompletionPort(a_chFile, _m_hHandle.hGet(), a_pulCompletionKey, 0);
    /*DEBUG*/xTEST_EQ(xNATIVE_HANDLE_INVALID, hRv);
    /*DEBUG*/xTEST_EQ(_m_hHandle.hGet(), hRv);
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vStatus(
    LPDWORD        a_lpNumberOfBytes,
    PULONG_PTR     a_lpCompletionKey,
    LPOVERLAPPED  *a_lpOverlapped,
    const ulong_t &a_culMilliseconds
)
{
    /*DEBUG*/xTEST_EQ(true, _m_hHandle.bIsValid());
    /*DEBUG*/xTEST_PTR(a_lpNumberOfBytes);
    /*DEBUG*/xTEST_PTR(a_lpCompletionKey);
    /*DEBUG*/xTEST_PTR(a_lpOverlapped);
    /*DEBUG*/// ulMilliseconds - n/a

    BOOL blRes = ::GetQueuedCompletionStatus(_m_hHandle.hGet(), a_lpNumberOfBytes, a_lpCompletionKey, a_lpOverlapped, a_culMilliseconds);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------
void
CxCompletionPort::vPostStatus(
    const ulong_t &a_culNumberOfBytesTransferred,
    ULONG_PTR      a_ulCompletionKey,
    LPOVERLAPPED   a_lpOverlapped
)
{
    /*DEBUG*/xTEST_EQ(true, _m_hHandle.bIsValid());
    /*DEBUG*/// ulNumberOfBytesTransferred - n/a
    /*DEBUG*/// ulCompletionKey            - n/a
    /*DEBUG*/xTEST_PTR(a_lpOverlapped);

    BOOL blRes = ::PostQueuedCompletionStatus(_m_hHandle.hGet(), a_culNumberOfBytesTransferred, a_ulCompletionKey, a_lpOverlapped);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
