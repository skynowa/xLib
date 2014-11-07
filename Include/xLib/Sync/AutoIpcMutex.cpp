/**
 * \file  AutoIpcMutex.inl
 * \brief auto mutex
 */


#if !xOPTION_HEADER_ONLY
    #include "AutoIpcMutex.h"
#endif

#include <xLib/Sync/IpcMutex.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
AutoIpcMutex::AutoIpcMutex(
    IpcMutex      &a_mutex,
    std::ctstring_t &a_name
) :
    _mutex(a_mutex)
{
    _mutex.create(a_name);
    _mutex.lock(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
xINLINE
AutoIpcMutex::~AutoIpcMutex()
{
    _mutex.unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
