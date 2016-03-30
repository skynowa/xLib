/**
 * \file  User_win.inl
 * \brief [CLASS_COMMENTS]
 */


xNAMESPACE_BEGIN2(xlib, system)

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
    bool_t                   isAdmin     = false;
    SID_IDENTIFIER_AUTHORITY ntAuthority = { SECURITY_NT_AUTHORITY };
    PSID                     adminGroup  = xPTR_NULL;

    BOOL blRv = ::AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, &adminGroup);
    xCHECK_RET(blRv == FALSE, false);

    {
        BOOL isMember = FALSE;

        blRv = ::CheckTokenMembership(xPTR_NULL, adminGroup, &isMember);
        if (blRv == FALSE || isMember == FALSE) {
            isAdmin = false;
        } else {
            isAdmin = true;
        }
    }

    (void_t)::FreeSid(adminGroup);

    xCHECK_RET(!isAdmin, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_loginName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
        char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: User::loginName() - LOGIN_NAME_MAX

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
xINLINE std::tstring_t
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

    tchar_t buff[MAX_PATH + 1] = {0};

    HRESULT hrRv = SHGetFolderPath(xPTR_NULL, CSIDL_PROFILE, xPTR_NULL, 0UL, &buff[0]);
    xTEST_EQ(S_OK == hrRv, true);

    sRv.assign(buff);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
User::_shellPath_impl() const
{
    std::tstring_t sRv;

    LPITEMIDLIST idList = {0};

    HRESULT hrRv = ::SHGetSpecialFolderLocation(xPTR_NULL, CSIDL_WINDOWS, &idList);
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
