/**
 * \file  Ssh2User.h
 * \brief user info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

class Ssh2User
{
public:
                   Ssh2User();
    explicit       Ssh2User(const std::tstring_t &login);
    virtual       ~Ssh2User();

    unsigned int   userUid() const;
    unsigned int   userGid() const;
    std::tstring_t userName() const;
    std::tstring_t homeDir() const;
    std::tstring_t userShell() const;

private:
    passwd *       _userInfo;

    unsigned int   _userUid;
    unsigned int   _userGid;
    std::tstring_t _userName;
    std::tstring_t _homeDir;
    std::tstring_t _userShell;

    void           _construct();
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Csv.cpp"
#endif
