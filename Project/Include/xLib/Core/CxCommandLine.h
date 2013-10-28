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
                       CxCommandLine() {}
        ///< constructor

    std::tstring_t     get() xWARN_UNUSED_RV;
        ///< get command line string for the current process
    void_t             args(std::vec_tstring_t *args);
        ///< get command line arguments
    void_t             setArgs(cint_t &argsNum, tchar_t *args[]);
        ///< set command line arguments

    static long_t      argsMax() xWARN_UNUSED_RV;
        ///< get maximum length of command line arguments (in chars)
private:
    std::vec_tstring_t _args;  ///< command line arguments
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Core/CxCommandLine.cpp>
#endif
