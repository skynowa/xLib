/***********************************************************************
*   hGetAssociatedIcon   
*
************************************************************************/


#include <registry.hpp>
//---------------------------------------------------------------------------
HICON hGetAssociatedIcon(const tString &csFileExt) {   //после удалить хендл ::DestroyIcon()           	

	bool  bRes = false;
	int   iRes = - 1;

	tString sTemp = csFileExt;

	if (_T('.') != sTemp[1]) {
		sTemp = _T(".") + sTemp;
	}

	std::auto_ptr<TRegistry> apregReg(new TRegistry());
	/*DEDUG*/CHECK_RET(NULL == apregReg.get(), NULL);
	
	apregReg->RootKey = HKEY_LOCAL_MACHINE;
	
	bRes = apregReg->OpenKey(_T("Software\\CLASSES"), false);
	/*DEDUG*/CHECK_RET(false == bRes, NULL);
	
	bRes = apregReg->OpenKey(sTemp, false);
	/*DEDUG*/CHECK_RET(false == bRes, NULL);
	
	sTemp = apregReg->ReadString(_T(""));    //(Default)
	/*DEDUG*/CHECK_RET(true == sTemp.IsEmpty(), NULL);
	
	bRes = apregReg->OpenKey(_T("\\Software\\CLASSES\\") + sTemp + _T("\\DefaultIcon"), false);
	/*DEDUG*/CHECK_RET(false == bRes, NULL);

	sTemp  = apregReg->ReadString("");
	/*DEDUG*/CHECK_RET(false == bRes, NULL);
	
	/*DEDUG*/CHECK_RET(_T("%1")     == sTemp, NULL);
	/*DEDUG*/CHECK_RET(_T("\"%1\"") == sTemp, NULL);

	int iPos   = sTemp.LastDelimiter(_T(","));
	int iIndex = sTemp.SubString(iPos + 1, sTemp.Length() - iPos).ToInt();

	sTemp.Delete(iPos, sTemp.Length() - iPos + 1).Trim();

	//удаляем кавычки
	if (_T('"') == sTemp[1]) {
		sTemp.Delete(1, 1);		
	}
	if (_T('"') == sTemp[sTemp.Length()]) {
		sTemp.Delete(sTemp.Length(), 1);		
	} 
	//ShowMessage(sTemp);

	HICON hIconLarge = NULL; 
	HICON hIconSmall = NULL;
	iRes = ::ExtractIconEx(sTemp.c_str(), 0, &hIconLarge, &hIconSmall, 1);  
	/*DEDUG*/CHECK_RET(- 1 == iRes, NULL);
	
	return hIconSmall; 
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
//HICON __fastcall hGetAssociatedIcon(char* pFilePath) {
//	WORD iconIndex = 0;
//	HICON hIcon    = 0;
//
//	if (pFilePath == "") {
//		pFilePath = "nul.txt";
//	}
//	try	{
//		char buf[MAX_PATH];
//		strncpy(buf, pFilePath, sizeof(buf));
//		hIcon = ::ExtractAssociatedIcon(HInstance, buf, &iconIndex);
//	} catch (...) {
//		hIcon = 0;
//	}
//	return 0/*hIcon*/;
//}
//---------------------------------------------------------------------------


