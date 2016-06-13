/**
 * \file  IpcSemaphore.h
 * \brief semaphore
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class IpcSemaphore
    /// semaphore (interprocess)
{
public:
#if   xENV_WIN
    typedef Handle handle_t;
#elif xENV_UNIX
    typedef sem_t *  handle_t;
#endif

                     IpcSemaphore();
    virtual         ~IpcSemaphore();

    long_t           valueMax() const;
        ///< maximum value
    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create(clong_t &initialValue, std::ctstring_t &name);
        ///< create
    void_t           open(std::ctstring_t &name);
        ///< open
    void_t           post() const;
        ///< release
    void_t           wait(culong_t &timeoutMsec) const;
        ///< wait
    long_t           value() const xWARN_UNUSED_RV;
        ///< get value

private:
    handle_t         _handle;
    std::tstring_t   _name;

    bool_t           _isValid() const xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(IpcSemaphore)

xPLATFORM_IMPL:
    void_t           _construct_impl();
    void_t           _destruct_impl();
    long_t           _valueMax_impl() const;
    void_t           _create_impl(clong_t &initialValue, std::ctstring_t &name);
    void_t           _open_impl(std::ctstring_t &name);
    void_t           _post_impl() const;
    void_t           _wait_impl(culong_t &timeoutMsec) const;
    long_t           _value_impl() const xWARN_UNUSED_RV;
    bool_t           _isValid_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "IpcSemaphore.cpp"
#endif


/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*
*/
