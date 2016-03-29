/**
 * \file  User_unix.inl
 * \brief user info
 */


#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
User::_construct_impl()
{
    struct passwd  pwd; xSTRUCT_ZERO(pwd);
    struct passwd *result = xPTR_NULL;

    size_t buffSize = ::sysconf(xGETPW_R_SIZE_MAX);
    if (buffSize == - 1) {
        // Should be more than enough
        buffSize = 16384;
    }

    std::string buff;
    buff.resize(buffSize);

    int iRv = ::getpwnam_r(xT("skynowa"), &pwd, &buff.at(0), buffSize, &result);
    if (result == xPTR_NULL) {
        if (iRv == 0) {
            Trace() << "Not found";
        } else {
            Trace() << "Error";
        }

        return;
    }

    Trace()
        << xTRACE_VAR(result->pw_name)   << "\n"
        << xTRACE_VAR(result->pw_passwd) << "\n"
        << xTRACE_VAR(result->pw_uid)    << "\n"
        << xTRACE_VAR(result->pw_gid)    << "\n"
        << xTRACE_VAR(result->pw_dir)    << "\n"
        << xTRACE_VAR(result->pw_shell);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
User::_destruct_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_loginName_impl() const
{
    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
User::_userId_impl() const
{
    return 0;
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
User::_groupId_impl() const
{
    return 0;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_homeDir_impl() const
{
    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_shell_impl() const
{
    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
