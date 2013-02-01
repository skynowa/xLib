/**
 * \file  CxCgi.cpp
 * \brief CGI
 */


#include <xLib/Net/CxCgi.h>

#include <xLib/Common/CxUtils.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>


xNAMESPACE_BEGIN(NxLib)

using namespace NxCgi;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCgi::CxCgi(
    const size_t a_cuiMaxSize
) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, a_cuiMaxSize)
{
}
//---------------------------------------------------------------------------
/* virtual */
CxCgi::~CxCgi() {

}
//---------------------------------------------------------------------------
std::tstring_t
CxCgi::dump() const {
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CGI dump]\n\n")
            xT("%s\n")
            xT("%s\n")
            xT("%s\n"),
            Environment.dump().c_str(),
            Cookies.dump().c_str(),
            Formdata.dump().c_str()
    );

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxCgi::redirect(
    const std::tstring_t &a_csUrl
)
{
    xTEST_EQ(false, a_csUrl.empty())

    std::tstring_t sHttpResponse;

    sHttpResponse.append( CxString::format(xT("Location: %s\n"), a_csUrl.c_str()) );
    sHttpResponse.append( CxConst::xNL );

    std::tcout << sHttpResponse << std::endl;
}
//---------------------------------------------------------------------------
/* static */
void
CxCgi::pageShow(
    const std::tstring_t &a_csFilePath
)
{
    std::tstring_t sFileContent;

    CxFile::textRead(a_csFilePath, &sFileContent);

    std::tcout << sFileContent << std::endl;
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
/* static */
void
CxCgi::uriEncode(
    const std::tstring_t &a_csUri,
    const std::tstring_t &a_csReserved,
    std::tstring_t       *a_psEncodedStr
)
{
    xFOREACH_CONST(std::tstring_t, it, a_csUri) {
        tchar_t chChar = *it;

        if ((chChar >= 'a' && chChar <= 'z') || (chChar >= 'A' && chChar <= 'Z') || (chChar >= '0' && chChar <= '9') ||
             chChar == '-' || chChar == '_'  || chChar == '.' || chChar == '~')
        {
            (*a_psEncodedStr) += chChar;
        }
        else if (chChar <= 0x20 || chChar >= 0x7F || std::tstring_t::npos != URI_ILLEGAL.find(chChar) || std::tstring_t::npos != a_csReserved.find(chChar)) {
            (*a_psEncodedStr) += '%';
            //--encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) chChar, 2);

            /*
                poco_assert (width > 0 && width < 64);

                char buffer[64];
                std::sprintf(buffer, "%0*X", width, value);
                str.append(buffer);
             */
            (*a_psEncodedStr) += CxString::format(xT("%0*X"), 2, (uint_t)(uchar_t)chChar);
        }
        else {
            (*a_psEncodedStr) += chChar;
        }
    }
}
//---------------------------------------------------------------------------
//TODO: bUriDecode ()
/* static */
void
CxCgi::uriDecode(
    const std::tstring_t &a_csUri,
    std::tstring_t       *a_psDecodedStr
)
{
    std::tstring_t::const_iterator it  = a_csUri.begin();
    std::tstring_t::const_iterator end = a_csUri.end();

    while (it != end) {
        tchar_t chChar = *it++;

        if (chChar == '%') {
            if (it == end) {
                ////throw SyntaxException("URI encoding: no hex digit following percent sign", str);
                xTEST_FAIL;
            }

            tchar_t hi = *it++;
            if (it == end) {
                ////throw SyntaxException("URI encoding: two hex digits must follow percent sign", str);
                xTEST_FAIL;
            }

            tchar_t lo = *it++;
            if (hi >= '0' && hi <= '9')
                chChar = hi - '0';
            else if (hi >= 'A' && hi <= 'F')
                chChar = hi - 'A' + 10;
            else if (hi >= 'a' && hi <= 'f')
                chChar = hi - 'a' + 10;
            else {
                ////throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
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
                xTEST_FAIL;
            }
        }

        (*a_psDecodedStr) += chChar;
    }
}
//----------------------------------------------------------------------------------------------------
//TODO: cgl_parsecgibuf
int
cgl_parsecgibuf(/*cgllist *cdata,*/ char *a_query) {
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
//    std::tstring_t sRv = CxString::replaceAll(s, CxConst::xSPACE, xT("+"));
//
//    vUrlEscape(sRv, fw);
//
//    return 
//}
////----------------------------------------------------------------------------------------------------
////TODO: cgl_urldecode
//void
//CxCgi::cgl_urldecode(char *s) {
//    //--cgl_charify(s, '+', ' ');
//    std::tstring_t sRv;
//
//    sRv = CxString::replaceAll(s, xT("+"), CxConst::xSPACE);
//
//    vUrlUnescape(sRv);
//}
//----------------------------------------------------------------------------------------------------
//TODO: bUrlEscape
void
CxCgi::urlEscape(char *a_s, FILE *a_fw) {
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
}
//----------------------------------------------------------------------------------------------------
//TODO: bUrlUnescape
//modified from the Apache code. Code shrinks string, so can be done in place.
void
CxCgi::urlUnescape(char *a_s) {
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
}
//----------------------------------------------------------------------------------------------------
//TODO: cgl_hex2char
//ripped off from the Apache code
char
CxCgi::cgl_hex2char(char *a_what) {
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
    CxCgi &a_ccgCgi
) :
    _m_ccgCgi         (a_ccgCgi),
    _m_rtRequestType(rtUknown)
{
    _init();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiEnvironment::~CxCgiEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: sGetAuthType
const std::tstring_t &
CxCgiEnvironment::authType() const {
    return _m_sAuthType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::contentLength() const {
    return _m_sContentLength;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::contentType() const {
    return _m_sContentType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::documentRoot() const {
    return _m_sDocumentRoot;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::gatewayInterface() const {
    return _m_sGatewayInterface;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpAccept() const {
    return _m_sHttpAccept;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpCookie() const {
    return _m_sHttpCookie;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpPragma() const {
    return _m_sHttpPragma;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpUserAgent() const {
    return _m_sHttpUserAgent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::pathInfo() const {
    return _m_sPathInfo;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::pathTranslated() const {
    return _m_sPathTranslated;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::queryString() const {
    return _m_sQueryString;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::remoteAddr() const {
    return _m_sRemoteAddr;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::remoteHost() const {
    return _m_sRemoteHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::remoteIdent() const {
    return _m_sRemoteIdent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::remotePort() const {
    return _m_sRemotePort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::remoteUser() const {
    return _m_sRemoteUser;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::requestMethod() const {
    return _m_sRequestMethod;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::requestUri() const {
    return _m_sRequestUri;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::scriptFilename() const {
    return _m_sScriptFilename;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::scriptName() const {
    return _m_sScriptName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::serverAdmin() const {
    return _m_sServerAdmin;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::serverName() const {
    return _m_sServerName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::serverPort() const {
    return _m_sServerPort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::serverProtocol() const {
    return _m_sServerProtocol;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::serverSoftware() const {
    return _m_sServerSoftware;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpReferer() const {
    return _m_sHttpReferer;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpHost() const {
    return _m_sHttpHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::httpAcceptLanguage() const {
   return _m_sHttpAcceptLanguage;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::countryCode() const {
    return _m_sCountryCode;
}
//---------------------------------------------------------------------------
CxCgiEnvironment::ExRequestType
CxCgiEnvironment::requestType() const {
    return _m_rtRequestType;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiEnvironment::dump() const {
    std::tstring_t sRv;

    sRv = CxString::format(
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
            authType().c_str(),
            contentLength().c_str(),
            contentType().c_str(),
            documentRoot().c_str(),
            gatewayInterface().c_str(),
            httpAccept().c_str(),
            httpCookie().c_str(),
            httpPragma().c_str(),
            httpUserAgent().c_str(),
            pathInfo().c_str(),
            pathTranslated().c_str(),
            queryString().c_str(),
            remoteAddr().c_str(),
            remoteHost().c_str(),
            remoteIdent().c_str(),
            remotePort().c_str(),
            remoteUser().c_str(),
            requestMethod().c_str(),
            requestUri().c_str(),
            scriptFilename().c_str(),
            scriptName().c_str(),
            serverAdmin().c_str(),
            serverName().c_str(),
            serverPort().c_str(),
            serverProtocol().c_str(),
            serverSoftware().c_str(),
            httpReferer().c_str(),
            httpHost().c_str(),
            httpAcceptLanguage().c_str(),
            countryCode().c_str()
    );

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxCgiEnvironment::_init() {
    _m_sAuthType           = CxEnvironment::var(xT("AUTH_TYPE"));
    _m_sContentLength      = CxEnvironment::var(xT("CONTENT_LENGTH"));
    _m_sContentType        = CxEnvironment::var(xT("CONTENT_TYPE"));
    _m_sDocumentRoot       = CxEnvironment::var(xT("DOCUMENT_ROOT"));
    _m_sGatewayInterface   = CxEnvironment::var(xT("GATEWAY_INTERFACE"));
    _m_sHttpAccept         = CxEnvironment::var(xT("HTTP_ACCEPT"));
    _m_sHttpCookie         = CxEnvironment::var(xT("HTTP_COOKIE"));
    _m_sHttpPragma         = CxEnvironment::var(xT("HTTP_PRAGMA"));
    _m_sHttpUserAgent      = CxEnvironment::var(xT("HTTP_USER_AGENT"));
    _m_sPathInfo           = CxEnvironment::var(xT("PATH_INFO"));
    _m_sPathTranslated     = CxEnvironment::var(xT("PATH_TRANSLATED"));
    _m_sQueryString        = CxEnvironment::var(xT("QUERY_STRING"));
    _m_sRemoteAddr         = CxEnvironment::var(xT("REMOTE_ADDR"));
    _m_sRemoteHost         = CxEnvironment::var(xT("REMOTE_HOST"));
    _m_sRemoteIdent        = CxEnvironment::var(xT("REMOTE_IDENT"));
    _m_sRemotePort         = CxEnvironment::var(xT("REMOTE_PORT"));
    _m_sRemoteUser         = CxEnvironment::var(xT("REMOTE_USER"));
    _m_sRequestMethod      = CxEnvironment::var(xT("REQUEST_METHOD"));
    _m_sRequestUri         = CxEnvironment::var(xT("REQUEST_URI"));
    _m_sScriptFilename     = CxEnvironment::var(xT("SCRIPT_FILENAME"));
    _m_sScriptName         = CxEnvironment::var(xT("SCRIPT_NAME"));
    _m_sServerAdmin        = CxEnvironment::var(xT("SERVER_ADMIN"));
    _m_sServerName         = CxEnvironment::var(xT("SERVER_NAME"));
    _m_sServerPort         = CxEnvironment::var(xT("SERVER_PORT"));
    _m_sServerProtocol     = CxEnvironment::var(xT("SERVER_PROTOCOL"));
    _m_sServerSoftware     = CxEnvironment::var(xT("SERVER_SOFTWARE"));
    _m_sHttpReferer        = CxEnvironment::var(xT("HTTP_REFERER"));
    _m_sHttpHost           = CxEnvironment::var(xT("HTTP_HOST"));
    _m_sHttpAcceptLanguage = CxEnvironment::var(xT("HTTP_ACCEPT_LANGUAGE"));
    _m_sCountryCode        = CxEnvironment::var(xT("GEOIP_COUNTRY_CODE"));

    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::var(xT("HTTP_GEOIP_COUNTRY_CODE"));
    }
    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::var(xT("HTTP_COUNTRY_CODE"));
    }

    //--------------------------------------------------
    //is data from a GET or a POST?
    if        (false != CxString::compareNoCase(xT("GET"), requestMethod()) ) {
        _m_rtRequestType = rtGet;
    } else if (false != CxString::compareNoCase(xT("POST"), requestMethod()) ) {
        _m_rtRequestType = rtPost;
    }
    else {
        _m_rtRequestType = rtUknown;
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
    CxCgi &a_ccgCgi
):
    _m_ccgCgi(a_ccgCgi)
{
    _init();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiCookies::~CxCgiCookies() {
    xFOREACH(TCookies, it, items) {
        xPTR_DELETE(*it);
    }
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::operator [] (
    const std::tstring_t &a_csCookieName
)
{
    xFOREACH_CONST(TCookies, it, items) {
        xCHECK_DO(false == CxString::compareNoCase(a_csCookieName, (*it)->sValue()), continue);

        return (*it)->sValue();
    }

    return std::tstring_t();
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::dump() const {
    std::tstring_t sRv;

    sRv.append(xT("[CxCgiCookies dump]\n\n"));

    xFOREACH_CONST(TCookies, it, items) {
        std::tstring_t sItemN = CxString::format(
                xT("Name: %s\n")
                xT("Value: %s\n")
                xT("Domain: %s\n")
                xT("Path: %s\n")
                xT("Expires: %s\n")
                xT("Secure: %s\n")
                xT("HttpOnly: %s\n\n"),
                (*it)->sName().c_str(),
                (*it)->sValue().c_str(),
                (*it)->sDomain().c_str(),
                (*it)->sPath().c_str(),
                (*it)->sExpires().c_str(),
                CxString::boolToStr((*it)->bGetSecure()).c_str(),
                CxString::boolToStr((*it)->bGetHttpOnly()).c_str()
        );

        sRv.append( xT("[Item]:\n") );
        sRv.append(sItemN);
        sRv.append(CxConst::xNL);
    }

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxCgiCookies::_init() {
    std::tstring_t     sRawCookies = _m_ccgCgi.Environment.httpCookie();
    std::vec_tstring_t vsRawCookies;
    TCookies           vecckCookies;

    CxString::split(sRawCookies, CxConst::xSEMICOLON, &vsRawCookies);

    xFOREACH_CONST(std::vec_tstring_t, it, vsRawCookies) {
        CxCookiePv0 *pckItem = new(std::nothrow) CxCookiePv0(*it);
        xTEST_PTR(pckItem);

        vecckCookies.push_back(pckItem);
    }

    std::swap(vecckCookies, items);
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
    CxCgi        &a_ccgCgi,
    const size_t  a_cuiMaxSize
) :
    _m_cuiMaxData(a_cuiMaxSize),
    _m_ccgCgi    (a_ccgCgi)
{
    _init();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiFormData::~CxCgiFormData() {

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiFormData::rawData() const {
    return _m_sFormData;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiFormData::dump() const {
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CxCgiFormData dump]\n\n")
            xT("Data: %s\n\n"),
            rawData().c_str());

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxCgiFormData::_init() {
    int iRv = _m_ccgCgi.Environment.requestType();
    switch (iRv) {
        case CxCgiEnvironment::rtGet: {
                xTEST_EQ(false, _m_ccgCgi.Environment.queryString().empty());

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = _m_ccgCgi.Environment.queryString();
            }
            break;

        case CxCgiEnvironment::rtPost: {
                bool bRv = false;

                bRv = CxString::compareNoCase(xT("application/x-www-form-urlencoded"), _m_ccgCgi.Environment.contentType());
                xTEST_EQ(true, bRv);

                //get content length
                size_t uiPostSize = 0;  // in bytes
                if (true == _m_ccgCgi.Environment.contentLength().empty()) {
                    uiPostSize = 0;
                }
                else {
                    uiPostSize = CxString::cast<size_t>( _m_ccgCgi.Environment.contentLength() );
                }
                xTEST_LESS(size_t(0U), uiPostSize);
                xTEST_GR_EQ(_m_cuiMaxData, uiPostSize);  //secure
                xTEST_EQ(false, _m_cuiMaxData <= uiPostSize);

                //read, parse data
                CxFile       sfFile;
                std::tstring_t sBuff;

                sfFile.attach(stdin);

                sBuff.resize(uiPostSize);

                size_t uiRes = sfFile.read(&sBuff.at(0), sBuff.size());
                xTEST_EQ(uiRes, sBuff.size());

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = sBuff;

                (FILE *)sfFile.detach();
            }
            break;

        default: {
                ////xTEST_FAIL;
            }
            break;
    }
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
