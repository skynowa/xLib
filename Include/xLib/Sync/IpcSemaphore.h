/**
 * \file  IpcSemaphore.h
 * \brief semaphore
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class IpcSemaphore
    /// semaphore (interprocess)
{
public:
#if   xENV_WIN
    using handle_t = HANDLE;
#elif xENV_UNIX
    using handle_t = sem_t *;
#endif

///\name ctors, dtor
///\{
			 IpcSemaphore();
	virtual ~IpcSemaphore();

	xNO_COPY_ASSIGN(IpcSemaphore);
///\}

    long_t           valueMax() const;
        ///< maximum value
    const handle_t & handle() const;
        ///< get handle
    void_t           create(clong_t initialValue, std::ctstring_t &name);
        ///< create
    void_t           open(std::ctstring_t &name);
        ///< open
    void_t           post() const;
        ///< release
    void_t           wait(culong_t timeoutMsec) const;
        ///< wait
    long_t           value() const;
        ///< get value

private:
    handle_t       _handle {};
    std::tstring_t _name;

    bool_t _isValid() const;

xPLATFORM_IMPL:
    void_t _ctor_impl();
    void_t _dtor_impl();
    long_t _valueMax_impl() const;
    void_t _create_impl(clong_t initialValue, std::ctstring_t &name);
    void_t _open_impl(std::ctstring_t &name);
    void_t _post_impl() const;
    void_t _wait_impl(culong_t timeoutMsec) const;
    long_t _value_impl() const;
    bool_t _isValid_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * SysV  semaphores are semget/semop/semctl
 * POSIX semaphores are sem_open/sem_close/sem_*
 */
