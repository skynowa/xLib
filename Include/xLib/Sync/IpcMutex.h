/**
 * \file  IpcMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class IpcMutex
    /// mutex
{
public:
#if   xENV_WIN
    typedef Handle handle_t;
#elif xENV_UNIX
    typedef sem_t *  handle_t;
#endif

                     IpcMutex();
    virtual         ~IpcMutex() {}

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

    xNO_COPY_ASSIGN(IpcMutex)

xPLATFORM:
    void_t           _create_impl(std::ctstring_t &name);
    void_t           _open_impl(std::ctstring_t &name);
    void_t           _lock_impl(culong_t &timeoutMsec) const;
    void_t           _unlock_impl() const;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "IpcMutex.inl"
