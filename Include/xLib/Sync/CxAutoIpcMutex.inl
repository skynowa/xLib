/**
 * \file  CxAutoIpcMutex.inl
 * \brief auto mutex
 */


#include <xLib/Sync/CxIpcMutex.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxAutoIpcMutex::CxAutoIpcMutex(
    CxIpcMutex      &a_mutex,
    std::ctstring_t &a_name
) :
    _mutex(a_mutex)
{
    _mutex.create(a_name);
    _mutex.lock(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
inline
CxAutoIpcMutex::~CxAutoIpcMutex()
{
    _mutex.unlock();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
