/**
 * \file  Pipe.h
 * \brief Pipe is a section of shared memory that processes use for communication
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, sync)

class Pipe
    /// Pipe is a section of shared memory that processes use for communication
{
public:
#if   xENV_WIN
    using handle_t = CRITICAL_SECTION;
#elif xENV_UNIX
    using handle_t = pthread_mutex_t;
#endif

             Pipe();
        ///< constructor
    virtual ~Pipe();
        ///< destructor

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create();

private:
    handle_t         _handle {};   ///< native handle

    xNO_COPY_ASSIGN(Pipe)

xPLATFORM_IMPL:
    void_t   _construct_impl();
    void_t   _destruct_impl();
    void_t   _create_impl();
};

xNAMESPACE_END2(xl, sync)
//-------------------------------------------------------------------------------------------------
