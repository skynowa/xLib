/***********************************************************************
*   vShowDlgProperties
*
************************************************************************/



//---------------------------------------------------------------------------
void vShowDlgProperties(const String &csFilePath) {
	////typedef BOOL (WINAPI *SHOBJECTPROPERTIES)(HWND hwnd, DWORD dwType, LPCWSTR lpObject, LPCWSTR lpPage);
	typedef BOOL (WINAPI *SHOBJECTPROPERTIES)(HWND hwnd, DWORD dwType, LPCTSTR lpObject, LPCTSTR lpPage);

	#ifndef SHOP_FILEPATH
	#define SHOP_FILEPATH		    0x00000002
	#endif

	#define SHOP_EXPORT_ORDINAL     178

	SHOBJECTPROPERTIES pSHObjectProperties = (SHOBJECTPROPERTIES)::GetProcAddress(::LoadLibrary(_T("shell32")), (LPCSTR)_T("SHObjectProperties"));

	if (!pSHObjectProperties) {
		pSHObjectProperties = (SHOBJECTPROPERTIES)::GetProcAddress(::LoadLibrary(_T("shell32")), (LPCSTR)SHOP_EXPORT_ORDINAL);
	}

	if (pSHObjectProperties) {
		pSHObjectProperties(/*Handle*/0, SHOP_FILEPATH, csFilePath.c_str(), 0);
	}
}
//---------------------------------------------------------------------------