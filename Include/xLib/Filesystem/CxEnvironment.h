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
        static BOOL         bIsExists          (const std::tstring &csVarName);
            ///< check for existence
        static std::tstring sGetVar            (const std::tstring &csVarName);
            ///< get value by name
        static BOOL         bSetVar            (const std::tstring &csVarName, const std::tstring &csValue);
            ///< set or change value by name
        static BOOL         bDeleteVar         (const std::tstring &csVarName);
            ///< delete var
        static BOOL         bGetValues         (std::vector<std::tstring> *pvsValues);
            ///< get all values
        static std::tstring sExpandStrings     (const std::tstring &csvVar);
            ///< expands strings by separator "%"

        static std::tstring sGetCommandLine    ();
            ///< get command-line string for the current process
        static BOOL         bGetCommandLineArgs(std::vector<std::tstring> *pvsArgs);
            ///< get commandline arguments
        static BOOL         bSetCommandLineArgs(const INT ciArgsCount, TCHAR *paszArgs[]);
            ///< set commandline arguments

    private:
        static std::vector<std::tstring> _m_vsCommandLineArgs;  ///< command line arguments

                            CxEnvironment      ();
            ///< constructor
        virtual            ~CxEnvironment      ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxEnvironmentH

//_MAX_ENV
