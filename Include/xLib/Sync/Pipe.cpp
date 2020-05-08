/**
 * \file  Pipe.cpp
 * \brief Pipe is a section of shared memory that processes use for communication
 */


#include "Pipe.h"

#if   xENV_WIN
    #include "Platform/Win/Pipe_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Pipe_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Pipe_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Pipe_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Apple/Pipe_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Pipe::Pipe()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
Pipe::~Pipe()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
const Pipe::handle_t &
Pipe::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
