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
#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

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
        CxHandle _m_hCP;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCompletionPortH
