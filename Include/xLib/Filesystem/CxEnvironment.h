/****************************************************************************
* Class name:  CxEnvironment
* Description: system environment variables
* File name:   CxEnvironment.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.04.2010 17:43:45
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Fso_CxEnvironmentH
#define xLib_Fso_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEnvironment : public CxNonCopyable {
	public:
        static BOOL    bIsExists          (const tString &csVarName);
	   	static tString sGetVar		      (const tString &csVarName);
		static BOOL    bSetVar		      (const tString &csVarName, const tString &csValue);
		static BOOL    bDeleteVar         (const tString &csVarName);
		static BOOL    bGetValues         (std::vector<tString> *pvecsValues);
		static tString sExpandStrings     (const tString &csvVar);
		static tString sGetCommandLine    ();
		static BOOL    bGetCommandLineArgs(std::vector<tString> *pvecsArgs);

	private:
		               CxEnvironment      ();
	    virtual       ~CxEnvironment      ();
};
//---------------------------------------------------------------------------
#endif //xLib_Fso_CxEnvironmentH


/*
    Linux (printenv)
*/

/*
size_t
CxCgi::ulGetEnvironStringCount() {
    size_t uiRes = 0;

  for (size_t i = 0; _environ[i]; i ++) {
      ++ uiRes;
  }

    return uiRes;
}*/
