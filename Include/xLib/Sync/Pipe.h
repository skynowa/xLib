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
    const int_t & handleRead() const;
    const int_t & handleWrite() const;

    void_t   create() override;
    void_t   close() override;
    void_t   closeRead();
    void_t   closeWrite();

private:
    HandleNative _handle {};    ///< native handle

#if   xENV_WIN
	// TODO:
#elif xENV_UNIX
	enum FdIndex : std::size_t
	{
		Read  = 0,
		Write = 1
	};

	std::vector<int_t> _handles;	///< native handles
#endif

    xNO_COPY_ASSIGN(Pipe)

xPLATFORM_IMPL:
    void_t _create_impl();

    enum class CloseMode
	{
		Unknown = 0,
		Read    = 1,
		Write   = 2,
		All     = 3
	};
    xUSING_CONST(CloseMode);

    void_t _close_impl(cCloseMode mode);
};

xNAMESPACE_END2(xl, sync)
//-------------------------------------------------------------------------------------------------
