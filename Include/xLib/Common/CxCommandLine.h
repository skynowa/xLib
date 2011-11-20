/**
 * \file   CxCommandLine.h
 * \brief
 */


#ifndef xLib_CxCommandLineH
#define xLib_CxCommandLineH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCommandLine :
    public CxNonCopyable
{
    public:
        static LONG         liGetArgsMax ();
            ///< get maximum length of commandline arguments (in chars)
        static std::tstring sGet         ();
            ///< get commandline string for the current process
        static bool         bGetArgs     (std::vector<std::tstring> *pvsArgs);
            ///< get commandline arguments
        static bool         bSetArgs     (const int ciArgsCount, tchar *paszArgs[]);
            ///< set commandline arguments

    private:
        static std::vector<std::tstring> _ms_vsArgs;  ///< command line arguments

                            CxCommandLine();
            ///< constructor
        virtual            ~CxCommandLine();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxCommandLineH
