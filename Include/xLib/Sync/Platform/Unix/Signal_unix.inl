/**
 * \file  Signal_unix.inl
 * \brief
 */


#include <xLib/Core/Const.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Signal::_decription_impl(
    cint_t &a_signalNum
)
{
    std::tstring_t sRv;

   /**
    * FAQ: ::psignal, ::sys_siglist
    */

    const char *pszRv = ::strsignal(a_signalNum);
    xTEST_NA(pszRv);
    if (pszRv == xPTR_NULL) {
        sRv = Const::strUnknown();
    } else {
        sRv = pszRv;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
