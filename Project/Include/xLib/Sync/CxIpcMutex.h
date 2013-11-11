/**
 * \file  CxIpcMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex :
    public CxNonCopyable
    /// mutex
{
public:
#if xOS_ENV_WIN
    typedef CxHandle handle_t;
#else
    typedef sem_t *  handle_t;
#endif

                     CxIpcMutex() {}
    virtual         ~CxIpcMutex() {}

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create(std::ctstring_t &name);
        ///< create
    void_t           open(std::ctstring_t &name);
        ///< open
    void_t           lock(culong_t &timeoutMsec) const;
        ///< unlock by timeout in msec
    void_t           unlock() const;
        ///< lock

private:
    handle_t         _handle;   ///< mutex native handle
    std::tstring_t   _name;     ///< mutex name
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxIpcMutex.inl>
