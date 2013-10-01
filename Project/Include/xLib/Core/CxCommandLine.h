/**
 * \file   CxCommandLine.h
 * \brief  command line
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCommandLine :
    private CxNonCopyable
    /// command line
{
public:
    static long_t         argsMax      () xWARN_UNUSED_RV;
        ///< get maximum length of command line arguments (in chars)
    static std::tstring_t get          () xWARN_UNUSED_RV;
        ///< get command line string for the current process
    static void_t         args         (std::vec_tstring_t *pvsArgs);
        ///< get command line arguments
    static void_t         setArgs      (cint_t &ciArgsCount, tchar_t *paszArgs[]);
        ///< set command line arguments

private:
    static std::vec_tstring_t _ms_vsArgs;  ///< command line arguments

                          CxCommandLine();
        ///< constructor
    virtual              ~CxCommandLine();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
