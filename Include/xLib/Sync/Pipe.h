/**
 * \file  Pipe.h
 * \brief Pipe is a section of shared memory that processes use for communication
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Core/HandlePolicy.h>
#include <xLib/Interface/ISync.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, sync)

class Pipe :
	public ISync<HandleNative>
    /// Pipe is a section of shared memory that processes use for communication
{
public:
             Pipe();
        ///< constructor
    virtual ~Pipe();
        ///< destructor

    const HandleNative & handle() const override;
        ///< get handle
    void_t   create() override;
    void_t   close() override;

private:
    HandleNative _handle {};    ///< native handle

    xNO_COPY_ASSIGN(Pipe)

xPLATFORM_IMPL:
    void_t _create_impl();
    void_t _close_impl();
};

xNAMESPACE_END2(xl, sync)
//-------------------------------------------------------------------------------------------------
