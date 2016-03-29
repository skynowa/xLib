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
    #if xHAVE_GETLOGIN_R
        char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: User::loginUserName() - LOGIN_NAME_MAX

        int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
        if (iRv == 0) {
            sRv.assign(buff);
            return sRv;
        }
    #else
        const char *buff = ::getlogin();
        if (buff != xPTR_NULL) {
            sRv.assign(buff);
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
    std::tstring_t sRv;

    _passwd(&sRv, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL);

    return sRv;
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
    _passwd(xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, &sRv, xPTR_NULL);
    xCHECK_RET(!sRv.empty(), sRv);

    // try to get from system environment
    sRv = Environment::var(xT("HOME"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_shellPath_impl() const
{
    std::tstring_t sRv;

    _passwd(xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, xPTR_NULL, &sRv);

    return sRv;
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
    std::string *a_pw_gecos,  ///< [out] Real name (maybe as xPTR_NULL)
    std::string *a_pw_dir,    ///< [out] Home directory (maybe as xPTR_NULL)
    std::string *a_pw_shell   ///< [out] Shell program (maybe as xPTR_NULL)
) const
{
    xTEST_NA(a_pw_name);
    xTEST_NA(a_pw_passwd);
    xTEST_NA(a_pw_uid);
    xTEST_NA(a_pw_gid);
    xTEST_NA(a_pw_gecos);
    xTEST_NA(a_pw_dir);
    xTEST_NA(a_pw_shell);

    struct passwd *pwRv = xPTR_NULL;

    const uid_t userId = ::getuid();
    xTEST_NA(userId);

#if xHAVE_GETPWUID_R
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
    buff.resize(buffSize);

    int_t iRv = ::getpwuid_r(userId, &pwBuff, &buff.at(0), buff.size(), &pwRv);
    xTEST_EQ(iRv, 0);
#else
    pwRv = ::getpwuid(userId);
#endif

    xTEST_PTR(pwRv);

    Utils::ptrAssignT(a_pw_name,   std::tstring_t(pwRv->pw_name));
    Utils::ptrAssignT(a_pw_passwd, std::tstring_t(pwRv->pw_passwd));
    Utils::ptrAssignT(a_pw_uid,    pwRv->pw_uid);
    Utils::ptrAssignT(a_pw_gid,    pwRv->pw_gid);
    // TODO: [Android] pwRv->pw_gecos
#if xTODO_ANDROID
    Utils::ptrAssignT(a_pw_gecos,  std::tstring_t(pwRv->pw_gecos));
#endif
    Utils::ptrAssignT(a_pw_dir,    std::tstring_t(pwRv->pw_dir));
    Utils::ptrAssignT(a_pw_shell,  std::tstring_t(pwRv->pw_shell));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
