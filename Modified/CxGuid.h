/**********************************************************************
 *	Класс CXGuid (CXGuid.h)       
 *
 ***********************************************************************/
 

#ifndef CXGuidH
#define CXGuidH       
//---------------------------------------------------------------------------
#include <XLib/Common.h>
//---------------------------------------------------------------------------
class CXGuid : public CXNonCopyable {
	public:
		        CXGuid           ();
		       ~CXGuid           ();
		tstring sGenerateGUID    (INT iFormat);

	private:
		tstring sFormatGUID      (INT iFormat);
		tstring sGUIDSPrintf     (const tstring &sFormat);
		tstring sGetFormat1String();
		tstring sGetFormat2String();
		tstring sGetFormat3String();
		tstring sGetFormat4String();
		tstring sGetFormat5String();
		tstring sGetFormat6String();
		tstring sGetCommentGUID  ();

		GUID    m_guid;
};
//---------------------------------------------------------------------------
#endif