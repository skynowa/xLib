/**
 * \file   User.h
 * \brief  user info
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/Path.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class User
    ///< user info
{
public:
///\name ctors, dtor
///\{
			 User() = default;
	virtual ~User() = default;

	xNO_COPY_ASSIGN(User);
///\}

    uint_t         id() const;
        ///< It is account of owner of this process. It defines which files that this process
        /// has access to
    uint_t         effectiveId() const;
        ///< It is normally same as Real UserID, but sometimes it is changed to enable
        ///< a non-privileged user to access files that can only be accessed by root
    uint_t         groupId() const;
        ///< group ID
    bool_t         isAdmin() const;
        ///< is current user an admin
    std::tstring_t loginName() const;
        ///< login name
    std::tstring_t name() const;
        ///< get the name of the user associated with the current thread

xPLATFORM_IMPL:
    uint_t         _id_impl() const;
    uint_t         _effectiveId_impl() const;
    uint_t         _groupId_impl() const;
    bool_t         _isAdmin_impl() const;
    std::tstring_t _loginName_impl() const;
    std::tstring_t _name_impl() const;

private:
#if   xENV_WIN
     uint_t _getuid() const;
     uint_t _geteuid() const;

     BOOL   _getUserSID(HANDLE token, PSID *sid) const;
     uint_t _getUID(HANDLE token) const;
#elif xENV_UNIX
    void_t _passwd(std::string *pw_name, std::string *pw_passwd, uid_t *pw_uid, gid_t *pw_gid,
				std::string *pw_dir, std::string *pw_shell) const;
        ///< get password file entry

    friend class xl::fs::Path; // for _passwd()
#endif
};

} // namespace
//-------------------------------------------------------------------------------------------------
