/**
 * \file  User_unix.inl
 * \brief
 */


#include <xLib/Core/Utils.h>


namespace xl::system
{

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
User::_effectiveId_impl() const
{
    return ::geteuid();
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
        constexpr int_t buffSize       {LOGIN_NAME_MAX + 1};
        char            buff[buffSize] {};

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
		const std::array envVars{xT("LOGNAME"), xT("USER")};

		for (const auto &it_envVar : envVars) {
			Environment env(it_envVar);

			bool_t bRv = env.isExists();
			xCHECK_DO(!bRv, continue);

			sRv = env.var();

			return sRv;
		}
	}

    return {};
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

} // namespace
