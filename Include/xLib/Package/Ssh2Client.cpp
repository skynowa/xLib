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
Ssh2Client::Ssh2Client() :
    _session (xPTR_NULL),
    _socket  (- 1),
    _hostName(),
    _port    (0),
    _userName(),
    _password()
{
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
xINLINE void
Ssh2Client::construct(
    std::ctstring_t &a_hostName,
    cushort_t       &a_port,
    std::ctstring_t &a_userName,
    std::ctstring_t &a_password
)
{
    userPassword = a_password;

    _hostName = a_hostName;
    _port     = a_port;
    _userName = a_userName;
    _password = a_password;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::connect()
{
    int iRv = - 1;

    hostent *he = ::gethostbyname( _hostName.c_str() );
    xTEST_PTR(he);

    sockaddr_in s; xSTRUCT_ZERO(s);
    s.sin_addr   = *(struct in_addr *)(he->h_addr_list[0]);
    s.sin_family = he->h_addrtype;
    s.sin_port   = htons(_port);

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
keyBoardCallback(
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
        iRv = ::libssh2_userauth_password(_session, _userName.c_str(), _password.c_str());
        break;
    case uaKeyboardInteractive:
        iRv = ::libssh2_userauth_keyboard_interactive(_session, _userName.c_str(),
                &keyBoardCallback);
        break;
    case uaUnknown:
    default:
        iRv = - 1;
        break;
    }

    if (iRv != 0) {
        // Trace() << lastErrorFormat();
    }

    xTEST(0 == iRv);
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

    iRv = ::libssh2_userauth_publickey_fromfile(_session, _userName.c_str(), publicKey.c_str(),
            privateKey.c_str(), _password.c_str());
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

        _convertStdToHtml(&stdOut);

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

        _convertStdToHtml(&stdErr);

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
void
Ssh2Client::_convertStdToHtml(
    std::tstring_t *a_std
)
{
    *a_std = String::replaceAll(*a_std, "\n", "<br />");

    #define RESET       "\033[0m"
    #define BLACK       "\033[30m"
    #define RED         "\033[31m"
    #define GREEN       "\033[32m"
    #define YELLOW      "\033[33m"
    #define BLUE        "\033[34m"
    #define MAGENTA     "\033[35m"
    #define CYAN        "\033[36m"
    #define WHITE       "\033[37m"
    #define BOLDBLACK   "\033[1m\033[30m"
    #define BOLDRED     "\033[1m\033[31m"
    #define BOLDGREEN   "\033[1m\033[32m"
    #define BOLDYELLOW  "\033[1m\033[33m"
    #define BOLDBLUE    "\033[1m\033[34m"
    #define BOLDMAGENTA "\033[1m\033[35m"
    #define BOLDCYAN    "\033[1m\033[36m"
    #define BOLDWHITE   "\033[1m\033[37m"

    #define RESET_       "\033[0;1;0m"
    #define BLACK_       "\033[0;1;30m"
    #define RED_         "\033[0;1;31m"
    #define GREEN_       "\033[0;1;32m"
    #define YELLOW_      "\033[0;1;33m"
    #define BLUE_        "\033[0;1;34m"
    #define MAGENTA_     "\033[0;1;35m"
    #define CYAN_        "\033[0;1;36m"
    #define WHITE_       "\033[0;1;37m"
    #define BOLDBLACK_   "\033[0;1;1m\033[30m"
    #define BOLDRED_     "\033[0;1;1m\033[31m"
    #define BOLDGREEN_   "\033[0;1;1m\033[32m"
    #define BOLDYELLOW_  "\033[0;1;1m\033[33m"
    #define BOLDBLUE_    "\033[0;1;1m\033[34m"
    #define BOLDMAGENTA_ "\033[0;1;1m\033[35m"
    #define BOLDCYAN_    "\033[0;1;1m\033[36m"
    #define BOLDWHITE_   "\033[0;1;1m\033[37m"

    #define COLOR_1      "\033[1m"
    #define COLOR_2      "\033[0;32m"

    std::map<std::tstring_t, std::tstring_t> colorsCodes;
    colorsCodes[RESET]        = "";

    colorsCodes[BLACK]        = xLEX_TO_STR(BLACK);
    colorsCodes[RED]          = xLEX_TO_STR(RED);
    colorsCodes[GREEN]        = xLEX_TO_STR(GREEN);
    colorsCodes[YELLOW]       = xLEX_TO_STR(YELLOW);
    colorsCodes[BLUE]         = xLEX_TO_STR(BLUE);
    colorsCodes[MAGENTA]      = xLEX_TO_STR(MAGENTA);
    colorsCodes[CYAN]         = xLEX_TO_STR(CYAN);
    colorsCodes[WHITE]        = xLEX_TO_STR(WHITE);
    colorsCodes[BOLDBLACK]    = xLEX_TO_STR(BOLDBLACK);
    colorsCodes[BOLDRED]      = xLEX_TO_STR(BOLDRED);
    colorsCodes[BOLDGREEN]    = xLEX_TO_STR(BOLDGREEN);
    colorsCodes[BOLDYELLOW]   = xLEX_TO_STR(BOLDYELLOW);
    colorsCodes[BOLDBLUE]     = xLEX_TO_STR(BOLDBLUE);
    colorsCodes[BOLDMAGENTA]  = xLEX_TO_STR(BOLDMAGENTA);
    colorsCodes[BOLDCYAN]     = xLEX_TO_STR(BOLDCYAN);
    colorsCodes[BOLDWHITE]    = xLEX_TO_STR(BOLDWHITE);

    colorsCodes[BLACK_]       = xLEX_TO_STR(BLACK);
    colorsCodes[RED_]         = xLEX_TO_STR(RED);
    colorsCodes[GREEN_]       = xLEX_TO_STR(GREEN);
    colorsCodes[YELLOW_]      = xLEX_TO_STR(YELLOW);
    colorsCodes[BLUE_]        = xLEX_TO_STR(BLUE);
    colorsCodes[MAGENTA_]     = xLEX_TO_STR(MAGENTA);
    colorsCodes[CYAN_]        = xLEX_TO_STR(CYAN);
    colorsCodes[WHITE_]       = xLEX_TO_STR(WHITE);
    colorsCodes[BOLDBLACK_]   = xLEX_TO_STR(BOLDBLACK);
    colorsCodes[BOLDRED_]     = xLEX_TO_STR(BOLDRED);
    colorsCodes[BOLDGREEN_]   = xLEX_TO_STR(BOLDGREEN);
    colorsCodes[BOLDYELLOW_]  = xLEX_TO_STR(BOLDYELLOW);
    colorsCodes[BOLDBLUE_]    = xLEX_TO_STR(BOLDBLUE);
    colorsCodes[BOLDMAGENTA_] = xLEX_TO_STR(BOLDMAGENTA);
    colorsCodes[BOLDCYAN_]    = xLEX_TO_STR(BOLDCYAN);
    colorsCodes[BOLDWHITE_]   = xLEX_TO_STR(BOLDWHITE);

    colorsCodes[COLOR_1]      = xLEX_TO_STR(BLACK);
    colorsCodes[COLOR_2]      = xLEX_TO_STR(BLACK);

    for (std::map<std::tstring_t, std::tstring_t>::iterator it = colorsCodes.begin();
         it != colorsCodes.end();
         ++ it)
    {
        std::tstring_t htmlTag;
        {
            if (it->first == RESET) {
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
