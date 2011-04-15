/****************************************************************************
* Class name:  CxIni
* Description: ������ � ini-�������
* File name:   CxIni.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     23.04.2009 12:10:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Filesystem/Win/CxIni.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxStdioFile.h>

#include <iostream>
#include <stdio.h>


/****************************************************************************
*	public: ������
*
*****************************************************************************/

//-------------------------------------------------------------------------
//TODO: + CxIni (����������� - ���� � ���������� Exe)
CxIni::CxIni() :
	_m_bRes     (FALSE),
	_m_sFilePath()		
{
	/*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);        

	_m_bRes = bSetPath(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") )); 
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//TODO: + CxIni (����������� - ���� � �������� ����������)
CxIni::CxIni(const tString &csFilePath) :
	_m_bRes     (FALSE),
	_m_sFilePath()		
{
	/*DEBUG*/xASSERT_DO(true  == _m_sFilePath.empty(), return);        
	/*DEBUG*/xASSERT_DO(false == csFilePath.empty(),   return);        

	_m_bRes = bSetPath(csFilePath); 
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//TODO: + ~CxIni (����������)
/*virtual*/
CxIni::~CxIni() {
	_m_bRes = bFlush();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//-------------------------------------------------------------------------
//TODO: + bCreateDefault (�������� ����� ��-���������)
BOOL CxIni::bCreateDefault(const tString &csContent) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/// csContent - n/a;  
	
	//�������� �����
	_m_bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	
	//�������� �����
	CxStdioFile sfFile;

	_m_bRes = sfFile.bOpen(_m_sFilePath, xT("w+"));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	INT iRes = sfFile.iFprintf(csContent.c_str());
	/*DEBUG*/xASSERT_RET(CxStdioFile::etError != iRes, FALSE);

	return TRUE;
}
//-------------------------------------------------------------------------
//TODO: + sGetPath (��������� ���� � �����)
tString CxIni::sGetPath() {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());

	return _m_sFilePath;
}
//---------------------------------------------------------------------------
//TODO: + bSetPath (��������� ���� � ����)
BOOL CxIni::bSetPath(const tString &csFilePath) {
	/*DEBUG*///_m_sFilePath - n/a
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

	_m_sFilePath.assign(csFilePath); 
	
	_m_bRes = CxDir::bCreateForce(CxPath::sGetDir(_m_sFilePath));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bFlush (����� ����������� � ����)
BOOL CxIni::bFlush() {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

	_m_bRes = ::WritePrivateProfileString(NULL, NULL, NULL, _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE == _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bClear (������� �����)
BOOL CxIni::bClear() {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);

	std::vector<tString> vecsNames;

	_m_bRes = bSectionsReadNames(&vecsNames);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	for (std::size_t i = 0; i < vecsNames.size(); ++ i) {
		_m_bRes = bSectionDelete(vecsNames.at(i));
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	}

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: ����
*
*****************************************************************************/

//-------------------------------------------------------------------------
//TODO: + bKeyIsExists (������������� ������)
BOOL CxIni::bKeyIsExists(const tString &csSection, const tString &csKey) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE); 

	std::map<tString, tString> mapsContent;

	_m_bRes = bSectionRead(csSection, &mapsContent);
	xASSERT(FALSE != _m_bRes);

	if (mapsContent.end() == mapsContent.find(csKey)) {
		return FALSE;
	} else {
		return TRUE;
	}
}
//---------------------------------------------------------------------------
//TODO: + iKeyReadInt (������ INT)
INT CxIni::iKeyReadInt(const tString &csSection, const tString &csKey, LONG iDefaultValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    0);
	/*DEBUG*///csKey         - n/a
	/*DEBUG*///iDefaultValue - n/a

	return CxString::lexical_cast<LONG>( sKeyReadString(csSection, csKey, CxString::lexical_cast(iDefaultValue)) );
}
//-------------------------------------------------------------------------
//TODO: + bKeyWriteInt (������ INT)
BOOL CxIni::bKeyWriteInt(const tString &csSection, const tString &csKey, LONG iValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey     - n/a
	/*DEBUG*///iValue    - n/a

	return bKeyWriteString(csSection, csKey, CxString::lexical_cast(iValue)); 
}
//-------------------------------------------------------------------------
//TODO: + dKeyReadFloat (������ FLOAT)
double CxIni::dKeyReadFloat(const tString &csSection, const tString &csKey, double dDefaultValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), 0.0);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    0.0);
	/*DEBUG*///csKey         - n/a
	/*DEBUG*///dDefaultValue - n/a

	return CxString::lexical_cast<double>( sKeyReadString(csSection, csKey, CxString::lexical_cast(dDefaultValue)) );
}
//-------------------------------------------------------------------------
//TODO: + bKeyWriteFloat (������ FLOAT)
BOOL CxIni::bKeyWriteFloat(const tString &csSection, const tString &csKey, double dValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey     - n/a
	/*DEBUG*///dValue    - n/a

	return bKeyWriteString(csSection, csKey, CxString::lexical_cast(dValue)); 
}
//-------------------------------------------------------------------------
//TODO: + bKeyReadBool (������ BOOL)
BOOL CxIni::bKeyReadBool(const tString &csSection, const tString &csKey, BOOL bDefaultValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey         - n/a
	/*DEBUG*///bDefaultValue - n/a

	BOOL    bRes = FALSE;	
	tString sStr;
	tString sDefaultValue; 
	
	sStr = CxString::sBoolToStr(bDefaultValue);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	sStr = sKeyReadString(csSection, csKey, sStr);

	bRes = CxString::bStrToBool(sStr);
	/*DEBUG*/

	return bRes;
}
//-------------------------------------------------------------------------
//TODO: + bKeyWriteBool (������ BOOL)
BOOL CxIni::bKeyWriteBool(const tString &csSection, const tString &csKey, BOOL bValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey     - n/a
	/*DEBUG*///bValue    - n/a

	tString sValue;

	sValue = bValue ? xT("true") : xT("false");

	return bKeyWriteString(csSection, csKey, sValue);
}
//-------------------------------------------------------------------------
//TODO: + sKeyReadString (������ tString)
tString CxIni::sKeyReadString(const tString &csSection, const tString &csKey, const tString &csDefaultValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), tString());
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    tString());
	/*DEBUG*///csKey          - n/a
	/*DEBUG*///csDefaultValue - n/a

	tString           sRes;
	const std::size_t cuiLineSize = 32;
	ULONG             ulRes       = 0;

	sRes.resize(cuiLineSize);

	for ( ; ; ) {
		ulRes = ::GetPrivateProfileString(csSection.c_str(), csKey.c_str(), csDefaultValue.c_str(), &sRes.at(0), sRes.size(), _m_sFilePath.c_str());
		/*DEBUG*/// n/a

		if (ulRes < sRes.size() - 2) {
			sRes.resize(ulRes);

			break;
		} else {
			sRes.resize(sRes.size() * 2);
		}
	}

	return sRes;
}
//-------------------------------------------------------------------------
//TODO: + bKeyWriteString (������ tString)
BOOL CxIni::bKeyWriteString(const tString &csSection, const tString &csKey, const tString &csValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey     - n/a
	/*DEBUG*///csValue   - n/a

	_m_bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), csValue.c_str(), _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//-------------------------------------------------------------------------
//TODO: + usKeyReadBin (������ uString)
uString CxIni::usKeyReadBin(const tString &csSection, const tString &csKey, const uString &cusDefaultValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), uString());
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    uString());
	/*DEBUG*///csKey          - n/a
	/*DEBUG*///cusDefaultValue - n/a

	uString usRes;

	tString sHexStr = sKeyReadString(csSection, csKey, tString(cusDefaultValue.begin(), cusDefaultValue.end()));

	//sHexStr -> usRes
	usRes = CxString::sBaseToString<uString/*UCHAR*/>(sHexStr, 16);

	return usRes;
}
//-------------------------------------------------------------------------
//TODO: + bKeyWriteBin (������ uString)
BOOL CxIni::bKeyWriteBin(const tString &csSection, const tString &csKey, const uString &cusValue) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*///csKey     - n/a
	/*DEBUG*///cusValue  - n/a

	//cusValue (uString) -> sHexStr (tString)
	tString sHexStr = CxString::sStringToBase(cusValue, 16);

	return bKeyWriteString(csSection, csKey, sHexStr);
}
//-------------------------------------------------------------------------
//TODO: + bKeyClear (������� �����)
BOOL CxIni::bKeyClear(const tString &csSection, const tString &csKey) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);

	return bKeyWriteString(csSection, csKey, tString());
}
//---------------------------------------------------------------------------
//TODO: + bKeyDelete (�������� �����)
BOOL CxIni::bKeyDelete(const tString &csSection, const tString &csKey) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(false == csKey.empty(),        FALSE);
	
	_m_bRes = ::WritePrivateProfileString(csSection.c_str(), csKey.c_str(), NULL, _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	
	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: ������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + bSectionIsExists (������������� ������)
BOOL CxIni::bSectionIsExists(const tString &csSection) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE); 

	ULONG             ulRes       = 0;
	tString           sRes;	
	const std::size_t cuiLineSize = 32;

	sRes.resize(cuiLineSize);

	ulRes = ::GetPrivateProfileString(csSection.c_str(), NULL, xT(""), &sRes.at(0), sRes.size(), _m_sFilePath.c_str());

	return (ulRes > 0);
}
//---------------------------------------------------------------------------
//TODO: + bSectionRead (������ ������)
BOOL CxIni::bSectionRead(const tString &csSection, std::map<tString, tString> *pmapsContent) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pmapsContent,         FALSE);

	tString           sBuff;
	const std::size_t cuiSectionSize = 32 * 4;
	ULONG             ulRes          = 0;

	sBuff.resize(cuiSectionSize);

	for ( ; ; ) {
		ulRes = ::GetPrivateProfileSection(csSection.c_str(), &sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
		/*DEBUG*/// n/a
		xCHECK_RET(0 == ulRes, TRUE);	//������ ����� ��� �� ����������

		if (ulRes < sBuff.size() - 2) {
			sBuff.resize(ulRes);

			break;
		} else {
			sBuff.resize(sBuff.size() * 2);
		}
	}
	
	//-------------------------------------
	//���������� std::vector
	std::vector<tString> vecsContent;
	
	vecsContent.clear();

	sBuff = CxString::sReplaceAll(sBuff, xT('\0'), CxConst::xNL.at(0));
	/*DEBUG*/
	
	sBuff = CxString::sTrimRightChars(sBuff, CxConst::xNL);
	/*DEBUG*/

	if (tString::npos != sBuff.find(CxConst::xNL)) {
		_m_bRes = CxString::bSplit(sBuff, CxConst::xNL, &vecsContent);
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
	} else {
		vecsContent.push_back(sBuff);	
	}

	//-------------------------------------
	//���������� std::map
	/*
	qqq=111
	www=222
	eee=333
	*/
	(*pmapsContent).clear();

	std::vector<tString> vecsKeyValue;
	std::pair<std::map<tString, tString>::iterator, bool> itRet;

	for (std::vector<tString>::const_iterator it = vecsContent.begin(); it != vecsContent.end(); ++ it) {
		_m_bRes = CxString::bSplit(*it, xT("="), &vecsKeyValue);
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
	
		itRet = (*pmapsContent).insert( std::pair<tString, tString>(vecsKeyValue.at(0), vecsKeyValue.at(1)) ); 
		/*DEBUG*/xASSERT_RET(false != itRet.second, FALSE);		//element 'z' already existed
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSectionWrite (������ ������)
BOOL CxIni::bSectionWrite(const tString &csSection, const std::map<tString, tString> &mapsContent) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);
	/*DEBUG*/// vecsContent - n/a

	tString sContent; 
		
	//-------------------------------------
	//������ std::map
	for (std::map<tString, tString>::const_iterator it = mapsContent.begin(); 
		it != mapsContent.end(); 
		++ it) 
	{
		sContent.append((*it).first);
		sContent.append(xT("="));
		sContent.append((*it).second);
		sContent.push_back(xT('\0'));
	}	
	
	//-------------------------------------
	//������
	_m_bRes = ::WritePrivateProfileSection(csSection.c_str(), sContent.c_str(), _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	return TRUE;
}
//-------------------------------------------------------------------------
//TODO: + bSectionsReadNames (������ ���� ���� ������) 
BOOL CxIni::bSectionsReadNames(std::vector<tString> *pvecsNames) {	
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pvecsNames,           FALSE);

	tString           sBuff;
	const std::size_t cuiSectionsNamesSize = 32 * 8;
	ULONG             ulRes                = 0;

	sBuff.resize(cuiSectionsNamesSize);

	for ( ; ; ) {
		ulRes = ::GetPrivateProfileSectionNames(&sBuff.at(0), /*DWORD*/sBuff.size(), _m_sFilePath.c_str());
		/*DEBUG*/// n/a
		xCHECK_RET(0 == ulRes, TRUE);	//���� ����

		if (ulRes < sBuff.size() - 2) {
			sBuff.resize(ulRes);

			break;
		} else {
			sBuff.resize(sBuff.size() * 2);
		}
	}

	//-------------------------------------
	//���������� std::vector
	sBuff.resize(ulRes);
	(*pvecsNames).clear();

	sBuff = CxString::sReplaceAll(sBuff, xT('\0'), CxConst::xNL.at(0));
	/*DEBUG*/

	sBuff = CxString::sTrimRightChars(sBuff, CxConst::xNL);
	/*DEBUG*/

	_m_bRes = CxString::bSplit(sBuff, CxConst::xNL, pvecsNames);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

	return TRUE;
}
//-------------------------------------------------------------------------
//TODO: + bSectionClear (������ ������)
BOOL CxIni::bSectionClear(const tString &csSection) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

	_m_bRes = ::WritePrivateProfileSection(csSection.c_str(), xT(""), _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//-------------------------------------------------------------------------
//TODO: + bSectionDelete (�������� ������)
BOOL CxIni::bSectionDelete(const tString &csSection) {
	/*DEBUG*/xASSERT_RET(false == _m_sFilePath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csSection.empty(),    FALSE);

	_m_bRes = ::WritePrivateProfileSection(csSection.c_str(), NULL, _m_sFilePath.c_str());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//-------------------------------------------------------------------------









