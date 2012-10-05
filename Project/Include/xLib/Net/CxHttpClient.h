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

        void     vHead   (const std::string &csUrl,  std::string *psResponse);
        void     vGet    (const std::string &csUrl,  std::string *psResponse);
        void     vPost   (const std::string &csUrl,  const std::string &csParams, std::string *psResponse);
        void     vOptions(const std::string &csUrl);
        void     vTrace  (const std::string &csUrl);
        void     vPut    (const std::string &csUrl);
        void     vDelete (const std::string &csUrl);
        void     vConnect(const std::string &csUrl);
        void     vPatch  (const std::string &csUrl);
        void     vLink   (const std::string &csUrl);
        void     vUnlink (const std::string &csUrl);

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
