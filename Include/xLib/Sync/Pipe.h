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
namespace xl::sync
{

class Pipe :
	public ISync<HandleNative>
    /// Pipe is a section of shared memory that processes use for communication
{
public:
///@name ctors, dtor
///@{
			 Pipe();
	virtual ~Pipe();

	xNO_COPY_ASSIGN(Pipe)
///@}

    cHandleNative & handle() const override;
	cint_t        & handleRead() const;
	cint_t        & handleWrite() const;

    void_t          create() override;

    std::tstring_t  readAll() const;

    void_t          close() override;
    void_t          closeRead();
    void_t          closeWrite();

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

xPLATFORM_IMPL:
    void_t _create_impl();

    enum class CloseMode
	{
		Read  = 1,
		Write = 2,
		All   = 3
	};
    xUSING_CONST(CloseMode);

    std::ssize_t _read_impl(cint_t handleRead, void_t *buff, std::csize_t buffSize) const;
    void_t       _close_impl(cCloseMode mode);
};

} // namespace
//-------------------------------------------------------------------------------------------------
