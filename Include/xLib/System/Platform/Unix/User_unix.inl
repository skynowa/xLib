/**
 * \file  User_unix.inl
 * \brief user info
 */


#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
User::_construct_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
User::_destruct_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
User::_isAdmin_impl() const
{
    const uid_t rootId = 0;
    uid_t       userId = 0;

    userId = ::getuid();
    xTESTS_NA;
    xCHECK_RET(userId != rootId, false);

    userId = ::geteuid();
    xTESTS_NA;
    xCHECK_RET(userId != rootId, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_loginName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
    #if cmGETLOGIN_R_FOUND
        char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: User::loginName() - LOGIN_NAME_MAX

        int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
        if (iRv == 0) {
            sRv = xA2T(buff);
            return sRv;
        }
    #else
        const char *buff = ::getlogin();
        if (buff != xPTR_NULL) {
            sRv = xA2T(buff);
            return sRv;
        }
    #endif
    }

    // try system environment
    {
        std::ctstring_t var = xT("LOGNAME");

        bool_t bRv = Environment::isExists(var);
        if (bRv) {
            sRv = Environment::var(var);
            return sRv;
        }
    }

    // try system environment
    {
        std::ctstring_t var = xT("USER");

        bool_t bRv = Environment::isExists(var);
        if (bRv) {
            sRv = Environment::var(var);
            return sRv;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_name_impl() const
{
    std::string sRv;

    _passwd(&sRv, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
User::_userId_impl() const
{
    uid_t uiRv;

    _passwd(xPTR_NULL, xPTR_NULL, &uiRv, xPTR_NULL, xPTR_NULL, xPTR_NULL);

    return static_cast<uint_t>(uiRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
User::_groupId_impl() const
{
    gid_t uiRv;

    _passwd(xPTR_NULL, xPTR_NULL, xPTR_NULL, &uiRv, xPTR_NULL, xPTR_NULL);

    return static_cast<uint_t>(uiRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_homeDir_impl() const
{
    std::tstring_t sRv;

   /*
    * MAN: user's home directory
    *
    * Login programs use the value of this field to initialize
    * the HOME environment variable for the login shell.
    * An application that wants to determine its user's home directory
    * should inspect the value of HOME (rather than the value getpwuid(getuid())->pw_dir)
    * since this allows the user to modify their notion of "the home directory"
    * during a login session. To determine the (initial) home directory of another user,
    * it is necessary to use getpwnam("username")->pw_dir or similar.
    */

    // try to get from API
    std::string asRv;

    _passwd(xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, &asRv, xPTR_NULL);
    xCHECK_RET(!asRv.empty(), xA2T(asRv));

    // try to get from system environment
    sRv = Environment::var(xT("HOME"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_shellPath_impl() const
{
    std::string sRv;

    _passwd(xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, &sRv);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
User::_passwd(
    std::string *a_pw_name,   ///< [out] Username (maybe as xPTR_NULL)
    std::string *a_pw_passwd, ///< [out] Password (maybe as xPTR_NULL)
    uid_t       *a_pw_uid,    ///< [out] User ID (maybe as xPTR_NULL)
    gid_t       *a_pw_gid,    ///< [out] Group ID (maybe as xPTR_NULL)
    std::string *a_pw_dir,    ///< [out] Home directory (maybe as xPTR_NULL)
    std::string *a_pw_shell   ///< [out] Shell program (maybe as xPTR_NULL)
) const
{
    xTEST_NA(a_pw_name);
    xTEST_NA(a_pw_passwd);
    xTEST_NA(a_pw_uid);
    xTEST_NA(a_pw_gid);
    xTEST_NA(a_pw_dir);
    xTEST_NA(a_pw_shell);

    struct passwd *pwRv = xPTR_NULL;

    const uid_t userId = ::getuid();
    xTEST_NA(userId);

#if cmGETPWUID_R_FOUND
    long_t buffSize = - 1L;
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (buffSize == - 1L) {
            buffSize = xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX;
        }

        xTEST_GR(buffSize, 0L);
    }

    struct passwd pwBuff; xSTRUCT_ZERO(pwBuff);
    std::string   buff;
    buff.resize( static_cast<std::size_t>(buffSize) );

    int_t iRv = ::getpwuid_r(userId, &pwBuff, &buff.at(0), buff.size(), &pwRv);
    xTEST_EQ(iRv, 0);
#else
    pwRv = ::getpwuid(userId);
#endif

    xTEST_PTR(pwRv);

    Utils::ptrAssignT(a_pw_name,   std::string(pwRv->pw_name));
    Utils::ptrAssignT(a_pw_passwd, std::string(pwRv->pw_passwd));
    Utils::ptrAssignT(a_pw_uid,    pwRv->pw_uid);
    Utils::ptrAssignT(a_pw_gid,    pwRv->pw_gid);
    Utils::ptrAssignT(a_pw_dir,    std::string(pwRv->pw_dir));
    Utils::ptrAssignT(a_pw_shell,  std::string(pwRv->pw_shell));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
