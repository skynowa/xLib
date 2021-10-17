/**
 * \file   Warnings.h
 * \brief  warnings on/off
 */


#pragma once

// TODO: warnings - rm

#if   xCOMPILER_MINGW
    // off
#elif xCOMPILER_MS
    // off
    #pragma warning(disable: 4996) // function or variable may be unsafe (deprecated)
#elif xCOMPILER_CLANG
    // off
#elif xCOMPILER_GNUC
    // off
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
    #error Unknown complier
#endif
