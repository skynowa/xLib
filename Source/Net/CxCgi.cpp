/**
 * \file  CxCgi.cpp
 * \brief CGI
 */


#include <xLib/Net/CxCgi.h>

#include <xLib/Common/CxMacros.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(NxLib)

using namespace NxCgi;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCgi::CxCgi(
    const size_t cuiMaxSize
) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, cuiMaxSize)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxCgi::~CxCgi() {

}
//---------------------------------------------------------------------------
std::tstring_t
CxCgi::sGetDump()  const{
    /*DEBUG*/

    std::tstring_t sRes;

    sRes = CxString::sFormat(
            xT("[CGI dump]\n\n")
            xT("%s\n")
            xT("%s\n")
            xT("%s\n"),
            Environment.sGetDump().c_str(),
            Cookies.sGetDump().c_str(),
            Formdata.sGetDump().c_str()
    );

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCgi::bRedirect(
    const std::tstring_t &csUrl
)
{
    /*DEBUG*/xASSERT_RET(false == csUrl.empty(), false)

    std::tstring_t sHttpResponse;

    sHttpResponse.append( CxString::sFormat(xT("Location: %s\n"), csUrl.c_str()) );
    sHttpResponse.append( CxConst::xNL );

    std::tcout << sHttpResponse << std::endl;

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxCgi::bPageShow(
    const std::tstring_t &csFilePath
)
{
    bool bRes = false;

    std::tstring_t sFileContent;

    bRes = CxFile::bTextRead(csFilePath, &sFileContent);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    std::tcout << sFileContent << std::endl;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private: encoding, decoding
*
*****************************************************************************/

namespace {
    static const std::tstring_t URI_ILLEGAL   = xT("%<>{}|\\\"^`");
    ////static const std::tstring_t ILLEGAL_CHARS = xT("()[]/|\\',;");     //for cookie
}
//---------------------------------------------------------------------------
//TODO: bUriEncode
/*static*/
bool
CxCgi::bUriEncode(
    const std::tstring_t &csUri,
    const std::tstring_t &csReserved,
    std::tstring_t       *psEncodedStr
)
{
    for (std::tstring_t::const_iterator it = csUri.begin(); it != csUri.end(); ++ it) {
        char chChar = *it;

        if ((chChar >= 'a' && chChar <= 'z') || (chChar >= 'A' && chChar <= 'Z') || (chChar >= '0' && chChar <= '9') ||
             chChar == '-' || chChar == '_'  || chChar == '.' || chChar == '~')
        {
            (*psEncodedStr) += chChar;
        }
        else if (chChar <= 0x20 || chChar >= 0x7F || std::tstring_t::npos != URI_ILLEGAL.find(chChar) || std::tstring_t::npos != csReserved.find(chChar)) {
            (*psEncodedStr) += '%';
            //--encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) chChar, 2);

            /*
                poco_assert (width > 0 && width < 64);

                char buffer[64];
                std::sprintf(buffer, "%0*X", width, value);
                str.append(buffer);
             */
            (*psEncodedStr) += CxString::sFormat(xT("%0*X"), 2, (uint_t)(uchar_t)chChar);
        }
        else {
            (*psEncodedStr) += chChar;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: bUriDecode ()
/*static*/
bool
CxCgi::bUriDecode(
    const std::tstring_t &csUri,
    std::tstring_t       *psDecodedStr
)
{
    std::tstring_t::const_iterator it  = csUri.begin();
    std::tstring_t::const_iterator end = csUri.end();

    while (it != end) {
        char chChar = *it++;

        if (chChar == '%') {
            if (it == end) {
                ////throw SyntaxException("URI encoding: no hex digit following percent sign", str);
                return false;
            }

            char hi = *it++;
            if (it == end) {
                ////throw SyntaxException("URI encoding: two hex digits must follow percent sign", str);
                return false;
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
                return false;
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
                return false;
            }
        }

        (*psDecodedStr) += chChar;
    }

    return true;
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
//    std::tstring_t sRes = CxString::sReplaceAll(s, CxConst::xSPACE, xT("+"));
//
//    return bUrlEscape(sRes, fw);
//}
////----------------------------------------------------------------------------------------------------
////TODO: cgl_urldecode
//void
//CxCgi::cgl_urldecode(char *s) {
//    //--cgl_charify(s, '+', ' ');
//    std::tstring_t sRes;
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


/**
 * \class CxCgiEnvironment
 * \brief CGI environment
 */

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCgiEnvironment::CxCgiEnvironment(
    CxCgi &ccgCgi
) :
    _m_ccgCgi         (ccgCgi),
    _m_rmRequestMethod(rmUknown)
{
    _bInit();
}
//---------------------------------------------------------------------------
/*virtual*/
CxCgiEnvironment::~CxCgiEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: sGetAuthType
const std::tstring_t &
CxCgiEnvironment::sGetAuthType() const {
    /*DEBUG*/

    return _m_sAuthType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetContentLength() const {
    /*DEBUG*/

    return _m_sContentLength;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetContentType() const {
    /*DEBUG*/

    return _m_sContentType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetDocumentRoot() const {
    /*DEBUG*/

    return _m_sDocumentRoot;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetGatewayInterface() const {
    /*DEBUG*/

    return _m_sGatewayInterface;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpAccept() const {
    /*DEBUG*/

    return _m_sHttpAccept;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpCookie() const {
    /*DEBUG*/

    return _m_sHttpCookie;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpPragma() const {
    /*DEBUG*/

    return _m_sHttpPragma;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpUserAgent() const {
    /*DEBUG*/

    return _m_sHttpUserAgent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetPathInfo() const {
    /*DEBUG*/

    return _m_sPathInfo;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetPathTranslated() const {
    /*DEBUG*/

    return _m_sPathTranslated;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetQueryString() const {
    /*DEBUG*/

    return _m_sQueryString;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRemoteAddr() const {
    /*DEBUG*/

    return _m_sRemoteAddr;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRemoteHost() const {
    /*DEBUG*/

    return _m_sRemoteHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRemoteIdent() const {
    /*DEBUG*/

    return _m_sRemoteIdent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRemotePort() const {
    /*DEBUG*/

    return _m_sRemotePort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRemoteUser() const {
    /*DEBUG*/

    return _m_sRemoteUser;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRequestMethod() const {
    /*DEBUG*/

    return _m_sRequestMethod;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetRequestUri() const {
    /*DEBUG*/

    return _m_sRequestUri;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetScriptFilename() const {
    /*DEBUG*/

    return _m_sScriptFilename;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetScriptName() const {
    /*DEBUG*/

    return _m_sScriptName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetServerAdmin() const {
    /*DEBUG*/

    return _m_sServerAdmin;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetServerName() const {
    /*DEBUG*/

    return _m_sServerName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetServerPort() const {
    /*DEBUG*/

    return _m_sServerPort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetServerProtocol() const {
    /*DEBUG*/

    return _m_sServerProtocol;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetServerSoftware() const {
    /*DEBUG*/

    return _m_sServerSoftware;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpReferer() const {
    /*DEBUG*/

    return _m_sHttpReferer;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpHost() const {
    /*DEBUG*/

    return _m_sHttpHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetHttpAcceptLanguage() const {
   /*DEBUG*/

   return _m_sHttpAcceptLanguage;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGetCountryCode() const {
    /*DEBUG*/

    return _m_sCountryCode;
}
//---------------------------------------------------------------------------
CxCgiEnvironment::ERequestMethod
CxCgiEnvironment::rmGetRequestMethod() const {
    /*DEBUG*/

    return _m_rmRequestMethod;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiEnvironment::sGetDump() const {
    /*DEBUG*/

    std::tstring_t sRes;

    sRes = CxString::sFormat(
            xT("[CxCgiEnvironment dump]\n\n")
            xT("AUTH_TYPE: %s\n")
            xT("CONTENT_LENGTH: %s\n")
            xT("CONTENT_TYPE: %s\n")
            xT("DOCUMENT_ROOT: %s\n")
            xT("GATEWAY_INTERFACE: %s\n")
            xT("HTTP_ACCEPT: %s\n")
            xT("HTTP_COOKIE: %s\n")
            xT("HTTP_PRAGMA: %s\n")
            xT("HTTP_USER_AGENT: %s\n")
            xT("PATH_INFO: %s\n")
            xT("PATH_TRANSLATED: %s\n")
            xT("QUERY_STRING: %s\n")
            xT("REMOTE_ADDR: %s\n")
            xT("REMOTE_HOST: %s\n")
            xT("REMOTE_IDENT: %s\n")
            xT("REMOTE_PORT: %s\n")
            xT("REMOTE_USER: %s\n")
            xT("REQUEST_METHOD: %s\n")
            xT("REQUEST_URI: %s\n")
            xT("SCRIPT_FILENAME: %s\n")
            xT("SCRIPT_NAME: %s\n")
            xT("SERVER_ADMIN: %s\n")
            xT("SERVER_NAME: %s\n")
            xT("SERVER_PORT: %s\n")
            xT("SERVER_PROTOCOL: %s\n")
            xT("SERVER_SOFTWARE: %s\n")
            xT("HTTP_REFERER: %s\n")
            xT("HTTP_HOST: %s\n")
            xT("HTTP_ACCEPT_LANGUAGE: %s\n")
            xT("GEOIP_COUNTRY_CODE: %s\n\n"),
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
bool
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
    if        (false != CxString::bCompareNoCase(xT("GET"), sGetRequestMethod()) ) {
        _m_rmRequestMethod = rmGet;
    } else if (false != CxString::bCompareNoCase(xT("POST"), sGetRequestMethod()) ) {
        _m_rmRequestMethod = rmPost;
    }
    else {
        _m_rmRequestMethod = rmUknown;
    }

    return true;
}
//---------------------------------------------------------------------------


/**
 * \class CxCgiCookies
 * \brief CGI cookies
 */

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCgiCookies::CxCgiCookies(
    CxCgi &ccgCgi
):
    _m_ccgCgi(ccgCgi)
{
    _bInit();
}
//---------------------------------------------------------------------------
/*virtual*/
CxCgiCookies::~CxCgiCookies() {
    for (TCookies::iterator it = Items.begin(); it != Items.end(); ++ it) {
        xPTR_DELETE(*it);
    }
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::operator [] (
    const std::tstring_t &csCookieName
)
{
    /*DEBUG*/

    for (TCookies::const_iterator it = Items.begin(); it != Items.end(); ++ it) {
        xCHECK_DO(false == CxString::bCompareNoCase(csCookieName, (*it)->sGetValue()), continue);

        return (*it)->sGetValue();
    }

    return std::tstring_t();
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::sGetDump() const {
    /*DEBUG*/

    std::tstring_t sRes;

    sRes.append(xT("[CxCgiCookies dump]\n\n"));

    for (TCookies::const_iterator it = Items.begin(); it != Items.end(); ++ it) {
        std::tstring_t sItemN = CxString::sFormat(
                xT("Name: %s\n")
                xT("Value: %s\n")
                xT("Domain: %s\n")
                xT("Path: %s\n")
                xT("Expires: %s\n")
                xT("Secure: %s\n")
                xT("HttpOnly: %s\n\n"),
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
bool
CxCgiCookies::_bInit() {
    /*DEBUG*/

    bool                 bRes           = false;
    std::tstring_t              sRawCookies    = _m_ccgCgi.Environment.sGetHttpCookie();
    std::vector<std::tstring_t> vsRawCookies;
    TCookies             vecckCookies;

    bRes = CxString::bSplit(sRawCookies, CxConst::xSEMICOLON, &vsRawCookies);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    for (std::vector<std::tstring_t>::const_iterator it = vsRawCookies.begin(); it != vsRawCookies.end(); ++ it) {
        CxCookiePv0 *pckItem = new(std::nothrow) CxCookiePv0(*it);
        /*DEBUG*/xASSERT_RET(NULL != pckItem, false);

        vecckCookies.push_back(pckItem);
    }

    std::swap(vecckCookies, Items);

    return true;
}
//---------------------------------------------------------------------------


/**
 * \class CxCgiFormData
 * \brief CGI form data
 */

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCgiFormData::CxCgiFormData(
    CxCgi        &ccgCgi,
    const size_t  cuiMaxSize
) :
    _m_cuiMaxData(cuiMaxSize),
    _m_ccgCgi    (ccgCgi)
{
    _bInit();
}
//---------------------------------------------------------------------------
/*virtual*/
CxCgiFormData::~CxCgiFormData() {

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiFormData::sGetRawData() const {
    /*DEBUG*/

    return _m_sFormData;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiFormData::sGetDump() const {
    /*DEBUG*/

    std::tstring_t sRes;

    sRes = CxString::sFormat(
            xT("[CxCgiFormData dump]\n\n")
            xT("Data: %s\n\n"),
            sGetRawData().c_str());

    return sRes;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxCgiFormData::_bInit() {
    /*DEBUG*/

    int iRes = _m_ccgCgi.Environment.rmGetRequestMethod();
    switch (iRes) {
        case CxCgiEnvironment::rmGet: {
                /*DEBUG*/xASSERT_RET(false == _m_ccgCgi.Environment.sGetQueryString().empty(), false);

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = _m_ccgCgi.Environment.sGetQueryString();
            }
            break;

        case CxCgiEnvironment::rmPost: {
                bool bRes = false;

                bRes = CxString::bCompareNoCase(xT("application/x-www-form-urlencoded"), _m_ccgCgi.Environment.sGetContentType());
                /*DEBUG*/xASSERT_RET(true == bRes, false);

                //get content length
                size_t uiPostSize = 0;  // in bytes
                if (true == _m_ccgCgi.Environment.sGetContentLength().empty()) {
                    uiPostSize = 0;
                }
                else {
                    uiPostSize = CxString::lexical_cast<size_t>( _m_ccgCgi.Environment.sGetContentLength() );
                }
                /*DEBUG*/xASSERT_RET(0U            <  uiPostSize, false);
                /*DEBUG*/xASSERT_RET(_m_cuiMaxData >= uiPostSize, false);  //secure
                xCHECK_RET(_m_cuiMaxData <= uiPostSize, false);


                //read, parse data
                CxFile       sfFile;
                std::tstring_t sBuff;

                bRes = sfFile.bAttach(stdin);
                /*DEBUG*/xASSERT_RET(true == bRes, false);

                sBuff.resize(uiPostSize);

                size_t uiRes = sfFile.uiRead(&sBuff.at(0), sBuff.size());
                /*DEBUG*/xASSERT_RET(uiRes == sBuff.size(), false);

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = sBuff;

                (void)sfFile.pDetach();
            }
            break;

        default: {
                /////*DEBUG*/xASSERT_RET(false, false);
            }
            break;
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
