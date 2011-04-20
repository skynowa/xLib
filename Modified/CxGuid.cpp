/**********************************************************************
 *	Класс CXGuid (CXGuid.cpp)       
 *
 ***********************************************************************/

 
#include <XLib/CXGuid.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXGuid::CXGuid() {
	::ZeroMemory(&m_guid, sizeof(GUID));
}
//---------------------------------------------------------------------------
CXGuid::~CXGuid() {

}
//---------------------------------------------------------------------------
tstring CXGuid::sGenerateGUID(INT iFormat) {
	//-------------------------------------
	//CHECK
	if (iFormat < 0 || iFormat > 5) {
		return "";
	}

	//-------------------------------------
	//JOB
	::CoCreateGuid(&m_guid);
	
	return sFormatGUID(iFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGUIDSPrintf(const tstring &sFormat) {
	TCHAR szBuff[250] = {0};	
	::wsprintf(
		szBuff, 
		sFormat.c_str(),
		m_guid.Data1, 
		m_guid.Data2, 
		m_guid.Data3,
		m_guid.Data4[0], m_guid.Data4[1],
		m_guid.Data4[2], m_guid.Data4[3], m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7]
	);

	return tstring(szBuff);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetCommentGUID() {
	tstring sHeader = "";
	sHeader = "// " + sGetFormat4String() + "\n";
	
	return sHeader;
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat1String() {
	// {EEE5D2B4-DCCE-11D3-B4C4-D237E35336F0}
	// IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
	//		0xeee5d2b4, 0xdcce, 0x11d3, 0xb4, 0xc4, 0xd2, 0x37, 0xe3, 0x53, 0x36, 0xf0);
	tstring sFormat = 
		sGetCommentGUID() + 
		"IMPLEMENT_OLECREATE(<<class>>, <<external_name>>,\n"
		"\t0x%08X, 0x%04X, 0x%04X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X);\n\n";

	return sGUIDSPrintf(sFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat2String() {
	// {EEE5D2B5-DCCE-11D3-B4C4-D237E35336F0}
	// DEFINE_GUID(<<name>>, 
	//		0xeee5d2b5, 0xdcce, 0x11d3, 0xb4, 0xc4, 0xd2, 0x37, 0xe3, 0x53, 0x36, 0xf0);
	tstring sFormat = 
		sGetCommentGUID() + 
		"DEFINE_GUID(<<name>>,\n"
		"\t0x%04X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X);\n\n";

	return sGUIDSPrintf(sFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat3String() {
	// {EEE5D2B6-DCCE-11D3-B4C4-D237E35336F0}
	// static const GUID <<name>> = 
	//		{ 0xeee5d2b6, 0xdcce, 0x11d3, { 0xb4, 0xc4, 0xd2, 0x37, 0xe3, 0x53, 0x36, 0xf0 } };
	tstring sFormat = 
		sGetCommentGUID() + 
		"static const GUID <<name>> =\n"
		"\t{ 0x%04X, 0x%02X, 0x%02X, { 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X } };\n\n";

	return sGUIDSPrintf(sFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat4String() {
	// {EEE5D2B7-DCCE-11D3-B4C4-D237E35336F0}

	return "{" + sGetFormat5String() + "}";
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat5String() {
	// EEE5D2B7-DCCE-11D3-B4C4-D237E35336F0
	tstring sFormat = "%04X-%02X-%02X-%02X%02X-%02X%02X%02X%02X%02X%02X";
	
	return sGUIDSPrintf(sFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sGetFormat6String() {
	// __declspec(uuid("EEE5D2B4-DCCE-11D3-B4C4-D237E35336F0"))

	tstring sFormat = "__declspec(uuid(\"" + sGetFormat5String() + "\"))";
	
    return sGUIDSPrintf(sFormat);
}
//---------------------------------------------------------------------------
tstring CXGuid::sFormatGUID(INT iFormat) {
	//-------------------------------------
	//CHECK
	if (iFormat < 0 || iFormat > 5) {
		return "";
	}

	//-------------------------------------
	//JOB
	tstring tsRes = "";

	switch(iFormat) {
		case 0:	//IMPLEMENT_OLECREATE 
			tsRes = sGetFormat1String();
			break;

		case 1:	//DEFINE_GUID
			tsRes = sGetFormat2String();
			break;

		case 2: //STRUCT_GUID
			tsRes = sGetFormat3String();
			break;

		case 3: //REGISTRY_FORMAT
			tsRes = sGetFormat4String();
			break;

		case 4:	//PLAIN_FORMAT
			tsRes = sGetFormat5String();
			break;

		case 5:	//DECLSPEC_UUID
			tsRes = sGetFormat6String();
			break;
            
        default:
            /*DEBUG*/XASSERT(false);
            break;   
	}

	return tsRes;
}
//---------------------------------------------------------------------------