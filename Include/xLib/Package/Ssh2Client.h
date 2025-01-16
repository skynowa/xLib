/**
 * \file  Ssh2Client.h
 * \brief SSH2 client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Net/TcpClient.h>
#include <libssh2.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

struct Ssh2ClientOption
{
    enum class StdFormat
    {
        sfUnknown = 0,
        sfRaw     = 1,
        sfText    = 2,
        sfHtml    = 3
    };
    xUSING_CONST(StdFormat);

    std::tstring_t hostName;
    ushort_t       port;
    std::tstring_t userName;
    std::tstring_t password;
    StdFormat      stdFormat;
};
xUSING_CONST(Ssh2ClientOption);

class Ssh2Client
{
public:
    enum class UserAuth
    {
        uaUnknown             = 0,
        uaPassword            = 1,
        uaKeyboardInteractive = 2,
    };
    xUSING_CONST(UserAuth);

///\name ctors, dtor
///\{
	explicit  Ssh2Client(cSsh2ClientOption &option);
	virtual  ~Ssh2Client();

	xNO_DEFAULT_CONSTRUCT(Ssh2Client);
	xNO_COPY_ASSIGN(Ssh2Client);
///\}

    bool_t         isAlive();
    bool_t         connect();
    void_t         authPassword(cUserAuth userAuth);
    void_t         authPublicKey(std::ctstring_t &keyDirPath);

    bool_t         channelExec(std::ctstring_t &cmd, cbool_t isBlockingMode);
    bool_t         channelReadLine(std::tstring_t *stdOut, std::tstring_t *stdErr);
    void_t         channelClose();

    void_t         disconnect();

    int            lastError();
    std::tstring_t lastErrorFormat();

private:
    cSsh2ClientOption &_option;
    TcpClient          _tcpClient;
    LIBSSH2_SESSION   *_session {};
    LIBSSH2_CHANNEL   *_channel {};

    void_t         _wait(clong_t timeoutSec);
    static
    void_t         _authPassword_OnKeyboardInteractive(const char *name, int nameLen,
                        const char *instruction, int instructionLen, int numPrompts,
                        const LIBSSH2_USERAUTH_KBDINT_PROMPT *prompts,
                        LIBSSH2_USERAUTH_KBDINT_RESPONSE *responses, void_t **abstract);
    void_t         _channelStdStreamReadLine(cbool_t stdOutOrErr, std::tstring_t *stdStream,
                        bool_t *isChannelEof);
    void_t         _convertStdToHtml(std::tstring_t *std);
};

} // namespace
//-------------------------------------------------------------------------------------------------
