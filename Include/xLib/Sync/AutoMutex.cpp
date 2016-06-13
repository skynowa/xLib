/**
 * \file  AutoMutex.h
 * \brief auto critical section (using between threads)
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "AutoMutex.h"
#endif

#include <xLib/Sync/Mutex.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
AutoMutex::AutoMutex(
    Mutex *a_mutex
) :
    _mutex(a_mutex)
{
    _mutex->create();
    _mutex->lock();
}
//-------------------------------------------------------------------------------------------------
xINLINE
AutoMutex::~AutoMutex()
{
    _mutex->unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
