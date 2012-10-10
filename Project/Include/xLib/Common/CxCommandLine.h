/**
 * \file   CxCommandLine.h
 * \brief  command line
 */


#ifndef xLib_CxCommandLineH
#define xLib_CxCommandLineH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCommandLine :
    private CxNonCopyable
    /// command line
{
    public:
        static long_t         liArgsMax    ();
            ///< get maximum length of commandline arguments (in chars)
        static std::tstring_t sGet         ();
            ///< get commandline string for the current process
        static void           vArgs        (std::vec_tstring_t *pvsArgs);
            ///< get commandline arguments
        static void           vSetArgs     (const int &ciArgsCount, tchar_t *paszArgs[]);
            ///< set commandline arguments

    private:
        static std::vec_tstring_t _ms_vsArgs;  ///< command line arguments

                              CxCommandLine();
            ///< constructor
        virtual              ~CxCommandLine();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxCommandLineH
