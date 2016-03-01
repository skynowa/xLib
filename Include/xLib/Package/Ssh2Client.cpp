/**
 * \file  Ssh2Client.cpp
 * \brief SSH2 client
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2Client.h"
#endif

#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>

xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

cint_t         blockSize = 1024;
std::tstring_t userPassword;

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2Client::Ssh2Client(
    cSsh2ClientData &a_data
) :
    _data   (a_data),
    _socket (- 1),
    _session(xPTR_NULL)
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
Ssh2Client::connect()
{
    int iRv = - 1;

    hostent *he = ::gethostbyname( _data.hostName.c_str() );
    xTEST_PTR(he);

    sockaddr_in s; xSTRUCT_ZERO(s);
    s.sin_addr   = *(struct in_addr *)(he->h_addr_list[0]);
    s.sin_family = he->h_addrtype;
    s.sin_port   = htons(_data.port);

    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    xTEST_GR(_socket, - 1);

    iRv = ::connect(_socket, (sockaddr *)&s, sizeof(sockaddr_in));
    if (iRv == - 1) {
        return false;
    }
    xTEST_GR(iRv, - 1);

    _session = ::libssh2_session_init();
    xTEST_PTR(_session);

    iRv = ::libssh2_session_startup(_session, _socket);
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

        a_responses[0].text   = ::strdup( userPassword.c_str() );
        a_responses[0].length = userPassword.size();
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
        iRv = ::libssh2_userauth_password(_session, _data.userName.c_str(), _data.password.c_str());
        break;
    case uaKeyboardInteractive:
        iRv = ::libssh2_userauth_keyboard_interactive(_session, _data.userName.c_str(),
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

    iRv = ::libssh2_userauth_publickey_fromfile(_session, _data.userName.c_str(), publicKey.c_str(),
            privateKey.c_str(), _data.password.c_str());
    xTEST(0 == iRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::executeCmd(
    std::ctstring_t &a_cmd,
    std::tstring_t  *a_stdOut,
    std::tstring_t  *a_stdErr
)
{
    xTEST_PTR(_session);
    xTEST_NA(a_stdOut);
    xTEST_NA(a_stdErr);

    int iRv = - 1;

    LIBSSH2_CHANNEL *channel = ::libssh2_channel_open_session(_session);
    xTEST_PTR(channel);

    iRv = ::libssh2_channel_exec(channel, a_cmd.c_str());
    xTEST_GR(iRv, - 1);

    // stdout
    if (a_stdOut != xPTR_NULL) {
        std::tstring_t stdOut;
        char           block[blockSize + 1] = {0};

        for (int read = 0; ; ) {
            read = ::libssh2_channel_read(channel, block, blockSize);
            if (0 >= read) {
                break;
            }

            if (read < blockSize) {
                block[read] = '\0';
            }

            stdOut.append(block);
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
            break;
        case Ssh2ClientData::sfUnknown:
        default:
            xTEST(false);
            break;
        }

        // out
        std::swap(stdOut, *a_stdOut);
    }

    // stderr
    if (a_stdErr != xPTR_NULL) {
        std::tstring_t stdErr;
        char           block[blockSize + 1] = {0};

        for (int read = 0; ; ) {
            read = ::libssh2_channel_read_stderr(channel, block, blockSize);
            if (0 >= read) {
                break;
            }

            if (read < blockSize) {
                block[read] = '\0';
            }

            stdErr.append(block);
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
            _convertStdToHtml(&stdErr);
            break;
        case Ssh2ClientData::sfUnknown:
        default:
            xTEST(false);
            break;
        }

        // out
        std::swap(stdErr, *a_stdErr);
    }

    iRv = ::libssh2_channel_close(channel);
    xTEST_GR(iRv, - 1);

    iRv = ::libssh2_channel_free(channel);  channel = xPTR_NULL;
    xTEST_GR(iRv, - 1);

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

    iRv = ::close(_socket); _socket = - 1;
    xTEST_GR(iRv, - 1);

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
    std::tstring_t sRv;

    char *error     = xPTR_NULL;
    int   errorSize = 0;

    (int)::libssh2_session_last_error(_session, &error, &errorSize, 0);
    if (error == xPTR_NULL) {
        sRv = xT("[Unknown]");
    } else {
        sRv.assign(error, errorSize);
    }

    return sRv;
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
    *a_std = String::replaceAll(*a_std, "\n", "<br />");

    // http://misc.flogisoft.com/bash/tip_colors_and_formatting
    // http://ascii-table.com/ansi-escape-sequences.php
    std::map_tstring_t colorsCodes;

    // Attributes set
    colorsCodes["\e[1m"]    = ""; // Bold/Bright
    colorsCodes["\e[2m"]    = ""; // Dim
    colorsCodes["\e[4m"]    = ""; // Underlined
    colorsCodes["\e[5m"]    = ""; // Blink
    colorsCodes["\e[7m"]    = ""; // Reverse (invert the foreground and background colors)
    colorsCodes["\e[8m"]    = ""; // Hidden (usefull for passwords)

    // Attributes Reset
    colorsCodes["\e[0m"]    = ""; // Reset all attributes
    colorsCodes["\e[21m"]   = ""; // Reset bold/bright
    colorsCodes["\e[22m"]   = ""; // Reset dim
    colorsCodes["\e[24m"]   = ""; // Reset underlined
    colorsCodes["\e[25m"]   = ""; // Reset blink
    colorsCodes["\e[27m"]   = ""; // Reset reverse
    colorsCodes["\e[28m"]   = ""; // Reset hidden

    // Regular
    colorsCodes["\e[0;30m"] = "Black";
    colorsCodes["\e[0;31m"] = "Red";    // \e[0;1;31m
    colorsCodes["\e[0;32m"] = "Green";  // \e[0;1;32m
    colorsCodes["\e[0;33m"] = "Yellow";
    colorsCodes["\e[0;34m"] = "Blue";
    colorsCodes["\e[0;35m"] = "Purple";
    colorsCodes["\e[0;36m"] = "Cyan";
    colorsCodes["\e[0;37m"] = "White";

    // Bold
    colorsCodes["\e[1;30m"] = "Black";
    colorsCodes["\e[1;31m"] = "Red";
    colorsCodes["\e[1;32m"] = "Green";
    colorsCodes["\e[1;33m"] = "Yellow";
    colorsCodes["\e[1;34m"] = "Blue";
    colorsCodes["\e[1;35m"] = "Purple";
    colorsCodes["\e[1;36m"] = "Cyan";
    colorsCodes["\e[1;37m"] = "White";

    // Underline
    colorsCodes["\e[4;30m"] = "Black";
    colorsCodes["\e[4;31m"] = "Red";
    colorsCodes["\e[4;32m"] = "Green";
    colorsCodes["\e[4;33m"] = "Yellow";
    colorsCodes["\e[4;34m"] = "Blue";
    colorsCodes["\e[4;35m"] = "Purple";
    colorsCodes["\e[4;36m"] = "Cyan";
    colorsCodes["\e[4;37m"] = "White";

    // Background
    colorsCodes["\e[40m"]   = "Black";
    colorsCodes["\e[41m"]   = "Red";
    colorsCodes["\e[42m"]   = "Green";
    colorsCodes["\e[43m"]   = "Yellow";
    colorsCodes["\e[44m"]   = "Blue";
    colorsCodes["\e[45m"]   = "Purple";
    colorsCodes["\e[46m"]   = "Cyan";
    colorsCodes["\e[47m"]   = "White";

    // Etc
    colorsCodes["\e[0;1;32m"] = "Green";

    xFOREACH_CONST(std::map_tstring_t, it, colorsCodes) {
        std::tstring_t htmlTag;
        {
            if (it->first == "\e[0m") {
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
