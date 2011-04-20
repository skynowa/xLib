/**********************************************************************
 *	����� CXUrlCoder (CXUrlCoder.cpp)
 *
 ***********************************************************************/


#include <string>
#include <vector>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>

#include <xLib/Net/CxUrlCoder.h>
//---------------------------------------------------------------------------
CXUrlCoder::CXUrlCoder(){

}
//---------------------------------------------------------------------------
CXUrlCoder::~CXUrlCoder(){

}
//--------------------------------------------------------------------------
std::string CXUrlCoder::sEncode(const std::string &csStr) {
	std::string sRes;
	INT iSize = csStr.size();
	
	CHAR *pszBuff = new CHAR[iSize + 1];
	strcpy(pszBuff, csStr.c_str());
	
	
	for (INT i = 0; i < iSize; i ++) {
		if (bIsOrdinaryChar(pszBuff[i])) {
			sRes = sRes + pszBuff[i];
		} 
		else if (pszBuff[i] == ' ') {
			sRes = sRes + "+";
		} 
		else {
			CHAR tmp[6] = {0};
			sprintf(tmp, "%%%x", pszBuff[i]);
			sRes = sRes + tmp;
		}
	}

	delete [] pszBuff;
	
	return sRes;
}
//--------------------------------------------------------------------------
BOOL CXUrlCoder::bIsOrdinaryChar(CHAR chChar) {
	//ALPHA / DIGIT / "-" / "." / "_" / "~"
	CHAR ch = tolower(chChar);
	if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || 
		ch == 'g' || ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || 
		ch == 'm' || ch == 'n' || ch == 'o' || ch == 'p' || ch == 'q' || ch == 'r' || 
		ch == 's' || ch == 't' || ch == 'u' || ch == 'v' || ch == 'w' || ch == 'x' || 
		ch == 'y' || ch == 'z' || ch == '0' || ch == '1' || ch == '2' || ch == '3' || 
		ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ||
		ch == '-' || ch == '.' || ch == '_' || ch == '~') 
	{
		return true;
	} else {
		return false;
	}
}
//--------------------------------------------------------------------------
std::string CXUrlCoder::sDecode(const std::string &csStr) {
	std::string  Res;
	int          iLen    = csStr.length();
	CHAR        *pszBuff = new CHAR[iLen + 1];
	strcpy(pszBuff, csStr.c_str());

	for (int i = 0; i < iLen; i ++) {
		if (pszBuff[i] == '+') {
			Res = Res + " ";
		} 
		else if (pszBuff[i] == '%') {
			CHAR tmp[4] = {0};
			CHAR hex[4] = {0};
			hex[0] = pszBuff[ ++i];
			hex[1] = pszBuff[ ++i];
			hex[2] = '\0';
			//int hex_i = atoi(hex);
			sprintf(tmp, "%c", iConvertToDec(hex));
			Res = Res + tmp;
		} else {
			Res = Res + pszBuff[i];
		}
	}

	delete [] pszBuff;
	return Res;
}
//--------------------------------------------------------------------------
INT CXUrlCoder::iConvertToDec(LPCSTR pcszHex) {
	INT  iRes       = 0;
	CHAR szBuff[12] = {0};
	sprintf(szBuff, "%s", pcszHex);
	INT iLen = strlen(szBuff);

	for (INT i = 0; i < iLen; i ++) {
		CHAR tmp[4];
		tmp[0] = szBuff[i];
		tmp[1] = '\0';
		vGetAsDec(tmp);
		INT tmp_i = atoi(tmp);
		INT rs = 1;
		for (INT j = i; j < (iLen - 1); j ++) {
			rs *= 16;
		}
		iRes += (rs *tmp_i);
	}

	return iRes;
}
//--------------------------------------------------------------------------
void CXUrlCoder::vGetAsDec(LPSTR pszHex) {
	CHAR chTmp = tolower(pszHex[0]);
	if (chTmp == 'a') {
		strcpy(pszHex, "10");
	} else if (chTmp == 'b') {
		strcpy(pszHex, "11");
	} else if (chTmp == 'c') {
		strcpy(pszHex, "12");
	} else if (chTmp == 'd') {
		strcpy(pszHex, "13");
	} else if (chTmp == 'e') {
		strcpy(pszHex, "14");
	} else if (chTmp == 'f') {
		strcpy(pszHex, "15");
	} else if (chTmp == 'g') {
		strcpy(pszHex, "16");
	}
}
//--------------------------------------------------------------------------
