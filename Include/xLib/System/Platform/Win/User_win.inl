/**
 * \file  User_win.inl
 * \brief
 */


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

    xTRACE_NOT_IMPLEMENTED;

    return 0;
}
//-------------------------------------------------------------------------------------------------
bool_t
User::_isAdmin_impl() const
{
    SID_IDENTIFIER_AUTHORITY ntAuthority {SECURITY_NT_AUTHORITY};
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
        sRv = _name_impl();
        if ( !sRv.empty() ) {
            return sRv;
        }
    }

    // try system environment
	{
	#if 0
		const std::array envVars{xT("USERNAME")};

		for (const auto &it_envVar : envVars) {
			Environment env(it_envVar);

			bool_t bRv = env.isExists();
			xCHECK_DO(!bRv, continue);

			sRv = env.value();

			return sRv;
		}
	#else
		Environments envs;

		std::cvec_tstring_t envVars{xT("USERNAME")};
		sRv = envs.findFirstOf(envVars);

		return sRv;
	#endif
	}

    return {};
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
User::_name_impl() const
{
    std::tstring_t sRv;

    DWORD   buffSize             {xUSER_NAME_MAX + 1};
    tchar_t buff[xUSER_NAME_MAX] {};

    BOOL blRv = ::GetUserName(&buff[0], &buffSize);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, buffSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

struct HeapDeleter
{
	using pointer = LPVOID;

    void operator () (LPVOID p)
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
    if (openToken == FALSE) {
        return static_cast<uint_t>(-1);	// TODO: uint_t cast
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
    if (openToken == FALSE &&
        ::GetLastError() == ERROR_NO_TOKEN)
	{
        openToken = ::OpenThreadToken(thread, TOKEN_READ | TOKEN_QUERY_SOURCE, TRUE, &token);
        if (openToken == FALSE &&
			::GetLastError() == ERROR_NO_TOKEN)
		{
            openToken = ::OpenProcessToken(process, TOKEN_READ | TOKEN_QUERY_SOURCE, &token);
        }
    }

    if (openToken == FALSE) {
        return static_cast<uint_t>(-1);	// TODO: uint_t cast
    }

    handle_unique_ptr tokenPtr(token);

    return _getUID(token);
}
//-------------------------------------------------------------------------------------------------
BOOL
User::_getUserSID(
	HANDLE  token,	///<
	PSID   *out_sid	///< [out]
) const
{
    if (token   == nullptr ||
        token   == INVALID_HANDLE_VALUE ||
        out_sid == nullptr)
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
    if (getTokenInfo == FALSE) {
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
    if (copySid == FALSE) {
        return FALSE;
    }

    if ( !IsValidSid(sidL) ) {
        return FALSE;
    }

	// [out]
    *out_sid = sidL;

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
    if (getSID == FALSE || sid == FALSE) {
        return static_cast<uint_t>(-1);	// TODO: uint_t cast
    }

    heap_unique_ptr sidPtr((LPVOID)sid);

	LPWSTR stringSid {};
    BOOL convertSid = ::ConvertSidToStringSidW(sid, &stringSid);
    if (convertSid == FALSE) {
        return static_cast<uint_t>(-1);	// TODO: uint_t cast
    }

    uint_t ret = static_cast<uint_t>(-1);	// TODO: uint_t cast

    LPCWSTR p = ::wcsrchr(stringSid, L'-');
    if (p != nullptr &&
        ::iswdigit(p[1]))
    {
        ++ p;
        ret = ::_wtoi(p);
    }

    ::LocalFree(stringSid);

    return ret;
}
//-------------------------------------------------------------------------------------------------

} // namespace
