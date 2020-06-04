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
uint_t
User::_id_impl() const
{
    uid_t uiRv;

    _passwd(nullptr, nullptr, &uiRv, nullptr, nullptr, nullptr);

    return static_cast<uint_t>(uiRv);
}
//-------------------------------------------------------------------------------------------------
uint_t
User::_groupId_impl() const
{
    gid_t uiRv;

    _passwd(nullptr, nullptr, nullptr, &uiRv, nullptr, nullptr);

    return static_cast<uint_t>(uiRv);
}
//-------------------------------------------------------------------------------------------------
bool_t
User::_isAdmin_impl() const
{
    const uid_t rootId {0};

    xCHECK_RET(id()        != rootId, false);
    xCHECK_RET(::geteuid() != rootId, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_loginName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
    #if cmHAVE_GETLOGIN_R
        cint_t buffSize       = xUSER_NAME_MAX + 1;
        char   buff[buffSize] = {0}; // TODO: [skynowa] User::loginName() - LOGIN_NAME_MAX

        int_t iRv = ::getlogin_r(buff, buffSize);
        if (iRv == 0) {
            sRv = xA2T(buff);
            return sRv;
        }
    #else
        const char *buff = ::getlogin();
        if (buff != nullptr) {
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
std::tstring_t
User::_name_impl() const
{
    std::string sRv;

    _passwd(&sRv, nullptr, nullptr, nullptr, nullptr, nullptr);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
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

    _passwd(nullptr, nullptr, nullptr, nullptr, &asRv, nullptr);
    xCHECK_RET(!asRv.empty(), xA2T(asRv));

    // try to get from system environment
    sRv = Environment::var(xT("HOME"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_shellPath_impl() const
{
    std::string sRv;

    _passwd(nullptr, nullptr, nullptr, nullptr, nullptr, &sRv);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
User::_passwd(
    std::string *a_pw_name,   ///< [out] Username (maybe as nullptr)
    std::string *a_pw_passwd, ///< [out] Password (maybe as nullptr)
    uid_t       *a_pw_uid,    ///< [out] User ID (maybe as nullptr)
    gid_t       *a_pw_gid,    ///< [out] Group ID (maybe as nullptr)
    std::string *a_pw_dir,    ///< [out] Home directory (maybe as nullptr)
    std::string *a_pw_shell   ///< [out] Shell program (maybe as nullptr)
) const
{
    xTEST_NA(a_pw_name);
    xTEST_NA(a_pw_passwd);
    xTEST_NA(a_pw_uid);
    xTEST_NA(a_pw_gid);
    xTEST_NA(a_pw_dir);
    xTEST_NA(a_pw_shell);

    // !!! Don't use User::id() - recursive call !!!
    const uid_t id = ::getuid();
    xTEST_NA(id);

    struct passwd *pwRv {};

#if cmHAVE_GETPWUID_R
    long_t buffSize = - 1L;
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (buffSize == - 1L) {
            buffSize = xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX;
        }

        xTEST_GR(buffSize, 0L);
    }

    struct passwd pwBuff {};
    std::string   buff;
    buff.resize( static_cast<std::size_t>(buffSize) );

    int_t iRv = ::getpwuid_r(id, &pwBuff, &buff.at(0), buff.size(), &pwRv);
    xTEST_EQ(iRv, 0);
#else
    pwRv = ::getpwuid(id);
#endif

    xTEST_PTR(pwRv);
    xTEST_EQ(pwRv->pw_uid, id);

    Utils::ptrAssignT(a_pw_name,   std::string(pwRv->pw_name));
    Utils::ptrAssignT(a_pw_passwd, std::string(pwRv->pw_passwd));
    Utils::ptrAssignT(a_pw_uid,    pwRv->pw_uid);
    Utils::ptrAssignT(a_pw_gid,    pwRv->pw_gid);
    Utils::ptrAssignT(a_pw_dir,    std::string(pwRv->pw_dir));
    Utils::ptrAssignT(a_pw_shell,  std::string(pwRv->pw_shell));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
