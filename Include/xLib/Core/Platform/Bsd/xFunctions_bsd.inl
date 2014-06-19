/**
 * \file   xFunctions_bsd.inl
 * \brief  function macroses
 */


#include <xLib/Core/CxUtils.h>


xNAMESPACE_BEGIN(std)

//-------------------------------------------------------------------------------------------------
/**
 * clock
 *
 * get std::clock_t (http://bugs.vcmi.eu/view.php?id=719)
 */

inline std::clock_t
clock() /* xWARN_UNUSED_RV */
{
    rusage ruUsage; xSTRUCT_ZERO(ruUsage);

    int_t iRv = ::getrusage(RUSAGE_SELF, &ruUsage);
    if (iRv == - 1) {
        return - 1;
    }

    std::clock_t clkRv =
        static_cast<std::clock_t>( ruUsage.ru_utime.tv_sec  + ruUsage.ru_stime.tv_sec ) * 1000000 +
        ruUsage.ru_utime.tv_usec + ruUsage.ru_stime.tv_usec;

    return clkRv;
}

#define xSTD_CLOCK  ::clock
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(std)

