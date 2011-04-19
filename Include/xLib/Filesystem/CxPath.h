/****************************************************************************
* Class name:  CxPath
* Description: file system path
* File name:   CxPath.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:27:28
*
*****************************************************************************/


#ifndef xLib_Fso_CxPathH
#define xLib_Fso_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxPath : public CxNonCopyable {
	public:	
		static tString sGetExe      ();
		static tString sGetExeDir   ();
        #if defined(xOS_WIN)
		static tString sGetDrive    (const tString &csFilePath);
        #endif
		static tString sGetDir      (const tString &csFilePath);
		static tString sGetDirName  (const tString &csFilePath);
		static tString sGetFullName (const tString &csFilePath);
		static tString sGetName     (const tString &csFilePath);
		static tString sGetExt      (const tString &csFilePath);

        #if defined(xOS_WIN)
   		static tString sSetDrive    (const tString &csFilePath, const tString &csDrivePath);
        #endif
		static tString sSetDir      (const tString &csFilePath, const tString &csDirPath); 
		static tString sSetFullName (const tString &csFilePath, const tString &csFullName);
		static tString sSetName     (const tString &csFilePath, const tString &csName); 
		static tString sSetExt      (const tString &csFilePath, const tString &csExt);

		static tString sRemoveExt   (const tString &csFilePath);
		static tString sRemoveExtIf (const tString &csFilePath, const tString &csExt);

		//normalize
		static BOOL    bIsValidName (const tString &csFilePath);
		
		static tString sToWin       (const tString &csFilePath, BOOL bIsSlashAtEnd);
		static tString sToNix       (const tString &csFilePath, BOOL bIsSlashAtEnd);
		static tString sToCurrentOs (const tString &csFilePath, BOOL bIsSlashAtEnd);    //TODO: make test

		static tString sMinimizeName(const tString &csFileName, const std::size_t cuiMaxSize);
		static tString sMinimize    (const tString &csFilePath, const std::size_t cuiMaxSize);
		static tString sSetValidName(const tString &csFileName);

		static tString sSlashAppend (const tString &csDirPath);
		static tString sSlashRemove (const tString &csDirPath);

	private:	   
					   CxPath       ();
		virtual  	  ~CxPath       ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Fso_CxPathH

//static tString sGetRelativePath     (const tString &csFilePath); /*-*/
//
/*
//---------------------------------------------------------------------------
//TODO:   convert path separators to forward slashes
void convert_path_separators(tString &s) {
	for (tString::iterator itr = s.begin(); itr != s.end(); ++ itr) {
		if (*itr == _T('\\') || *itr == _T('!')) {
			*itr = _T('/');
		}
	}
}
//---------------------------------------------------------------------------
*/
/*ExpandUNCFileName	���������� ������ ��� ����� �� ������� �����.*/
/*ExtractShortPathName	������������ ������� ��� ����� � ������ DOS.*/
/*ProcessPath	��������� �� ������� ����� ����� ��� �����, ��� �������� � ��� �����.*/
