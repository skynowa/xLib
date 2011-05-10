/**********************************************************************
*	Класс  CxAccess (CxAccess.h)
*
***********************************************************************/


#ifndef xVCL_OLE_CxAccessH
#define xVCL_OLE_CxAccessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/Win/CxFile.h>

#include <xVCL/xCommon.h>
#include <ComObj.hpp>   //OLE
//---------------------------------------------------------------------------
class CxAccess : public CxNonCopyable {
	public:
        		CxAccess          ();
        	   ~CxAccess          ();

		BOOL    bIsMdbFile        (const String &csFilePath);
		BOOL    bIsOleAppInstalled(const String &csApplicationString);
		BOOL    bCreateResMdb     (const String &csFilePath, const String &csResource);
		BOOL    bCreateAdoMdb     (const String &csMdbFilePath);
		BOOL    bCompactMdb       (const String &csMdbFilePath, const String &csPass1, const String &csPass2);
		String  sGetADOVersion    ();
	
	private:
		BOOL    _m_bRes;
		Variant _m_vRes;

};
//---------------------------------------------------------------------------
#endif	//xVCL_OLE_CxAccessH
