/**
 * \file  CxHttpClient.h
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#ifndef xLib_Net_CxHttpClientH
#define xLib_Net_CxHttpClientH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxHttpClient :
    private CxNonCopyable
    /// protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
{
public:
    //status line
    class CxStatusLine;

    //header
    class CxHeader;

    //body
    class CxBody;

    enum ExProtocolVersion
        /// protocol version
    {
        pv10 = 0,
        pv11 = 1
    };

    enum ExMethod
        /// method
    {
        hmHead,
        hmGet,
        hmPost,
        hmOptions,
        hmTrace,
        hmPut,
        hmDelete,
        hmConnect,
        hmPatch,
        hmLink,
        hmUnlink
    };

    void     head        (std::ctstring_t &csUrl,  std::tstring_t *psResponse);
    void     get         (std::ctstring_t &csUrl,  std::tstring_t *psResponse);
    void     post        (std::ctstring_t &csUrl,  std::ctstring_t &csParams, std::tstring_t *psResponse);
    void     options     (std::ctstring_t &csUrl);
    void     trace       (std::ctstring_t &csUrl);
    void     put         (std::ctstring_t &csUrl);
    void     del         (std::ctstring_t &csUrl);
    void     connect     (std::ctstring_t &csUrl);
    void     patch       (std::ctstring_t &csUrl);
    void     link        (std::ctstring_t &csUrl);
    void     unlink      (std::ctstring_t &csUrl);

             CxHttpClient();
    virtual ~CxHttpClient();
};
//------------------------------------------------------------------------------
class CxHttpClient::CxStatusLine
    /// HTTP status line
{
public:
             CxStatusLine();
    virtual ~CxStatusLine();

private:

};
//------------------------------------------------------------------------------
class CxHttpClient::CxHeader
    /// HTTP header
{
public:
             CxHeader();
    virtual ~CxHeader();

private:

};
//------------------------------------------------------------------------------
class CxHttpClient::CxBody
    /// HTTP nody
{
public:
             CxBody();
    virtual ~CxBody();

private:

};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxHttpClientH
