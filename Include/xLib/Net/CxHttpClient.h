/**
 * \file  CxHttpClient.h
 * \brief protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
 */


#ifndef xLib_Net_CxHttpClientH
#define xLib_Net_CxHttpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxHttpClient :
    public CxNonCopyable
    /// protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
{
    public:
        //status line
        class CxStatusLine;

        //header
        class CxHeader;

        //body
        class CxBody;

        enum EProtocolVersion
            /// protocol version
        {
            pv10 = 0,
            pv11 = 1
        };

        enum EMethod
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

        BOOL     bHead   (const std::string &csUrl,  std::string *psResponse);
        BOOL     bGet    (const std::string &csUrl,  std::string *psResponse);
        BOOL     bPost   (const std::string &csUrl,  const std::string &csParams, std::string *psResponse);
        BOOL     bOptions(const std::string &csUrl);
        BOOL     bTrace  (const std::string &csUrl);
        BOOL     bPut    (const std::string &csUrl);
        BOOL     bDelete (const std::string &csUrl);
        BOOL     bConnect(const std::string &csUrl);
        BOOL     bPatch  (const std::string &csUrl);
        BOOL     bLink   (const std::string &csUrl);
        BOOL     bUnlink (const std::string &csUrl);

                 CxHttpClient();
        virtual ~CxHttpClient();
};
//---------------------------------------------------------------------------
class CxHttpClient::CxStatusLine
    /// HTTP status line
{
    public:
                 CxStatusLine();
        virtual ~CxStatusLine();

    private:

};
//---------------------------------------------------------------------------
class CxHttpClient::CxHeader
    /// HTTP header
{
    public:
                 CxHeader();
        virtual ~CxHeader();

    private:

};
//---------------------------------------------------------------------------
class CxHttpClient::CxBody
    /// HTTP nody
{
    public:
                 CxBody();
        virtual ~CxBody();

    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxHttpClientH
