/**
 * \file  Ssh2Client.cpp
 * \brief SSH2 client
 */


#include "Ssh2Client.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Net/DnsClient.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Log/LogStream.h>


namespace xl::package
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

cint_t         blockSize      = 1024;
cint_t         blockSizeMin   = 1;
std::tstring_t userPassword;
clong_t        waitTimeoutSec = 10;

}
//-------------------------------------------------------------------------------------------------
Ssh2Client::Ssh2Client(
    cSsh2ClientOption &a_option
) :
    _option(a_option)
{
    userPassword = a_option.password;

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

    if (DnsClient::isAddressIpv4(_option.hostName) ||
        DnsClient::isAddressIpv6(_option.hostName))
    {
        hostAddr = _option.hostName;
    } else {
        DnsClient::hostAddrByName(_option.hostName, &hostAddr);
    }

    return TcpClient::isServerAlive(hostAddr, _option.port);
}
//-------------------------------------------------------------------------------------------------
bool_t
Ssh2Client::connect()
{
    int_t iRv = 0;

    std::tstring_t hostAddr;

    if (DnsClient::isAddressIpv4(_option.hostName) ||
        DnsClient::isAddressIpv6(_option.hostName))
    {
        hostAddr = _option.hostName;
    } else {
        DnsClient::hostAddrByName(_option.hostName, &hostAddr);
    }

    _tcpClient.create(ISocket::AddressFamily::afInet, ISocket::Type::tpStream, ISocket::Protocol::ptIp);
    _tcpClient.connect(hostAddr, _option.port);

    _session = ::libssh2_session_init();
    xTEST_PTR(_session);

    // \see [Win] UINT_PTR - _wait()
    while ((iRv = ::libssh2_session_startup(_session, static_cast<int_t>( _tcpClient.handle().get() ))) == LIBSSH2_ERROR_EAGAIN) {
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
    // TODO: [skynowa] StdStreamV2
    ///-- xTEST_DIFF(a_userAuth, uaUnknown);

    int iRv = - 1;

    switch (a_userAuth) {
    case UserAuth::uaPassword:
        while ((iRv = ::libssh2_userauth_password(_session, xT2A(_option.userName).c_str(),
            xT2A(_option.password).c_str())) == LIBSSH2_ERROR_EAGAIN)
        {
            _wait(waitTimeoutSec);
        }

        break;
    case UserAuth::uaKeyboardInteractive:
        while ((iRv = ::libssh2_userauth_keyboard_interactive(_session, xT2A(_option.userName).c_str(),
            &_authPassword_OnKeyboardInteractive)) == LIBSSH2_ERROR_EAGAIN)
        {
            _wait(waitTimeoutSec);
        }

        break;
    case UserAuth::uaUnknown:
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

    while ((iRv = ::libssh2_userauth_publickey_fromfile(_session, xT2A(_option.userName).c_str(),
        xT2A(publicKey).c_str(), xT2A(privateKey).c_str(),
        xT2A(_option.password).c_str())) == LIBSSH2_ERROR_EAGAIN)
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

    xCHECK_RET(a_stdOut == nullptr, false);
    xCHECK_RET(a_stdErr == nullptr, false);

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
    switch (_option.stdFormat) {
    case Ssh2ClientOption::StdFormat::sfRaw:
        // skip
        break;
    case Ssh2ClientOption::StdFormat::sfText:
        // TODO: [skynowa] sfText
        break;
    case Ssh2ClientOption::StdFormat::sfHtml:
        if ( !stdErr.empty() ) {
            LogCout() << "\n" << stdErr;
        }

        _convertStdToHtml(&stdOut);
        _convertStdToHtml(&stdErr);

        if ( !stdErr.empty() ) {
            LogCout() << "\n" << stdErr;
        }
        break;
    case Ssh2ClientOption::StdFormat::sfUnknown:
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
            // LogCout() << "stdout: " << xTRACE_VAR(read);
        } else {
            read = ::libssh2_channel_read_stderr(_channel, block, blockSizeMin);
            // LogCout() << "stderr: " << xTRACE_VAR(read);
        }

        if (read == LIBSSH2_ERROR_EAGAIN) {
            _wait(waitTimeoutSec);
            *a_isChannelEof = false;

            break;
        }

        *a_isChannelEof = static_cast<bool_t>( ::libssh2_channel_eof(_channel) );
        if (*a_isChannelEof && read == 0) {
            LogCout() << "libssh2_channel_eof: breaking";
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
    _channel = nullptr;
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
    _session = nullptr;
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

    char *error     = nullptr;
    int   errorSize = 0;

    int_t iRv = ::libssh2_session_last_error(_session, &error, &errorSize, 0);
    xUNUSED(iRv);

    if (error == nullptr) {
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

    fd_set *readfd {};
    if (directions & LIBSSH2_SESSION_BLOCK_INBOUND) {
        readfd = &fd;
    }

    fd_set *writefd {};
    if (directions & LIBSSH2_SESSION_BLOCK_OUTBOUND) {
        writefd = &fd;
    }

   /**
    * [Win] UINT_PTR - is not a pointer, it's a simple unsigned integer
    *
    * https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tsts/f959534d-51f2-4103-8fb5-812620efe49b
    *
    * BUT it's big enough to hold a pointer.
    * In other words, it's safe to cast a pointer to UINT_PTR or INT_PTR and back to a pointer.
    * On the other hand, it's not safe to cast a pointer to a normal unsigned int, or int.
    */

    iRv = ::select(static_cast<int_t>(_tcpClient.handle().get() + 1), readfd, writefd, nullptr, &timeout);
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

#if xENV_UNIX
    // http://misc.flogisoft.com/bash/tip_colors_and_formatting
    // http://ascii-table.com/ansi-escape-sequences.php
    std::map_tstring_t colorsCodes;

    // Attributes set
    colorsCodes[xT("\033[1m")]    = xT(""); // Bold/Bright
    colorsCodes[xT("\033[2m")]    = xT(""); // Dim
    colorsCodes[xT("\033[4m")]    = xT(""); // Underlined
    colorsCodes[xT("\033[5m")]    = xT(""); // Blink
    colorsCodes[xT("\033[7m")]    = xT(""); // Reverse (invert the foreground and background colors)
    colorsCodes[xT("\033[8m")]    = xT(""); // Hidden (usefull for passwords)

    // Attributes Reset
    colorsCodes[xT("\033[0m")]    = xT(""); // Reset all attributes
    colorsCodes[xT("\033[21m")]   = xT(""); // Reset bold/bright
    colorsCodes[xT("\033[22m")]   = xT(""); // Reset dim
    colorsCodes[xT("\033[24m")]   = xT(""); // Reset underlined
    colorsCodes[xT("\033[25m")]   = xT(""); // Reset blink
    colorsCodes[xT("\033[27m")]   = xT(""); // Reset reverse
    colorsCodes[xT("\033[28m")]   = xT(""); // Reset hidden

    // Regular
    colorsCodes[xT("\033[0;30m")] = xT("Black");
    colorsCodes[xT("\033[0;31m")] = xT("Red");
    colorsCodes[xT("\033[0;32m")] = xT("Green");
    colorsCodes[xT("\033[0;33m")] = xT("Yellow");
    colorsCodes[xT("\033[0;34m")] = xT("Blue");
    colorsCodes[xT("\033[0;35m")] = xT("Purple");
    colorsCodes[xT("\033[0;36m")] = xT("Cyan");
    colorsCodes[xT("\033[0;37m")] = xT("White");

    colorsCodes[xT("\033[0;1;30m")] = xT("Black");
    colorsCodes[xT("\033[0;1;31m")] = xT("Red");
    colorsCodes[xT("\033[0;1;32m")] = xT("Green");
    colorsCodes[xT("\033[0;1;33m")] = xT("Yellow");
    colorsCodes[xT("\033[0;1;34m")] = xT("Blue");
    colorsCodes[xT("\033[0;1;35m")] = xT("Purple");
    colorsCodes[xT("\033[0;1;36m")] = xT("Cyan");
    colorsCodes[xT("\033[0;1;37m")] = xT("White");

    // Bold
    colorsCodes[xT("\033[1;30m")] = xT("Black");
    colorsCodes[xT("\033[1;31m")] = xT("Red");
    colorsCodes[xT("\033[1;32m")] = xT("Green");
    colorsCodes[xT("\033[1;33m")] = xT("Yellow");
    colorsCodes[xT("\033[1;34m")] = xT("Blue");
    colorsCodes[xT("\033[1;35m")] = xT("Purple");
    colorsCodes[xT("\033[1;36m")] = xT("Cyan");
    colorsCodes[xT("\033[1;37m")] = xT("White");

    // Underline
    colorsCodes[xT("\033[4;30m")] = xT("Black");
    colorsCodes[xT("\033[4;31m")] = xT("Red");
    colorsCodes[xT("\033[4;32m")] = xT("Green");
    colorsCodes[xT("\033[4;33m")] = xT("Yellow");
    colorsCodes[xT("\033[4;34m")] = xT("Blue");
    colorsCodes[xT("\033[4;35m")] = xT("Purple");
    colorsCodes[xT("\033[4;36m")] = xT("Cyan");
    colorsCodes[xT("\033[4;37m")] = xT("White");

    // Background
    colorsCodes[xT("\033[40m")]   = xT("Black");
    colorsCodes[xT("\033[41m")]   = xT("Red");
    colorsCodes[xT("\033[42m")]   = xT("Green");
    colorsCodes[xT("\033[43m")]   = xT("Yellow");
    colorsCodes[xT("\033[44m")]   = xT("Blue");
    colorsCodes[xT("\033[45m")]   = xT("Purple");
    colorsCodes[xT("\033[46m")]   = xT("Cyan");
    colorsCodes[xT("\033[47m")]   = xT("White");

    for (const auto &[code, name] : colorsCodes) {
        std::tstring_t htmlTag;
        {
            if (code == xT("\033[0m")) {
                htmlTag = xT("</font>");
            } else {
                htmlTag = xT("<font color=\"") + name + xT("\">");
            }
        }

        *a_std = String::replaceAll(*a_std, code, htmlTag);
    }
#else
    // TODO: [win] _convertStdToHtml
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
