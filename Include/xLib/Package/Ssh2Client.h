/**
 * \file  Ssh2Client.h
 * \brief SSH2 client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <libssh2.h>
#include "Ssh2User.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

class Ssh2Client
{
public:
    enum UserAuth
    {
        uaUnknown             = 0,
        uaPassword            = 1,
        uaKeyboardInteractive = 2,
    };
    xTYPEDEF_CONST(UserAuth);

                   Ssh2Client();
    virtual       ~Ssh2Client();

    void           construct(std::ctstring_t &hostName, cushort_t &port, std::ctstring_t &userName,
                        std::ctstring_t &password, cbool_t &isUseKey, std::ctstring_t &keyDirPath);

    bool           connect();
    void           authPassword(cUserAuth userAuth);
    void           authPublicKey();
    bool           executeCmd(std::ctstring_t &cmd, std::tstring_t *stdOut, std::tstring_t *stdErr);
    void           disconnect();

    int            lastError();
    std::tstring_t lastErrorFormat();

private:
    LIBSSH2_SESSION * _session;
    int            _socket;

    Ssh2User       _user;

    std::tstring_t _hostName;
    ushort_t       _port;
    std::tstring_t _userName;
    std::tstring_t _password;
    bool           _isUseKey;
    std::tstring_t _keyDirPath;

};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2Client.cpp"
#endif
