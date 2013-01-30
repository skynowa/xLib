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
    static long_t         argsMax      ();
        ///< get maximum length of command line arguments (in chars)
    static std::tstring_t get          ();
        ///< get command line string for the current process
    static void           args         (std::vec_tstring_t *pvsArgs);
        ///< get command line arguments
    static void           setArgs      (const int &ciArgsCount, tchar_t *paszArgs[]);
        ///< set command line arguments

private:
    static std::vec_tstring_t _ms_vsArgs;  ///< command line arguments

                          CxCommandLine();
        ///< constructor
    virtual              ~CxCommandLine();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_CxCommandLineH
