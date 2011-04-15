/****************************************************************************
* Class name:  CxMemoryIni
* Description: �������� �������� � ������
* File name:   CxMemoryIni.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.07.2010 13:01:42
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Fso_CxMemoryIniH
#define xLib_Fso_CxMemoryIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <map>	
//---------------------------------------------------------------------------
class CxMemoryIni : public CxNonCopyable {
	public:
    			  CxMemoryIni();
		explicit  CxMemoryIni(const tString &csFilePath);
		virtual  ~CxMemoryIni();

		BOOL      bFlush     ();

	private:
		typedef std::map<tString, tString> IniPair;

		BOOL      _m_bRes;
		tString   _m_sFilePath;


};
//---------------------------------------------------------------------------
#endif //xLib_Fso_CxMemoryIniH
