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
CxCgi::sDump()  const{
    /*DEBUG*/

    std::tstring_t sRv;

    sRv = CxString::sFormat(
            xT("[CGI dump]\n\n")
            xT("%s\n")
            xT("%s\n")
            xT("%s\n"),
            Environment.sDump().c_str(),
            Cookies.sDump().c_str(),
            Formdata.sDump().c_str()
    );

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxCgi::vRedirect(
    const std::tstring_t &a_csUrl
)
{
    /*DEBUG*/xTEST_EQ(false, a_csUrl.empty())

    std::tstring_t sHttpResponse;

    sHttpResponse.append( CxString::sFormat(xT("Location: %s\n"), a_csUrl.c_str()) );
    sHttpResponse.append( CxConst::xNL );

    std::tcout << sHttpResponse << std::endl;
}
//---------------------------------------------------------------------------
/* static */
void
CxCgi::vPageShow(
    const std::tstring_t &a_csFilePath
)
{
    std::tstring_t sFileContent;

    CxFile::vTextRead(a_csFilePath, &sFileContent);

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
CxCgi::vUriEncode(
    const std::tstring_t &a_csUri,
    const std::tstring_t &a_csReserved,
    std::tstring_t       *a_psEncodedStr
)
{
    xFOREACH_CONST(std::tstring_t, it, a_csUri) {
        char chChar = *it;

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
            (*a_psEncodedStr) += CxString::sFormat(xT("%0*X"), 2, (uint_t)(uchar_t)chChar);
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
CxCgi::vUriDecode(
    const std::tstring_t &a_csUri,
    std::tstring_t       *a_psDecodedStr
)
{
    std::tstring_t::const_iterator it  = a_csUri.begin();
    std::tstring_t::const_iterator end = a_csUri.end();

    while (it != end) {
        char chChar = *it++;

        if (chChar == '%') {
            if (it == end) {
                ////throw SyntaxException("URI encoding: no hex digit following percent sign", str);
                xTEST_FAIL;
            }

            char hi = *it++;
            if (it == end) {
                ////throw SyntaxException("URI encoding: two hex digits must follow percent sign", str);
                xTEST_FAIL;
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
//    std::tstring_t sRv = CxString::sReplaceAll(s, CxConst::xSPACE, xT("+"));
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
//    sRv = CxString::sReplaceAll(s, xT("+"), CxConst::xSPACE);
//
//    vUrlUnescape(sRv);
//}
//----------------------------------------------------------------------------------------------------
//TODO: bUrlEscape
void
CxCgi::vUrlEscape(char *a_s, FILE *a_fw) {
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
CxCgi::vUrlUnescape(char *a_s) {
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
    _m_rmRequestMethod(rmUknown)
{
    _bInit();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiEnvironment::~CxCgiEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: sGetAuthType
const std::tstring_t &
CxCgiEnvironment::sAuthType() const {
    /*DEBUG*/

    return _m_sAuthType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sContentLength() const {
    /*DEBUG*/

    return _m_sContentLength;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sContentType() const {
    /*DEBUG*/

    return _m_sContentType;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sDocumentRoot() const {
    /*DEBUG*/

    return _m_sDocumentRoot;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sGatewayInterface() const {
    /*DEBUG*/

    return _m_sGatewayInterface;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpAccept() const {
    /*DEBUG*/

    return _m_sHttpAccept;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpCookie() const {
    /*DEBUG*/

    return _m_sHttpCookie;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpPragma() const {
    /*DEBUG*/

    return _m_sHttpPragma;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpUserAgent() const {
    /*DEBUG*/

    return _m_sHttpUserAgent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sPathInfo() const {
    /*DEBUG*/

    return _m_sPathInfo;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sPathTranslated() const {
    /*DEBUG*/

    return _m_sPathTranslated;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sQueryString() const {
    /*DEBUG*/

    return _m_sQueryString;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRemoteAddr() const {
    /*DEBUG*/

    return _m_sRemoteAddr;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRemoteHost() const {
    /*DEBUG*/

    return _m_sRemoteHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRemoteIdent() const {
    /*DEBUG*/

    return _m_sRemoteIdent;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRemotePort() const {
    /*DEBUG*/

    return _m_sRemotePort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRemoteUser() const {
    /*DEBUG*/

    return _m_sRemoteUser;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRequestMethod() const {
    /*DEBUG*/

    return _m_sRequestMethod;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sRequestUri() const {
    /*DEBUG*/

    return _m_sRequestUri;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sScriptFilename() const {
    /*DEBUG*/

    return _m_sScriptFilename;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sScriptName() const {
    /*DEBUG*/

    return _m_sScriptName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sServerAdmin() const {
    /*DEBUG*/

    return _m_sServerAdmin;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sServerName() const {
    /*DEBUG*/

    return _m_sServerName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sServerPort() const {
    /*DEBUG*/

    return _m_sServerPort;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sServerProtocol() const {
    /*DEBUG*/

    return _m_sServerProtocol;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sServerSoftware() const {
    /*DEBUG*/

    return _m_sServerSoftware;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpReferer() const {
    /*DEBUG*/

    return _m_sHttpReferer;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpHost() const {
    /*DEBUG*/

    return _m_sHttpHost;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sHttpAcceptLanguage() const {
   /*DEBUG*/

   return _m_sHttpAcceptLanguage;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiEnvironment::sCountryCode() const {
    /*DEBUG*/

    return _m_sCountryCode;
}
//---------------------------------------------------------------------------
CxCgiEnvironment::ExRequestMethod
CxCgiEnvironment::rmRequestMethod() const {
    /*DEBUG*/

    return _m_rmRequestMethod;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiEnvironment::sDump() const {
    /*DEBUG*/

    std::tstring_t sRv;

    sRv = CxString::sFormat(
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
            sAuthType().c_str(),
            sContentLength().c_str(),
            sContentType().c_str(),
            sDocumentRoot().c_str(),
            sGatewayInterface().c_str(),
            sHttpAccept().c_str(),
            sHttpCookie().c_str(),
            sHttpPragma().c_str(),
            sHttpUserAgent().c_str(),
            sPathInfo().c_str(),
            sPathTranslated().c_str(),
            sQueryString().c_str(),
            sRemoteAddr().c_str(),
            sRemoteHost().c_str(),
            sRemoteIdent().c_str(),
            sRemotePort().c_str(),
            sRemoteUser().c_str(),
            sRequestMethod().c_str(),
            sRequestUri().c_str(),
            sScriptFilename().c_str(),
            sScriptName().c_str(),
            sServerAdmin().c_str(),
            sServerName().c_str(),
            sServerPort().c_str(),
            sServerProtocol().c_str(),
            sServerSoftware().c_str(),
            sHttpReferer().c_str(),
            sHttpHost().c_str(),
            sHttpAcceptLanguage().c_str(),
            sCountryCode().c_str()
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
CxCgiEnvironment::_bInit() {
    /*DEBUG*/

    _m_sAuthType           = CxEnvironment::sVar(xT("AUTH_TYPE"));
    _m_sContentLength      = CxEnvironment::sVar(xT("CONTENT_LENGTH"));
    _m_sContentType        = CxEnvironment::sVar(xT("CONTENT_TYPE"));
    _m_sDocumentRoot       = CxEnvironment::sVar(xT("DOCUMENT_ROOT"));
    _m_sGatewayInterface   = CxEnvironment::sVar(xT("GATEWAY_INTERFACE"));
    _m_sHttpAccept         = CxEnvironment::sVar(xT("HTTP_ACCEPT"));
    _m_sHttpCookie         = CxEnvironment::sVar(xT("HTTP_COOKIE"));
    _m_sHttpPragma         = CxEnvironment::sVar(xT("HTTP_PRAGMA"));
    _m_sHttpUserAgent      = CxEnvironment::sVar(xT("HTTP_USER_AGENT"));
    _m_sPathInfo           = CxEnvironment::sVar(xT("PATH_INFO"));
    _m_sPathTranslated     = CxEnvironment::sVar(xT("PATH_TRANSLATED"));
    _m_sQueryString        = CxEnvironment::sVar(xT("QUERY_STRING"));
    _m_sRemoteAddr         = CxEnvironment::sVar(xT("REMOTE_ADDR"));
    _m_sRemoteHost         = CxEnvironment::sVar(xT("REMOTE_HOST"));
    _m_sRemoteIdent        = CxEnvironment::sVar(xT("REMOTE_IDENT"));
    _m_sRemotePort         = CxEnvironment::sVar(xT("REMOTE_PORT"));
    _m_sRemoteUser         = CxEnvironment::sVar(xT("REMOTE_USER"));
    _m_sRequestMethod      = CxEnvironment::sVar(xT("REQUEST_METHOD"));
    _m_sRequestUri         = CxEnvironment::sVar(xT("REQUEST_URI"));
    _m_sScriptFilename     = CxEnvironment::sVar(xT("SCRIPT_FILENAME"));
    _m_sScriptName         = CxEnvironment::sVar(xT("SCRIPT_NAME"));
    _m_sServerAdmin        = CxEnvironment::sVar(xT("SERVER_ADMIN"));
    _m_sServerName         = CxEnvironment::sVar(xT("SERVER_NAME"));
    _m_sServerPort         = CxEnvironment::sVar(xT("SERVER_PORT"));
    _m_sServerProtocol     = CxEnvironment::sVar(xT("SERVER_PROTOCOL"));
    _m_sServerSoftware     = CxEnvironment::sVar(xT("SERVER_SOFTWARE"));
    _m_sHttpReferer        = CxEnvironment::sVar(xT("HTTP_REFERER"));
    _m_sHttpHost           = CxEnvironment::sVar(xT("HTTP_HOST"));
    _m_sHttpAcceptLanguage = CxEnvironment::sVar(xT("HTTP_ACCEPT_LANGUAGE"));
    _m_sCountryCode        = CxEnvironment::sVar(xT("GEOIP_COUNTRY_CODE"));

    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::sVar(xT("HTTP_GEOIP_COUNTRY_CODE"));
    }
    if (true == _m_sCountryCode.empty()) {
        _m_sCountryCode    = CxEnvironment::sVar(xT("HTTP_COUNTRY_CODE"));
    }

    //--------------------------------------------------
    //is data from a GET or a POST?
    if        (false != CxString::bCompareNoCase(xT("GET"), sRequestMethod()) ) {
        _m_rmRequestMethod = rmGet;
    } else if (false != CxString::bCompareNoCase(xT("POST"), sRequestMethod()) ) {
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
    CxCgi &a_ccgCgi
):
    _m_ccgCgi(a_ccgCgi)
{
    _vInit();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiCookies::~CxCgiCookies() {
    xFOREACH(TCookies, it, Items) {
        xPTR_DELETE(*it);
    }
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::operator [] (
    const std::tstring_t &a_csCookieName
)
{
    /*DEBUG*/

    xFOREACH_CONST(TCookies, it, Items) {
        xCHECK_DO(false == CxString::bCompareNoCase(a_csCookieName, (*it)->sValue()), continue);

        return (*it)->sValue();
    }

    return std::tstring_t();
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiCookies::sDump() const {
    /*DEBUG*/

    std::tstring_t sRv;

    sRv.append(xT("[CxCgiCookies dump]\n\n"));

    xFOREACH_CONST(TCookies, it, Items) {
        std::tstring_t sItemN = CxString::sFormat(
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
                CxString::sBoolToStr((*it)->bGetSecure()).c_str(),
                CxString::sBoolToStr((*it)->bGetHttpOnly()).c_str()
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
CxCgiCookies::_vInit() {
    /*DEBUG*/

    std::tstring_t     sRawCookies = _m_ccgCgi.Environment.sHttpCookie();
    std::vec_tstring_t vsRawCookies;
    TCookies           vecckCookies;

    CxString::vSplit(sRawCookies, CxConst::xSEMICOLON, &vsRawCookies);

    xFOREACH_CONST(std::vec_tstring_t, it, vsRawCookies) {
        CxCookiePv0 *pckItem = new(std::nothrow) CxCookiePv0(*it);
        /*DEBUG*/xTEST_PTR(pckItem);

        vecckCookies.push_back(pckItem);
    }

    std::swap(vecckCookies, Items);
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
    _vInit();
}
//---------------------------------------------------------------------------
/* virtual */
CxCgiFormData::~CxCgiFormData() {

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCgiFormData::sRawData() const {
    /*DEBUG*/

    return _m_sFormData;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCgiFormData::sDump() const {
    /*DEBUG*/

    std::tstring_t sRv;

    sRv = CxString::sFormat(
            xT("[CxCgiFormData dump]\n\n")
            xT("Data: %s\n\n"),
            sRawData().c_str());

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxCgiFormData::_vInit() {
    /*DEBUG*/

    int iRv = _m_ccgCgi.Environment.rmRequestMethod();
    switch (iRv) {
        case CxCgiEnvironment::rmGet: {
                /*DEBUG*/xTEST_EQ(false, _m_ccgCgi.Environment.sQueryString().empty());

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = _m_ccgCgi.Environment.sQueryString();
            }
            break;

        case CxCgiEnvironment::rmPost: {
                bool bRv = false;

                bRv = CxString::bCompareNoCase(xT("application/x-www-form-urlencoded"), _m_ccgCgi.Environment.sContentType());
                /*DEBUG*/xTEST_EQ(true, bRv);

                //get content length
                size_t uiPostSize = 0;  // in bytes
                if (true == _m_ccgCgi.Environment.sContentLength().empty()) {
                    uiPostSize = 0;
                }
                else {
                    uiPostSize = CxString::string_cast<size_t>( _m_ccgCgi.Environment.sContentLength() );
                }
                /*DEBUG*/xTEST_LESS(size_t(0U), uiPostSize);
                /*DEBUG*/xTEST_GR_EQ(_m_cuiMaxData, uiPostSize);  //secure
                xTEST_EQ(false, _m_cuiMaxData <= uiPostSize);

                //read, parse data
                CxFile       sfFile;
                std::tstring_t sBuff;

                sfFile.vAttach(stdin);

                sBuff.resize(uiPostSize);

                size_t uiRes = sfFile.uiRead(&sBuff.at(0), sBuff.size());
                /*DEBUG*/xTEST_EQ(uiRes, sBuff.size());

                //TODO: cgl_parsecgibuf(cgl_Formdata, cgl_Buf)

                _m_sFormData = sBuff;

                (void)sfFile.pDetach();
            }
            break;

        default: {
                /////*DEBUG*/xTEST_FAIL;
            }
            break;
    }
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
