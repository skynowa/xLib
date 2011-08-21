/****************************************************************************
* Class name:  CxCgi
* Description: CGI
* File name:   CxCgi.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     11:01:2010 13:20:00
*
*****************************************************************************/


#include <xLib/Net/CxCgi.h>

#include <xLib/Common/CxMacros.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxStdioFile.h>

using namespace NxCgi;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCgi
CxCgi::CxCgi(const size_t cuiMaxSize) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, cuiMaxSize)
{
}
//---------------------------------------------------------------------------
//DONE: CxCgi
/*virtual*/
CxCgi::~CxCgi() {

}
//---------------------------------------------------------------------------
//DONE: sGetDump (dump)
tString
CxCgi::sGetDump()  const{
    /*DEBUG*/

    tString sRes;

    sRes = CxString::sFormat(
            xT("[CGI dump]\n\n"
            "%s\n"
            "%s\n"
            "%s\n"),
            Environment.sGetDump().c_str(),
            Cookies.sGetDump().c_str(),
            Formdata.sGetDump().c_str()
    );

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bRedirect (redirect to URL)
/*static*/
BOOL
CxCgi::bRedirect(const tString &csUrl) {
    /*DEBUG*/xASSERT_RET(false == csUrl.empty(), FALSE)

    tString sHttpResponse;

    sHttpResponse.append( CxString::sFormat(xT("Location: %s\n"), csUrl.c_str()) );
    sHttpResponse.append( CxConst::xNL );

    tcout << sHttpResponse << tendl;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPageShow (show file)
/*static*/
BOOL
CxCgi::bPageShow(
    const tString &csFilePath
)
{
    BOOL bRes = FALSE;

    tString sFileContent;

    bRes = CxStdioFile::bTextRead(csFilePath, &sFileContent);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    tcout << sFileContent << tendl;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private: encoding, decoding
*
*****************************************************************************/

namespace {
    static const tString URI_ILLEGAL   = xT("%<>{}|\\\"^`");
    ////static const tString ILLEGAL_CHARS = xT("()[]/|\\',;");     //for cookie
}
//---------------------------------------------------------------------------
//TODO: bUriEncode ()
/*static*/
BOOL
CxCgi::bUriEncode(
        const tString &csUri,
        const tString &csReserved,
        tString       *psEncodedStr
)
{
    for (tString::const_iterator it = csUri.begin(); it != csUri.end(); ++ it) {
        char chChar = *it;

        if ((chChar >= 'a' && chChar <= 'z') || (chChar >= 'A' && chChar <= 'Z') || (chChar >= '0' && chChar <= '9') ||
             chChar == '-' || chChar == '_'  || chChar == '.' || chChar == '~')
        {
            (*psEncodedStr) += chChar;
        }
        else if (chChar <= 0x20 || chChar >= 0x7F || tString::npos != URI_ILLEGAL.find(chChar) || tString::npos != csReserved.find(chChar)) {
            (*psEncodedStr) += '%';
            //--encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) chChar, 2);

            /*
                poco_assert (width > 0 && width < 64);

                char buffer[64];
                std::sprintf(buffer, "%0*X", width, value);
                str.append(buffer);
             */
            (*psEncodedStr) += CxString::sFormat(xT("%0*X"), 2, (UINT)(UCHAR)chChar);
        }
        else {
            (*psEncodedStr) += chChar;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUriDecode ()
/*static*/
BOOL
CxCgi::bUriDecode(
        const tString &csUri,
        tString       *psDecodedStr
)
{
    tString::const_iterator it  = csUri.begin();
    tString::const_iterator end = csUri.end();

    while (it != end) {
        char chChar = *it++;

        if (chChar == '%') {
            if (it == end) {
                ////throw SyntaxException("URI encoding: no hex digit following percent sign", str);
                return FALSE;
            }

            char hi = *it++;
            if (it == end) {
                ////throw SyntaxException("URI encoding: two hex digits must follow percent sign", str);
                return FALSE;
            }

            char lo = *it++;
            if (hi >= '0' && hi <= '9')
                chChar = hi - '0';
            else if (hi >= 'A' && hi <= 'F')
                chChar = hi - 'A' + 10;
            else if (hi >= 'a' && hi <= 'f')
                chChar = hi - 'a' + 10;
            else {
                ////throw SyntaxException("URI encoding: not a hex digit");
                return FALSE;
            }

            chChar *= 16;
            if (lo >= '0' && lo <= '9')
                chChar += lo - '0';
            else if (lo >= 'A' && lo <= 'F')
                chChar += lo - 'A' + 10;
            else if (lo >= 'a' && lo <= 'f')
                chChar += lo - 'a' + 10;
            else {
                ////throw SyntaxException("URI encoding: not a hex digit");
                return FALSE;
            }
        }

        (*psDecodedStr) += chChar;
    }

    return TRUE;
}
//----------------------------------------------------------------------------------------------------
//TODO: cgl_parsecgibuf
int
cgl_parsecgibuf(/*cgllist *cdata,*/ char *query) {
//    char *s;
//    char *np;
//    char *vp;
//
//    if (!cdata || !query) {
//        cgl_seterrno(CGL_NULLARG);
//        return -1;
//    }
//
//    /* get rid of + signs */
//    cgl_charify(query, '+', ' ');
//
//    np = s = query;
//
//    while (*np) {
//
//        /* find name/value pairs */
//        for ( ; *s && *s != '&'; s++) ;
//
//        /* chop them up */
//        if (*s == '&') {
//            *s = '\0'; s++;
//        }
//        if ((vp = strchr(np, '=')) != NULL) {
//            *vp = '\0';
//            vp++;
//            cgl_urlunescape(np);
//            cgl_urlunescape(vp);
//            if (cgl_insertnode(cdata,
//                np, vp, CGL_INSERT_TAIL) == -1) {
//                return -1;
//            }
//        }
//
//        np = s;
//    }

    return 0;
}
//----------------------------------------------------------------------------------------------------
//TODO: cgl_urlencode
//int
//CxCgi::cgl_urlencode(char *s, FILE *fw) {
//    if (!s)
//        return 0;
//
//    //--cgl_charify(s, ' ', '+');
//    tString sRes = CxString::sReplaceAll(s, CxConst::xSPACE, xT("+"));
//
//    return bUrlEscape(sRes, fw);
//}
////----------------------------------------------------------------------------------------------------
////TODO: cgl_urldecode
//void
//CxCgi::cgl_urldecode(char *s) {
//    //--cgl_charify(s, '+', ' ');
//    tString sRes;
//
//    sRes = CxString::sReplaceAll(s, xT("+"), CxConst::xSPACE);
//
//    bUrlUnescape(sRes);
//
//    return;
//}
//----------------------------------------------------------------------------------------------------
//TODO: bUrlEscape
int
CxCgi::bUrlEscape(char *s, FILE *fw) {
//    register int    c;
//
//    while((c = *s++) != (char)0) {
//        switch(c) {
//            case '\0':
//                break;
//
//            case '%': case ' ': case '?': case '&':
//            case '>': case '<': case '\"': case ';':
//            case '=': case '@': case ':': case '#':
//                fprintf(fw, "%%%02x", c);
//                break;
//
//            default:
//                if (fputc(c, fw) == EOF)
//                    return EOF;
//                break;
//        }
//    }

    return 0;
}
//----------------------------------------------------------------------------------------------------
//TODO: bUrlUnescape
//modified from the Apache code. Code shrinks string, so can be done in place.
int
CxCgi::bUrlUnescape(char *s) {
//    int    error;
//    char    *p;
//
//    if (!s)
//        return 0;
//
//    error = 0;
//
//    for (p = s; *s; s++, p++) {
//        if (*s != '%') {
//            *p = *s;
//            continue;
//        } else {
//            if (!isxdigit((unsigned char)*(s+1)) || !isxdigit((unsigned char)*(s+2))) {
//                error = 1;
//                *p = '%';
//            } else {
//                *p = cgl_hex2char((s+1));
//                s++; s++;
//                if (*p == '/' || *p == (char)0)
//                    error = 1;
//            }
//        }
//    }
//
//    *p = (char)0;
//    if (error)
//        return -1;

    return 0;
}
//----------------------------------------------------------------------------------------------------
//TODO: cgl_hex2char
//ripped off from the Apache code
char
CxCgi::cgl_hex2char(char *what) {
    register char digit = '\0';

//    if (!what)
//        return (char)0;
//
//    digit = ((what[0] >= 'A') ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
//    digit *= 16;
//    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));

    return(digit);
}
//----------------------------------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxCgiEnvironment
* Description: CGI environment
* File name:   CxCgiEnvironment.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12 квіт. 2011 18:10:17
*
*****************************************************************************/

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCgiEnvironment
CxCgiEnvironment::CxCgiEnvironment(CxCgi &ccgCgi) :
    _m_ccgCgi         (ccgCgi),
    _m_rmRequestMethod(rmUknown)
{
    _bInit();
}
//---------------------------------------------------------------------------
//DONE: ~CxCgiEnvironment
/*virtual*/
CxCgiEnvironment::~CxCgiEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: sGetAuthType
const tString &
CxCgiEnvironment::sGetAuthType() const {
    /*DEBUG*/

    return _m_sAuthType;
}
//---------------------------------------------------------------------------
//DONE: sGetContentLength
const tString &
CxCgiEnvironment::sGetContentLength() const {
    /*DEBUG*/

    return _m_sContentLength;
}
//---------------------------------------------------------------------------
//DONE: sGetContentType
const tString &
CxCgiEnvironment::sGetContentType() const {
    /*DEBUG*/

    return _m_sContentType;
}
//---------------------------------------------------------------------------
//DONE: sGetDocumentRoot
const tString &
CxCgiEnvironment::sGetDocumentRoot() const {
    /*DEBUG*/

    return _m_sDocumentRoot;
}
//---------------------------------------------------------------------------
//DONE: sGetGatewayInterface
const tString &
CxCgiEnvironment::sGetGatewayInterface() const {
    /*DEBUG*/

    return _m_sGatewayInterface;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpAccept
const tString &
CxCgiEnvironment::sGetHttpAccept() const {
    /*DEBUG*/

    return _m_sHttpAccept;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpCookie
const tString &
CxCgiEnvironment::sGetHttpCookie() const {
    /*DEBUG*/

    return _m_sHttpCookie;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpPragma
const tString &
CxCgiEnvironment::sGetHttpPragma() const {
    /*DEBUG*/

    return _m_sHttpPragma;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpUserAgent
const tString &
CxCgiEnvironment::sGetHttpUserAgent() const {
    /*DEBUG*/

    return _m_sHttpUserAgent;
}
//---------------------------------------------------------------------------
//DONE: sGetPathInfo
const tString &
CxCgiEnvironment::sGetPathInfo() const {
    /*DEBUG*/

    return _m_sPathInfo;
}
//---------------------------------------------------------------------------
//DONE: sGetPathTranslated
const tString &
CxCgiEnvironment::sGetPathTranslated() const {
    /*DEBUG*/

    return _m_sPathTranslated;
}
//---------------------------------------------------------------------------
//DONE: sGetQueryString
const tString &
CxCgiEnvironment::sGetQueryString() const {
    /*DEBUG*/

    return _m_sQueryString;
}
//---------------------------------------------------------------------------
//DONE: sGetRemoteAddr
const tString &
CxCgiEnvironment::sGetRemoteAddr() const {
    /*DEBUG*/

    return _m_sRemoteAddr;
}
//---------------------------------------------------------------------------
//DONE: sGetRemoteHost
const tString &
CxCgiEnvironment::sGetRemoteHost() const {
    /*DEBUG*/

    return _m_sRemoteHost;
}
//---------------------------------------------------------------------------
//DONE: sGetRemoteIdent
const tString &
CxCgiEnvironment::sGetRemoteIdent() const {
    /*DEBUG*/

    return _m_sRemoteIdent;
}
//---------------------------------------------------------------------------
//DONE: sGetRemotePort
const tString &
CxCgiEnvironment::sGetRemotePort() const {
    /*DEBUG*/

    return _m_sRemotePort;
}
//---------------------------------------------------------------------------
//DONE: sGetRemoteUser
const tString &
CxCgiEnvironment::sGetRemoteUser() const {
    /*DEBUG*/

    return _m_sRemoteUser;
}
//---------------------------------------------------------------------------
//DONE: sGetRequestMethod
const tString &
CxCgiEnvironment::sGetRequestMethod() const {
    /*DEBUG*/

    return _m_sRequestMethod;
}
//---------------------------------------------------------------------------
//DONE: sGetRequestUri
const tString &
CxCgiEnvironment::sGetRequestUri() const {
    /*DEBUG*/

    return _m_sRequestUri;
}
//---------------------------------------------------------------------------
//DONE: sGetScriptFilename
const tString &
CxCgiEnvironment::sGetScriptFilename() const {
    /*DEBUG*/

    return _m_sScriptFilename;
}
//---------------------------------------------------------------------------
//DONE: sGetScriptName
const tString &
CxCgiEnvironment::sGetScriptName() const {
    /*DEBUG*/

    return _m_sScriptName;
}
//---------------------------------------------------------------------------
//DONE: sGetServerAdmin
const tString &
CxCgiEnvironment::sGetServerAdmin() const {
    /*DEBUG*/

    return _m_sServerAdmin;
}
//---------------------------------------------------------------------------
//DONE: sGetServerName
const tString &
CxCgiEnvironment::sGetServerName() const {
    /*DEBUG*/

    return _m_sServerName;
}
//---------------------------------------------------------------------------
//DONE: sGetServerPort
const tString &
CxCgiEnvironment::sGetServerPort() const {
    /*DEBUG*/

    return _m_sServerPort;
}
//---------------------------------------------------------------------------
//DONE: sGetServerProtocol
const tString &
CxCgiEnvironment::sGetServerProtocol() const {
    /*DEBUG*/

    return _m_sServerProtocol;
}
//---------------------------------------------------------------------------
//DONE: sGetServerSoftware
const tString &
CxCgiEnvironment::sGetServerSoftware() const {
    /*DEBUG*/

    return _m_sServerSoftware;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpReferer
const tString &
CxCgiEnvironment::sGetHttpReferer() const {
    /*DEBUG*/

    return _m_sHttpReferer;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpHost
const tString &
CxCgiEnvironment::sGetHttpHost() const {
    /*DEBUG*/

    return _m_sHttpHost;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpAcceptLanguage
const tString &
CxCgiEnvironment::sGetHttpAcceptLanguage() const {
   /*DEBUG*/

   return _m_sHttpAcceptLanguage;
}
//---------------------------------------------------------------------------
//DONE: sGetCountryCode
const tString &
CxCgiEnvironment::sGetCountryCode() const {
    /*DEBUG*/

    return _m_sCountryCode;
}
//---------------------------------------------------------------------------
//DONE: rmGetRequestMethod ()
CxCgiEnvironment::ERequestMethod
CxCgiEnvironment::rmGetRequestMethod() const {
    /*DEBUG*/

    return _m_rmRequestMethod;
}
//---------------------------------------------------------------------------
//DONE: sGetDump (dump)
tString
CxCgiEnvironment::sGetDump() const {
    /*DEBUG*/

    tString sRes;

    sRes = CxString::sFormat(
            xT("[CxCgiEnvironment dump]\n\n"
            "AUTH_TYPE: %s\n"
            "CONTENT_LENGTH: %s\n"
            "CONTENT_TYPE: %s\n"
            "DOCUMENT_ROOT: %s\n"
            "GATEWAY_INTERFACE: %s\n"
            "HTTP_ACCEPT: %s\n"
            "HTTP_COOKIE: %s\n"
            "HTTP_PRAGMA: %s\n"
            "HTTP_USER_AGENT: %s\n"
            "PATH_INFO: %s\n"
            "PATH_TRANSLATED: %s\n"
            "QUERY_STRING: %s\n"
            "REMOTE_ADDR: %s\n"
            "REMOTE_HOST: %s\n"
            "REMOTE_IDENT: %s\n"
            "REMOTE_PORT: %s\n"
            "REMOTE_USER: %s\n"
            "REQUEST_METHOD: %s\n"
            "REQUEST_URI: %s\n"
            "SCRIPT_FILENAME: %s\n"
            "SCRIPT_NAME: %s\n"
            "SERVER_ADMIN: %s\n"
            "SERVER_NAME: %s\n"
            "SERVER_PORT: %s\n"
            "SERVER_PROTOCOL: %s\n"
            "SERVER_SOFTWARE: %s\n"
            "HTTP_REFERER: %s\n"
            "HTTP_HOST: %s\n"
            "HTTP_ACCEPT_LANGUAGE: %s\n"
            "GEOIP_COUNTRY_CODE: %s\n\n"),
            sGetAuthType().c_str(),
            sGetContentLength().c_str(),
            sGetContentType().c_str(),
            sGetDocumentRoot().c_str(),
            sGetGatewayInterface().c_str(),
            sGetHttpAccept().c_str(),
            sGetHttpCookie().c_str(),
            sGetHttpPragma().c_str(),
            sGetHttpUserAgent().c_str(),
            sGetPathInfo().c_str(),
            sGetPathTranslated().c_str(),
            sGetQueryString().c_str(),
            sGetRemoteAddr().c_str(),
            sGetRemoteHost().c_str(),
            sGetRemoteIdent().c_str(),
            sGetRemotePort().c_str(),
            sGetRemoteUser().c_str(),
            sGetRequestMethod().c_str(),
            sGetRequestUri().c_str(),
            sGetScriptFilename().c_str(),
            sGetScriptName().c_str(),
            sGetServerAdmin().c_str(),
            sGetServerName().c_str(),
            sGetServerPort().c_str(),
            sGetServerProtocol().c_str(),
            sGetServerSoftware().c_str(),
            sGetHttpReferer().c_str(),
            sGetHttpHost().c_str(),
            sGetHttpAcceptLanguage().c_str(),
            sGetCountryCode().c_str()
    );

    return sRes;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bInit (initiate class data)
BOOL
CxCgiEnvironment::_bInit() {
    /*DEBUG*/

    _m_sAuthType           = CxEnvironment::sGetVar(xT("AUTH_TYPE"));
    _m_sContentLength      = CxEnvironment::sGetVar(xT("CONTENT_LENGTH"));
    _m_sContentType        = CxEnvironment::sGetVar(xT("CONTENT_TYPE"));
    _m_sDocumentRoot       = CxEnvironment::sGetVar(xT("DOCUMENT_ROOT"));
    _m_sGatewayInterface   = CxEnvironment::sGetVar(xT("GATEWAY_INTERFACE"));
    _m_sHttpAccept         = CxEnvironment::sGetVar(xT("HTTP_ACCEPT"));
    _m_sHttpCookie         = CxEnvironment::sGetVar(xT("HTTP_COOKIE"));
    _m_sHttpPragma         = CxEnvironment::sGetVar(xT("HTTP_PRAGMA"));
    _m_sHttpUserAgent      = CxEnvironment::sGetVar(xT("HTTP_USER_AGENT"));
    _m_sPathInfo           = CxEnvironment::sGetVar(xT("PATH_INFO"));
    _m_sPathTranslated     = CxEnvironment::sGetVar(xT("PATH_TRANSLATED"));
    _m_sQueryString        = CxEnvironment::sGetVar(xT("QUERY_STRING"));
    _m_sRemoteAddr         = CxEnvironment::sGetVar(xT("REMOTE_ADDR"));
    _m_sRemoteHost         = CxEnvironment::sGetVar(xT("REMOTE_HOST"));
    _m_sRemoteIdent        = CxEnvironment::sGetVar(xT("REMOTE_IDENT"));
    _m_sRemotePort         = CxEnvironment::sGetVar(xT("REMOTE_PORT"));
    _m_sRemoteUser         = CxEnvironment::sGetVar(xT("REMOTE_USER"));
    _m_sRequestMethod      = CxEnvironment::sGetVar(xT("REQUEST_METHOD"));
    _m_sRequestUri         = CxEnvironment::sGetVar(xT("REQUEST_URI"));
    _m_sScriptFilename     = CxEnvironment::sGetVar(xT("SCRIPT_FILENAME"));
    _m_sScriptName         = CxEnvironment::sGetVar(xT("SCRIPT_NAME"));
    _m_sServerAdmin        = CxEnvironment::sGetVar(xT("SERVER_ADMIN"));
    _m_sServerName         = CxEnvironment::sGetVar(xT("SERVER_NAME"));
    _m_sServerPort         = CxEnvironment::sGetVar(xT("SERVER_PORT"));
    _m_sServerProtocol     = CxEnvironment::sGetVar(xT("SERVER_PROTOCOL"));
    _m_sServerSoftware     = CxEnvironment::sGetVar(xT("SERVER_SOFTWARE"));
    _m_sHttpReferer        = CxEnvironment::sGetVar(xT("HTTP_REFERER"));
    _m_sHttpHost           = CxEnvironment::sGetVar(xT("HTTP_HOST"));
    _m_sHttpAcceptLanguage = CxEnvironment::sGetVar(xT("HTTP_ACCEPT_LANGUAGE"));
    _m_sCountryCode        = CxEnvironment::sGetVar(xT("GEOIP_COUNTRY_CODE"));

    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::sGetVar(xT("HTTP_GEOIP_COUNTRY_CODE"));
    }
    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::sGetVar(xT("HTTP_COUNTRY_CODE"));
    }

    //--------------------------------------------------
    //is data from a GET or a POST?
    if        (FALSE != CxString::bCompareNoCase(xT("GET"), sGetRequestMethod()) ) {
        _m_rmRequestMethod = rmGet;
    } else if (FALSE != CxString::bCompareNoCase(xT("POST"), sGetRequestMethod()) ) {
        _m_rmRequestMethod = rmPost;
    }
    else {
        _m_rmRequestMethod = rmUknown;
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxCgiCookies
* Description: CGI cookies
* File name:   CxCgiCookies
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12 квіт. 2011 18:19:42
*
*****************************************************************************/

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCgiCookies
CxCgiCookies::CxCgiCookies(CxCgi &ccgCgi):
    _m_ccgCgi(ccgCgi)
{
    _bInit();
}
//---------------------------------------------------------------------------
//DONE: ~CxCgiCookies
/*virtual*/
CxCgiCookies::~CxCgiCookies() {
    for (TCookies::iterator it = Items.begin(); it != Items.end(); ++ it) {
        xPTR_DELETE(*it);
    }
}
//---------------------------------------------------------------------------
//DONE: operator [] (no case searchig cookie value by name from list)
tString
CxCgiCookies::operator [](const tString &csCookieName) {
    /*DEBUG*/

    for (TCookies::const_iterator it = Items.begin(); it != Items.end(); ++ it) {
        xCHECK_DO(FALSE == CxString::bCompareNoCase(csCookieName, (*it)->sGetValue()), continue);

        return (*it)->sGetValue();
    }

    return tString();
}
//---------------------------------------------------------------------------
//DONE: sGetDump ()
tString
CxCgiCookies::sGetDump() const {
    /*DEBUG*/

    tString sRes;

    sRes.append(xT("[CxCgiCookies dump]\n\n"));

    for (TCookies::const_iterator it = Items.begin(); it != Items.end(); ++ it) {
        tString sItemN = CxString::sFormat(
                xT("Name: %s\n"
                "Value: %s\n"
                "Domain: %s\n"
                "Path: %s\n"
                "Expires: %s\n"
                "Secure: %s\n"
                "HttpOnly: %s\n\n"),
                (*it)->sGetName().c_str(),
                (*it)->sGetValue().c_str(),
                (*it)->sGetDomain().c_str(),
                (*it)->sGetPath().c_str(),
                (*it)->sGetExpires().c_str(),
                CxString::sBoolToStr((*it)->bGetSecure()).c_str(),
                CxString::sBoolToStr((*it)->bGetHttpOnly()).c_str()
        );

        sRes.append( xT("[Item]:\n") );
        sRes.append(sItemN);
        sRes.append(CxConst::xNL);
    }

    return sRes;
}
//---------------------------------------------------------------------------

/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bInit (initiate class data)
BOOL
CxCgiCookies::_bInit() {
    /*DEBUG*/

    BOOL                 bRes           = FALSE;
    tString              sRawCookies    = _m_ccgCgi.Environment.sGetHttpCookie();
    std::vector<tString> vsRawCookies;
    TCookies             vecckCookies;

    bRes = CxString::bSplit(sRawCookies, CxConst::xSEMICOLON, &vsRawCookies);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for (std::vector<tString>::const_iterator it = vsRawCookies.begin(); it != vsRawCookies.end(); ++ it) {
        CxCookiePv0 *pckItem = new(std::nothrow) CxCookiePv0(*it);
        /*DEBUG*/xASSERT_RET(NULL != pckItem, FALSE);

        vecckCookies.push_back(pckItem);
    }

    std::swap(vecckCookies, Items);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
* Class name:  CxCgiFormData
* Description: CGI form data
* File name:   CxCgiFormData.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     12 квіт. 2011 18:19:42
*
*****************************************************************************/

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCgiFormData
CxCgiFormData::CxCgiFormData(CxCgi &ccgCgi, const size_t cuiMaxSize):
    _m_cuiMaxData(cuiMaxSize),
    _m_ccgCgi    (ccgCgi)
{
    _bInit();
}
//---------------------------------------------------------------------------
//DONE: ~CxCgiFormData
/*virtual*/
CxCgiFormData::~CxCgiFormData() {

}
//---------------------------------------------------------------------------
//DONE: sGetRawData ()
const tString &
CxCgiFormData::sGetRawData() const {
    /*DEBUG*/

    return _m_sFormData;
}
//---------------------------------------------------------------------------
//DONE: sGetDump ()
tString
CxCgiFormData::sGetDump() const {
    /*DEBUG*/

    tString sRes;

    sRes = CxString::sFormat(
            xT("[CxCgiFormData dump]\n\n"
            "Data: %s\n\n"),
            sGetRawData().c_str());

    return sRes;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bInitFormData (initiate class data)
BOOL
CxCgiFormData::_bInit() {
    /*DEBUG*/

    INT iRes = _m_ccgCgi.Environment.rmGetRequestMethod();
    switch (iRes) {
        case CxCgiEnvironment::rmGet: {
                /*DEBUG*/xASSERT_RET(false == _m_ccgCgi.Environment.sGetQueryString().empty(), FALSE);

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData.assign(_m_ccgCgi.Environment.sGetQueryString());
            }
            break;

        case CxCgiEnvironment::rmPost: {
                BOOL bRes = FALSE;

                bRes = CxString::bCompareNoCase(xT("application/x-www-form-urlencoded"), _m_ccgCgi.Environment.sGetContentType());
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                //get content length
                size_t uiPostSize = 0;  // in bytes
                if (true == _m_ccgCgi.Environment.sGetContentLength().empty()) {
                    uiPostSize = 0;
                }
                else {
                    uiPostSize = CxString::lexical_cast<size_t>( _m_ccgCgi.Environment.sGetContentLength() );
                }
                /*DEBUG*/xASSERT_RET(0U            <  uiPostSize, FALSE);
                /*DEBUG*/xASSERT_RET(_m_cuiMaxData >= uiPostSize, FALSE);  //secure
                xCHECK_RET(_m_cuiMaxData <= uiPostSize, FALSE);


                //read, parse data
                CxStdioFile sfFile;
                tString     sBuff;

                bRes = sfFile.bOpen(stdin);
                /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                sBuff.resize(uiPostSize);

                size_t uiRes = sfFile.uiRead(&sBuff.at(0), sBuff.size());
                /*DEBUG*/xASSERT_RET(uiRes == sBuff.size(), FALSE);

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData.assign(sBuff);
            }
            break;

        default: {
                /////*DEBUG*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
