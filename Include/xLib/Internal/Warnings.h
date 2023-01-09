/**
 * \file   Warnings.h
 * \brief  warnings on/off
 */


#pragma once

#if   xCOMPILER_MINGW
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif xCOMPILER_MS
    #pragma warning(disable: 4996) // function or variable may be unsafe (deprecated)
    #pragma warning(disable: 4127) // warning C4127: conditional expression is constant
#elif xCOMPILER_CLANG
	// n/a
#elif xCOMPILER_GNUC
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
