/**
 * \file  Ssh2Client.cpp
 * \brief SSH2 client
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Ssh2Client.h"
#endif

xNAMESPACE_BEGIN2(xlib, package)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_ANONYM_BEGIN

std::csize_t   blockSize = 1024;
std::tstring_t userPassword;

xNAMESPACE_ANONYM_END

//-------------------------------------------------------------------------------------------------
xINLINE
Ssh2Client::Ssh2Client() :
    _session   (xPTR_NULL),
    _socket    (- 1),
    _user      (),
    _hostName  (),
    _port      (0),
    _userName  (),
    _password  (),
    _isUseKey  (false),
    _keyDirPath("NOTSET")
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
Ssh2Client::init(
    const std::tstring_t     &a_hostName,
    const unsigned short int &a_port,
    const std::tstring_t     &a_userName,
    const std::tstring_t     &a_password,
    const bool               &a_isUseKey,
    const std::tstring_t     &a_keyDirPath
)
{
    userPassword = a_password;

    _hostName    = a_hostName;
    _port        = a_port;
    _userName    = a_userName;
    _password    = a_password;
    _isUseKey    = a_isUseKey;
    _keyDirPath  = a_keyDirPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::connect()
{
    int iRv = - 1;

    hostent *he = ::gethostbyname(_hostName.c_str());
    xTEST_PTR(he);

    sockaddr_in s;

    s.sin_addr   = *(struct in_addr *)(he->h_addr_list[0]);
    s.sin_family = he->h_addrtype;
    s.sin_port   = htons(_port);

    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    xTEST_GR(_socket, - 1);

    iRv = ::connect(_socket, (sockaddr *)&s, sizeof(sockaddr_in));
    if (- 1 == iRv) {
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

xINLINE void
Ssh2Client::authPassword()
{
    xTEST_PTR(_session);
    xTEST(!_isUseKey);

    int         iRv = - 1;
    std::tstring_t internal_user;

    if (_userName.compare("") == 0) {
        internal_user = std::tstring_t(_user.userName());
    } else {
        internal_user = std::tstring_t(_userName);
    }

#if 0
    iRv = ::libssh2_userauth_password(_session, internal_user.c_str(), _password.c_str());
#else
    iRv = ::libssh2_userauth_keyboard_interactive(_session, internal_user.c_str(),
        &keyBoardCallback);
#endif
    if (iRv != 0) {
        std::cerr << lastErrorFormat() << std::endl;
    }

    xTEST(0 == iRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void
Ssh2Client::authPublicKey()
{
    xTEST_PTR(_session);
    xTEST(_isUseKey);

    int iRv = - 1;

    std::tstring_t privateKey;
    std::tstring_t publicKey;
    std::tstring_t internal_user;

    if (_userName.compare("") == 0) {
        internal_user = std::tstring_t(_user.userName());
    } else {
        internal_user = std::tstring_t(_userName);
    }

    if (_keyDirPath.compare("NOTSET") != 0) {
        // Use the provided path to find the keypair
        privateKey = _keyDirPath;
        privateKey.append("/id_rsa");

        publicKey  = _keyDirPath;
        publicKey.append("/id_rsa.pub");
    } else {
        // Try to guess where the user has his keypair
        privateKey = _user.homeDir();
        privateKey.append("/.ssh/id_rsa");

        publicKey = _user.homeDir();
        publicKey.append("/.ssh/id_rsa.pub");
    }

    iRv = ::libssh2_userauth_publickey_fromfile(
                _session, internal_user.c_str(), publicKey.c_str(),
                privateKey.c_str(), _password.c_str()
    );
    xTEST(0 == iRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool
Ssh2Client::executeCmd(
    const std::tstring_t &a_cmd,
    std::tstring_t       *a_stdOut,
    std::tstring_t       *a_stdErr
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
    if (xPTR_NULL != a_stdOut) {
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

        // out
        std::swap(stdOut, *a_stdOut);
    }

    // stderr
    if (xPTR_NULL != a_stdErr) {
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
        sRv = "[Unknown]";
    } else {
        sRv.assign(error, errorSize);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, package)
