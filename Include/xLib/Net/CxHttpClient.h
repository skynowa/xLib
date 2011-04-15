/****************************************************************************
* Class name:  CxHttpClient
* Description: protocol HTTP/1.0 (RFC 1945)  HTTP/1.1 (...)
* File name:   CxHttpClient.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.11.2009 14:43:15
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxHttpClientH
#define xLib_Net_CxHttpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxHttpClient {
	public:
		//status line
		class CxStatusLine;

		//header
		class CxHeader;

		//body
		class CxBody;

		/****************************************************************************
		* ���������
		*
		*****************************************************************************/

		//protocol version
		enum EProtocolVersion {
			pv10 = 0,
			pv11 = 1
		};

		//method
		enum EMethod {
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
//status line
class CxHttpClient::CxStatusLine {
    public:
                 CxStatusLine();
        virtual ~CxStatusLine();

    private:

};
//---------------------------------------------------------------------------
//header
class CxHttpClient::CxHeader {
    public:
                 CxHeader();
        virtual ~CxHeader();

    private:

};
//---------------------------------------------------------------------------
//body
class CxHttpClient::CxBody {
    public:
                 CxBody();
        virtual ~CxBody();

    private:

};
//---------------------------------------------------------------------------
#endif	//xLib_Net_CxHttpClientH
