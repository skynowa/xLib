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
        static long_t         liGetArgsMax ();
            ///< get maximum length of commandline arguments (in chars)
        static std::tstring_t sGet         ();
            ///< get commandline string for the current process
        static bool           bGetArgs     (std::vector<std::tstring_t> *pvsArgs);
            ///< get commandline arguments
        static bool           bSetArgs     (const int ciArgsCount, tchar_t *paszArgs[]);
            ///< set commandline arguments

    private:
        static std::vector<std::tstring_t> _ms_vsArgs;  ///< command line arguments

                              CxCommandLine();
            ///< constructor
        virtual              ~CxCommandLine();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxCommandLineH
