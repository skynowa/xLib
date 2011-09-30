/**
 * \file  CxCompletionPort.h
 * \brief completion port
 */


#ifndef xLib_Sync_CxCompletionPortH
#define xLib_Sync_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxCompletionPort :
    public CxNonCopyable
    /// completion port
{
    public:
                 CxCompletionPort();
        virtual ~CxCompletionPort();

        BOOL     bCreate         (ULONG ulThreadsNum /*= 0*/);
        BOOL     bAssociate      (HANDLE hFile, ULONG_PTR pulCompletionKey);
        BOOL     bGetStatus      (LPDWORD lpNumberOfBytes, PULONG_PTR lpCompletionKey, LPOVERLAPPED *lpOverlapped, ULONG ulMilliseconds);
        BOOL     bPostStatus     (ULONG ulNumberOfBytesTransferred, ULONG_PTR ulCompletionKey, LPOVERLAPPED lpOverlapped);

    private:
        BOOL     _m_bRes;
        CxHandle _m_hCP;
};
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCompletionPortH
