/**
 * \file  User_win.inl
 * \brief [CLASS_COMMENTS]
 */


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
uint_t
User::_id_impl() const
{
    // TODO: [skynowa] User::id - GetTokenInformation::TokenUser
	// /home/skynowa/Projects/CppTest/Windows/getuid.cpp
	// https://docs.microsoft.com/en-us/windows/win32/secauthz/searching-for-a-sid-in-an-access-token-in-c--

    xNOT_IMPLEMENTED;

    return 0;
}
//-------------------------------------------------------------------------------------------------
uint_t
User::_groupId_impl() const
{
    // TODO: [skynowa] User::groupId - GetTokenInformation::TokenGroups

    xNOT_IMPLEMENTED;

    return 0;
}
//-------------------------------------------------------------------------------------------------
bool_t
User::_isAdmin_impl() const
{
    SID_IDENTIFIER_AUTHORITY ntAuthority { SECURITY_NT_AUTHORITY };
    PSID                     adminGroup  {};
    BOOL blRv = ::AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, &adminGroup);
    xCHECK_RET(blRv == FALSE, false);

	BOOL isMember {};
	blRv = ::CheckTokenMembership(nullptr, adminGroup, &isMember);
	xCHECK_RET(blRv == FALSE, false);

    (void_t)::FreeSid(adminGroup);
    adminGroup = nullptr;

    return static_cast<bool_t>(isMember);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_loginName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
    	// TODO: [skynowa] User::loginName() - LOGIN_NAME_MAX
        char buff[xUSER_NAME_MAX + 1] = {0};
        int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
        if (iRv == 0) {
            sRv.assign(buff);
            return sRv;
        }
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
    std::tstring_t sRv;

    DWORD   buffSize                 = xUSER_NAME_MAX;
    tchar_t buff[xUSER_NAME_MAX + 1] = {0};

    BOOL blRv = ::GetUserName(&buff[0], &buffSize);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, buffSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_homeDir_impl() const
{
    std::tstring_t sRv;

    tchar_t buff[MAX_PATH + 1] = {0};

    HRESULT hrRv = SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0UL, &buff[0]);
    xTEST_EQ(S_OK == hrRv, true);

    sRv.assign(buff);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_shellPath_impl() const
{
    std::tstring_t sRv;

    LPITEMIDLIST idList = {0};

    HRESULT hrRv = ::SHGetSpecialFolderLocation(nullptr, CSIDL_WINDOWS, &idList);
    xTEST_EQ(hrRv, S_OK);

    tchar_t buff[MAX_PATH + 1] = {0};

    BOOL blRv = ::SHGetPathFromIDList(idList, buff);
    xTEST_DIFF(blRv, FALSE);

    sRv.append(buff);
    sRv.append(Const::slash());
    sRv.append(xT("explorer.exe"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
