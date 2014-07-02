/**
 * \file  AutoIpcMutex.inl
 * \brief auto mutex
 */


#include <xLib/Sync/IpcMutex.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
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
inline
AutoIpcMutex::~AutoIpcMutex()
{
    _mutex.unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
