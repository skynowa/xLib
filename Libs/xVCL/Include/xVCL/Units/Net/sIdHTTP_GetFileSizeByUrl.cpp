/***********************************************************************
*  sIdHTTP_GetFileSizeByUrl - размер файла по URL 
*
************************************************************************/


#include <vcl.h>

#include "IdHTTP.hpp"
//---------------------------------------------------------------------------
tString sIdHTTP_GetFileSizeByUrl(/*TIdHTTP *pIdHTTP, */const tString &csURL) {
//	/*DEBUG*/////xASSERT(NULL  != pIdHTTP);
//	/*DEBUG*/xASSERT(false == csURL.IsEmpty());
//
//	tString sRes     = _T("Uknown");
	__int64 i64Bytes = 0;
//
//	//-------------------------------------
//	//получаем значение
//	std::auto_ptr<TIdHTTP> apIdHTTP(new TIdHTTP(NULL));
	///*DEBUG*/xASSERT(NULL != apIdHTTP.get());
	////apIdHTTP->Head(csURL);
//	i64Bytes = apIdHTTP->Response->ContentLength;
//
//	//-------------------------------------
//	//форматируем строку
//    __int64 i64GB = 1024 * 1024 * 1024;
//	__int64 i64MB = 1024 * 1024;
//	__int64 i64KB = 1024;
//
//	if (i64Bytes / i64GB > 0) {
//		sRes = tString().sprintf(_T("%.2f GB"), static_cast<float>(i64Bytes) / static_cast<float>(i64GB));
//	}
//	else if (i64Bytes / i64MB > 0) {
//		sRes = tString().sprintf(_T("%.2f MB"), static_cast<float>(i64Bytes) / static_cast<float>(i64MB));
//	}
//	else if (i64Bytes / i64KB > 0) {
//		sRes = tString().sprintf(_T("%.2f KB"), static_cast<float>(i64Bytes) / static_cast<float>(i64KB));
//	}
//	else {
//		sRes = IntToStr(i64Bytes) + _T(" Byte(s)");
//    }
//
//	return sRes;

//	TIdHTTP *pIdHTTP = new TIdHTTP(NULL);
//	delete pIdHTTP;

	return _T("");
}
//---------------------------------------------------------------------------

/*
function BytesToStr(const i64Size: Int64): string;

  i64GB = 1024 * 1024 * 1024;
  i64MB = 1024 * 1024;
  i64KB = 1024;

  if i64Size div i64GB > 0 then
    Result := Format('%.2f GB', [i64Size / i64GB])
  else if i64Size div i64MB > 0 then
    Result := Format('%.2f MB', [i64Size / i64MB])
  else if i64Size div i64KB > 0 then
    Result := Format('%.2f KB', [i64Size / i64KB])
  else
    Result := IntToStr(i64Size) + ' Byte(s)';
end;*/