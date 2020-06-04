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
    return _getuid();
}
//-------------------------------------------------------------------------------------------------
uint_t
User::_effectiveId_impl() const
{
    return _geteuid();
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
#pragma comment(lib,"advapi32.lib")
//-------------------------------------------------------------------------------------------------
namespace
{

struct HeapDeleter
{
    using pointer = LPVOID;

    void operator ( )(LPVOID p)
    {
        ::HeapFree(::GetProcessHeap(), 0, p);
    }
};
using heap_unique_ptr = std::unique_ptr<LPVOID, HeapDeleter>;

struct HandleDeleter
{
	using pointer = HANDLE;

    void operator () (HANDLE p)
    {
        ::CloseHandle(p);
    }
};
using handle_unique_ptr = std::unique_ptr<HANDLE, HandleDeleter>;

} // namespace
//-------------------------------------------------------------------------------------------------
// https://stackoverflow.com/questions/1594746/win32-equivalent-of-getuid
uint_t
User::_getuid() const
{
    HANDLE process = ::GetCurrentProcess();
    handle_unique_ptr processPtr(process);

    HANDLE token {};
    BOOL openToken = ::OpenProcessToken(process, TOKEN_READ | TOKEN_QUERY_SOURCE, &token);
    if (!openToken) {
        return -1;
    }

    handle_unique_ptr tokenPtr(token);

    return _getUID(token);
}
//-------------------------------------------------------------------------------------------------
uint_t
User::_geteuid() const
{
    HANDLE process = ::GetCurrentProcess();
    HANDLE thread  = ::GetCurrentThread();

    HANDLE token {};
    BOOL openToken = ::OpenThreadToken(thread, TOKEN_READ | TOKEN_QUERY_SOURCE, FALSE, &token);
    if (!openToken &&
		::GetLastError() == ERROR_NO_TOKEN)
	{
        openToken = ::OpenThreadToken(thread, TOKEN_READ | TOKEN_QUERY_SOURCE, TRUE, &token);
        if (!openToken &&
			::GetLastError() == ERROR_NO_TOKEN)
		{
            openToken = ::OpenProcessToken(process, TOKEN_READ | TOKEN_QUERY_SOURCE, &token);
        }
    }

    if (!openToken) {
        return -1;
    }

    handle_unique_ptr tokenPtr(token);

    return _getUID(token);
}
//-------------------------------------------------------------------------------------------------
BOOL
User::_getUserSID(
	HANDLE  token,
	PSID   *sid
) const
{
    if (token == nullptr ||
		token == INVALID_HANDLE_VALUE ||
		sid   == nullptr)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD tokenInformationLength {};
    ::GetTokenInformation(token, TokenUser, nullptr, 0, &tokenInformationLength);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        return FALSE;
    }

    heap_unique_ptr data( ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, tokenInformationLength) );
    if (data.get() == nullptr) {
        return FALSE;
    }

    BOOL getTokenInfo = ::GetTokenInformation(token, TokenUser, data.get(), tokenInformationLength,
		&tokenInformationLength);
    if (! getTokenInfo) {
        return FALSE;
    }

    PTOKEN_USER pTokenUser = reinterpret_cast<PTOKEN_USER>( data.get() );
    DWORD       sidLength  = ::GetLengthSid(pTokenUser->User.Sid);

    heap_unique_ptr sidPtr( ::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sidLength) );

    PSID sidL = (PSID)(sidPtr.get());
    if (sidL == nullptr) {
        return FALSE;
    }

    BOOL copySid = ::CopySid(sidLength, sidL, pTokenUser->User.Sid);
    if (!copySid) {
        return FALSE;
    }

    if ( !IsValidSid(sidL) ) {
        return FALSE;
    }

	// [out]
    *sid = sidL;

    sidPtr.release();

    return TRUE;
}
//-------------------------------------------------------------------------------------------------
uint_t
User::_getUID(
	HANDLE token
) const
{
    PSID sid {};
    BOOL getSID = _getUserSID(token, &sid);
    if (!getSID || !sid) {
        return -1;
    }

    heap_unique_ptr sidPtr((LPVOID)(sid));

	LPWSTR stringSid {};
    BOOL convertSid = ::ConvertSidToStringSidW(sid, &stringSid);
    if (!convertSid) {
        return -1;
    }

    uint_t ret = -1;
    LPCWSTR p = ::wcsrchr(stringSid, L'-');
    if (p && ::iswdigit(p[1])) {
        ++ p;
        ret = ::_wtoi(p);
    }

    ::LocalFree(stringSid);

    return ret;
}
//-------------------------------------------------------------------------------------------------
#if 0

int main()
{
	uint_t uid  = _getuid();
	uint_t euid = _geteuid();

	std::cout
		<< "uid: "  << std::setbase(10) << uid  << std::endl
		<< "euid: " << std::setbase(10) << euid << std::endl
		<< std::endl;

	return EXIT_SUCCESS;
}

#endif
//-------------------------------------------------------------------------------------------------
