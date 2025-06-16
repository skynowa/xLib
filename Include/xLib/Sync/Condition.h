/**
 * \file   Condition.h
 * \brief  condition variable
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Condition
    /// condition variable
{
public:
///\name ctors, dtor
///\{
			 Condition() = default;
	virtual ~Condition();

	xNO_COPY_ASSIGN(Condition);
///\}

#if !xENV_WIN
    const pthread_mutex_t & mutex() const;
        ///< get mutex handle
    const pthread_cond_t &  handle() const;
        ///< get handle
#endif

    void_t                  create();
        ///< create
    void_t                  wait(culong_t &timeoutMs);
        ///< wait
    void_t                  signal();
        ///< signal one
    void_t                  broadcast();
        ///< signal all

private:
#if !xENV_WIN
    pthread_mutex_t _mutex {};
    pthread_cond_t  _handle {};
#endif

xPLATFORM_IMPL:
    void_t _dtor_impl();
    void_t _create_impl();
    void_t _wait_impl(culong_t &timeoutMs);
    void_t _signal_impl();
    void_t _broadcast_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
