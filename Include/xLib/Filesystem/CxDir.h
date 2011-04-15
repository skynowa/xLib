/****************************************************************************
* Class name:  CxDir
* Description: directory
* File name:   CxDir.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     04.06.2009 9:23:33
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Fso_CxDirH
#define xLib_Fso_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDir : public CxNonCopyable {
	public:
		static BOOL    bIsExists    (const tString &csDirPath);
		static BOOL    bIsEmpty     (const tString &csDirPath, const tString &csMask = CxConst::xMASK_ALL);
		//static BOOL  bIsRoot      (const tString &csDirPath);
		static BOOL    bIsDir       (const tString &csDirPath);
		static tString sGetCurrent  ();  
		static BOOL    bSetCurrent  (const tString &csDirPath); 
		static tString sGetTempPath (); 
		static BOOL    bCreate      (const tString &csDirPath); 
		static BOOL    bCreateForce (const tString &csDirPath); 
		static BOOL    bCopy        (const tString &csFromDirPath, const tString &csToDirPath, BOOL bFailIfExists);
		static BOOL    bMove        (const tString &csInDirPath,   const tString &csOutDirPath);

		static BOOL    bDelete      (const tString &csDirPath); 
		static BOOL    bClearForce  (const tString &csDirPath); 
		static BOOL    bDeleteForce (const tString &csDirPath); 

		static BOOL    bFindFiles	(const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsFilePathes);
		static BOOL    bFindDirs    (const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsDirPathes);

	private:
			           CxDir        ();
					  ~CxDir        ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Fso_CxDirH
