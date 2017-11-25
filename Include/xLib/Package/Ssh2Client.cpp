/**
 * \file  Ssh2Client.cpp
 * \brief SSH2 client
 */


#include "Ssh2Client.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Net/DnsClient.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

cint_t         blockSize      = 1024;
cint_t         blockSizeMin   = 1;
std::tstring_t userPassword;
clong_t        waitTimeoutSec = 10;

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
Ssh2Client::Ssh2Client(
    cSsh2ClientData &a_data
) :
    _data     (a_data),
    _tcpClient(),
    _session  (xPTR_NULL),
    _channel  (xPTR_NULL)
{
    userPassword = a_data.password;

    int iRv = ::libssh2_init(0);
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
Ssh2Client::~Ssh2Client()
{
    (void_t)::libssh2_exit();
}
//-------------------------------------------------------------------------------------------------
bool_t
Ssh2Client::isAlive()
{
    std::tstring_t hostAddr;

    if (DnsClient::isAddressIpv4(_data.hostName) ||
        DnsClient::isAddressIpv6(_data.hostName))
    {
        hostAddr = _data.hostName;
    } else {
        DnsClient::hostAddrByName(_data.hostName, &hostAddr);
    }

    return TcpClient::isServerAlive(hostAddr, _data.port);
}
//-------------------------------------------------------------------------------------------------
bool_t
Ssh2Client::connect()
{
    int_t iRv = 0;

    std::tstring_t hostAddr;

    if (DnsClient::isAddressIpv4(_data.hostName) ||
        DnsClient::isAddressIpv6(_data.hostName))
    {
        hostAddr = _data.hostName;
    } else {
        DnsClient::hostAddrByName(_data.hostName, &hostAddr);
    }

    _tcpClient.create(ISocket::afInet, ISocket::tpStream, ISocket::ptIp);
    _tcpClient.connect(hostAddr, _data.port);

    _session = ::libssh2_session_init();
    xTEST_PTR(_session);

    while ((iRv = ::libssh2_session_startup(_session, _tcpClient.handle().get())) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, 0);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::authPassword(
    cUserAuth a_userAuth
)
{
    xTEST_PTR(_session);
    // TODO: StdStreamV2
    ///-- xTEST_DIFF(a_userAuth, uaUnknown);

    int iRv = - 1;

    switch (a_userAuth) {
    case uaPassword:
        while ((iRv = ::libssh2_userauth_password(_session, xT2A(_data.userName).c_str(),
            xT2A(_data.password).c_str())) == LIBSSH2_ERROR_EAGAIN)
        {
            _wait(waitTimeoutSec);
        }

        break;
    case uaKeyboardInteractive:
        while ((iRv = ::libssh2_userauth_keyboard_interactive(_session, xT2A(_data.userName).c_str(),
            &_authPassword_OnKeyboardInteractive)) == LIBSSH2_ERROR_EAGAIN)
        {
            _wait(waitTimeoutSec);
        }

        break;
    case uaUnknown:
    default:
        iRv = - 1;
        break;
    }

    xTEST_EQ_MSG(iRv, 0, lastErrorFormat());
}
//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::authPublicKey(
    std::ctstring_t &a_keyDirPath
)
{
    xTEST_PTR(_session);

    int iRv = - 1;

    std::ctstring_t privateKey = a_keyDirPath + xT("/id_rsa");
    std::ctstring_t publicKey  = a_keyDirPath + xT("/id_rsa.pub");

    while ((iRv = ::libssh2_userauth_publickey_fromfile(_session, xT2A(_data.userName).c_str(),
        xT2A(publicKey).c_str(), xT2A(privateKey).c_str(),
        xT2A(_data.password).c_str())) == LIBSSH2_ERROR_EAGAIN)
    {
        _wait(waitTimeoutSec);
    }

    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
bool_t
Ssh2Client::channelExec(
    std::ctstring_t &a_cmd,
    cbool_t          a_isBlockingMode
)
{
    xTEST_PTR(_session);
    xTEST_PTR_FAIL(_channel);
    xTEST(!a_cmd.empty());
    xTEST_NA(a_isBlockingMode);

    ssize_t iRv = - 1;

    _channel = ::libssh2_channel_open_session(_session);
    xTEST_PTR(_channel);

    (void_t)::libssh2_channel_set_blocking(_channel, static_cast<int>(a_isBlockingMode));

#if 0
    while ((iRv = ::libssh2_channel_exec(_channel, xT2A(a_cmd).c_str())) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, (ssize_t)0);
#else
	// % echo $0
	std::cstring_t shellName = "zsh";

    while ((iRv = ::libssh2_channel_request_pty(_channel, shellName.c_str())) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, (ssize_t)0);

    while ((iRv = ::libssh2_channel_shell(_channel)) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, (ssize_t)0);

    while ((iRv = ::libssh2_channel_write(_channel, xT2A(a_cmd).c_str(), a_cmd.size())) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, (ssize_t)a_cmd.size());
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Ssh2Client::channelReadLine(
    std::tstring_t *a_stdOut,
    std::tstring_t *a_stdErr
)
{
    xTEST_PTR(_session);
    xTEST_PTR(_channel);
    xTEST_PTR(a_stdOut);
    xTEST_PTR(a_stdErr);

    std::tstring_t stdOut;
    bool_t         isStdOutChannelEof = false;
    _channelStdStreamReadLine(true, &stdOut, &isStdOutChannelEof);

    std::tstring_t stdErr;
    bool_t         isStdErrChannelEof = false;
    _channelStdStreamReadLine(false, &stdErr, &isStdErrChannelEof);

    if (isStdOutChannelEof && stdOut.empty() /* && isStdErrChannelEof && stdErr.empty() */) {
        a_stdOut->clear();
        a_stdErr->clear();

        return false;
    }

    // data format
    switch (_data.stdFormat) {
    case Ssh2ClientData::sfRaw:
        // skip
        break;
    case Ssh2ClientData::sfText:
        // TODO: sfText
        break;
    case Ssh2ClientData::sfHtml:
        if ( !stdErr.empty() ) {
            Trace() << "\n" << stdErr;

            FileLog log;
            log.setFilePath("./log.log");
            log << "\n" << stdErr << "\n";
        }

        _convertStdToHtml(&stdOut);
        _convertStdToHtml(&stdErr);

        if ( !stdErr.empty() ) {
            Trace() << "\n" << stdErr;

            FileLog log;
            log.setFilePath("./log.log");
            log << "\n" << stdErr << "\n\n\n";
        }
        break;
    case Ssh2ClientData::sfUnknown:
    default:
        xTEST(false);
        break;
    }

    // out
    std::swap(stdOut, *a_stdOut);
    std::swap(stdErr, *a_stdErr);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::_channelStdStreamReadLine(
    cbool_t         a_stdOutOrErr,  ///< std::out (true) ot std::cerr (false) stream
    std::tstring_t *a_stdStream,    ///< std stream
    bool_t         *a_isChannelEof  ///< is channel EOF
)
{
    Utils::ptrAssignT(a_stdStream, std::tstring_t());
    Utils::ptrAssignT(a_isChannelEof, false);

    char block[blockSizeMin + 1] = {0};

    for ( ; ; ) {
        ssize_t read = 0;
        if (a_stdOutOrErr) {
            read = ::libssh2_channel_read(_channel, block, blockSizeMin);
            // Trace() << "stdout: " << xTRACE_VAR(read);
        } else {
            read = ::libssh2_channel_read_stderr(_channel, block, blockSizeMin);
            // Trace() << "stderr: " << xTRACE_VAR(read);
        }

        if (read == LIBSSH2_ERROR_EAGAIN) {
            _wait(waitTimeoutSec);
            *a_isChannelEof = false;

            break;
        }

        *a_isChannelEof = static_cast<bool_t>( ::libssh2_channel_eof(_channel) );
        if (*a_isChannelEof && read == 0) {
            Trace() << "libssh2_channel_eof: breaking";
            break;
        }

        xCHECK_DO(read <= 0, break);

        if (read < blockSizeMin) {
            block[read] = '\0';
        }

        if (block[0] == Const::nl()[0]) {
            break;
        }

        *a_stdStream += xA2T(block);
    } // for ( ; ; )
}
//-------------------------------------------------------------------------------------------------


void_t
Ssh2Client::channelClose()
{
    xTEST_PTR(_channel);

    int iRv = - 1;

    while ((iRv = ::libssh2_channel_close(_channel)) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, 0);

    while ((iRv = ::libssh2_channel_free(_channel)) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    _channel = xPTR_NULL;
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::disconnect()
{
    xTEST_PTR(_session);

    int iRv = - 1;

    while ((iRv = ::libssh2_session_disconnect(_session, "Ssh2Client disconnected.")) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    xTEST_EQ(iRv, 0);

    _tcpClient.close();

    while ((iRv = ::libssh2_session_free(_session)) == LIBSSH2_ERROR_EAGAIN) {
        _wait(waitTimeoutSec);
    }
    _session = xPTR_NULL;
    xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
int
Ssh2Client::lastError()
{
    return ::libssh2_session_last_errno(_session);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Ssh2Client::lastErrorFormat()
{
    std::string asRv;

    char *error     = xPTR_NULL;
    int   errorSize = 0;

    int_t iRv = ::libssh2_session_last_error(_session, &error, &errorSize, 0);
    xUNUSED(iRv);

    if (error == xPTR_NULL) {
        asRv = "[Unknown]";
    } else {
        asRv.assign(error, static_cast<std::size_t>( errorSize ));
    }

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::_wait(
    clong_t a_timeoutSec ///< timeout (seconds)
)
{
    int iRv = 0;

    timeval timeout;
    timeout.tv_sec  = a_timeoutSec;
    timeout.tv_usec = 0;

    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(_tcpClient.handle().get(), &fd);

    // now make sure we wait in the correct direction
    cint_t directions = ::libssh2_session_block_directions(_session);

    fd_set *readfd = xPTR_NULL;
    if (directions & LIBSSH2_SESSION_BLOCK_INBOUND) {
        readfd = &fd;
    }

    fd_set *writefd = xPTR_NULL;
    if (directions & LIBSSH2_SESSION_BLOCK_OUTBOUND) {
        writefd = &fd;
    }

    iRv = ::select(_tcpClient.handle().get() + 1, readfd, writefd, xPTR_NULL, &timeout);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Ssh2Client::_authPassword_OnKeyboardInteractive(
    const char                           *a_name,
    int                                   a_nameLen,
    const char                           *a_instruction,
    int                                   a_instructionLen,
    int                                   a_numPrompts,
    const LIBSSH2_USERAUTH_KBDINT_PROMPT *a_prompts,
    LIBSSH2_USERAUTH_KBDINT_RESPONSE     *a_responses,
    void_t                              **a_abstract
)
{
    xUNUSED(a_name);
    xUNUSED(a_nameLen);
    xUNUSED(a_instruction);
    xUNUSED(a_instructionLen);

    if (a_numPrompts == 1) {
        xTEST(!userPassword.empty());

        a_responses[0].text   = ::strdup( xT2A(userPassword).c_str() );
        a_responses[0].length = static_cast<uint_t>( userPassword.size() * sizeof(std::tstring_t::value_type) );
    }

    xUNUSED(a_prompts);
    xUNUSED(a_abstract);
}
//-------------------------------------------------------------------------------------------------
void_t
Ssh2Client::_convertStdToHtml(
    std::tstring_t *a_std
)
{
    *a_std = String::replaceAll(*a_std, xT("\n"), xT("<br />"));

    // http://misc.flogisoft.com/bash/tip_colors_and_formatting
    // http://ascii-table.com/ansi-escape-sequences.php
    std::map_tstring_t colorsCodes;

    // Attributes set
    colorsCodes[xT("\e[1m")]    = xT(""); // Bold/Bright
    colorsCodes[xT("\e[2m")]    = xT(""); // Dim
    colorsCodes[xT("\e[4m")]    = xT(""); // Underlined
    colorsCodes[xT("\e[5m")]    = xT(""); // Blink
    colorsCodes[xT("\e[7m")]    = xT(""); // Reverse (invert the foreground and background colors)
    colorsCodes[xT("\e[8m")]    = xT(""); // Hidden (usefull for passwords)

    // Attributes Reset
    colorsCodes[xT("\e[0m")]    = xT(""); // Reset all attributes
    colorsCodes[xT("\e[21m")]   = xT(""); // Reset bold/bright
    colorsCodes[xT("\e[22m")]   = xT(""); // Reset dim
    colorsCodes[xT("\e[24m")]   = xT(""); // Reset underlined
    colorsCodes[xT("\e[25m")]   = xT(""); // Reset blink
    colorsCodes[xT("\e[27m")]   = xT(""); // Reset reverse
    colorsCodes[xT("\e[28m")]   = xT(""); // Reset hidden

    // Regular
    colorsCodes[xT("\e[0;30m")] = xT("Black");
    colorsCodes[xT("\e[0;31m")] = xT("Red");
    colorsCodes[xT("\e[0;32m")] = xT("Green");
    colorsCodes[xT("\e[0;33m")] = xT("Yellow");
    colorsCodes[xT("\e[0;34m")] = xT("Blue");
    colorsCodes[xT("\e[0;35m")] = xT("Purple");
    colorsCodes[xT("\e[0;36m")] = xT("Cyan");
    colorsCodes[xT("\e[0;37m")] = xT("White");

    colorsCodes[xT("\e[0;1;30m")] = xT("Black");
    colorsCodes[xT("\e[0;1;31m")] = xT("Red");
    colorsCodes[xT("\e[0;1;32m")] = xT("Green");
    colorsCodes[xT("\e[0;1;33m")] = xT("Yellow");
    colorsCodes[xT("\e[0;1;34m")] = xT("Blue");
    colorsCodes[xT("\e[0;1;35m")] = xT("Purple");
    colorsCodes[xT("\e[0;1;36m")] = xT("Cyan");
    colorsCodes[xT("\e[0;1;37m")] = xT("White");

    // Bold
    colorsCodes[xT("\e[1;30m")] = xT("Black");
    colorsCodes[xT("\e[1;31m")] = xT("Red");
    colorsCodes[xT("\e[1;32m")] = xT("Green");
    colorsCodes[xT("\e[1;33m")] = xT("Yellow");
    colorsCodes[xT("\e[1;34m")] = xT("Blue");
    colorsCodes[xT("\e[1;35m")] = xT("Purple");
    colorsCodes[xT("\e[1;36m")] = xT("Cyan");
    colorsCodes[xT("\e[1;37m")] = xT("White");

    // Underline
    colorsCodes[xT("\e[4;30m")] = xT("Black");
    colorsCodes[xT("\e[4;31m")] = xT("Red");
    colorsCodes[xT("\e[4;32m")] = xT("Green");
    colorsCodes[xT("\e[4;33m")] = xT("Yellow");
    colorsCodes[xT("\e[4;34m")] = xT("Blue");
    colorsCodes[xT("\e[4;35m")] = xT("Purple");
    colorsCodes[xT("\e[4;36m")] = xT("Cyan");
    colorsCodes[xT("\e[4;37m")] = xT("White");

    // Background
    colorsCodes[xT("\e[40m")]   = xT("Black");
    colorsCodes[xT("\e[41m")]   = xT("Red");
    colorsCodes[xT("\e[42m")]   = xT("Green");
    colorsCodes[xT("\e[43m")]   = xT("Yellow");
    colorsCodes[xT("\e[44m")]   = xT("Blue");
    colorsCodes[xT("\e[45m")]   = xT("Purple");
    colorsCodes[xT("\e[46m")]   = xT("Cyan");
    colorsCodes[xT("\e[47m")]   = xT("White");

    xFOR_EACH_CONST(std::map_tstring_t, it, colorsCodes) {
        std::tstring_t htmlTag;
    #if 0
        {
            if (it->first == xT("\e[0m")) {
                htmlTag = xT("</font>");
            } else {
                htmlTag = xT("<font color=\"") + it->second + xT("\">");
            }
        }
    #endif

        *a_std = String::replaceAll(*a_std, it->first, htmlTag);
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
