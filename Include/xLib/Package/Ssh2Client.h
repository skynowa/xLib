/**
 * \file  Ssh2Client.h
 * \brief SSH2 client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <libssh2.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

struct Ssh2ClientData
{
    enum StdFormat
    {
        sfUnknown = 0,
        sfRaw     = 1,
        sfText    = 2,
        sfHtml    = 3
    };
    xTYPEDEF_CONST(StdFormat);

    std::tstring_t hostName;
    ushort_t       port;
    std::tstring_t userName;
    std::tstring_t password;
    StdFormat      stdFormat;
};
xTYPEDEF_CONST(Ssh2ClientData);

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

    explicit       Ssh2Client(cSsh2ClientData &data);
    virtual       ~Ssh2Client();

    bool           connect();
    void           authPassword(cUserAuth userAuth);
    void           authPublicKey(std::ctstring_t &keyDirPath);
    bool           executeCmd(std::ctstring_t &cmd, std::tstring_t *stdOut, std::tstring_t *stdErr);
    void           disconnect();

    int            lastError();
    std::tstring_t lastErrorFormat();

private:
    cSsh2ClientData &_data;
    int            _socket;
    LIBSSH2_SESSION * _session;

    void           _convertStdToHtml(std::tstring_t *std);
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2Client.cpp"
#endif
