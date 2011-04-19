/****************************************************************************
* Class name:  CxMemoryIni
* Description: memory ini
* File name:   CxMemoryIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.07.2010 13:01:42
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
