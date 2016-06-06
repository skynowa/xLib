/**
 * \file  Ssh2Client.cpp
 * \brief SSH2 client
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2Client.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Net/DnsClient.h>
#include <xLib/Log/Trace.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>


xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

cint_t         blockSize    = 1024;
cint_t         blockSizeMin = 1;
std::tstring_t userPassword;

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
xINLINE
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
    xTEST_GR(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2Client::~Ssh2Client()
{
    (void)::libssh2_exit();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::isAlive()
{
    std::tstring_t hostAddr;

    if (DnsClient::isAddressIpv4(_data.hostName) || DnsClient::isAddressIpv6(_data.hostName)) {
        hostAddr = _data.hostName;
    } else {
        DnsClient::hostAddrByName(_data.hostName, &hostAddr);
    }

    return TcpClient::isServerAlive(hostAddr, _data.port);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::connect()
{
    int_t iRv = 0;

    std::tstring_t hostAddr;

    if (DnsClient::isAddressIpv4(_data.hostName) || DnsClient::isAddressIpv6(_data.hostName)) {
        hostAddr = _data.hostName;
    } else {
        DnsClient::hostAddrByName(_data.hostName, &hostAddr);
    }

    _tcpClient.create(Socket::afInet, Socket::tpStream, Socket::ptIp);
    _tcpClient.connect(hostAddr, _data.port);

    _session = ::libssh2_session_init();
    xTEST_PTR(_session);

    iRv = ::libssh2_session_startup(_session, _tcpClient.handle());
    xTEST(iRv == 0);

    return true;
}
//-------------------------------------------------------------------------------------------------
static void
onkeyboardInteractive(
    const char                           *a_name,
    int                                   a_nameLen,
    const char                           *a_instruction,
    int                                   a_instructionLen,
    int                                   a_numPrompts,
    const LIBSSH2_USERAUTH_KBDINT_PROMPT *a_prompts,
    LIBSSH2_USERAUTH_KBDINT_RESPONSE     *a_responses,
    void                                **a_abstract
)
{
    xUNUSED(a_name);
    xUNUSED(a_nameLen);
    xUNUSED(a_instruction);
    xUNUSED(a_instructionLen);

    if (a_numPrompts == 1) {
        xTEST(!userPassword.empty());

        a_responses[0].text   = ::strdup( xT2A(userPassword).c_str() );
        a_responses[0].length = userPassword.size() * sizeof(std::tstring_t::value_type);
    }

    xUNUSED(a_prompts);
    xUNUSED(a_abstract);
}
//-------------------------------------------------------------------------------------------------
xINLINE void
Ssh2Client::authPassword(
    cUserAuth a_userAuth
)
{
    xTEST_PTR(_session);
    xTEST(a_userAuth != uaUnknown);

    int iRv = - 1;

    switch (a_userAuth) {
    case uaPassword:
        iRv = ::libssh2_userauth_password(_session, xT2A(_data.userName).c_str(), xT2A(_data.password).c_str());
        break;
    case uaKeyboardInteractive:
        iRv = ::libssh2_userauth_keyboard_interactive(_session, xT2A(_data.userName).c_str(),
                &onkeyboardInteractive);
        break;
    case uaUnknown:
    default:
        iRv = - 1;
        break;
    }

    xTEST_MSG(0 == iRv, lastErrorFormat());
}
//-------------------------------------------------------------------------------------------------
xINLINE void
Ssh2Client::authPublicKey(
    std::ctstring_t &a_keyDirPath
)
{
    xTEST_PTR(_session);

    int iRv = - 1;

    std::ctstring_t privateKey = a_keyDirPath + xT("/id_rsa");
    std::ctstring_t publicKey  = a_keyDirPath + xT("/id_rsa.pub");

    iRv = ::libssh2_userauth_publickey_fromfile(_session, xT2A(_data.userName).c_str(),
        xT2A(publicKey).c_str(), xT2A(privateKey).c_str(), xT2A(_data.password).c_str());
    xTEST(0 == iRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::channelExec(
    std::ctstring_t &a_cmd,
    cbool_t          a_isBlockingMode
)
{
    xTEST_PTR(_session);
    xTEST_PTR_FAIL(_channel);
    xTEST(!a_cmd.empty());
    xTEST_NA(a_isBlockingMode);

    int iRv = - 1;

    _channel = ::libssh2_channel_open_session(_session);
    xTEST_PTR(_channel);

    ::libssh2_channel_set_blocking(_channel, static_cast<int>(a_isBlockingMode));

    iRv = ::libssh2_channel_exec(_channel, xT2A(a_cmd).c_str());
    xTEST_GR(iRv, - 1);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
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
    bool           isStdOutChannelEof = true;
    {
        char block[blockSizeMin + 1] = {0};

        for ( ; ; ) {
            int read = ::libssh2_channel_read(_channel, block, blockSizeMin);
            if (read == LIBSSH2_ERROR_EAGAIN) {
                continue;
            }

            isStdOutChannelEof = ::libssh2_channel_eof(_channel);
            if (isStdOutChannelEof && read == 0) {
                Trace() << "libssh2_channel_eof: breaking";
                break;
            }

            xCHECK_DO(read < 0, break);

            if (read < blockSizeMin) {
                block[read] = '\0';
            }

            if (block[0] == Const::nl()[0]) {
                Trace() << xTRACE_VAR(xLINE);
                break;
            }

            stdOut.append( xA2T(block) );
        } // for ( ; ; )
    }

    std::tstring_t stdErr;
    bool           isStdErrChannelEof = true;
    {
        char block[blockSizeMin + 1] = {0};

        for ( ; ; ) {
            int read = ::libssh2_channel_read_stderr(_channel, block, blockSizeMin);
            Trace() << xTRACE_VAR(read);
            if (read == LIBSSH2_ERROR_EAGAIN) {
                continue;
            }

            isStdErrChannelEof = ::libssh2_channel_eof(_channel);
            if (isStdErrChannelEof && read == 0) {
                Trace() << "libssh2_channel_eof: breaking";
                break;
            }

            xCHECK_DO(read < 0, break);

            if (read < blockSizeMin) {
                block[read] = '\0';
            }

            if (block[0] == Const::nl()[0]) {
                Trace() << xTRACE_VAR(xLINE);
                break;
            }

            stdErr.append( xA2T(block) );
        } // for ( ; ; )
    }

    if (isStdOutChannelEof && stdOut.empty() /*&& isStdErrChannelEof && stdErr.empty()*/) {
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
        _convertStdToHtml(&stdOut);
        _convertStdToHtml(&stdErr);
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
xINLINE void
Ssh2Client::channelClose()
{
    xTEST_PTR(_channel);

    int iRv = - 1;

    iRv = ::libssh2_channel_close(_channel);
    xTEST_GR(iRv, - 1);

    iRv = ::libssh2_channel_free(_channel);  _channel = xPTR_NULL;
    xTEST_GR(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::channelExecReadAll(
    std::ctstring_t &a_cmd,
    std::tstring_t  *a_stdOut,
    std::tstring_t  *a_stdErr
)
{
    xTEST_PTR(_session);
    xTEST_PTR_FAIL(_channel);
    xTEST(!a_cmd.empty());
    xTEST_PTR(a_stdOut);
    xTEST_PTR(a_stdErr);

    bool bRv = false;

    bRv = channelExec(a_cmd, true);
    xTEST(bRv);

    std::tstring_t stdOut;
    {
        char block[blockSize + 1] = {0};

        for ( ; ; ) {
            int read = ::libssh2_channel_read(_channel, block, blockSize);
            xCHECK_DO(read <= 0, break);

            if (read < blockSize) {
                block[read] = '\0';
            }

            stdOut.append( xA2T(block) );
        }
    }

    std::tstring_t stdErr;
    {
        char block[blockSize + 1] = {0};

        for ( ; ; ) {
            int read = ::libssh2_channel_read_stderr(_channel, block, blockSize);
            xCHECK_DO(read <= 0, break);

            if (read < blockSize) {
                block[read] = '\0';
            }

            stdErr.append( xA2T(block) );
        }
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
        _convertStdToHtml(&stdOut);
        _convertStdToHtml(&stdErr);
        break;
    case Ssh2ClientData::sfUnknown:
    default:
        xTEST(false);
        break;
    }

    // out
    std::swap(stdOut, *a_stdOut);
    std::swap(stdErr, *a_stdErr);

    channelClose();

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void
Ssh2Client::disconnect()
{
    xTEST_PTR(_session);

    int iRv = - 1;

    iRv = ::libssh2_session_disconnect(_session, "Ssh2Client disconnected.");
    xTEST_GR(iRv, - 1);

    _tcpClient.close();

    iRv = ::libssh2_session_free(_session); _session = xPTR_NULL;
    xTEST_GR(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE int
Ssh2Client::lastError()
{
    return ::libssh2_session_last_errno(_session);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Ssh2Client::lastErrorFormat()
{
    std::string asRv;

    char *error     = xPTR_NULL;
    int   errorSize = 0;

    (int)::libssh2_session_last_error(_session, &error, &errorSize, 0);
    if (error == xPTR_NULL) {
        asRv = "[Unknown]";
    } else {
        asRv.assign(error, errorSize);
    }

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void
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
    colorsCodes[xT("\e[0;31m")] = xT("Red");    // \e[0;1;31m
    colorsCodes[xT("\e[0;32m")] = xT("Green");  // \e[0;1;32m
    colorsCodes[xT("\e[0;33m")] = xT("Yellow");
    colorsCodes[xT("\e[0;34m")] = xT("Blue");
    colorsCodes[xT("\e[0;35m")] = xT("Purple");
    colorsCodes[xT("\e[0;36m")] = xT("Cyan");
    colorsCodes[xT("\e[0;37m")] = xT("White");

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

    // Etc
    colorsCodes[xT("\e[0;1;32m")] = xT("Green");

    xFOR_EACH_CONST(std::map_tstring_t, it, colorsCodes) {
        std::tstring_t htmlTag;
        {
            if (it->first == xT("\e[0m")) {
                htmlTag = xT("</font>");
            } else {
                htmlTag = xT("<font color=\"") + it->second + xT("\">");
            }
        }

        *a_std = String::replaceAll(*a_std, it->first, htmlTag);
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, package)
