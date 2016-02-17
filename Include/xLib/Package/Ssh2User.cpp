/**
 * \file  Ssh2User.cpp
 * \brief user info
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2User.h"
#endif

xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2User::Ssh2User() :
    _userInfo (xPTR_NULL),
    _userUid  (0U),
    _userGid  (0U),
    _userName (),
    _homeDir  (),
    _userShell()
{
	_construct();
}
//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2User::Ssh2User(
    std::ctstring_t &a_login
) :
    _userInfo (xPTR_NULL),
    _userName (),
    _homeDir  (),
    _userUid  (0U),
    _userGid  (0U),
    _userShell()
{
	_userInfo = ::getpwnam( a_login.c_str() );
	xTEST_PTR(_userInfo);

	_construct();
}
//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2User::~Ssh2User()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
Ssh2User::userUid() const
{
    return _userUid;
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
Ssh2User::userGid() const
{
    return _userGid;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Ssh2User::userName() const
{
    return _userName;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Ssh2User::homeDir() const
{
    return _homeDir;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Ssh2User::userShell() const
{
    return _userShell;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void
Ssh2User::_construct()
{
    _userInfo = ::getpwuid( ::getuid() );
    xTEST_PTR(_userInfo);

    _userUid   = static_cast<uint_t>( _userInfo->pw_uid );
    _userGid   = static_cast<uint_t>( _userInfo->pw_gid );
    _userName  = std::tstring_t(_userInfo->pw_name);
    _homeDir   = std::tstring_t(_userInfo->pw_dir);
    _userShell = std::tstring_t(_userInfo->pw_shell);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, package)
