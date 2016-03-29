/**
 * \file   User.h
 * \brief  user info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, system)

class User
    ///< user info
{
public:
                   User();
        ///< constructor
    virtual       ~User();
        ///< destructor

    bool_t         isAdmin() const xWARN_UNUSED_RV;
        ///< is current user an admin
    std::tstring_t loginName() const xWARN_UNUSED_RV;
        ///< login name
    std::tstring_t name() const xWARN_UNUSED_RV;
        ///< get the name of the user associated with the current thread
    uint_t         userId() const;
        ///< user ID
    uint_t         groupId() const;
        ///< group ID
    std::tstring_t homeDir() const;
        ///< get home directory
    std::tstring_t shellPath() const;

private:
#if xENV_UNIX
    void_t         _passwd(std::string *pw_name, std::string *pw_passwd, uid_t *pw_uid,
                       gid_t *pw_gid, std::string *pw_gecos, std::string *pw_dir,
                       std::string *pw_shell) const;
        ///< get password file entry
#endif

    xNO_COPY_ASSIGN(User)

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();

    bool_t         _isAdmin_impl() const xWARN_UNUSED_RV;
    std::tstring_t _loginName_impl() const xWARN_UNUSED_RV;
    std::tstring_t _name_impl() const xWARN_UNUSED_RV;
    uint_t         _userId_impl() const xWARN_UNUSED_RV;
    uint_t         _groupId_impl() const xWARN_UNUSED_RV;
    std::tstring_t _homeDir_impl() const xWARN_UNUSED_RV;
    std::tstring_t _shellPath_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "User.cpp"
#endif
