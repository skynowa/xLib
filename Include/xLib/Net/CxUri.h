/****************************************************************************
* Class name:  CxUri
* Description: ��������������� ������������� ������� (RFC 3986)
* File name:   CxUri.h
* Compilers:   Visual C++ 2008
* String type: Ansi (!!!!!)
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     17.11.2009 12:41:10
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxUriH
#define xLib_Net_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxUri {
	public:
				           CxUri            ();
	    explicit           CxUri            (const std::string &csUri);
				          ~CxUri            ();

		std::string        sGetUri          ();	
		BOOL               bSetUri          (const std::string &csScheme, const std::string &csAuthority, const std::string &csPath, const std::string &csQuery, const std::string &csFragment);

		std::string        sGetScheme       ();	
		BOOL               bSetScheme       (const std::string &csScheme);

		std::string        sGetAuthority    (); 
		BOOL               bSetAuthority    (const std::string &csAuthority); 

		std::string        sGetUserInfo     ();	
		BOOL               bSetUserInfo     (const std::string &csUserInfo);	

		std::string        sGetHost         ();
		BOOL               bSetHost         (const std::string &csHost);

		USHORT             usGetPort        ();
		BOOL               bSetPort         (const USHORT &cusPort);

		std::string        sGetPath         ();        
		BOOL               bSetPath         (const std::string &csPath);        

		std::string        sGetQuery        ();   
		BOOL               bSetQuery        (const std::string &csQuery);   

		std::string        sGetFragment     ();
		BOOL               bSetFragment     (const std::string &csFragment);

		static std::string sEncodeComponent (const std::string &csUri);
		static std::string sDecodeComponent (const std::string &csUri);

		BOOL               bClear           ();
	
	private:
		static const std::string RESERVED_PATH;
		static const std::string RESERVED_QUERY;
		static const std::string RESERVED_FRAGMENT;
		static const std::string ILLEGAL;

		std::string        _m_sScheme;	
		std::string        _m_sAuthority; 
		std::string        _m_sUserInfo;	
		std::string        _m_sHost;
		USHORT             _m_usPort;
		std::string        _m_sPath;        
		std::string        _m_sQuery;   
		std::string        _m_sFragment;

		BOOL			   _bParse          (const std::string &csUri);
		BOOL        	   _bNormilize      (const std::string &csUri); 
		USHORT      	   _usGetDefaultPort() const;
		BOOL        	   _bIsDefaultPort  () const;
};
//---------------------------------------------------------------------------
#endif	//xLib_Net_CxUriH
