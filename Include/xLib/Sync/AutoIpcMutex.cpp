/**
 * \file  AutoIpcMutex.inl
 * \brief auto mutex
 */


#include "AutoIpcMutex.h"

#include <xLib/Sync/IpcMutex.h>


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AutoIpcMutex::AutoIpcMutex(
    IpcMutex        &a_mutex,
    std::ctstring_t &a_name
) :
    _mutex(a_mutex)
{
    _mutex.create(a_name);
    _mutex.lock(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
AutoIpcMutex::~AutoIpcMutex()
{
    _mutex.unlock();
}
//-------------------------------------------------------------------------------------------------

} // namespace
