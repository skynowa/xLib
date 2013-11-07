/**
 * \file  CxCompletionPort.h
 * \brief completion port
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCompletionPort :
    public CxNonCopyable
    /// completion port
{
public:
             CxCompletionPort();
    virtual ~CxCompletionPort();

    void_t   create(culong_t &threadsNum /* = 0UL */);
    void_t   associate(const HANDLE &file, ULONG_PTR completionKey);
    void_t   status(LPDWORD numberOfBytes, PULONG_PTR completionKey, LPOVERLAPPED *overlapped,
                culong_t &msec);
    void_t   postStatus(culong_t &numOfBytesTransferred, ULONG_PTR completionKey,
                LPOVERLAPPED overlapped);

private:
    CxHandle _handle;
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Sync/Win/CxCompletionPort.cpp>
#endif
