/****************************************************************************
* Class name:  CxEnvironment
* Description: system environment variables
* File name:   CxEnvironment.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.04.2010 17:43:45
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxEnvironmentH
#define xLib_Filesystem_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEnvironment : public CxNonCopyable {
    public:
        static BOOL    bIsExists          (const tString &csVarName);
        static tString sGetVar            (const tString &csVarName);
        static BOOL    bSetVar            (const tString &csVarName, const tString &csValue);
        static BOOL    bDeleteVar         (const tString &csVarName);
        static BOOL    bGetValues         (std::vector<tString> *pvsValues);
        static tString sExpandStrings     (const tString &csvVar);
        static tString sGetCommandLine    ();
        static BOOL    bGetCommandLineArgs(std::vector<tString> *pvsArgs);

    private:
                       CxEnvironment      ();
        virtual       ~CxEnvironment      ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxEnvironmentH
