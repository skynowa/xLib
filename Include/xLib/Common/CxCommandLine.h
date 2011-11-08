/**
 * \file   CxCommandLine.h
 * \brief
 */


#ifndef xLib_CxCommandLineH
#define xLib_CxCommandLineH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCommandLine :
    public CxNonCopyable
{
	public:
        static LONG         liGetArgsMax ();
            ///< get maximum length of commandline arguments (in chars)
        static std::string_t sGet         ();
            ///< get commandline string for the current process
        static BOOL         bGetArgs     (std::vector<std::string_t> *pvsArgs);
            ///< get commandline arguments
        static BOOL         bSetArgs     (const INT ciArgsCount, char_t *paszArgs[]);
            ///< set commandline arguments

    private:
        static std::vector<std::string_t> _ms_vsArgs;  ///< command line arguments

                            CxCommandLine();
            ///< constructor
        virtual            ~CxCommandLine();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_CxCommandLineH
