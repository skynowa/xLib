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

    void     head        (const std::tstring_t &csUrl,  std::tstring_t *psResponse);
    void     get         (const std::tstring_t &csUrl,  std::tstring_t *psResponse);
    void     post        (const std::tstring_t &csUrl,  const std::tstring_t &csParams, std::tstring_t *psResponse);
    void     options     (const std::tstring_t &csUrl);
    void     trace       (const std::tstring_t &csUrl);
    void     put         (const std::tstring_t &csUrl);
    void     del         (const std::tstring_t &csUrl);
    void     connect     (const std::tstring_t &csUrl);
    void     patch       (const std::tstring_t &csUrl);
    void     link        (const std::tstring_t &csUrl);
    void     unlink      (const std::tstring_t &csUrl);

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
