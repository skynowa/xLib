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

    std::tstring_t loginName() const;
        ///< login name
    uint_t         userId() const;
        ///< user ID
    uint_t         groupId() const;
        ///< group ID
    std::tstring_t homeDir() const;
        ///< initial working directory
    std::tstring_t shell() const;
        ///< program to use as shell

private:
    xNO_COPY_ASSIGN(User)

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();

    std::tstring_t _loginName_impl() const xWARN_UNUSED_RV;
    uint_t         _userId_impl() const xWARN_UNUSED_RV;
    uint_t         _groupId_impl() const xWARN_UNUSED_RV;
    std::tstring_t _homeDir_impl() const xWARN_UNUSED_RV;
    std::tstring_t _shell_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "User.cpp"
#endif
