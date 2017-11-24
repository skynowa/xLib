/**
 * \file   User.cpp
 * \brief  user info
 */


#include "User.h"

#include <xLib/Log/Trace.h>
#include <xLib/System/Environment.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>

#if   xENV_WIN
    #include "Platform/Win/User_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/User_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/User_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/User_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/User_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
User::User()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
User::~User()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
User::isAdmin() const
{
    return _isAdmin_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::loginName() const
{
    return _loginName_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::name() const
{
    return _loginName_impl();
}
//-------------------------------------------------------------------------------------------------
uint_t
User::userId() const
{
    return _userId_impl();
}
//-------------------------------------------------------------------------------------------------
uint_t
User::groupId() const
{
    return _groupId_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::homeDir() const
{
    return _homeDir_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::shellPath() const
{
    return _shellPath_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
