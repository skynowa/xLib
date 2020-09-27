/**
 * \file  IpcMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class IpcMutex
    /// mutex
{
public:
#if   xENV_WIN
    using handle_t = Handle;
#elif xENV_UNIX
    using handle_t = sem_t *;
#endif

                     IpcMutex() = default;
    virtual         ~IpcMutex() = default;

    const handle_t & handle() const;
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
    handle_t         _handle {};    ///< mutex native handle
    std::tstring_t   _name;         ///< mutex name

    xNO_COPY_ASSIGN(IpcMutex)

xPLATFORM_IMPL:
    void_t           _create_impl(std::ctstring_t &name);
    void_t           _open_impl(std::ctstring_t &name);
    void_t           _lock_impl(culong_t &timeoutMsec) const;
    void_t           _unlock_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
// TODO: IpcSemaphore_unix -> IpcMutex_unix.inl - re copy paste
//-------------------------------------------------------------------------------------------------
