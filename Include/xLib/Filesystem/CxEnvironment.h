/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#ifndef xLib_Filesystem_CxEnvironmentH
#define xLib_Filesystem_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEnvironment :
    public CxNonCopyable
    /// system environment variables
{
    public:
        static BOOL    bIsExists          (const std::tstring &csVarName);
        static std::tstring sGetVar            (const std::tstring &csVarName);
        static BOOL    bSetVar            (const std::tstring &csVarName, const std::tstring &csValue);
        static BOOL    bDeleteVar         (const std::tstring &csVarName);
        static BOOL    bGetValues         (std::vector<std::tstring> *pvsValues);
        static std::tstring sExpandStrings     (const std::tstring &csvVar);

        static std::tstring sGetCommandLine    ();
        static BOOL    bGetCommandLineArgs(std::vector<std::tstring> *pvsArgs);
        static BOOL    bSetCommandLineArgs(const INT ciArgsCount, TCHAR *paszArgs[]);

    private:
        static std::vector<std::tstring> _m_vsCommandLineArgs;

                       CxEnvironment      ();
        virtual       ~CxEnvironment      ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxEnvironmentH

//_MAX_ENV
