/**
 * \file  CxCompletionPort.cpp
 * \brief completion port
 */


#include <xLib/Sync/Win/CxCompletionPort.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCompletionPort
CxCompletionPort::CxCompletionPort() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: ~CxCompletionPort
/*virtual*/
CxCompletionPort::~CxCompletionPort() {
    /*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates an input/output (I/O) completion port and associates it with a specified file handle, or creates an I/O completion port that is not yet associated with a file handle, allowing association at a later time.)
bool
CxCompletionPort::bCreate(
    ulong_t a_ulThreadsNum
)
{
    /*DEBUG*/// _m_hCP       - n/a
    /*DEBUG*/// ulThreadsNum - n/a

    _m_hCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, a_ulThreadsNum);
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bAssociate
bool
CxCompletionPort::bAssociate(
    HANDLE    a_hFile,
    ULONG_PTR a_pulCompletionKey
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/// hFile
    /*DEBUG*/xASSERT_RET(NULL  != a_pulCompletionKey,  false);

    HANDLE hRv = ::CreateIoCompletionPort(a_hFile, _m_hCP.hGet(), a_pulCompletionKey, 0);
    /*DEBUG*/xASSERT_RET(NULL          != hRv, false);
    /*DEBUG*/xASSERT_RET(_m_hCP.hGet() == hRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bGetStatus (Attempts to dequeue an I/O completion packet from the specified I/O completion port.)
bool
CxCompletionPort::bGetStatus(
    LPDWORD       a_lpNumberOfBytes,
    PULONG_PTR    a_lpCompletionKey,
    LPOVERLAPPED *a_lpOverlapped,
    ulong_t       a_ulMilliseconds
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_lpNumberOfBytes,   false);
    /*DEBUG*/xASSERT_RET(NULL  != a_lpCompletionKey,   false);
    /*DEBUG*/xASSERT_RET(NULL  != a_lpOverlapped,      false);
    /*DEBUG*/// ulMilliseconds - n/a

    BOOL blRes = ::GetQueuedCompletionStatus(_m_hCP.hGet(), a_lpNumberOfBytes, a_lpCompletionKey, a_lpOverlapped, a_ulMilliseconds);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bPostStatus (Posts an I/O completion packet to an I/O completion port.)
bool
CxCompletionPort::bPostStatus(
    ulong_t      a_ulNumberOfBytesTransferred,
    ULONG_PTR    a_ulCompletionKey,
    LPOVERLAPPED a_lpOverlapped
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hCP.bIsValid(), false);
    /*DEBUG*/// ulNumberOfBytesTransferred - n/a
    /*DEBUG*/// ulCompletionKey            - n/a
    /*DEBUG*/xASSERT_RET(NULL  != a_lpOverlapped,    false);

    BOOL blRes = ::PostQueuedCompletionStatus(_m_hCP.hGet(), a_ulNumberOfBytesTransferred, a_ulCompletionKey, a_lpOverlapped);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
